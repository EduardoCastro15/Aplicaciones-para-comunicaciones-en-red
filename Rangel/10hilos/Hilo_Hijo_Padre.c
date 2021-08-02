//Creacion de 10 hilos
//Pasando como parametro una estructura (Padre -> Hijo)
//Enviando respuesta del hijo al padre
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
	int res = val->x;
	printf("\n\nYo soy el hilo: %li \n", pthread_self());
	printf("x: %d \n", val->x);
	printf("y: %f \n", val->y);
	printf("z: %s", val->z);
	free(arg);
	pthread_exit((void*)res);
}

int main(int argc, char const *argv[]){
	pthread_t *tid = (pthread_t *)malloc(10*sizeof(pthread_t));
	void *res = NULL;
	int i;

	printf("Hilo Principal: %li INICIO\n", pthread_self());
	for(i=0;i<10;i++){
		Data* val=(Data*)malloc(10*sizeof(Data));
		val->x = i;
		val->y = i + 0.5;
		val->z = "Soy la cadena";
		pthread_create(&tid[i], NULL, child_function, (void*)val);
	}
	
	for(i=0;i<10;i++){
		pthread_join(tid[i], &res);
		printf("\nRespuesta del hijo: %d\n", (int)(int*)res);
	}
	printf("\n\nHilo Principal: %li FIN\n", pthread_self());
	free(tid);
	return 0;
}