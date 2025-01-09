#include "pessoa.h"
#include <iostream>
#include <string>
using namespace std;

pessoa::pessoa(string s, unsigned int x){
 	this->nome = s;
 	this->DataAni = x;
  	cout << __PRETTY_FUNCTION__ << "\n";
}

pessoa::~pessoa(){
	cout << __PRETTY_FUNCTION__ << "\n";
}

void pessoa::SetName(string s){
	this->nome = s;
	cout << __PRETTY_FUNCTION__ << "\n";
}

void pessoa::SetBornDate(unsigned int x){
	this->DataAni = x;
	cout << __PRETTY_FUNCTION__ << "\n";
}

string pessoa::GetName(){
	string s;
	s = this->nome;
	cout << __PRETTY_FUNCTION__ << "\n";

	return s;
}

unsigned int pessoa::GetBornDate(){
	unsigned int x;
	x = this->DataAni;
	cout << __PRETTY_FUNCTION__ << "\n";

	return x;
}

void pessoa::Print(){
	cout << this->nome << "\n" << this->DataAni << "\n";  
	cout << __PRETTY_FUNCTION__ << "\n";
}