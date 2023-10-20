import socket

# Configuración del cliente
host = '127.0.0.1'  # Dirección IP del servidor (localhost en este caso)
port = 12345       # Puerto al que se conectará el cliente

# Crear un socket TCP
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Conectar al servidor
client_socket.connect((host, port))

# Enviar datos al servidor
mensaje = "Hola, servidor TCP"
client_socket.send(mensaje.encode('utf-8'))

print(f"Conexión saliente, mensaje: {mensaje}")

# Cerrar la conexión con el servidor
client_socket.close()
