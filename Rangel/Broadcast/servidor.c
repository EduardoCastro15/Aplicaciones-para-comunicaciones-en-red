#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include <netinet/in.h>

void salir_error(const char *func) {
	perror(func);
	exit(EXIT_FAILURE);
}

int inicializar(struct sockaddr_in* server_addr, int puerto) {
	int sock_fd, status_conexion;
	server_addr -> sin_family = AF_INET;
	server_addr -> sin_port = htons(puerto);
	server_addr -> sin_addr.s_addr = INADDR_ANY;
	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	int band = 1;
	if(sock_fd < 0) salir_error("socket()");
	// Nos ayuda a configurar al servidor broadcast
	status_conexion = setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, &band, sizeof(int));
	if(status_conexion < 0) salir_error("setsockopt");

	status_conexion = bind(sock_fd, (struct sockaddr*)server_addr, sizeof(*server_addr));
	if(status_conexion < 0) salir_error("bind()");
	return sock_fd;
}

void recibir_solicitudes(int server_sock_fd) {
	char mensaje[] = "Mensaje recibido :)\n";
	char buffer[256];
	int n;
	int client_sock_fd;
	int puerto_cliente = 8888;
	struct sockaddr_in client_addr;
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(puerto_cliente);
	client_addr.sin_addr.s_addr = inet_addr("192.168.0.255");

	int len = sizeof(client_addr);
	while(1) {
		sendto(server_sock_fd, mensaje, strlen(mensaje), MSG_CONFIRM, (struct sockaddr*)&client_addr, len);
		printf("Mensaje enviado: %s\n", mensaje);
		sleep(1);
	}
}

void _main(int puerto) {
	struct sockaddr_in server_addr;
	int sock_fd = inicializar(&server_addr, puerto);
	recibir_solicitudes(sock_fd);
	close(sock_fd);
}

int main(int argc, char **argv) {
	char server_message[256];
	int server_socket, client_socket;
	int port;
	int aux;
	
	argc--; argv++;
	if(argc != 1){
		printf("El programa recibe como parametro el puerto <port>\n");
		exit(EXIT_FAILURE);
	}
	_main(atoi(argv[0]));
	return 0;
}




