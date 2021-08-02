#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

int tiempoEspera=5000;
int udp_socket, dbind, tam, lrecv;
unsigned char mensaje[512];
struct sockaddr_in local, remota ,cliente;
struct timeval start, end;
long mtime, seconds, useconds;
unsigned char mensajeRecivido[512];


void mandarMendaje(){
    mtime=0;
    tam= sendto(udp_socket,mensaje, strlen(mensaje), 0, (struct sockaddr *)&remota, sizeof(remota));
    if(tam == -1){perror("\nError en bind");exit(0);} 
    else{
        lrecv= sizeof(cliente);
        gettimeofday(&start, NULL);
        while (mtime<tiempoEspera) {
            tam= recvfrom(udp_socket, mensajeRecivido, 512, MSG_DONTWAIT, (struct sockaddr *)&cliente, &lrecv);
            if(tam == -1){}
            else{ printf("Mensaje recibido: %s", mensajeRecivido); break;}
            gettimeofday(&end, NULL);
            seconds = end.tv_sec -start.tv_sec;    
            useconds = end.tv_usec -start.tv_usec;    
            mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
            if (mtime>=tiempoEspera) {
                mtime=0;
                gettimeofday(&start, NULL);
                tam= sendto(udp_socket,mensaje, strlen(mensaje), 0, (struct sockaddr *)&remota, sizeof(remota));
            }
    }

    }
}

int main () {

    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket==-1) {perror("\nError al abrir el socket"); exit(0);}
    else {
        local.sin_family= AF_INET;
        local.sin_port= htons(0);      
        local.sin_addr.s_addr= INADDR_ANY;
        dbind= bind(udp_socket, (struct sockaddr *)&local, sizeof(local));
        if(dbind == -1){ perror("\nError en bind"); exit(0); }
        else{
            remota.sin_family= AF_INET;
            remota.sin_port= htons(8080);
            remota.sin_addr.s_addr=inet_addr("127.0.0.1");
            printf("Mensaje: ");
            fgets(mensaje,sizeof(mensaje),stdin);
            mandarMendaje();
       }

    }
    close(udp_socket);
    return 0;
}

