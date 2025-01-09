	#include <cstdio> 
	#include <iostream>


	#ifndef __WIN32                 // Para colorir o printf caso não-Windows
	#define    RED "\x1b[1;31m"
	#define    GRN "\x1b[1;32m"
	#define    YEL "\x1b[1;33m"
	#define    BLU "\x1b[1;34m"
	#define    MGN "\x1b[1;35m"
	#define    CYN "\x1b[1;36m"
	#define    WHT "\x1b[1;37m"
	#define    NRM "\x1b[0m"
	#else                           // No caso de Windows ignorar códigos das cores
	#define    RED ""
	#define    GRN ""
	#define    YEL ""
	#define    BLU ""
	#define    MGN ""
	#define    CYN ""
	#define    WHT ""
	#define    NRM ""
	#endif

void limpar_stdin (void)
{
// Esta função limpa todo o stdin

    while ( getchar() != '\n' );
}


void recolher_input_utilizador (int *a)
{
// Esta função recolhe o input do utilizador (inteiros) e guarda-os em &n1 e &n2

    int i;      // variavel que guarda qtd de leituras com sucesso do scanf

    do{
        printf("Indique o valor A (inteiro): ");
        i = scanf ("%d", a);
        limpar_stdin();
    } while ( i != 1 );
}

double fatorial(int a){

	int i;
	double fat = 1.0;

	for(i = a; i > 0; i--){
		fat *= i;
	}

	return fat;

}

int main (int argc, char **argv){
	int a;
	double fat;
 	
 	printf("\n");
    printf("#############################################################################\n");
    printf("# Nome: Fatorial                                                            #\n");
    printf("# Syntax: <nome programa> <nrint1> <nrint2>                                 #\n");
    printf("# Data: 01-Oct-2020                                                         #\n");
    printf("# Por:                                                                      #\n");
    printf("#     André Esteves            #196509                                      #\n");
    printf("#     Juna Santos              #196549                                      #\n");
    printf("# Descrição:                                                                #\n");
    printf("#     Este programa calcula a soma dos quadrados entre 2 nrs                #\n");
    printf("# introduzidos pelo utilizador .                                            #\n");
    printf("#############################################################################\n\n");

    // Testes iniciais de leitura
    if ((argc != 2) || (sscanf (argv[1], "%d", &a) != 1 ))
    {
     
        printf (YEL"\n   Syntax: %s <A> \n\n", argv[0]);
        recolher_input_utilizador (&a);
    }

    if(a < 0){
    	recolher_input_utilizador (&a);
    }


    fat = fatorial(a);

    printf(CYN "Fatorial de %d: %.0lf\n", a, fat);

    return 0;
	}






