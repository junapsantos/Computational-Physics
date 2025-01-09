#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cmath>

#define MAX 55
#define MIN 5

int main(){

	int i; // variavel temporaria
	double x, y, soma, valor_medio; //variavel
	double v_x[1000], v_y[1000];


	srand(time(NULL)); // iniciar srand

	//Gerar valores aleatorios e guardar num vetor
	for (i = 0; i < 1000; i++){
		x = ((double) rand()) / ((double) RAND_MAX) * (MAX - MIN + 1); //valor aleatorio [0, 50]
		x += MIN;								//valor aleatorio [5,55]
		v_x[i] = x;							//guardar valores
		y = (x / (x - 10));
		v_y[i] = y;
		soma += x;
	}


	valor_medio = (soma / 1000);

	for (i = 0; i < 1000; i++){
		printf("x = %lf\n", v_x[i]);
		printf ("y = %lf\n", v_y[i]);
		printf("Desvio Padrao: %lf\n", fabs(valor_medio - v_x[i]));
	}

	printf("Valor Medio: %lf\n", valor_medio);


	return 0;
}