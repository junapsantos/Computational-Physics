#ifndef __FCmatrix__
#define __FCmatrix__

#include "Vec.h" 
#include <vector>
#include <iostream>
using namespace std;

class FCmatrix {
public:
	FCmatrix();								 //Default Constructor
	~FCmatrix();							 //Destructor

	FCmatrix(double**, int , int);     		 //matrix m rows x n columns given from pointer of pointers
	FCmatrix(double*, int, int);

	FCmatrix(vector<Vec>);			//matrix m rows x n columns given as vector of Vec, by reference
	FCmatrix(FCmatrix&);			//Copy Constructor

	// operators
	virtual Vec &operator[](int) = 0;           //get a row by giving index inside []
	virtual Vec operator[](int) const = 0;      //para mudar o valor de um elemento da matriz (este operador, nesta classe, acessa ao vec i da matriz; dentro da classe Vec há outro operador [] que acessa à posição i do vec)

	// methods
	virtual string GetName() const = 0;
	virtual int GetRowN() const = 0; 					//number of m rows of M
	virtual int GetColN() const = 0; 					//number of n columns of M 

	virtual Vec GetRow(int) const = 0;        		//return row i
	virtual Vec GetCol(int) const = 0;     		    //return column i

	//virtual double Determinant() = 0;

	// row max element index
	virtual int GetRowMax(int) = 0;
	// row max element index (scaled by s, from j on)
	virtual int GetColMax(int) = 0;

	virtual void swapRows(int, int)=0;    //swap 2 given rows in the matrix

	virtual void Print() const;


	

protected:
	vector<Vec> M;
	string classname;
};

#endif