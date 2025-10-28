#!/usr/bin/env bash
# matar-8000-8100.sh
# Procura processos que escutam nas portas 8000..8100 (TCP e UDP) e mata-os.
# Uso:
#   sudo ./matar-8000-8100.sh         # dry-run (não mata)
#   sudo ./matar-8000-8100.sh --apply # mata realmente (SIGTERM -> espera -> SIGKILL se necessário)
#
# Opcional:
#   Exporta WHITELIST_PORTS como "8001,8002" para proteger certas portas dentro do intervalo.

set -euo pipefail

RANGE_MIN=8000
RANGE_MAX=8100
DRY_RUN=1
TIMEOUT_TERM=5  # segundos a esperar após SIGTERM antes de SIGKILL

if [[ "${1:-}" == "--apply" ]]; then
  DRY_RUN=0
fi

# Ler whitelist opcional (ex.: export WHITELIST_PORTS="8001,8080")
IFS=',' read -r -a WHITELIST <<< "${WHITELIST_PORTS:-}"

in_whitelist_port() {
  local p=$1
  for w in "${WHITELIST[@]}"; do
    [[ -z "$w" ]] && continue
    if [[ "$w" == "$p" ]]; then
      return 0
    fi
  done
  return 1
}

if [[ $EUID -ne 0 ]]; then
  echo "Este script deve ser executado como root (sudo)." >&2
  exit 2
fi

run_or_show() {
  if [[ $DRY_RUN -eq 1 ]]; then
    echo "[DRY-RUN] $*"
  else
    echo "[EXEC] $*"
    eval "$@"
  fi
}

echo "Procurando processos que escutam nas portas ${RANGE_MIN}-${RANGE_MAX} (TCP e UDP)..."
if [[ ${#WHITELIST[@]} -gt 0 ]]; then
  echo "Whitelist de portas ativa: ${WHITELIST[*]}"
fi
echo "Modo: $( [[ $DRY_RUN -eq 1 ]] && echo "DRY-RUN (não vou matar nada)" || echo "APPLY (vou tentar matar)")"
echo

# Função que coleta PIDs para portas no intervalo, usando ss
collect_pids() {
  local -n _out=$1
  _out=()

  # Captura TCP e UDP listeners
  for proto in tcp udp; do
    # ss lista endpoints com a coluna 5 sendo endereço:porta; precisamos do pid=NNN via users:(("prog",pid=NNN,...))
    while IFS= read -r line; do
      # extrair port (último campo antes de espaço)
      # Exemplo de campo: 0.0.0.0:8000 ou [::]:8000
      addrport=$(awk '{print $5}' <<< "$line")
      # isolar última parte após :
      port="${addrport##*:}"
      # se falhar, pular
      if ! [[ "$port" =~ ^[0-9]+$ ]]; then
        continue
      fi
      # checar intervalo
      if (( port < RANGE_MIN || port > RANGE_MAX )); then
        continue
      fi
      # verificar whitelist
      if in_whitelist_port "$port"; then
        echo "Porta $port está na whitelist — ignorando."
        continue
      fi
      # extrair pid (pid=1234)
      if [[ "$line" =~ pid=([0-9]+) ]]; then
        pid="${BASH_REMATCH[1]}"
        # ignorar PID vazio
        if [[ -n "$pid" ]]; then
          _out+=("$pid:$port:$proto")
        fi
      else
        # sem PID (socket do kernel, systemd sem pid, etc) — registamos com pid=-
        _out+=("-:$port:$proto")
      fi
    done < <(ss -lpan "sport >= :$RANGE_MIN" 2>/dev/null | grep -E "LISTEN|udp")
  done

  # tornar único por PID (mantendo primeiro port/proto encontrado)
  # usaremos associative array para isto
  declare -A seen
  local uniq=()
  for entry in "${_out[@]}"; do
    IFS=':' read -r pid port proto <<< "$entry"
    key="$pid"
    if [[ -z "${seen[$key]:-}" ]]; then
      seen[$key]=1
      uniq+=("$entry")
    fi
  done
  _out=("${uniq[@]}")
}

declare -a TARGETS
collect_pids TARGETS

if [[ ${#TARGETS[@]} -eq 0 ]]; then
  echo "Nenhum processo em escuta nas portas ${RANGE_MIN}-${RANGE_MAX} encontrado."
  exit 0
fi

echo "Processos/entradas a considerar:"
for e in "${TARGETS[@]}"; do
  IFS=':' read -r pid port proto <<< "$e"
  if [[ "$pid" == "-" ]]; then
    echo "  porta $port/$proto -> sem PID identificável (socket sem PID). Não será morto."
    continue
  fi
  # Mostrar info do processo
  if ps -p "$pid" > /dev/null 2>&1; then
    echo "  PID $pid , porta $port/$proto"
    ps -fp "$pid" || true
  else
    echo "  PID $pid (já não existe) , porta $port/$proto"
  fi
  echo "----"
done

echo
if [[ $DRY_RUN -eq 1 ]]; then
  echo "Dry-run completo. Se quiseres que eu mate os processos execute:"
  echo "  sudo $0 --apply"
  exit 0
fi

# Agora executar kills: SIGTERM -> aguardar -> SIGKILL se necessário
for e in "${TARGETS[@]}"; do
  IFS=':' read -r pid port proto <<< "$e"
  if [[ "$pid" == "-" ]]; then
    echo "Porta $port/$proto sem PID — não é possível matar. Pular."
    continue
  fi

  if ! ps -p "$pid" > /dev/null 2>&1; then
    echo "PID $pid já não existe — pular."
    continue
  fi

  echo "Tentando terminar PID $pid (porta $port/$proto) com SIGTERM..."
  if kill "$pid" 2>/dev/null; then
    # esperar até TIMEOUT_TERM segundos por término
    for ((i=0;i<TIMEOUT_TERM;i++)); do
      if ! kill -0 "$pid" 2>/dev/null; then
        echo "PID $pid terminou com SIGTERM."
        break
      fi
      sleep 1
    done

    # se ainda existe, forçar
    if kill -0 "$pid" 2>/dev/null; then
      echo "PID $pid ainda activo após ${TIMEOUT_TERM}s — a enviar SIGKILL..."
      if kill -9 "$pid" 2>/dev/null; then
        echo "SIGKILL enviado a PID $pid."
        # pequena espera
        sleep 1
        if kill -0 "$pid" 2>/dev/null; then
          echo "ERRO: PID $pid não foi morto mesmo com SIGKILL."
        else
          echo "PID $pid morto."
        fi
      else
        echo "Falha ao enviar SIGKILL a PID $pid (permissões ou PID já alterado)."
      fi
    fi
  else
    echo "Falha ao enviar SIGTERM a PID $pid (já pode ter terminado ou sem permissões). Tentando SIGKILL..."
    if kill -9 "$pid" 2>/dev/null; then
      echo "SIGKILL enviado a PID $pid."
    else
      echo "Falha ao enviar SIGKILL a PID $pid."
    fi
  fi

  echo "----"
done

echo "Operação concluída."
exit 0

