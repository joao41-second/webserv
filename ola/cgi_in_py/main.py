#!/usr/bin/env python3


import os
import cgi
import cgitb
import html
from re import S
import sys

# Mostrar erros no navegador (útil em desenvolvimento)
cgitb.enable()

def cabecalho_http():
    # Imprime o cabeçalho HTTP e uma linha em branco
    print("Content-Type: text/html; charset=UTF-8")
    print("Cache-Control: no-store, no-cache, must-revalidate")
    print("Pragma: no-cache")
    print()

def pagina_principal_body():
    return """\
<html>
  <head>
    <meta charset="utf-8">
    <title>Pagina com Botoes</title>
  </head>
  <body>
    <h1>Escolha uma das opcoes:</h1>
    <form method="get" action="/pagina_principal.py">
      <input type="submit" name="pagina" value="Pagina 1">
      <input type="submit" name="pagina" value="Pagina 2">
      <input type="submit" name="pagina" value="Pagina 3">
      <input type="submit" name="pagina" value="Pagina 4">
      <input type="submit" name="pagina" value="Pagina 5">
    </form>
    <p>nao estou a atualizar</p>
  </body>
</html>
"""

def pagina_dinamica(pagina):
    paginas = {
        "Pagina 1": "Voce esta na Pagina 1",
        "Pagina 2": "Voce esta na Pagina 2",
        "Pagina 3": "Voce esta na Pagina 3",
        "Pagina 4": "Voce esta na Pagina 4",
        "Pagina 5": "Voce esta na Pagina 5"
    }

    if pagina == "Pagina 4":
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
            "<h1>Variaveis de ambiente recebidas pelo CGI</h1>"
            f"<p>Total: {len(env_items)}</p>"
            "<table style='border-collapse:collapse'>"
            "<thead><tr><th style='padding:6px;border:1px solid #ccc'>Nome</th><th style='padding:6px;border:1px solid #ccc'>Valor</th></tr></thead>"
            "<tbody>"
            + "".join(rows) +
            "</tbody></table>"
            "<p><a href=\"/cgi-bin/pagina_principal.py\">Voltar para a pagina inicial</a></p>"
        )
        return tabela

    conteudo = paginas.get(pagina)
    if conteudo:
        return f"<h1>{html.escape(conteudo)}</h1><p>Conteudo da {html.escape(pagina.lower())}.</p>"
    else:
        return "<h1>Erro: Pagina nao encontrada!</h1>"

def erro_http(codigo, mensagem):
    print(f"Status: {codigo}")
    cabecalho_http()
    print(f"<html><body><h1>Erro {html.escape(codigo)}: {html.escape(mensagem)}</h1></body></html>")

def main():
    # Garante que variaveis basicas existam
    os.environ.setdefault("PATH_INFO", "/")
    os.environ.setdefault("QUERY_STRING", "")
    os.environ.setdefault("REQUEST_METHOD", "GET")
    os.environ.setdefault("SCRIPT_NAME", sys.argv[0])

    # Obter parametros com seguranca
    try:
        form = cgi.FieldStorage()
    except Exception as e:
        erro_http("400 Bad Request", f"Erro ao processar dados do formulario: {e}")
        sys.exit(0)

    pagina = None
    if form is not None:
        try:
            pagina = form.getvalue("pagina")
        except TypeError:
            pagina = None

    cabecalho_http()

    if pagina:

        print(pagina_principal_body())
        print("<html><head><meta charset='utf-8'>")
        print(f"<title>{html.escape(pagina)}</title></head><body>")
        print(pagina_dinamica(pagina))
        print("</body></html>")
    else:
        print(pagina_principal_body())
        print(pagina)
        

if __name__ == "__main__":
    main()

