//Creacion de 10 hilos
//Pasando como parametro una estructura (Padre -> Hijo)
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

typedef struct Data{
	int x;
	float y;
	char* z;
}Data;

void *child_function(void* arg){
	Data *val =(Data*)arg;
	printf("\n\nYo soy el hilo: %li \n", pthread_self());
	printf("x: %d \n", val->x);
	printf("y: %f \n", val->y);
	printf("z: %s", val->z);
	free(arg);
	pthread_exit(NULL);
}

void main(){
	pthread_t *tid = (pthread_t *)malloc(10*sizeof(pthread_t));
	printf("Hilo Principal: %li INICIO\n", pthread_self());
	int i;
	for(i=0;i<10;i++){
		Data* val=(Data*)malloc(10*sizeof(Data));
		val->x = 1;
		val->y = 1.0;
		val->z = "123";
		pthread_create(&tid[i], NULL, child_function, (void*)val);
	}
	for(i=0;i<10;i++)
		pthread_join(tid[i], NULL);
	printf("\n\nHilo Principal: %li FIN\n", pthread_self());
}