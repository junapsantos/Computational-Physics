#include "pessoa_2.h"	
#include "alunoIST.h"
#include <iostream>
#include <string>

using namespace std;

alunoIST::alunoIST(int numero, string curso){
 	this->number = numero;
 	this->branch = curso;
  	cout << __PRETTY_FUNCTION__ << "\n";
}

alunoIST::~alunoIST(){
	cout << __PRETTY_FUNCTION__ << "\n";
}

void alunoIST::SetNumber(int numero){
	this->number = numero;
	cout << __PRETTY_FUNCTION__ << "\n";
}

void alunoIST::SetBranch(string curso){
	this->branch = curso;
	cout << __PRETTY_FUNCTION__ << "\n";
}

int alunoIST::GetNumber(){
	int numero;
	numero = this->number;
	cout << __PRETTY_FUNCTION__ << "\n";

	return numero;
}

string alunoIST::GetBranch(){
	string curso;
	curso = this->branch;
	cout << __PRETTY_FUNCTION__ << "\n";

	return curso;
}

void alunoIST::Print(){
	cout << this->number << "\n" << this->branch << "\n";  
	cout << __PRETTY_FUNCTION__ << "\n";
}