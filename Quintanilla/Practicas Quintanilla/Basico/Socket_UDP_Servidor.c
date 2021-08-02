#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

int main () {
    int udp_socket, dbind, tam, lrecv;
    struct sockaddr_in servidor, cliente;
    unsigned char mensaje[1000];
    unsigned char mensajeRecivido[512];
    
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket==-1) { perror("\nError al abrir el socket"); exit(0);}
    else {
        servidor.sin_family= AF_INET;
        servidor.sin_port= htons(8080);
        servidor.sin_addr.s_addr= INADDR_ANY;
        dbind= bind(udp_socket, (struct sockaddr *)&servidor, sizeof(servidor));
        if(dbind == -1){ perror("\nError en bind"); exit(0);}
        else{
            lrecv= sizeof(cliente);
            tam= recvfrom(udp_socket, mensajeRecivido, 512, 0, (struct sockaddr *)&cliente, &lrecv);
            if(tam == -1){ perror("\nError en bind");exit(0);}
            else{ printf("Mensaje recibido: %s", mensajeRecivido); }     
        }
    }
    close(udp_socket);
    return 0;
}