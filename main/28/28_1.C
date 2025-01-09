#include "pessoa.h"	
#include <iostream>
#include <string>

using namespace std;

pessoa** Pessoa(int N){

	pessoa** P = new pessoa* [N];
	for(int i = 0; i < N; i++)
		P[i] = new pessoa [1];
	
	return P;
}

int main(){

	int N = 1;
	string s;
	unsigned int x;

	pessoa** P_0 = Pessoa(N);
	pessoa P[N];

	P[0].SetName("Juna");
	P[0].SetBornDate(15082001);

	P_0[0][0]=P[0];

	s = P[0].GetName();
	x = P[0].GetBornDate();

	P[0].Print(); 
	P_0[0] -> Print(); 

	for(int i = 0; i < N; i++)  //Destruição dos ponteiros do array gerado
      {
        delete []P_0[i];
      }
    delete []P_0;
}