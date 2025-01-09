#include "turma.h"

using namespace std;

int main(){

	int a, b;
	alunoIST *aluno;

	Turma T;

	Turma T_1("C2", 7);

	alunoIST *aluno_1 = new alunoIST[1];
	aluno_1 -> SetName("Juna");
	aluno_1 -> SetBornDate(15082001);
	aluno_1 -> SetNumber(96549);
	aluno_1 -> SetBranch("MEFT");

	alunoIST *aluno_2 = new alunoIST[1];
	aluno_2 -> SetName("Andre");
	aluno_2 -> SetBornDate(24112001);
	aluno_2 -> SetNumber(96509);
	aluno_2 -> SetBranch("MEFT");

	alunoIST *aluno_3 = new alunoIST[1];
	aluno_3 -> SetName("Inês");
	aluno_3 -> SetBornDate(00062001);
	aluno_3 -> SetNumber(96535);
	aluno_3 -> SetBranch("MEFT");

	alunoIST *aluno_4 = new alunoIST[1];
	aluno_4 -> SetName("Rui");
	aluno_4 -> SetBornDate(00012001);
	aluno_4 -> SetNumber(96565);
	aluno_4 -> SetBranch("MEFT");

	alunoIST *aluno_5 = new alunoIST[1];
	aluno_5 -> SetName("Pedro");
	aluno_5 -> SetBornDate(00002001);
	aluno_5 -> SetNumber(96561);
	aluno_5 -> SetBranch("MEFT");

	alunoIST *aluno_6 = new alunoIST[1];
	aluno_6 -> SetName("Carolina");
	aluno_6 -> SetBornDate(00002001);
	aluno_6 -> SetNumber(96500);
	aluno_6 -> SetBranch("MEFT");

	alunoIST *aluno_7 = new alunoIST[1];
	aluno_7 -> SetName("Trombinhas");
	aluno_7 -> SetBornDate(20112001);
	aluno_7 -> SetNumber(00000);
	aluno_7 -> SetBranch("MEFT");

	T_1.AddAluno(aluno_1);
	T_1.AddAluno(aluno_2);
	T_1.AddAluno(aluno_3);
	T_1.AddAluno(aluno_4);
	T_1.AddAluno(aluno_5);
	T_1.AddAluno(aluno_6);
	T_1.AddAluno(aluno_7);


	T.AddAluno(aluno_7);

	aluno = T_1.FindAluno(96565);


	//aluno -> Print(); (Estou com problemas no print)
	

	Turma T_2(T_1); //CPY

	a = T_1.GetNalunos();

	b = T_1.GetN();

	cout << "Nalunos: " << a << "\n N: " << b << endl;

	delete[] aluno;

	return 0;
}