#programa SOCKET CLIENTE stream
import socket

# Crear un socket de cliente
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Conectar el cliente al servidor
client_socket.connect(('localhost', 12346))

# Enviar un mensaje al servidor
message = "Hola, servidor!"
client_socket.send(message.encode())

# Recibir respuesta del servidor
response = client_socket.recv(1024).decode()
print(f"Respuesta del servidor: {response}")

# Cerrar la conexión
client_socket.close()
