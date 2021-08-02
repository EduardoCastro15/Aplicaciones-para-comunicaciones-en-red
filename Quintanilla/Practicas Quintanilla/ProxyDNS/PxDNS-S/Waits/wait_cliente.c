#include "../Index.h"

int waitCliente (int socket_local, unsigned char *paq_cliente,
struct sockaddr_in * addr_cliente) {
   int tam_cliente;
   int lrecv = sizeof(*addr_cliente);
   do {
      tam_cliente = recvfrom(socket_local, paq_cliente, 512,
         MSG_DONTWAIT, (struct sockaddr *)addr_cliente, &lrecv);
      if(tam_cliente==-1){}
      else { return tam_cliente; }
   } while (1);
}
