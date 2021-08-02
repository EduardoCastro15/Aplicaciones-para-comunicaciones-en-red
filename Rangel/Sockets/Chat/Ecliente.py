import socket

HOST = "192.168.1.105"
PORT = 8080
buffer_size = 100

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as TCPClientSocket:
    TCPClientSocket.connect((HOST, PORT))
    print("Enviando mensaje...")
    while True:
        mensaje=input("@- \n")
        if mensaje=="fin":
            break
        TCPClientSocket.sendall(bytes(mensaje,'utf-8'))
        data = TCPClientSocket.recv(buffer_size)
        print("El servidor dice: ", repr(data))
        