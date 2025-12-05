#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import os
import html
import cgitb

cgitb.enable()

UPLOAD_DIR = "/tmp/site"
os.makedirs(UPLOAD_DIR, exist_ok=True)

def print_header():
    print("Content-Type: text/html; charset=utf-8")
    print()

def html_page(content):
    return f"""
<html><head><title>Upload em Chunks</title></head>
<body>{content}</body></html>
"""

def handle_get():
    # Formulário + JS para enviar chunks
    form_html = f"""
<h1>Enviar arquivo em chunks</h1>
<input type="file" id="fileInput"><br><br>
<button id="sendChunks">Enviar</button>

<script>
document.getElementById("sendChunks").onclick = async () => {{
    const file = document.getElementById("fileInput").files[0];
    if (!file) {{
        alert("Selecione um arquivo primeiro!");
        return;
    }}

    const chunkSize = 1024 * 50; // 50KB por chunk
    let offset = 0;
    const filename = encodeURIComponent(file.name);

    while (offset < file.size) {{
        const chunk = file.slice(offset, offset + chunkSize);
        await fetch("", {{
            method: "POST",
            headers: {{
                "X-File-Name": filename,
                "X-Chunk-Offset": offset
            }},
            body: chunk
        }});
        offset += chunkSize;
    }}

    alert("Upload concluído!");
}};
</script>
"""
    print(html_page(form_html))

def handle_post():
    # Lê dados do stdin (chunk enviado)
    try:
        chunk = sys.stdin.buffer.read()
        filename = os.environ.get("HTTP_X_FILE_NAME", "unnamed")
        offset = int(os.environ.get("HTTP_X_CHUNK_OFFSET", "0"))

        safe_filename = os.path.basename(filename)
        filepath = os.path.join(UPLOAD_DIR, safe_filename)

        # Abre arquivo em modo append binário
        with open(filepath, "r+b") as f:
            f.seek(offset)
            f.write(chunk)
    except FileNotFoundError:
        # Arquivo não existe ainda, criar novo
        with open(filepath, "wb") as f:
            f.write(chunk)
    except Exception as e:
        print(html_page(f"<h1>Erro:</h1><pre>{html.escape(str(e))}</pre>"))
        return

    print(html_page(f"<p>Chunk recebido: {html.escape(filename)}, offset {offset}, tamanho {len(chunk)} bytes</p>"))

def main():
    sys.stdout.reconfigure(encoding="utf-8")
    print_header()
    method = os.environ.get("REQUEST_METHOD", "GET")
    if method == "POST":
        handle_post()
    else:
        handle_get()

if __name__ == "__main__":
    main()

