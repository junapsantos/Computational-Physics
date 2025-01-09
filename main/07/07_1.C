
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


void recolher_input_utilizador (int *a, int *b)
{
// Esta função recolhe o input do utilizador (inteiros) e guarda-os em &n1 e &n2

    int i;      // variavel que guarda qtd de leituras com sucesso do scanf

    do{
        printf("Indique os valores A e B (inteiros): ");
        i = scanf ("%d %d", a, b);
        limpar_stdin();
    } while ( i != 2 );
}


int addnumbersS1 (int a, int b )
	{
	  int sum = 0;

	  for (int i = a; i <= b; i++)
	  {
	  	sum += i*i;
	  }

	  return sum;
	}

double addnumbersS2 (int a, int b )
	{
	  double sum = 0;

	  for (int i = a; i <= b; i++)
	  {
	  	sum += i*i;
	  }
	  return sum;
	}

<<<<<<< .mine
	int main (){
		int sumint,a,b,test;
||||||| .r27795
	int main (int argc){
		int sumint,a,b;
=======
	int main (int argc, char **argv){
		int sumint,a , b;
>>>>>>> .r27796
		double sumdobro;
 	
 	printf("\n");
    printf("#############################################################################\n");
    printf("# Nome: Funções para Strings                                                #\n");
    printf("# Syntax: <nome programa> <nrint1> <nrint2>                                 #\n");
    printf("# Data: 01-Oct-2020                                                         #\n");
    printf("# Por:                                                                      #\n");
    printf("#     André Esteves   #196509                                               #\n");
    printf("#     Juna Santos     #196549                                               #\n");
    printf("# Descrição:                                                                #\n");
    printf("#     Este programa calcula a soma dos quadrados entre 2 nrs                #\n");
    printf("# introduzidos pelo utilizador .                                            #\n");
    printf("#############################################################################\n\n");

<<<<<<< .mine
		test=scanf("%d %d", &a,&b);
||||||| .r27795
		scanf("%d %d", &a,&b);
=======
    // Testes iniciais de leitura
    if ((argc != 3) || (sscanf (argv[1], "%d", &a) != 1 ) || sscanf(argv[2], "%d", &b) != 1)
    {
     
        printf ("\n  RED Syntax: %s <A> <B>\n\n", argv[0]);
        recolher_input_utilizador (&a, &b);
    }
>>>>>>> .r27796

<<<<<<< .mine
		while (test!=2 || a<0 || b<0)
		{
			while(getchar()!=10);
   			printf("Insira 2 numeros inteiros!\n");
   			test=scanf("%d %d", &a,&b);
   		}
   		
||||||| .r27795
		while (argc!=3)
		{
		printf("ERRO!!! SYNTAX: <numero_inteiro(0-5000)> <numero_inteiro(0-5000)> \n");
		scanf("%d %d", &a,&b);
		
		}

=======
		sumint = addnumbersS1(a, b);

>>>>>>> .r27796
		sumdobro = addnumbersS2(a, b);
		printf("%d \n", sumint);
		printf("%lf \n", sumdobro);

		return 0;
	}

	