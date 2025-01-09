#ifndef __alunoIST__
#define __alunoIST__

#include"pessoa_2.h"
#include <string>
#include <iostream>
using namespace std;

class alunoIST : public pessoa {

 public: 

  alunoIST(int numero=96501, string curso="MEFT19/20"); //default constructor
  ~alunoIST();
  
  void SetNumber(int);       //set numero

  void SetBranch(string);	 //set curso

  int  GetNumber();			 //get numero

  string GetBranch();		 //get curso

  void Print();
  
 private:
  int number;
  string branch;
};
#endif
