#include <stdio.h> //Estandar
#include <sys/socket.h> //Sockets
#include <stdlib.h> //Exit function
#include <netinet/in.h> //Address of IP protcol
#include <sys/types.h> //Bind
#include <string.h> //memcpy
#include <arpa/inet.h> //inet_addr


int newSocket ();
int estrucSolicitud ( unsigned char * paq_solicitud, unsigned char name_search[] );
struct sockaddr_in addrSolicitud ( unsigned char ip [], int port);
void sendSolicitud ( int socket_local, unsigned char paq_solicitud[],
   int tam_solicitud, struct sockaddr_in addr_remote );
