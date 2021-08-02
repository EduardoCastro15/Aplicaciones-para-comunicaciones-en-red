
#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define ERROR -1

#define PROD_SEM_IDX 0
#define CONS_SEM_IDX 1

#define NUM_SECTIONS 7
#define NUM_CONS 7
#define NUM_PROD 7
#define NUM_PRODUCTIONS 100000
#define TAM_BUFF 200

typedef struct
{
    int index;
} producer_data;

typedef struct
{
    int index;
} consumer_data;

typedef struct
{
    int semid;
    char value[TAM_BUFF];
    int count;
} section_data;

void println(char *text);
void raise_error(char *msg);

void open_files();
void close_files();
void init_global_producer_consumer_sems();
void *producer_thread(producer_data *);
void *consumer_thread(consumer_data *);
void init_threads();
void join_threads();
void generate_sections();
key_t generate_key(int id);
void init_sems(int semid, int prod_val, int cons_val);
void *generate_producers_threads();
void *generate_consumers_threads();
void increment_sem(int semid, int semidx);
void decrement_sem(int semid, int semidx);