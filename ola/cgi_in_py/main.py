#!/usr/bin/env python3


import os
import cgi
import cgitb
import html
import sys

cgitb.enable()  # Mostra erros CGI no navegador (útil em desenvolvimento)

def cabecalho_http():
    # Imprime o cabeçalho HTTP e uma linha em branco
    print("Content-Type: text/html; charset=UTF-8")
    print()

def pagina_principal_body():
    return """\
<html>
  <head>
    <meta charset="utf-8">
    <title>Página com Botões</title>
  </head>
  <body>
    <h1>Escolha uma das opções:</h1>
    <form method="get">
      <input type="submit" name="pagina" value="Página 1">
      <input type="submit" name="pagina" value="Página 2">
      <input type="submit" name="pagina" value="Página 3">
      <input type="submit" name="pagina" value="Página 4">
      <input type="submit" name="pagina" value="Página 5">
    </form>
  </body>
</html>
"""

def pagina_dinamica(pagina):
    paginas = {
        "Página 1": "Você está na Página 1",
        "Página 2": "Você está na Página 2",
        "Página 3": "Você está na Página 3",
        "Página 4": "Você está na Página 4",
        "Página 5": "Você está na Página 5"
    }

    if pagina == "Página 4":
        env_items = sorted(os.environ.items())
        rows = []
        for k, v in env_items:
            rows.append(
                "<tr>"
                f"<td style='vertical-align:top;padding:4px;border:1px solid #ccc'><strong>{html.escape(k)}</strong></td>"
                f"<td style='vertical-align:top;padding:4px;border:1px solid #ccc'>{html.escape(v)}</td>"
                "</tr>"
            )
        tabela = (
            "<h1>Variáveis de Ambiente (envs) recebidas pelo CGI</h1>"
            f"<p>Total: {len(env_items)}</p>"
            "<table style='border-collapse:collapse'>"
            "<thead><tr><th style='padding:6px;border:1px solid #ccc'>Nome</th><th style='padding:6px;border:1px solid #ccc'>Valor</th></tr></thead>"
            "<tbody>"
            + "".join(rows) +
            "</tbody></table>"
            "<p><a href=\"/cgi-bin/pagina_principal.py\">Voltar para a página inicial</a></p>"
        )
        return tabela

    conteudo = paginas.get(pagina)
    if conteudo:
        return f"<h1>{html.escape(conteudo)}</h1><p>Conteúdo da {html.escape(pagina.lower())}.</p>"
    else:
        return "<h1>Erro: Página não encontrada!</h1>"

def erro_http(codigo, mensagem):
    # Envia status e página de erro
    print(f"Status: {codigo}")
    cabecalho_http()
    print(f"<html><body><h1>Erro {html.escape(codigo)}: {html.escape(mensagem)}</h1></body></html>")

def main():
    # --- CORREÇÃO IMPORTANTE ---
    # Garante que PATH_INFO exista para evitar erro "PATH_INFO not found"
    if "PATH_INFO" not in os.environ:
        os.environ["PATH_INFO"] = "/"

    # Também garante variáveis básicas, caso servidor não envie
    os.environ.setdefault("QUERY_STRING", "")
    os.environ.setdefault("REQUEST_METHOD", "GET")
    os.environ.setdefault("SCRIPT_NAME", sys.argv[0])

    # Obter parâmetros com segurança
    try:
        form = cgi.FieldStorage()
    except Exception as e:
        erro_http("400 Bad Request", f"Erro ao processar dados do formulário: {e}")
        sys.exit(1)

    pagina = None
    if form is not None:
        try:
            pagina = form.getvalue("pagina")
        except TypeError:
            pagina = None

    # Emitir cabeçalho e conteúdo
    cabecalho_http()
    if pagina:
        print("<html><head><meta charset='utf-8'>")
        print(f"<title>{html.escape(pagina)}</title></head><body>")
        print(pagina_dinamica(pagina))
        print("</body></html>")
    else:
        print(pagina_principal_body())

if __name__ == "__main__":
    main()
