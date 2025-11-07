#!/usr/bin/env python3

import os
import cgi
import cgitb
import html

cgitb.enable()  # Mostra erros CGI no navegador

# Cabeçalho HTTP comum
def cabecalho_http():
    print("Content-Type: text/html;charset=UTF-8\n")

# Gera tabela HTML com variáveis de ambiente ou mensagem de erro se não houver
def construir_tabela_envs():
    env_items = sorted(os.environ.items())
    if not env_items:
        return (
            "<h2 style='color:#b00020'>Erro: Nenhuma variável de ambiente encontrada!</h2>"
            "<p>O processo CGI não recebeu variáveis de ambiente. Verifique a configuração do servidor ou como o script foi invocado.</p>"
        )

    rows = []
    for k, v in env_items:
        rows.append(
            "<tr>"
            f"<td style='vertical-align:top;padding:4px;border:1px solid #ccc'><strong>{html.escape(k)}</strong></td>"
            f"<td style='vertical-align:top;padding:4px;border:1px solid #ccc'>{html.escape(v)}</td>"
            "</tr>"
        )

    tabela = (
        "<h2>Variáveis de Ambiente (envs) recebidas pelo CGI</h2>"
        f"<p>Total: {len(env_items)}</p>"
        "<table style='border-collapse:collapse'>"
        "<thead><tr><th style='padding:6px;border:1px solid #ccc'>Nome</th><th style='padding:6px;border:1px solid #ccc'>Valor</th></tr></thead>"
        "<tbody>"
        + "".join(rows) +
        "</tbody></table>"
    )
    return tabela

# Função que gera a página inicial com botões e agora a tabela de envs
def pagina_principal():
    cabecalho_http()
    tabela_envs_html = construir_tabela_envs()
    print(f"""
    <html>
        <head>
            <title>Página com Botões</title>
            <meta charset="utf-8" />
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
            <hr>
            {tabela_envs_html}
        </body>
    </html>
    """)

# Função que gera conteúdo dinâmico baseado no botão pressionado
def pagina_dinamica(pagina):
    paginas = {
        "Página 1": "Você está na Página 1",
        "Página 2": "Você está na Página 2",
        "Página 3": "Você está na Página 3",
        "Página 4": "Você está na Página 4",
        "Página 5": "Você está na Página 5"
    }

    conteudo = paginas.get(pagina)
    if conteudo:
        return (
            f"<h1>{html.escape(conteudo)}</h1>"
            f"<p>Conteúdo da {html.escape(pagina.lower())}.</p>"
            '<p><a href="/cgi-bin/pagina_principal.py">Voltar para a página inicial</a></p>'
        )
    else:
        return "<h1>Erro: Página não encontrada!</h1>"

# Função para enviar uma resposta de erro HTTP
def erro_http(codigo, mensagem):
    print(f"Status: {codigo}")
    cabecalho_http()
    print(f"<html><body><h1>Erro {html.escape(codigo)}: {html.escape(mensagem)}</h1></body></html>")

# Obter parâmetros de forma segura
try:
    form = cgi.FieldStorage()
except Exception:
    erro_http("400 Bad Request", "Não foi possível processar os dados do formulário")
    exit(1)

pagina = None
if form is not None:
    try:
        pagina = form.getvalue("pagina")
    except TypeError:
        pagina = None

# Lógica de exibição
if pagina:
    cabecalho_http()
    print(f"""
    <html>
        <head><title>{html.escape(pagina)}</title><meta charset="utf-8" /></head>
        <body>
            {pagina_dinamica(pagina)}
        </body>
    </html>
    """)
else:
    # Mostrar página inicial (agora com a tabela de envs)
    pagina_principal()
