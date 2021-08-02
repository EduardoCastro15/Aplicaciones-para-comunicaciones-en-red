#include "../Index_Respuesta.h"

int waitReplay (int socket_local, unsigned char * paq_respuesta,
struct sockaddr_in addr_remote) {
   struct timeval start, end;
   int tam_respuesta;
   int timeEspera = 1000;
   long mtime=0, seconds, useconds;
   int lrecv = sizeof(addr_remote);
   gettimeofday(&start, NULL);
   while (mtime<timeEspera) {
      tam_respuesta = recvfrom(socket_local, paq_respuesta, 512,
         MSG_DONTWAIT, (struct sockaddr *)&addr_remote, &lrecv);
      if(tam_respuesta==-1){}
      else {
         printf("Estado de la respuesta: Success\n");
         return tam_respuesta;
      }
      gettimeofday(&end, NULL);
      seconds = end.tv_sec -start.tv_sec;
      useconds = end.tv_usec -start.tv_usec;
      mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
   }
   perror( "Estado de la respuesta" );
   return tam_respuesta;
}
