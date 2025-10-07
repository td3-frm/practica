import socket
import threading

# Función para manejar la conexión de un cliente
def handle_client(client_socket):
    while True:
        # Recibir datos del cliente
        data = client_socket.recv(1024)
        if not data:
            break  # Si no se reciben datos, el cliente ha cerrado la conexión

        # Procesar los datos recibidos (en este caso, solo los imprimimos)
        print(f"Datos recibidos del cliente: {data.decode('utf-8')}")

        # Responder al cliente (opcional)
        response = "Mensaje recibido por el servidor"
        client_socket.send(response.encode('utf-8'))

    # Cerrar la conexión con el cliente
    client_socket.close()

# Configuración del servidor
host = '127.0.0.1'  # Dirección IP del servidor (localhost en este caso)
port = 12345       # Puerto en el que escuchará el servidor

# Crear un socket TCP
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Enlazar el socket al host y puerto especificados
server_socket.bind((host, port))

# Escuchar conexiones entrantes (máximo 5 en este ejemplo)
server_socket.listen(5)

print(f"Servidor TCP escuchando en {host}:{port}")

while True:
    # Esperar a que un cliente se conecte
    client_socket, client_address = server_socket.accept()
    print(f"Conexión entrante desde {client_address}")

    # Iniciar un nuevo hilo para manejar al cliente
    client_handler = threading.Thread(target=handle_client, args=(client_socket,))
    client_handler.start()
