#include <cstdio>
#include <cstdlib>
#include <cmath>

#define G 9.8

void limpar_stdin(void){

	while( getchar() != '\n');

}

int recolher_input_utilizador (void){

	int i;
	double h;		//altura indicada pelo utilizador, tempo

	do{
		printf("Indique a que altura deseja deixar cair a massa: (sair:0)");
		i = scanf("%lf", &h);
		limpar_stdin();

	}while( i != 1 || h < 0);

	return h;
}

int main(int argc, char **argv){

	double h, t;

	//testes de leitura
	if((argc != 2) || (sscanf (argv[1], "%lf", &h) != 1)){

		printf("\n Syntax: %s <Altura H>\n", argv[0]);
		h = recolher_input_utilizador();
	}

	//Validaçao dos valores lidos
	if(h == 0){
		return 0;
	}

	t = sqrt(h / (G / 2));

	printf("Tempo de queda: %lf\n", t);
	
	return 0;
	
}