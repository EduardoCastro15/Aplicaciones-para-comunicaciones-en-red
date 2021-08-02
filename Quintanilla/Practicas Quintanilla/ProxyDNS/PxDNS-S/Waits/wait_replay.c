#include "../Index.h"

int waitReplay (int socket_local, unsigned char *paq_reply) {
   int tam_reply;
   struct sockaddr_in addr_remote;
   int lrecv = sizeof(addr_remote);
   do {
      tam_reply = recvfrom(socket_local, paq_reply, 512,
         MSG_DONTWAIT, (struct sockaddr *)&addr_remote, &lrecv);
      if(tam_reply==-1){}
      else { return tam_reply; }
   } while (1);
}
