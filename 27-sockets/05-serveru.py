#programa SOCKET SERVIDOR datagramas (UDP) el servidor envia al socket lo que recibe del socket y lo muestra en pantalla
import socket

def main():
    HOST = "0.0.0.0"   # Escucha en todas las interfaces
    PORT = 4000        # Puerto por defecto

    # Crear socket UDP
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((HOST, PORT))
    print("Servidor UDP escuchando en " + HOST + ":" + str(PORT))
    
    while True:
        data, addr = sock.recvfrom(256)  # recibe datos del cliente
        mensaje = data.decode(errors='ignore')
        print("Cliente:--> " + mensaje)
        
        # responder al cliente
        sock.sendto(data, addr)

if __name__ == "__main__":
    main()