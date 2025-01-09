	#include <cstdio>    //printf
	#include <iostream> //cout
	#include <cstdlib>  //exit, rand, getchar
	#include <cmath>    //sin, cos
    #include <ctime>    //time
    using namespace std;


void Mmultiply(double **mx, double *vr, int n, int m, double *pt){ //n linhas, m colunas

	for (int i = 0; i < n ; i++){
		pt[i] = 0; 
		for (int j = 0; j < m; j++){
			pt[i] += mx[i][j] * vr[j]; 
		}
	}
			

	//Imprimir vetor resultado

	cout<<"\nvetor resultado:\n";
	for(int i = 0; i < n; i++){
		printf(" %2.lf \n", pt[i]);
	}

	cout << "\n";
}

int main (){
	int n,m;

	//Pedir m da matriz m*n 
	cout<<"Qual o nr de linhas (n) que pretende para a matriz nxm: ";
    cin >> n;

    //Pedir n da matriz m*n 
    cout<<"Qual o nr de colunas (m) que pretende para a matriz nxm: ";
    cin >> m;

    //matriz nxm
    double** mx = new double *[n];
		for (int i = 0; i < n; ++i)
  		  mx[i] = new double[m];

  	//Pedir elementos da matriz nxm
	printf("\nIntroduza os elementros da matriz %dx%d: \n",n,m);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin>>mx[i][j];	

	//vetor coluna (nr de linhas igual ao numero de colunas da matriz nxm)
	double *vr = new double [m];


	printf("\nIntroduza os elementos do vetor coluna vr \n(nr linhas = %d = nr de colunas da matriz %dx%d inserida): \n",m,n,m);
    for(int i = 0; i < m; i++)
            cin>>vr[i];	

	//vetor resultado
	double *pt = new double [n];

	//chamar funçao multiplicação da matriz nxm pelo vetor coluna (vr)
	Mmultiply(mx,vr,n,m,pt);

	if (n) delete [] mx[0];
	delete [] mx;

	return 0;
}