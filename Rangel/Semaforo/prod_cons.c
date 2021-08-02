//Utilizamos semaforos
//Tenemos una espera no activa


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <semaphore.h>
#include <unistd.h>

sem_t *sem_cons;
sem_t *sem_prod;
int p = 0;

void *consumir(void *arg){
	int i = 0;
	int* limite = (int*)arg;
	for(i = 0; i < *limite; i++){
		sem_wait(sem_cons);
		printf("Consumiendo: %d\n", p);
		sem_post(sem_prod);
	}
	pthread_exit(NULL);
}

void *producir(void *arg){
	int i = 0;
	int* limite = (int*)arg;
	for(i = 0; i < *limite; i++){
		sem_wait(sem_prod); // 
		p++;
		printf("Produciendo: %d\n", p);
		sem_post(sem_cons);
	}
	pthread_exit(NULL);
}

int main(int argc, char **argv){
	int limite1 = 20;
	int limite2 = 20;

	pthread_t *productor = (pthread_t*)malloc(sizeof(pthread_t));
	pthread_t *consumidor = (pthread_t*)malloc(sizeof(pthread_t));

	sem_prod = sem_open("/sem_pro", O_CREAT | O_EXCL, 0644, 1);
	sem_cons = sem_open("/sem_con", O_CREAT | O_EXCL, 0644, 0);

	pthread_create(consumidor, NULL, consumir, (void*)&limite1);
	pthread_create(productor, NULL, producir, (void*)&limite2);
	
	pthread_join(*productor, NULL);
	pthread_join(*consumidor, NULL);

	sem_close(sem_prod);
	sem_close(sem_cons);

	sem_unlink("/sem_pro");
	sem_unlink("/sem_con");
	return 0;
}

//Agregar 3 productores(cada uno va a generar 20 producciones) y 2 consumidores(Depende de la logica que le demos a la solución)
//Podemos decir que cada consumidor puede consumir la mitad de las producciones
//Pero puede pasar que un consumidor entre más veces a la sección crítica y consuma más de lo debido
//Recomendación: Dejar que se peleen entre los hilos consumidores, peor que al final se cumpla la cuota de consumo

//Agregar dos secciones críticas

//El algoritmo de producción es muy parecido al de consumo

//Debe haber un par de semaforos por sección crítica
//No nos sirve una espera no activa
//Hay que implementar una espera activa
//Cuando unos de los hilos quiera entrar:
	//Debe preguntar por el estado del semáforo
	//Si esta abierto va a poder entrar
//Si el hilo encuentra un semaforo cerrado
	//Va a cambiar a la siguiente sección crítica
	//Hasta encontrar uno semaforo abierto
	//Van a estar preguntando de manera infinita hasta que alguno de los consumidores vuelva a abrir el semaforo
//Por otro lado los hilos consumidores van a estar haciendo lo mismo que los productores
	//En un ciclo infinito van a estar preguntando a los semaforos si estan abiertos para poder entrar