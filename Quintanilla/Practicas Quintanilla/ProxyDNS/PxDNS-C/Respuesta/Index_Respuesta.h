#include <stdio.h> //Estandar
#include <stdlib.h> //Exit
#include <sys/time.h> //time
#include <netinet/in.h> //Address of IP protcol

int waitReplay (int socket_local, unsigned char * paq_respuesta,
struct sockaddr_in addr_remote);
int readHeader ( unsigned char paq_respuesta[] );
void readRR ( unsigned char paq_respuesta[], int position );
