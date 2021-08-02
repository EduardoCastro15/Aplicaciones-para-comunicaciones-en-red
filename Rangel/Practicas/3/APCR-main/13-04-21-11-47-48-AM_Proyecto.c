/*
	Instituto politécnico Nacional
	Escuela Superior de Cómputo
	Proyecto Sistemas Operativos
	Profesor: Rangel Guzman Josué
	Alumno: Frausto Hernández Omar
	Grupo: 2cv10
	27/11/2019


El problema propuesto es el siguiente:
Se cuenta con 8 productores y 4 consumidores, cada uno de los productores deberá escribir
100000 datos en 2 secciones de memoria que se tendrán y cada sección de memoria tendrá
divisiones de 7 segmentos, en los cuales deben ingresar ambos.
Los consumidores al entrar a la memoria deberán revisar si está disponible un dato y de ser así
deberán leerlo, por otra parte, el productor también verificará si está libre ese segmento para
poder escribir.
Los datos que vayan leyendo los consumidores deberán ser almacenados en 8 archivos de texto.
Cada archivo de texto almacenará un cierto dígito, es decir, el archivo de texto 111.txt
almacenará todos los datos que los consumidores lean el dígito “1111111” y así sucesivamente
hasta el “8888888”. Al finalizar el programa deberá de haber 800000 datos, sin pérdidas.
*/

#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>

typedef struct 
{
	int bandera;
	char contenido[8];
}zona;

zona *buffer;
int id_memory;
int semaforo;
key_t key;

int crearMemoria ();
void eliminarMemoria ();

void crearSemaforos ();
void eliminarSemaforo ();

void productor(int);
char * obtenerCadena(int);
void consumidor (int);


int main(int argc, char **argv[])
{
	int prod, cons;
	pid_t proceso;
	int *espera;

	buffer = malloc(sizeof(zona));
	buffer->bandera = 0;

	if (crearMemoria() != -1 )
	{
		crearSemaforos();
	} 
	else 
	{
		printf("ERROR al crear la memoria.\n");
		exit(-1);
	}

	for(int i = 0; i < 12; i++)
	{
		proceso = fork();
		switch(proceso)
		{
			case -1:
				printf("ERROR al crear procesos.\n");
				exit(-1);
			break;

			case 0:
				if ( i < 8)
				{
					for (int k = 0; k < 100000; k++)
					{
						productor(i);
					}
				}
				else
				{
					for(int m = 0; m < 200000; m++)
					{
						consumidor(i);
					}
				}
				exit(0);
			break;
			
			default:
			break;
		}
	}
	for (int i = 0; i < 12; i++) 
		wait(espera);

	eliminarSemaforo();
	eliminarMemoria();
	return 0;
}

int crearMemoria ()
{
	//generamos la llave
	key = ftok ("/bin/ls", 1008);

	if(key == -1)
		return -1;

    //creamos memoria
	id_memory = shmget(key, sizeof(zona)*7, 0777 | IPC_EXCL | IPC_CREAT);
	if ( id_memory == -1 )
	{
		id_memory = shmget(key, sizeof(zona)*7, 0777);
		printf("Ligando a la memoria compartida \n");
		buffer = (zona *)shmat(id_memory, (void*)0, 0);
		printf("Ligando la zona de datos a la memoria compartida\n");
		return 0;
	}
	else 
		printf("Se creo la memoria compartida\n");
	
	//ligamos la memoria
	buffer = (zona *)shmat(id_memory, (void*)0, 0);
	printf("Ligando la zona de datos a la memoria compartida\n");

	return 1;
}

void eliminarMemoria()
{
	shmdt(buffer);
	printf("Desligando la zona de datos de la memoria compartida.\n");
	
	shmctl(id_memory, IPC_RMID, (struct shmid_ds *)NULL);
	printf("Eliminando el segmento de memoria compartida.\n");
}


void crearSemaforos()
{
	semaforo = semget (key, 9, 0777 | IPC_EXCL | IPC_CREAT);

	if(semaforo == -1)
	{
		semaforo = semget (key, 9, 0777);
	
	} 
	else 
	{		
		printf("Creando el conjunto de semaforos\n");

		semctl(semaforo, 0, SETVAL, 5);
		semctl(semaforo, 1, SETVAL, 0);
		semctl(semaforo, 2, SETVAL, 1);
		semctl(semaforo, 3, SETVAL, 1);
		semctl(semaforo, 4, SETVAL, 1);
		semctl(semaforo, 5, SETVAL, 1);
		semctl(semaforo, 6, SETVAL, 1);
		semctl(semaforo, 7, SETVAL, 1);
		semctl(semaforo, 8, SETVAL, 1);

		printf("Inicializando los semaforos.\n");
	}
}

void eliminarSemaforo ()
{
	//for(int i=0 ; i<7; i++)
	semctl(semaforo, 0, IPC_RMID);
	semctl(semaforo, 1, IPC_RMID);
	semctl(semaforo, 2, IPC_RMID);
	semctl(semaforo, 3, IPC_RMID);
	semctl(semaforo, 4, IPC_RMID);
	semctl(semaforo, 5, IPC_RMID);
	semctl(semaforo, 6, IPC_RMID);
	semctl(semaforo, 7, IPC_RMID);
	semctl(semaforo, 8, IPC_RMID);
	//eliminarMemoria();
	printf("Eliminando los semaforos.\n");
}

char * obtenerCadena(int i)
{
	if(i == 0) return "11111111";
	if(i == 1) return "22222222";
	if(i == 2) return "33333333";
	if(i == 3) return "44444444";
	if(i == 4) return "55555555";
	if(i == 5) return "66666666";
	if(i == 6) return "77777777";
	else return "88888888";
}

void productor(int i)
{
	int x = 1;
	printf("Productor %d\n",i);
	int valorSemaforo;
	while (1)
	{
		valorSemaforo = semctl(semaforo, 0, GETVAL);
		if(valorSemaforo > 0)
		{
			semctl(semaforo, 0, SETVAL, valorSemaforo-1);
			//printf("Se redujo el valor del semaforo 0 en el productor %d.\n", i);
			break;
		}
	}

	while(x)
	{
		for(int j = 0; j<7; j++)
		{
			//sem_wait(j+2);
			valorSemaforo = semctl(semaforo, (j+2), GETVAL);
			//printf("%d", valorSemaforo);
			if(valorSemaforo > 0)
			{
				semctl(semaforo, (j+2), SETVAL, valorSemaforo-1);
				//printf("Se redujo el valor del semaforo %d en el productor %d para que nadie entre al campo a analizar.\n", (j+2), i);
				if(buffer -> bandera == 0)
				{
					strcpy(buffer -> contenido, obtenerCadena(i));
					buffer -> bandera = 1;
					//sem_signal(j+2);
					valorSemaforo = semctl(semaforo, j+2, GETVAL);
					semctl(semaforo, j+2, SETVAL, valorSemaforo+1);
					//printf("Se aumento el valor del semaforo %d en el productor %d.\n", j+2, i);
					x = 0;
					j = 7;
					break;
				}
				//sem_signal(j+2);
				valorSemaforo = semctl(semaforo, j+2, GETVAL);
				semctl(semaforo, j+2, SETVAL, valorSemaforo+1);
				//printf("Se aumento el valor del semaforo %d en el productor %d porque no pudo entrar a un campo.\n", j+2, i);
			}	
		}
	}
	//sem_signal(c);
	valorSemaforo = semctl(semaforo, 1, GETVAL);
	semctl(semaforo, 1, SETVAL, valorSemaforo+1);
	//printf("Se aumento el valor del semaforo 1 en el productor %d para que se pueda consumir.\n", i);
}

void consumidor (int i)
{
	printf("Consumidor %d\n",i);
	int x = 1;

	int fd1, valorSemaforo;
	char * myfifo1 = "/tmp/myfifo1";
	mkfifo(myfifo1, 0666);
	FILE *Archivo1;
	FILE *Archivo2;
	FILE *Archivo3;
	FILE *Archivo4;
	FILE *Archivo5;
	FILE *Archivo6;
	FILE *Archivo7;
	FILE *Archivo8;

	while (1)
	{
		valorSemaforo = semctl(semaforo, 1, GETVAL);
		if(valorSemaforo >0)
		{
			semctl(semaforo, 1, SETVAL, valorSemaforo-1);
			//printf("Se redujo el valor del semaforo 1 en el consumidor %d.\n", i);
			break;
		}
	}

	while(x)
	{
		for(int j = 0; j<7; j++ )
		{
			//sem_wait((j+2));
			valorSemaforo = semctl(semaforo, j+2, GETVAL);
			if(valorSemaforo >0)
			{
				semctl(semaforo, j+2, SETVAL, valorSemaforo-1);
				//printf("Se redujo el valor del semaforo %d en el consumidor %d.\n", j+2, i);
				if(buffer -> bandera == 1)
				{
					for(int k = 8; k < 12; k++)
					{
							if(k == i)
							{
								if(buffer->contenido[0] == '1')
								{
									Archivo1 = fopen ( "11111111.txt", "a" );
									fprintf(Archivo1,"Consumidor %d leyo %s \n",i-7,buffer->contenido);
									fclose(Archivo1);
								}
								else if(buffer->contenido[0] == '2')
								{
									Archivo2 = fopen ( "22222222.txt", "a" );
									fprintf(Archivo2,"Consumidor %d leyo %s \n",i-7,buffer->contenido);
									fclose(Archivo2);
								}
								else if(buffer->contenido[0] == '3')
								{
									Archivo3 = fopen ( "33333333.txt", "a" );
									fprintf(Archivo3,"Consumidor %d leyo %s \n",i-7,buffer->contenido);
									fclose(Archivo3);
								}
								else if(buffer->contenido[0] == '4')
								{	
									Archivo4 = fopen ( "44444444.txt", "a" );
									fprintf(Archivo4,"Consumidor %d leyo %s \n",i-7,buffer->contenido);
									fclose(Archivo4);
								}
								else if(buffer->contenido[0] == '5')
								{
									Archivo5 = fopen ( "55555555.txt", "a" );
									fprintf(Archivo5,"Consumidor %d leyo %s \n",i-7,buffer->contenido);
									fclose(Archivo5);
								}
								else if(buffer->contenido[0] == '6')
								{
									Archivo6 = fopen ( "66666666.txt", "a" );
									fprintf(Archivo6,"Consumidor %d leyo %s \n",i-7,buffer->contenido);
									fclose(Archivo6);
								}
								else if(buffer->contenido[0] == '7')
								{
									Archivo7 = fopen ( "77777777.txt", "a" );
									fprintf(Archivo7,"Consumidor %d leyo %s \n",i-7,buffer->contenido);
									fclose(Archivo7);
								}
								else if(buffer->contenido[0] == '8')
								{
									Archivo8 = fopen ( "88888888.txt", "a" );
									fprintf(Archivo8,"Consumidor %d leyo %s \n",i-7,buffer->contenido);
									fclose(Archivo8);
								}
								break;
							}
					}
					
					buffer->bandera = 0;
					valorSemaforo = semctl(semaforo, j+2, GETVAL);
					semctl(semaforo, j+2, SETVAL, valorSemaforo+1);
					//printf("Se aumento el valor del semaforo %d en el consumidor %d.\n", j+2, i);
					x = 0;
					j = 7;
					break;
				}
				semctl(semaforo, j+2, SETVAL, valorSemaforo+1);
				//printf("Se aumento el valor del semaforo %d en el consumidor %d.\n", j+2, i);
			}
		}	
	}
	//sem_signal(p);
	valorSemaforo = semctl(semaforo, 0, GETVAL);
	semctl(semaforo, 0, SETVAL, valorSemaforo+1);
	//printf("Se aumento el valor del semaforo 0 en el consumidor %d.\n", i);				
}