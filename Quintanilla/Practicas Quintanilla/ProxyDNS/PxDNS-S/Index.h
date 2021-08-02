#include <stdio.h> //Estandar
#include <sys/socket.h> //Sockets
#include <stdlib.h> //Exit function
#include <netinet/in.h> //Address of IP protcol
#include <sys/types.h> //Bind
#include <arpa/inet.h> //inet_addr

int newSocket ();
struct sockaddr_in addrSolicitud ( unsigned char ip [], int port);
int waitCliente (int socket_local, unsigned char * paq_cliente, struct sockaddr_in *addr_cliente);
int readDom ( unsigned char paq_respuesta[] );
void sendSolicitud ( int socket_local, unsigned char paq_solicitud[], int tam_solicitud, struct sockaddr_in addr_remote );
int waitReplay (int socket_local, unsigned char *paq_respuesta);
