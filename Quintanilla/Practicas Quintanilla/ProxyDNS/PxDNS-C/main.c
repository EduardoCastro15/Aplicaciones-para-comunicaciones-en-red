#include "Solicitud/Index_Solicitud.h"
#include "Respuesta/Index_Respuesta.h"
#include <stdio.h> //Estandar
#include <sys/socket.h> //Sockets
#include <stdlib.h> //Exit function
#include <unistd.h> //Close function
#include <netinet/in.h> //Address of IP protcol

int socket_local;
int tam_solicitud, tam_respuesta, position;
struct sockaddr_in addr_remote;
unsigned char name_search[50];
unsigned char paq_solicitud[512], paq_respuesta[512];

int main () {
   socket_local = newSocket();
   printf( "\n--> Bienvenido al analizar de DNS creado por Carmona\n" );
   printf( "--> Dominio buscado: " );
   fgets( name_search, sizeof( name_search ), stdin);
   tam_solicitud = estrucSolicitud( paq_solicitud, name_search );
   addr_remote = addrSolicitud( "192.168.0.38", 50000);
   sendSolicitud( socket_local, paq_solicitud, tam_solicitud, addr_remote );
   tam_respuesta = waitReplay( socket_local, paq_respuesta, addr_remote);
   if( !(((paq_respuesta[1] << 8) &0xFF00 ) | (paq_respuesta[0] & 0xFF)) ) { exit(0); }
   printf( "\n--> Encabezado:\n" );
   position = readHeader ( paq_respuesta );
   readRR ( paq_respuesta, position );
   close(socket_local);
   return 0;
}
