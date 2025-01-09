#include "pessoa_2.h"
#include "alunoIST.h"	
#include <iostream>
#include <string>

using namespace std;

//////////array Pessoas (igual ao 28)///////
pessoa** Pessoas(int N){ 

	pessoa** P = new pessoa* [N];
	for(int i = 0; i < N; i++){
		P[i] = new pessoa();
	}
	
	return P;
}

//////////array AlunosIST///////
alunoIST** AlunosIST(int N){ 
	alunoIST** IST = new alunoIST* [N];
	for(int i = 0; i < N; i++){
		IST[i] = new alunoIST();
	}
	return IST;
}

//////////Função Dummy///////
void Dummy(pessoa**P, const int N){
	cout<<"\n////////Imprimir "<<N<<" pessoas (Print() da class pessoa)///////\n"<<endl;
	for(int i=0; i<N; i++){
		cout<<"Pessoa "<<i+1<<":"<<endl;
		P[i]->Print();
		cout<<"\n"<<endl;
	}
}

int main(){

	int N =15; //eu queria imprimir 69, porque foi o nr de alunos de MEFT19/20, mas ficava muito grande a correr, portanto escolhi 15 porque é o dia que a juna faz anos

	alunoIST** MEFT1920 = AlunosIST(N);
	alunoIST A[N];

	cout<<"\n///////Criar um aluno e imprimir a partir do array de alunosIST////////\n"<<endl;
	alunoIST A0(96500, "MEFT1920");
	A[0]=A0;
	MEFT1920[0][0]=A[0];
	MEFT1920[0]-> Print();

	cout<<"\n///////Imprimir um aluno default a partir do array de alunosIST////////\n"<<endl;
	alunoIST A1;
	A[1]=A1;
	MEFT1920[1][0]=A[1];
	MEFT1920[1]-> Print();


	cout<<"\n///////Criar outro aluno, com as funções Set, e imprimir a partir do array de alunosIST////////\n"<<endl;
	A[2].SetNumber(96502);
	A[2].SetBranch("MEFT1920");
	MEFT1920[2][0]=A[2];
	MEFT1920[2]-> Print();

	cout<<"\n///////Imprimir os 69 alunos a partir do array de alunosIST////////\n"<<endl;

	for (int i=3; i<N;i++){ //definir o numero de cada um dos alunos com o incremento de 1
		MEFT1920[i][0].SetNumber(96500+i);
	}

	for(int i=0; i<N; i++){
		cout<<"Aluno IST "<<i+1<<":"<<endl;
		MEFT1920[i]->Print();
		cout<<"\n"<<endl;
	}

	///////Imprimir as 69 pessoas a partir do array de pessoas, com a função Dummy///////
	pessoa** P=Pessoas(N);
	Dummy(P,N);


	for(int i=0; i<N; i++)
		delete MEFT1920[i];
	delete[] MEFT1920;

	for(int i=0; i<N; i++)
		delete P[i];
	delete[] P;

return 0;
}