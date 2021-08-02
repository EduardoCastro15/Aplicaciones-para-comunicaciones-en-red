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
unsigned char nomArch[30], data[512];
struct sockaddr_in local, remota;

FILE *fr;

int main () {
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket==-1) {perror("\nError al abrir el socket"); exit(0);}

    else {
        local.sin_family= AF_INET;
        local.sin_port= htons(0);      
        local.sin_addr.s_addr= INADDR_ANY;
        dbind= bind(udp_socket, (struct sockaddr *)&local, sizeof(local));
        if (dbind == -1) { perror("\nError en bind"); exit(0); }

        else{
            remota.sin_family= AF_INET;
            remota.sin_port= htons(8080);
            remota.sin_addr.s_addr=inet_addr("127.0.0.1");
            printf("Archivo a leer: ");
            fgets(nomArch, sizeof(nomArch), stdin); 
            strtok(nomArch, "\n");

            fr = fopen(nomArch, "rb");
            if (fr==NULL) { printf("Archivo no existe"); exit(0); }

            else {
                int bytesLeidos, bytesTotal;
                while (!feof(fr)) {
                    bytesLeidos = fread(data, 1, 512, fr);
                    bytesTotal += bytesLeidos;
                    tam= sendto(udp_socket, data, bytesLeidos, 0, (struct sockaddr *)&remota, sizeof(remota));
                    if(tam == -1){perror("\nError en bind");exit(0);}

                    else {
                        printf("Enviados = %d bytes\n", tam);
                    }
                }
                printf("Tam archivo enviado: %i bytes",bytesTotal);
                fclose(fr);
            }
       }

    }
    close(udp_socket);
    return 0;
}

