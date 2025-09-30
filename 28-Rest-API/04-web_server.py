from http.server import SimpleHTTPRequestHandler, HTTPServer
from datetime import datetime

class MiServidor(SimpleHTTPRequestHandler):
    def do_GET(self):
        try:
            if self.path == "/":
                self.send_response(200)
                self.send_header("Content-type", "text/html")
                self.end_headers()
                mensaje_html = "<html><body><h1>Hola Mundo</h1></body></html>"
                self.wfile.write(mensaje_html.encode("utf-8"))
            elif self.path == "/secreto":
                self.send_error(403, "Acceso prohibido")
            elif self.path == "/hora":
                self.send_response(200)
                self.send_header("Content-type", "text/html")
                self.end_headers()
                hora_actual = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                mensaje_html = f"<html><body><h3>{hora_actual}</h3></body></html>"
                self.wfile.write(mensaje_html.encode("utf-8"))
             
            elif self.path == "/causar_error":
                raise Exception("Error simulado")
            else:
                self.send_error(404, "Página no encontrada")
        except Exception as e:
            self.send_error(500, f"Error interno del servidor: {str(e)}")
    
    def do_POST(self):
        self.send_error(405, "Método POST no permitido")

def ejecutar_servidor():
    puerto = 8080
    servidor = HTTPServer(("localhost", puerto), MiServidor)
    print(f"Servidor corriendo en http://localhost:{puerto}")
    servidor.serve_forever()

if __name__ == "__main__":
    ejecutar_servidor()
