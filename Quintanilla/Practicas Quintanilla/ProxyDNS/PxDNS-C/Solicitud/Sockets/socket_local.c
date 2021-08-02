#include "../Index_Solicitud.h"

static void newDir ( int * socket_local) {
   struct sockaddr_in addr_local;
   int bind_local;
   addr_local.sin_family = AF_INET;
   addr_local.sin_port = htons( 0 );
   addr_local.sin_addr.s_addr = INADDR_ANY;
   bind_local = bind( *socket_local, ( struct sockaddr * ) &addr_local,
      sizeof( addr_local ) );
   if ( bind_local == -1 ) {
      perror( "Estado de bind_local" );
      exit( 0 );
   } else { perror( "Estado de bind_local" ); }
}

int newSocket () {
   int socket_local;
   socket_local = socket( AF_INET, SOCK_DGRAM, 0 );
   if ( socket_local == -1 ) {
      perror( "\nEstado de socket_local" );
      exit( 0 );
   } else {
         perror( "\nEstado de socket_local" );
         newDir( &socket_local );
         return socket_local;
   }
}
