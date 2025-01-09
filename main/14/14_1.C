#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "header.h"


int main() {

	int *a_1 = fintv_1(100);
	double *a_2 = fdoublev_1(100);

	// retornar uma matriz de inteiros de dimensão 100x50 inicializados a 1
	int **a_3 = fintv_2(100,50);
	// retornar um tensor de double de dimensão 100x50x20 inicializados a 5.
	double ***a_4 = fdoublev_2(100, 50, 20);
	double ***a_5 = fdoublev_2(100, 50);

}

