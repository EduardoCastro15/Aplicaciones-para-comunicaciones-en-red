//Multiplicación de matrices usando n procesos
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

void Procesos(int** ,int** ,int ,int ,int ,int, int, int);

int main(int argc, char *argv[]){
	int i, j, k;
	int **MatrizA, **MatrizB;
	int FilasA, ColumnasA, FilasB, ColumnasB, NHilos;

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
		printf("El numero de columnas de la Matriz A es mayor al numero de Procesos\n\n");
		return -1;
	}
	//Crear de forma dinamica las matrices A, B, C
	//Llenarlas con valores aleatorios con valores entre 0 y 5 (A y B)

	//Matriz A
	MatrizA = (int **)malloc(FilasA*sizeof(int*));
	for(i = 0; i < FilasA; i++)
		MatrizA[i]=(int *)malloc(ColumnasA*sizeof(int));
	
	if(MatrizA == NULL){
		printf("\nError: No hay suficiente espacio en memoria\n\n");
		return -1;
	}

	for(i = 0; i < FilasA; i++)
		for(j = 0; j < ColumnasA; j++)
			MatrizA[i][j] = rand()%6;

	//Matriz B
	MatrizB = (int **)malloc(FilasB*sizeof(int*));
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

	//Creacion de los Procesos
	//Que informacion debemos enviarle a cada hilo para que pueda resolver una parte de la matriz?
	printf("\nMatriz C:\n");
	Procesos(MatrizA, MatrizB, FilasA, ColumnasA, FilasB, ColumnasB, NHilos, 0);

	for(j = 0; j < ColumnasA; j++)
		free (MatrizA[j]);
	free(MatrizA);

	for(j = 0; j < ColumnasB; j++)
		free (MatrizB[j]);
	free(MatrizB);
	return -1;
}

void Procesos(int **MatrizA, int **MatrizB, int FilasA, int ColumnasA, int FilasB, int ColumnasB, int NHilos, int Aux){
	int i, j, k, l, a, b, c=0, proceso, status, Next, Division;

	Division = (FilasA / NHilos);
	Next = Division;

	for(i = 0; i < NHilos; i++){
		proceso = fork();

		switch(proceso){
			case -1:
				perror("\nError al crear al hijo\n");
				break;
			case 0:
				for(j = Aux; j < Division; j++){
					for(k = 0; k < ColumnasB; k++){
						for(l = 0; l < ColumnasA; l++){
							c += MatrizA[j][l] * MatrizB[l][k];
						}
						printf("%i ", c);
						c=0;
					}
					printf("\n");
				}
				exit(0);
				break;
			default:
				Aux = Aux + Next;
				Division = Division + Next;
				if(i == NHilos-1)
					for(j = 0; j < NHilos; j++)
						wait(&status);
				break;
		}	
	}
}