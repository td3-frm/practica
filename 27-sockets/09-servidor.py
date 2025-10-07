#programa SOCKET SERVIDOR Stream el servidor envia al socket lo que recibe del socket y lo muestra en pantalla
import socket

def main():
	HOST = "0.0.0.0"   # Escucha en todas las interfaces
	PORT = 2000        # Puerto por defecto

	# 1 - Crear el socket TCP
	server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	print("Paso 1: Servidor creo socket en puerto: "+ str(PORT))
	#print("IP: " + HOST + " Puerto: " + str(PORT))
	
	# 2 - Asociar socket a dirección y puerto
	server_socket.bind((HOST, PORT))
	print("Paso 2: Asociar bind()")
        
	# 3 - Escuchar conexiones (máx 1 pendiente)
	server_socket.listen(1)
	print("Paso 3: Permitir conexiones listen()")

	while True:
		# 4 - Bloquear hasta que entre una conexión
		print("Paso 4: Bloqueo hasta que entre conexion accept()")
		conn, addr = server_socket.accept()
		#print(f"Desbloqueo de accept, entro conexion desde {addr}")
		print("Desbloqueo de accept, entro conexion -> Conn: " + str(conn))
		

		# enviar mensaje de bienvenida
		conn.sendall(b"Bienvenido al servidor\n")

		# loop de comunicación
		while True:
			data = conn.recv(256)
			if not data:
				break
			# eco de lo recibido
			conn.sendall(data)
			print("Cliente:--> " + data.decode(errors="ignore"), end="")

		conn.close()
		print("Conexion cerrada")

if __name__ == "__main__":
	main()
