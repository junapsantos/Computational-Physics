#include "pessoa_2.h"	
#include <iostream>
#include <string>

using namespace std;

pessoa** Pessoa(int N){

	pessoa** P = new pessoa* [N];
	for(int i = 0; i < N; i++){
		P[i] = new pessoa();
	}
	
	return P;
}

int main(){

	int N = 10;

	pessoa** P_0 = Pessoa(N);
	pessoa P[N];

	P[0].SetName("Juna");
	P[0].SetBornDate(15082001);

	cout<<"\n///////Imprimir a partir da pessoa, usando as funções Get////////\n"<<endl;

	string       s = P[0].GetName();
	unsigned int x = P[0].GetBornDate();

	cout<<"Nome: "<<s<<"\nData Nascimento: "<<x<<endl;

	cout<<"\n///////Imprimir a partir do array de pessoas////////\n"<<endl;

	P_0[0][0]=P[0];  

	P_0[0] -> Print(); //imprimir a partir do array de pessoas

	cout<<"\n///////Definir a 2ª pessoa do array////////\n"<<endl;

	P[1].SetName("André");
	P[1].SetBornDate(25112001);

	P_0[1][0]=P[1];

	cout<<"\n///////Imprimir todas as pessoas do array de 10 pessoas////////\n"<<endl;

	for(int i=0;i<N;i++){
		cout<<"\n"<<i+1<<"ªpessoa:"<<endl; 
		P_0[i] -> Print(); //a partir da 3ªpessoa é a pessoa do constructor default
	}


	for(int i = 0; i < N; i++)  //Destruição dos ponteiros do array gerado
      {
        delete P_0[i];
      }
    delete []P_0;

    return 0;
}