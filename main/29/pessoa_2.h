#ifndef __pessoa__
#define __pessoa__

#include <string>
#include <iostream>
using namespace std;

class pessoa {

 	public:

 		pessoa(string s="Trombinhas", unsigned int x=27092001); //constructor (nome aluno, data nascimento)
 		~pessoa();

 		void SetName(string);             //set name

 		void SetBornDate(unsigned int);	  //set nascimento

 		string GetName();				  //get name

 		unsigned int GetBornDate();		  //get nascimento

 		virtual void Print();   		  //print

 	private:
 		string nome;
 		unsigned int DataAni;

};

#endif