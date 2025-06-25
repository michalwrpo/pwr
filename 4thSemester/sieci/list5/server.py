from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse
from bs4 import BeautifulSoup
import json

HOST = '127.0.0.1'
PORT = 5689
words = ""

def remove_error_paragraphs():
    """Remove all <p> elements with class 'error' from words.html."""
    with open('words.html', 'r', encoding='utf-8') as f:
        soup = BeautifulSoup(f, 'html.parser')
    for p in soup.find_all('p', class_='error'):
        p.decompose()
    with open('words.html', 'w', encoding='utf-8') as f:
        f.write(str(soup))


class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/words':
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            with open('words.html', 'rb') as f:
                self.wfile.write(f.read())
        else:
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            with open('index.html', 'rb') as f:
                self.wfile.write(f.read())

    def do_POST(self):
        if self.path == '/words':
            remove_error_paragraphs()

            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            data = json.loads(post_data.decode())
            word = data.get('word', '')

            # Parse and modify words.html
            with open('words.html', 'r', encoding='utf-8') as f:
                soup = BeautifulSoup(f, 'html.parser')
            # Add new word as a <p> element
            if word:
                new_p = soup.new_tag('p')
                new_p.string = word
                soup.body.append(new_p)
            with open('words.html', 'w', encoding='utf-8') as f:
                f.write(str(soup))

            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            with open('words.html', 'rb') as f:
                self.wfile.write(f.read())
        else:
            self.send_response(403)
            self.end_headers()

    def do_DELETE(self):
        if self.path == '/words':
            remove_error_paragraphs()

            content_length = int(self.headers.get('Content-Length', 0))
            if content_length == 0:
                self.send_response(400)
                self.end_headers()
                return
            post_data = self.rfile.read(content_length)
            try:
                data = json.loads(post_data.decode())
                word = data.get('word', '')
            except Exception:
                self.send_response(400)
                self.end_headers()
                return

            # Parse and modify words.html
            with open('words.html', 'r', encoding='utf-8') as f:
                soup = BeautifulSoup(f, 'html.parser')
            removed = False
            if word:
                for p in soup.body.find_all('p'):
                    if p.string == word:
                        p.decompose()
                        removed = True
            
            if not removed:
                # Add error message as <p class="error">
                error_p = soup.new_tag('p', **{'class': 'error'})
                error_p.string = f"Error: Word '{word}' not found."
                soup.body.append(error_p)
            with open('words.html', 'w', encoding='utf-8') as f:
                f.write(str(soup))

            if removed:
                self.send_response(200)
            else:
                self.send_response(404)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            with open('words.html', 'rb') as f:
                self.wfile.write(f.read())
        else:
            self.send_response(403)
            self.end_headers()

def run():
    server_address = (HOST, PORT)
    httpd = HTTPServer(server_address, MyHandler)
    print(f"Server at: http://{HOST}:{PORT}/")
    httpd.serve_forever()

if __name__ == '__main__':
    run()
