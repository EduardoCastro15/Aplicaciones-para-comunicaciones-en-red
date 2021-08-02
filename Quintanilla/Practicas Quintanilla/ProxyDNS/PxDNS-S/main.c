#include "Index.h"
#include <string.h>
#include <stdio.h> //Estandar
#include <sys/socket.h> //Sockets
#include <stdlib.h> //Exit function
#include <unistd.h> //Close function
#include <netinet/in.h> //Address of IP protcol

int socket_local;
int tam_reply, tam_cliente;
struct sockaddr_in addr_cliente, addr_remote;
unsigned char name_search[50];
unsigned char paq_reply[512], paq_cliente[512];
// unsigned char mensajeRespuesta[20]="3www3carmona2mx0";

int main () {
   socket_local = newSocket();
   // addr_remote = addrSolicitud( "148.204.103.2", 53);
   addr_remote = addrSolicitud( "8.8.8.8", 53);
   printf( "\n--> Bienvenido al Proxy DNS creado por Carmona\n" );
   do {
      printf( "--> Esperando solicitud: \n" );
      tam_cliente = waitCliente( socket_local, paq_cliente, &addr_cliente );
      if( ! readDom ( paq_cliente ) ) {
         paq_cliente[2] = 0x81;
         paq_cliente[3] = 0x80;
         paq_cliente[7] = 0x01;
         paq_cliente[tam_cliente+1] = 0xC0;    //Apuntador
         paq_cliente[tam_cliente+2] = 0x0C;  //Apuntador
         paq_cliente[tam_cliente+3] = 0x00;  //Type
         paq_cliente[tam_cliente+4] = 0x01;  //Type
         paq_cliente[tam_cliente+5] = 0x00;  //Class
         paq_cliente[tam_cliente+6] = 0x01;  //Class
         paq_cliente[tam_cliente+7] = 0x00;  //TTL
         paq_cliente[tam_cliente+8] = 0x00;  //TTL
         paq_cliente[tam_cliente+9] = 0x0E;  //TTL
         paq_cliente[tam_cliente+10] = 0x0F;  //TTL
         paq_cliente[tam_cliente+11] = 0x00;  //Tam
         paq_cliente[tam_cliente+12] = 0x04;  //Tam
         paq_cliente[tam_cliente+13] = 0xC0;  //Respuesta   198.168.0.38
         paq_cliente[tam_cliente+14] = 0xA8;  //Respuesta
         paq_cliente[tam_cliente+15] = 0x00;  //Respuesta
         paq_cliente[tam_cliente+16] = 0x26;  //Respuesta

         // unsigned char tipo_peticion[2] = { 0x00, 0x01 };
         // unsigned char clase_peticion[2] = { 0x00, 0x01 };
         // memcpy( paq_cliente + tam_cliente, mensajeRespuesta, 20);
         // memcpy( paq_cliente + tam_cliente + sizeof(mensajeRespuesta), tipo_peticion, 2);
         // memcpy( paq_cliente + tam_cliente + sizeof(mensajeRespuesta) + 2, clase_peticion, 2);
         sendSolicitud ( socket_local, paq_cliente, tam_cliente+17, addr_cliente );
      }
      else {
         sendSolicitud ( socket_local, paq_cliente, tam_cliente, addr_remote );
         tam_reply = waitReplay ( socket_local, paq_reply );
         sendSolicitud ( socket_local, paq_reply, tam_reply, addr_cliente );
      }
   } while ( 1 );
   close(socket_local);
   return 0;
}
