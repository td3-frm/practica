##programa SOCKET CLIENTE stream: el cliente envia al socket lo que recibe por teclado y muestra en pantalla
import socket
import sys

def main():
	if len(sys.argv) != 2:
		PORT = 2000
	else:
		PORT = int(sys.argv[1])

	SERVER_IP = "127.0.0.1"

	# 1 - Crear socket TCP
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	print("Paso 1: Se creo socket cliente")

	# 2 - Conectarse al servidor
	try:
		sock.connect((SERVER_IP, PORT))
	except Exception as e:
		print("ERROR en funcion connect()", e)
		sys.exit(1)

	print("Paso 2: Connect(), cliente conectado con IP " + SERVER_IP + " Puerto " + str(PORT))

	try:
		while True:
			# leer datos desde socket
			data = sock.recv(256)
			if data:
				print("Servidor:--> " + data.decode(errors="ignore"), end="")

			# leer desde teclado
			entrada = sys.stdin.readline()
			if entrada:
				sock.sendall(entrada.encode())
	except KeyboardInterrupt:
		print("\nCliente interrumpido.")
	finally:
		sock.close()

if __name__ == "__main__":
	main()
