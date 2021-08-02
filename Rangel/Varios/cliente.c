#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>

#include <netinet/in.h>

void salir_error(const char *func) {
	perror(func);
	exit(EXIT_FAILURE);
}

int inicializar(struct sockaddr_in* server_addr, int puerto, char *direccion_ip) {
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

	if(sock_fd < 0) salir_error("socket()");

	server_addr -> sin_family = AF_INET;
	server_addr -> sin_port = htons(8888);
	// 192.168.1.4
	// 192.168.1.255
	// 255.255.255.255
	server_addr -> sin_addr.s_addr = inet_addr(direccion_ip);

	bind(sock_fd, (struct sockaddr*)server_addr, sizeof(*server_addr));
	return sock_fd;
}

void enviar_solicitud(int sock_fd) {
	char mensaje[] = "Hola a todos\n";
	char buffer[256];
	int n;

	struct sockaddr_in cliente;
	int len = sizeof(cliente);

	while(1) {
		n = recvfrom(sock_fd, buffer, 256, MSG_WAITALL, (struct sockaddr*)&cliente, &len);
		buffer[n] = '\0';

		printf("El servidor dijo: %s\n", buffer);
	}
}

void _main(int puerto, char *direccion_ip) {
	struct sockaddr_in server_addr;
	int sock_fd = inicializar(&server_addr, puerto, direccion_ip);
	enviar_solicitud(sock_fd);
	close(sock_fd);
}

int main(int argc, char **argv) {
	argc--; argv++;
	char direccion_ip[50];
	if(argc != 2){
		printf("El programa recibe como parametro el puerto <puerto> <direccion ip>\n");
		exit(EXIT_FAILURE);
	}
	strcpy(direccion_ip, argv[1]);
	_main(atoi(argv[0]), direccion_ip);
	return 0;
}





