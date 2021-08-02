//Multiplicacion de matrices usando n hilos
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct Var{
	int inicio;
	int final;
}Var;

int **MatrizA, **MatrizB, **MatrizC;
int FilasA, ColumnasA, FilasB, ColumnasB, NHilos;

void *Hilos(void *);

int main(int argc, char *argv[]){
	int i, j, k, NF, FR;
	
	
	if(argc != 6){
		printf("Error: El numero de parametros ingresados no es el correcto\n\n");
		return -1;
	}

	FilasA = atoi(argv[1]);
	ColumnasA = atoi(argv[2]);
	FilasB = atoi(argv[3]);
	ColumnasB = atoi(argv[4]);
	NHilos = atoi(argv[5]);

	if(ColumnasA != FilasB){
		printf("Error: no se pueden multiplicar\n");
		printf("El numero de filas de la Matriz A es mayor al numero de filas de la Matriz B\n\n");
		return -1;
	}
	if(ColumnasA < NHilos){
		printf("Error: no se pueden multiplicar\n");
		printf("El numero de columnas de la Matriz A es mayor al numero de Hilos\n\n");
		return -1;
	}
	//Crear de forma dinamica las matrices A, B, C
	//Llenarlas con valores aleatorios con valores entre 0 y 5 (A y B)

	pthread_t* tid = (pthread_t *)malloc(NHilos*sizeof(pthread_t));
	//Matriz A
	MatrizA = (int **)malloc(FilasA*sizeof(int*));
	for(i = 0; i < FilasA; i++)
		MatrizA[i]=(int*)malloc(ColumnasA*sizeof(int));
	
	if(MatrizA == NULL){
		printf("\nError: No hay suficiente espacio en memoria\n\n");
		return -1;
	}

	for(i = 0; i < FilasA; i++)
		for(j = 0; j < ColumnasA; j++)
			MatrizA[i][j] = rand()%6;

	//Matriz B
	MatrizB = (int **)malloc(FilasB*sizeof(int *));
	for(i = 0; i < FilasB; i++)
		MatrizB[i]=(int *)malloc(ColumnasB*sizeof(int));
	
	if(MatrizB == NULL){
		printf("\nError: No hay suficiente espacio en memoria\n\n");
		return -1;
	}

	for(i = 0; i < FilasB; i++)
		for(j = 0; j < ColumnasB; j++)
			MatrizB[i][j] = rand()%6;
	
	//Impresion de ambas matrices
	printf("Matriz A:\n");
	for(i = 0; i < FilasA; i++){
		for(j = 0; j < ColumnasA; j++)
			printf("%i ", MatrizA[i][j]);
		printf("\n");
	}
	printf("\nMatriz B:\n");
	for(i = 0; i < FilasB; i++){
		for(j = 0; j < ColumnasB; j++)
			printf("%i ", MatrizB[i][j]);
		printf("\n");
	}




	//Creacion de los hilos
	//Que informacion debemos enviarle a cada hilo para que pueda resolver una parte de la matriz?
	printf("\nMatriz C:\n");

	NF = FilasA / NHilos;
	FR = FilasA % NHilos;
	//pthread_create(&MatrizA[i][j], NULL, Hilos, (void*)val);

	for(i = 0; i < NHilos; i++){
		Var* Argu=(Var*)malloc(sizeof(Var));
		Argu->inicio = (i * (NF - 1 ))+ i;
		Argu->final = Argu->inicio + (NF -1);
		//Condicion para validar el valor a FR, si es > 0    -> Se debe agregar a uno de los hilos
		//ejemplo: FR = 2, distribuir una fila a cada hilo
		pthread_create(&tid[i], NULL, Hilos, (void*)Argu);
	}

	for(i = 0; i < NHilos; i++){
		pthread_join(tid[i], NULL);
	}
	/*
	for(i = 0; i < FilasA; i++){
		for(j = 0; j < ColumnasB; j++)
			printf(" %i ", MatrizC[i][j]);
		printf("\n"); 
	}

	for(j = 0; j < ColumnasA; j++)
		free (MatrizA[j]);
	free(MatrizA);

	for(j = 0; j < ColumnasB; j++)
		free (MatrizB[j]);
	free(MatrizB);*/
	return -1;
}

void *Hilos(void *Argu){ 
	int i, j, k;
	Var *Aux = (Var *)Argu;

	printf("\n%i\n", Aux->inicio);
	printf("%i\n", Aux->final);

	for(i = Aux->inicio; i < Aux->final; i++){
		for(j = 0; j < ColumnasB; j++){
			MatrizC[i][j] = 0;
			for(k = 0; k < ColumnasA; k++){
				MatrizC[i][j] += MatrizA[i][k] * MatrizB[k][j];
			}
		}
	}
}
