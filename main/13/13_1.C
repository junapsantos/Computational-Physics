	#include <cstdio> 
	#include <iostream>
	#include <cstdlib>
	#include <cmath>

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
        printf("Indique o valor do período (T), em segundos: ");
        i = scanf ("%d", a);
        limpar_stdin();
    } while ( i != 1 );
}



int main (int argc, char **argv)
{
	int a;
	double R=6371, G=6.67E-11, M=5.97E24, h;

if ((argc != 2) || (sscanf (argv[1], "%d", &a) != 1 ))
    {
        printf ("\n   Syntax: %s <T> \n\n", argv[0]);
        recolher_input_utilizador (&a);
    }

if(a < 0)
	{
    	recolher_input_utilizador (&a);
    }

h=(pow((G*M*a*a)/(4*M_PI*M_PI),1/3)-R)*1000;
printf("O valor de h é %lf\n",h );

    return 0;
}

