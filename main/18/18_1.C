#include <cstdio>
#include <iostream>
using namespace std; 

//Funcao que retorna o traco de uma matriz quadrada (soma dos elementos da diagonal principal)
//Escolhi 50 para valor max de linhas e colunas
double trace(int **m, int n1){

	double traco = 0;

	for (int i = 0; i < n1; i++){

		traco += m[i][i];						//Quando a linha e coluna coincidirem significa que é um dos elementos do traco

	}	

	return traco;
}

int main(){

	double trac;
	int n;

	//Pedir n da matriz n*n //fiz com cout porque é mais facil do que scanf
	cout<<"Qual o nr de colunas e linha pretende para a matriz nxn: ";
    cin >> n;

    int** m = new int*[n];
		for (int i = 0; i < n; ++i){
  		  m[i] = new int[n];
		}

    //Pedir elementos da matriz
	cout << "\nIntroduza os elementros da matriz n*n: \n";
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin>>m[i][j];

    trac = trace(m, 2);
    
    printf("Traço Da Matriz:%.0lf\n", trac);  	  //Imprimir traco

    //Free da matriz
    if (n) delete [] m[0];
		delete [] m;

	//Confirmar que fiz delete dos valores da matriz
	printf("%d\n", **m);
    return 0;          
}