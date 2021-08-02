#include "../Index.h"

struct sockaddr_in addrSolicitud ( unsigned char ip [], int port) {
   struct sockaddr_in addr_remote;
   addr_remote.sin_family= AF_INET;
   addr_remote.sin_port= htons(port);
   addr_remote.sin_addr.s_addr=inet_addr(ip);
   return addr_remote;
}

void sendSolicitud ( int socket_local, unsigned char paq_solicitud[],
   int tam_solicitud, struct sockaddr_in addr_remote ) {
   tam_solicitud = sendto( socket_local, paq_solicitud, tam_solicitud, 0,
      (struct sockaddr *)&addr_remote, sizeof( addr_remote ) );
   if( tam_solicitud == -1 ) {
      printf( "Estado del envio: ERROR\n" );
      exit( 0 );
   } else {
      printf( "Estado del envio: Success\n" );
   }
}
