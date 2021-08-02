#include<stdio.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<semaphore.h>
#include<string.h>
#include<stdlib.h>

#define MAXN 30
#define NUM_SECTIONS 2
#define NUM_CONSUMERS 2
#define NUM_PRODUCERS 3

int remaining_consumtions = MAXN * NUM_PRODUCERS;
int value[NUM_SECTIONS];
sem_t* sem[2 * NUM_SECTIONS];

void* produce(void* arg){
	for(int i = 1; i <= MAXN; i++){
		for(int j = 0; 1; j = (j + 1) % NUM_SECTIONS){
			int ret = sem_trywait(sem[2 * j]);
			if(ret == -1) continue;
			value[j] = i;
			printf("Productor %lu produció: %d en seccion: %d\n", pthread_self(), value[j], j);
			sem_post(sem[2 * j + 1]);
			break;
		}
	}
	return NULL;
}

void* consume(void* arg){
	while(remaining_consumtions > 0){
		for(int j = 0; remaining_consumtions > 0; j = (j + 1) % NUM_SECTIONS){
			int ret = sem_trywait(sem[2 * j + 1]);
			if(ret == -1) continue;
			printf("Consumidor %lu consumió: %d en seccion: %d\n", pthread_self(), value[j], j);
			sem_post(sem[2 * j]);
			break;
		}
		if(remaining_consumtions > 0){
			sem_wait(sem[2 * NUM_SECTIONS]);
			remaining_consumtions--;
			sem_post(sem[2 * NUM_SECTIONS]);
		}
	}
	return NULL;
}

void manage_semaphores(int create){
	char num[20], name_prod[20], name_cons[20];
	for(int i = 0; i < NUM_SECTIONS + 1; i++){
		sprintf(num, "%d", i);
		strcpy(name_prod, "/prod");
		strcpy(name_cons, "/cons");
		strcat(name_prod, num);
		strcat(name_cons, num);
		/* printf("prod: %s\n", name_prod); */
		/* printf("prod: %s\n", name_cons); */
		if(create){
			sem[2 * i] = sem_open(name_prod, O_CREAT | O_EXCL, 0644, 1);
			sem[2 * i + 1] = sem_open(name_cons, O_CREAT | O_EXCL, 0644, 0);
		}
		else{
			sem_close(sem[2 * i]);
			sem_close(sem[2 * i + 1]);
			sem_unlink(name_prod);
			sem_unlink(name_cons);
		}
	}

}

int main(){
	manage_semaphores(0);
	manage_semaphores(1);
	pthread_t tid[NUM_CONSUMERS + NUM_PRODUCERS];
	pthread_attr_t attr[NUM_CONSUMERS + NUM_PRODUCERS];
	for(int i = 0; i < NUM_CONSUMERS + NUM_PRODUCERS; i++)
		pthread_attr_init(&attr[i]);
	for(int i = 0; i < NUM_CONSUMERS; i++)
		pthread_create(&tid[i], &attr[i], consume, NULL);
	for(int i = 0; i < NUM_PRODUCERS; i++)
		pthread_create(&tid[i + NUM_CONSUMERS], &attr[i + NUM_CONSUMERS], produce, NULL);
	for(int i = 0; i < NUM_CONSUMERS + NUM_PRODUCERS; i++)
		pthread_join(tid[i], NULL);
	manage_semaphores(0);
	return 0;
}
