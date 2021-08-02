#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

int udp_socket, dbind, tam;
unsigned char mensaje[518];
struct sockaddr_in local, remota;

int main () {
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket==-1) {perror("\nError al abrir el socket"); exit(0);}
    else {
        local.sin_family= AF_INET;
        local.sin_port= htons(0);
        local.sin_addr.s_addr= INADDR_ANY;
        dbind= bind(udp_socket, (struct sockaddr *)&local, sizeof(local));
        if(dbind == -1){ perror("\nError en bind local"); exit(0); }
        else{
            remota.sin_family= AF_INET;
            remota.sin_port= htons(56);
            remota.sin_addr.s_addr=inet_addr("148.204.103.2");
            printf("Mensaje: ");
            fgets(mensaje,sizeof(mensaje),stdin);
            tam= sendto(udp_socket,mensaje, strlen(mensaje), 0, (struct sockaddr *)&remota, sizeof(remota));
            if(tam == -1){perror("\nError en bind");exit(0);}
            else{ perror("\nExito al enviar");}
       }
       close(udp_socket);
    }
    return 0;
}
