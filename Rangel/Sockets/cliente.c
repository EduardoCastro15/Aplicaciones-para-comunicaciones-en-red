#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> //Library that provides access to the POSIX
#include <sys/socket.h> //Libreria sockets, bind y send
#include <sys/types.h> //Libreria sockets,  bind y send
#include <netinet/in.h> //Internet address family
#include <arpa/inet.h> //Definitions for internet operations
#include <pthread.h>

int main(int argc, char *argv[]){
	int puerto;
	char *ip;
	int dsocket;
	struct sockaddr_in local;

	if(argc != 3){
		printf("El numero de parametros es correcto\n");
		exit(0);
	}

	ip = (char *)malloc(15*sizeof(char));

	strcpy(argv[1], ip);
	puerto = atoi(argv[2]);

	//1.- Crear socket
	dsocket = socket(AF_INET, SOCK_STREAM, 0);
	if(dsocket ==-1){
		perror("Error al al crear el socket");
		exit(0);
	}

	//2.- Conectarse al servidor
	local.sin_family = AF_INET;
	local.sin_port = htons(puerto);
	local.sin_addr.s_addr = inet_addr(ip);
	dconect = conect();

	//3.- Fase de comunicación
		//Enviar mensaje al servidor con send()
		//Recibir respuesta del servidor con recive()
		//Cerrar socket con close()

	return 0;
}