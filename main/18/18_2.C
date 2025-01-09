#include <cstdio>
#include <iostream>
using namespace std; 

//Funcao que imprime o traco de uma matriz quadrada (soma dos elementos da diagonal principal)
void trace(int **m, int n){

	double traco = 0;

	for (int i = 0; i < n; i++){

		traco += m[i][i];				//Quando a linha e coluna coincidirem significa que é um dos elementos do traco

	}	
	
	printf("Traço Da Matriz:%.0lf\n", traco);  	  //Imprimir traco

}

//Funcao que imprime uma linha i da matriz mxn
void array_i(int **matriz, int i, int n){

	int *linha = new int [n];

	for(int j = 0; j < n; j++){

		linha[j] = matriz[i][j];

	}

	for(int k = 0; k < n; k++)
		printf("%d ", linha[k]);
}


//Funcao que imprime a multiplicacao de uma matriz axb por outra matriz bxc
void mult_matriz(int **m, int **v, int a, int b, int c){

	int** resultado = new int *[a];
	
		for (int i = 0; i < a; ++i)
  		  resultado[i] = new int[c];	

	int elemento;

	for (int i1 = 0; i1 < a ; i1++)
		for(int j1 = 0; j1 < c; j1++ ){
			resultado[i1][j1] = 0; 
			for (int k = 0; k < b; k++)
				resultado[i1][j1] += m[i1][j1] * v[j1][k]; 
		}


	//Imprimir C++
	cout << "Resuldado da Multiplicacao:" << endl;
	for(int i = 0; i < a; ++i)
	{
		for(int j = 0; j < c; ++j)
		{
			cout << resultado[i][j] << " ";
			if(j == c - 1)
				cout << endl << endl;
		}
	}

	//Imprimir C
	for(int i2 = 0; i2 < a; i2++){
		
		printf("\n");

		for (int j2 = 0; j2 < c; j2++)
			printf("%d ", resultado[i2][j2]);
	}
}

int main(){

	double trac;
	int n, n1, n2, n3, n4, n5;
	int l;

	//Alinea a)
	//Pedir n da matriz n*n //fiz com cout porque é mais facil do que scanf
	cout<<"Qual o nr de colunas e linhas que pretende para a matriz nxn: ";
    cin >> n;

    int** m1 = new int*[n];

    	for (int i = 0; i < n; ++i){
  		 
  		  m1[i] = new int[n];

		}

    //Pedir elementos da matriz
	cout << "\nIntroduza os elementros da matriz nxn: \n";
	for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin>>m1[i][j];

    trace(m1, n);

    //Free da matriz
    if (n) delete [] m1[0];
		delete [] m1;

	//Alinea b)
	//Pedir m da matriz m*n 
	cout<<"Qual o nr de linhas (m) que pretende para a matriz mxn: ";
    cin >> n1;

    //Pedir n da matriz m*n 
    cout<<"Qual o nr de colunas (n) que pretende para a matriz mxn: ";
    cin >> n2;

    int** m2 = new int *[n1];
		for (int i = 0; i < n1; ++i)
  		  m2[i] = new int[n2];	


    //Pedir elementos da matriz mxn
	cout << "\nIntroduza os elementros da matriz mxn: \n";
    for(int i = 0; i < n1; i++)
        for(int j = 0; j < n2; j++)
            cin>>m2[i][j];

    //Pedir linha da matriz que pretende imprimir
  	cout<<"Qual a linha da matriz que pretende imprimir: ";
    cin >> l;

    array_i(m2, l - 1, n2);

    if (n1) delete [] m2[0];
	delete [] m2;

    //Alinea c)
	//Pedir m da matriz1 m*n 
	cout<<"\nMultiplicar 2 matrizes: Qual o nr de linhas que pretende para a matriz_1 mxn: ";
    cin >> n3;

    //Pedir n da matriz1 m*n 
    cout<<"\n Multiplicar 2 matrizes: Qual o nr de linhas que pretende para a matriz_2 mxn: ";
    cin >> n4;

    int** m3 = new int *[n3];
		for (int i = 0; i < n3; ++i)
  		  m3[i] = new int[n4];	


    //Pedir elementos da matriz mxn
	cout << "\nIntroduza os elementros da matriz mxn: \n ";
    for(int i = 0; i < n3; i++)
        for(int j = 0; j < n4; j++)
            cin>>m3[i][j];

    //Pedir n da matriz mxn 
    cout<<"Multiplicacao de 2 matrizes: Sendo que o nr de linhas terá de corresponder ao nr de colunas da Matriz_1 Qual o nr de colunas que pretende para a Matriz_2 mxn:";
    cin >> n5;

    int** m4 = new int *[n4];
		for (int i = 0; i < n4; ++i)
  		  m4[i] = new int[n5];	


    //Pedir elementos da matriz mxn
	cout << "\nIntroduza os elementros da matriz_2 mxn: \n";
    for(int i = 0; i < n4; i++)
        for(int j = 0; j < n5; j++)
            cin>>m4[i][j];

    mult_matriz(m3, m4, n3, n4, n5);
	
	if (n3) delete [] m3[0];
	delete [] m3;

	if (n4) delete [] m4[0];
	delete [] m4;

    return 0;          
}




