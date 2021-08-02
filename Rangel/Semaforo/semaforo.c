//Compilamos: gcc semaforo.c -o semaforo -pthread

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#define NUMHILOS 5

sem_t *semaforo;
int error, i, parametro, a;
char t;
void *z;

void *fun(void *ap )
{
    sem_t *sem = ap;
    char t;
    sem_wait( sem ); // Bloqueamos seccion critica
    printf( "\n Hilo ENTRO a seccion critica" );
    fflush( stdout );
    sleep( 1 );
    printf( "\n Hilo SALIO a seccion critica\n\n" );
    fflush( stdout );
    sem_post( sem ); // Desbloqueamos seccion critica
}

int main()
{
    // Creamos nuestro semaforo
    semaforo = sem_open( "sema", O_CREAT, 0666, 1 );

    // Declaramos el descritor de los hilos
    pthread_t hilos[NUMHILOS];

    // Creamos nuestros hilos
    for( i = 0; i < NUMHILOS; i++ )
        pthread_create( &hilos[i], NULL, (void *)fun, semaforo );

    // Esperamos a que nuestro hilos de ejecutan antes de terminar el programa
    for( i = 0; i < NUMHILOS; i++ )
        pthread_join( hilos[i], (void *)&z );

    // Destruimos nuestro semaforo
    sem_unlink( "sema" );
    sem_close( semaforo );
    return 0;
}