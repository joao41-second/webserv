#!/usr/bin/python3

import cgi
import cgitb
cgitb.enable()  # Mostra erros CGI no navegador

# Cabeçalho HTTP comum
def cabecalho_http():
    print("Content-Type: text/html;charset=UTF-8\n")

# Função que gera a página inicial com botões
def pagina_principal():
    cabecalho_http()
    print("""
    <html>
        <head>
            <title>Página com Botões</title>
            <!-- Favicon inline para evitar requisição automática -->
            <link rel="icon" href="data:;base64,iVBORw0KGgo=">
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
        return f"<h1>{conteudo}</h1><p>Conteúdo da {pagina.lower()}.</p>"
    else:
        return "<h1>Erro: Página não encontrada!</h1>"

# Função para enviar uma resposta de erro HTTP
def erro_http(codigo, mensagem):
    print(f"Status: {codigo}")
    cabecalho_http()
    print(f"<html><body><h1>Erro {codigo}: {mensagem}</h1></body></html>")

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
        <head><title>{pagina}</title></head>
        <body>
            {pagina_dinamica(pagina)}
            <br>
            <a href="/cgi-bin/pagina_principal.py">Voltar para a página inicial</a>
        </body>
    </html>
    """)
else:
    # Nenhum parâmetro recebido -> mostrar página inicial
    pagina_principal()

