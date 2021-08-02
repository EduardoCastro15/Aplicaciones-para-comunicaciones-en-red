import socket
import time
import datetime
class FileServer():
  def ServerProcess(self):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as TCPServerSocket:
        TCPServerSocket.bind((self.HOST, self.PORT))
        TCPServerSocket.listen()
        print("El servidor TCP está disponible y en espera de solicitudes")
        while True:
            Client_conn, Client_addr = TCPServerSocket.accept()
            with Client_conn:
                while True:
                  print("Cliente", Client_addr)
                  data = Client_conn.recv(self.buffer_size)
                  file_data = data.decode('utf-8').split('/')
                  file_name = file_data[0]
                  if file_name == "fin" and len(file_data) == 1:
                    break
                  file_size = int(file_data[1])
                  recived = 0
                  print("Salvando " + file_name)
                  file_to_save = open(f"{datetime.datetime.today().strftime('%d-%m-%y-%I-%M-%S-%p')}_{file_name}","wb")
                  Client_conn.sendall(bytes("Listo", 'utf-8'))
                  while recived < file_size:
                    data = Client_conn.recv(self.buffer_size)
                    file_to_save.write(data)
                    recived += self.buffer_size
                    print(f"{recived} de {file_size}")
                  file_to_save.close()
                  print("Se guardo exitosamente el archivo, listo para recibir  nuevo\n")
                  Client_conn.sendall(bytes('exito al guardar','utf-8'))
  def __init__(self):
    self.HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
    self.PORT = 65432  # Port to listen on (non-privileged ports are > 1023)
    self.buffer_size = 1024
    self.ServerProcess()
FileServer()
