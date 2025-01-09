#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <memory>
#include "header.h"


int main() {

	int *a_1 = fintv_1(100);
	//double *a_2 = fdoublev_1(100);

	// retornar uma matriz de inteiros de dimensão 100x50 inicializados a 1
	int **a_3 = fintv_2(100,50);
	// retornar um tensor de double de dimensão 100x50x20 inicializados a 5.
	double ***v = fdoublev_2(100, 50, 20);
	double ***a_5 = fdoublev_2(100, 50);


	print( v, 100, 50, 20);

	return 0;

	//nao estão a aceitar a funçao free!! Acho que só pertence a c++, tenho de aprender a usar delete[]
	for(int i; i < 100; i++){

		for(int j; j < 100; j++){

			for(int k; k < 100; k++){

				free (v[i][j][k]);
			}
		}
	}

}