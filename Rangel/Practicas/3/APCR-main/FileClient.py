import socket, os, time

class FileClient():
  def send_folder(self, TCPClientSocket, file_path, file_name):
    print(f"Enviando archivo {file_name}...")
    TCPClientSocket.sendall(bytes(f'{file_name}/{os.path.getsize(file_path)}','utf-8'))
    confirmacion = TCPClientSocket.recv(self.buffer_size)
    print(f"el servidor confirmo que esta listo: {confirmacion.decode('utf-8')}")
    file_to_send = open(file_path, "rb")
    print("El Servidor recibirá el archivo")
    while True:
      part_of_file = file_to_send.read(self.buffer_size)
      if not part_of_file:
        break
      TCPClientSocket.sendall(part_of_file)
    file_to_send.close()
    print("Esperando confirmación del servidor")
    confirmacion = TCPClientSocket.recv(self.buffer_size)
    print(f'El servidor dice: {confirmacion.decode("utf-8")}')
    print("terminando")

  def ClientProcess(self):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as TCPClientSocket:
      TCPClientSocket.connect((self.HOST, self.PORT))
      self.ProcessFolder(TCPClientSocket)
      TCPClientSocket.sendall(bytes('fin', 'utf-8'))
  def ProcessFolder(self,TCPClientSocket):
    #path = input("Introduce la ruta de archivos a enviar")
    path = "C:/Users/georg/Desktop/ESCOM/7mo. Semestre/Redes2/Semaforo"
    for f in os.listdir(path):
        self.send_folder(TCPClientSocket,os.path.join(path, f), f)
  def __init__(self):
    self.HOST = "127.0.0.1"  # The server's hostname or IP address
    self.PORT = 65432  # The port used by the server
    self.buffer_size = 1024
    self.ClientProcess()
FileClient()
