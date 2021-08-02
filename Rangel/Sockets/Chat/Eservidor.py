import socket
import time
HOST = "192.168.1.105"
PORT = 8080
buffer_size = 100

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as TCPServerSocket:
    TCPServerSocket.bind((HOST, PORT))
    TCPServerSocket.listen()
    print("Esperando mensaje...")
    while True:
        Client_conn, Client_addr = TCPServerSocket.accept()
        with Client_conn:
            print("Conectado a: ", Client_addr)
            while True:
                print("Esperando mensaje... ")
                data = Client_conn.recv(buffer_size)
                print("El cliente dice: ", data)
                data = input("@- ")
                if data == bytes("fin", 'utf-8'):
                    break
                Client_conn.sendall(data)
                
