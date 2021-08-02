//Programa clteUDP para enviar mensajes a través de un socket
//con el protocolo UDP

//Librerias de cajon
#include <stdlib.h> //Exit
#include <stdio.h>	//perror
#include <string.h>	//strlen


//Del manual socket y bind 
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

//Del manual 7 ip
#include <sys/socket.h>	//inet_addr
#include <netinet/in.h>	//inet_addr
#include <netinet/ip.h> /* superset of previous */

//Del manual close
#include <unistd.h>

//Del manual htons y de inet_addr
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
	unsigned char msj[100];							//Declaramos el mensaje a enviar
	int tam;										//El tam es el valor devuelto de sendto 
	int	udp_socket;									//Declaramos el socket para asignarle el estado del socket 
	udp_socket = socket(AF_INET, SOCK_DGRAM, 0);	//La sintaxis viene del manual, la función socket Aquí se abre el socket
	int lbind; 										//Declaramos el valor que tomara bind al ejecutar la funcion

	struct sockaddr_in local,remota;				//Delcaramos la estructura donde guardarremos las direcciones
 	
 	if (udp_socket==-1) 							//Comprobamos error, si función socket da -1 
	{
 		perror("\nError al abrir socket");
 		exit(0);
 	}
 	else
 	{
 		perror("\nExito al abrir el socket");		//Nos informamos que se abrio el socket
 													//Rellenaremos la direccion local
 		local.sin_family=AF_INET; 					//Rell. Familia con AF.INET siempre es así de manual
        local.sin_port=htons(0);   					//Puerto local, set as 0 pues somos clientes
        local.sin_addr.s_addr=INADDR_ANY;  			//Internet address

        lbind=bind(udp_socket, (struct sockaddr *)&local, sizeof(local)); //Enlazar socket con la dirección

        if (lbind==-1)								//Comprobamos si el socket fue enlazado correctamente
        {
        	perror("\nError al enlazar");			//Imprimimos el error
        	exit(0);
        }
        else
        {
        	perror("\nExito al enlazar");			//Imprimimos el exito
        												//Rellebamos direccion remota 
        	remota.sin_family=AF_INET; 					//Rell. Familia con AF.INET siempre es así de manual
       		remota.sin_port=htons(8080);   				//Port in network byte order
        	remota.sin_addr.s_addr=inet_addr("192.168.1.80");//Internet address convertido a binario 
        	printf("-..");

        	tam= sendto(udp_socket,msj,strlen(msj)+1,0,(struct sockaddr *)&remota,sizeof(remota)); //Enviamos 

        	if(tam==-1)
        	{
        		perror("\nError al enviar mensaje");
        		exit(0);
        	}
        	else
        	{
        		perror("\nExito al enviar mensaje");
        	}
        }
 	}

 	close(udp_socket);								//Cerramos el socket				
	return 0;
}