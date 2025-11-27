#!/usr/bin/env python3
# filepath: test_incomplete_chunks.py

import socket
import time

def test_incomplete_chunks():
    # Connect to your server
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('localhost', 8022))
    
    print("Connected to server")
    
    # Send HTTP request headers with Content-Length
    request = (
        "POST /test HTTP/1.1\r\n"
        "Host: localhost:8022\r\n"
        "Content-Length: 1000\r\n"  # Promise 1000 bytes
        "Content-Type: text/plain\r\n"
        "\r\n"
    )
    
    sock.send(request.encode())
    print("Sent headers (promised 1000 bytes)")
    
    # Send only partial body
    partial_body = "This is only 30 bytes long!!"
    sock.send(partial_body.encode())
    print(f"Sent only {len(partial_body)} bytes")
    
    print("Now waiting... Server expects 1000 bytes but won't get them.")
    print("Connection should timeout after 60 seconds...")
    
    # Keep connection open but don't send the rest
    # Wait to see if server closes connection
    try:
        sock.settimeout(70)  # Wait up to 70 seconds
        response = sock.recv(4096)
        if response:
            print(f"Received response: {response.decode()}")
        else:
            print("Connection closed by server (timeout)")
    except socket.timeout:
        print("Socket timeout - server didn't respond")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        sock.close()
        print("Connection closed")

if __name__ == "__main__":
    test_incomplete_chunks()