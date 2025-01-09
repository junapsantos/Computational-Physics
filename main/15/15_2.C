	#include <cstdio> 
	#include <iostream>
	#include <cstdlib>
	#include <cmath>
    #include <complex>

void limpar_stdin (void)// Esta função limpa todo o stdin
{ while ( getchar() != '\n' );}


void recolher_input_utilizador (double *a)// Esta função recolhe o input do utilizador (inteiros) e guarda-os em &n1 e &n2
{   int i;      // variavel que guarda qtd de leituras com sucesso do scanf
    do{
        printf("Indique o valor de x , em graus: ");
        i = scanf ("%lf", a);
        limpar_stdin();
    } while ( i != 1 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

double func1 (double x){
	double result;
	result= sqrt(fabs(sin(2*x)));
	return result;
}

void func2(double x, double& f){
	f=sqrt(fabs(sin(2*x)));	
}

void func3(const double x, const double* f){
	double result=*f;
	result=sqrt(fabs(sin(2*x)));	
}


int main (int argc, char **argv){
double res1, res2=1,res3=1, x;

if ((argc != 2) || (sscanf (argv[1], "%lf", &x) != 1 ))
    {
        printf ("\n   Syntax: %s <Graus> \n\n", argv[0]);
        recolher_input_utilizador (&x);
    }

    
res1= func1(x);
printf("res1: %lf\n",res1 );

func2(x,res2);
printf("res2: %lf\n",res2 );

func3(x, &res3);
printf("res3: %lf\n",res2 );

return 0;
}

