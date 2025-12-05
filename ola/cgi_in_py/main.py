#!/usr/bin/env python3


# -*- coding: utf-8 -*-

import sys
import cgi
import cgitb
import html
import os

# Ativa debug (útil no desenvolvimento)
cgitb.enable()

def print_header():
    print("Content-Type: text/html; charset=utf-8")
    print()  # linha vazia obrigatória

def html_page(content):
    return f"""<!doctype html>
<html lang="pt">
<head>
<meta charset="utf-8">
<title>CGI Python</title>
<style>
body {{
    font-family: Arial, sans-serif;
    max-width: 700px;
    margin: 2rem auto;
    padding: 1rem;
}}
textarea {{
    width: 100%;
    height: 200px;
}}
.box {{
    white-space: pre-wrap;
    border: 1px solid #ccc;
    background: #f7f7f7;
    padding: 1rem;
}}
button {{
    margin-top: 1rem;
}}
</style>
</head>
<body>
{content}

<hr>

<h2>Enviar dados em chunks (fetch + ReadableStream)</h2>
<button id="sendChunks">Enviar chunks</button>

<script>
document.getElementById("sendChunks").onclick = () => {{

    const encoder = new TextEncoder();

    const stream = new ReadableStream({{
        start(controller) {{

            controller.enqueue(encoder.encode("Primeiro chunk\\n"));

            setTimeout(() => {{
                controller.enqueue(encoder.encode("Segundo chunk\\n"));
            }}, 1000);

            setTimeout(() => {{
                controller.enqueue(encoder.encode("Terceiro chunk\\n"));
                controller.close();
            }}, 2000);

        }}
    }});

    fetch("", {{
        method : "POST",
        body   : stream
    }}).then(r => console.log("Chunks enviados:", r.status));
}};
</script>

</body>
</html>
"""

def handle_get():
    form_html = """
<h1>Enviar texto para o servidor</h1>
<form method="post" action="">
    <textarea name="texto"></textarea><br><br>
    <button type="submit">Enviar</button>
</form>
"""
    print(html_page(form_html))

def handle_post():
    # Lê POST normalmente (mesmo vindo em chunked)
    form = cgi.FieldStorage()
    texto = form.getfirst("texto", "")

    if not texto:  # Caso tenha sido enviado via chunks
        try:
            raw = sys.stdin.read()
            texto_safe = html.escape(raw)
        except:
            texto_safe = "(erro ao ler stdin)"
    else:
        texto_safe = html.escape(texto)

    result_html = f"""
<h1>Texto recebido</h1>
<div class="box">{texto_safe}</div>
<br>
<a href="">Voltar</a>
"""
    print(html_page(result_html))

def main():
    sys.stdout.reconfigure(encoding="utf-8")
    print_header()

    if os.environ.get("REQUEST_METHOD", "GET") == "POST":
        handle_post()
    else:
        handle_get()

if __name__ == "__main__":
    main()

