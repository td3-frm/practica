#programa SOCKET CLIENTE datagramas: el cliente envia al socket lo que recibe por teclado y muestra en pantalla
import socket
import sys

def main():
    SERVER_IP = "127.0.0.1"
    PORT = 4000

    # Crear socket UDP
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    #print(f"Cliente enviará datos a {SERVER_IP}:{PORT}")
    print("Cliente enviara datos a " + SERVER_IP + ":" + str(PORT))

    while True:
        try:
            msg = input("> ")  # leer desde teclado
            if not msg:
                continue

            # enviar al servidor
            sock.sendto(msg.encode(), (SERVER_IP, PORT))

            # esperar respuesta
            data, _ = sock.recvfrom(256)
            print("Servidor:--> " + data.decode(errors='ignore'), end="")

        except KeyboardInterrupt:
            print("\nCerrando cliente...")
            break

    sock.close()

if __name__ == "__main__":
    main()