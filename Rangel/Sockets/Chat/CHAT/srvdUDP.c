//Programa srvdUDP para recibir mensajes a través de un socket
//con el protocolo UDP

//Librerias de cajon
#include <stdlib.h> //Exit
#include <stdio.h>	//perror
#include <string.h> //strlen

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
//	unsigned char msj[100]="Hola que tal";			//Declaramos el mensaje a enviar
	unsigned char pkr[512];                         //Declaramos el mensaje recibido 
    int tam;										//El tam es el valor devuelto de sendto 
	int	udp_socket;									//Declaramos el socket para asignarle el estado del socket 
	udp_socket = socket(AF_INET, SOCK_DGRAM,0);	//La sintaxis viene del manual, la función socket Aquí se abre el socket
	int lbind; 										//Declaramos el valor que tomara bind al ejecutar la funcion
    int lcliente;                                   //Declaramos la longitud de la struct cliente

	struct sockaddr_in servidor,cliente;			//Delcaramos la estructura donde guardarremos las direcciones
 	
 	if (udp_socket==-1) 							//Comprobamos error, si función socket da -1 
	{
 		perror("\nError al abrir socket");
 		exit(0);
 	}
 	else
 	{
 		perror("\nExito al abrir el socket");		//Nos informamos que se abrio el socket
 													//Rellenaremos la direccion servidor
 		servidor.sin_family=AF_INET; 				//Rell. Familia con AF.INET siempre es así de manual
        servidor.sin_port=htons(8080);   				//Puerto servidor, set as 0 pues somos clientes
        servidor.sin_addr.s_addr=INADDR_ANY; 		//Internet address

        lbind=bind(udp_socket, (struct sockaddr *)&servidor, sizeof(servidor)); //Enlazar socket con la dirección

        if (lbind==-1)								//Comprobamos si el socket fue enlazado correctamente
        {
        	perror("\nError al enlazar");			//Imprimimos el error
        	exit(0);
        }
        else
        {
        	perror("\nExito al enlazar");			//Imprimimos el exito

            lcliente=sizeof(cliente);
            tam= recvfrom(udp_socket,pkr,512,0,(struct sockaddr *)&cliente,&lcliente);//Recibimos el mensaje

        	if(tam==-1)
        	{
        		perror("\nError al recibir mensaje");//Informamos del error
        		exit(0);
        	}
        	else
        	{
        		printf("\nExito al recibir mensaje, el mensaje es: %s \n",pkr);//Informamos exito y el mensaje
        	}
        }
 	}

 	close(udp_socket);								//Cerramos el socket				
	return 0;
}