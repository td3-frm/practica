#programa SOCKET SERVIDOR Stream 
import socket

# Crear un socket de servidor
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # SOCK_DGRAM

# Vincular el servidor a una dirección y puerto
server_socket.bind(('localhost', 12346))

# Habilitar al servidor para aceptar conexiones
server_socket.listen(5)
print("Servidor escuchando en puerto 12345...")

# Esperar una conexión
client_socket, client_address = server_socket.accept()
print(f"Conexión establecida con {client_address}")

# Recibir datos del cliente
data = client_socket.recv(1024).decode()
print(f"Mensaje recibido del cliente: {data}")

# Enviar una respuesta al cliente
response = "Hola, cliente! Recibí tu mensaje."
client_socket.send(response.encode())

# Cerrar la conexión
client_socket.close()
server_socket.close()
