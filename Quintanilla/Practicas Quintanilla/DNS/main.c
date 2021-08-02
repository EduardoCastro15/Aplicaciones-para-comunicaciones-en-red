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
   socket_local = newSocket(); //Crea un nuevo socket local
   printf( "\n--> Bienvenido al analizar de DNS creado por Carmona\n" );
   printf( "--> Dominio buscado: " );
   fgets( name_search, sizeof( name_search ), stdin);
   tam_solicitud = estrucSolicitud( paq_solicitud, name_search ); //Estructura la peticion de DNS
   addr_remote = addrSolicitud( "148.204.103.2", 53); //Agregamos la direccion y puerto del Servidor DNS
   sendSolicitud( socket_local, paq_solicitud, tam_solicitud, addr_remote );  //Envia la solicitud
   tam_respuesta = waitReplay( socket_local, paq_respuesta, addr_remote);  //Espera a que conteste el servidor
   if( !(((paq_respuesta[1] << 8) &0xFF00 ) | (paq_respuesta[0] & 0xFF)) ) { exit(0); }
   printf( "\n--> Encabezado:\n" );
   position = readHeader ( paq_respuesta );
   printf( "\n--> Registro de Recursos:\n" );
   readRR ( paq_respuesta, position ); //Analiza y muestra los resultados
   close(socket_local);
   return 0;
}
