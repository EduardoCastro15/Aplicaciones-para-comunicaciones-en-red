#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int socket_local, socket_cliente;
int bind_local, listen_local;
struct sockaddr_in addr_local, addr_cliente;

int main () {
   socket_local = socket( AF_INET, SOCK_STREAM, 0 );
   if (socket_local==-1) { perror( "\nEstado de socket_local" ); exit( 0 ); }
   perror( "\nEstado de socket_local" );
   addr_local.sin_family = AF_INET;
   addr_local.sin_port = htons( 8080 );
   addr_local.sin_addr.s_addr = INADDR_ANY;
   bind_local = bind( socket_local, (struct sockaddr *) &addr_local, sizeof( addr_local ) );
   if ( bind_local == -1 ) { perror( "Estado de bind_local" ); exit( 0 ); }
   perror( "Estado de bind_local" );
   listen_local = listen( socket_local, 5 );
   if ( listen_local == -1 ) { perror( "Estado de listen_local" ); exit( 0 ); }
   perror( "Estado de listen_local" );
   while(1) {
      int size_cliente = sizeof(struct sockaddr_in);
      socket_cliente = accept( socket_local, (struct sockaddr *) &addr_cliente, &size_cliente);
      if ( socket_cliente == -1 ) { perror( "Estado de socket_cliente" ); exit( 0 ); }
      perror( "Estado de socket_cliente" );
      send(socket_cliente,"<html><body><h1>Error</h1></body></html>", 40, 0);
      close(socket_cliente);
   }

   close(socket_local);
   return 0;
}
