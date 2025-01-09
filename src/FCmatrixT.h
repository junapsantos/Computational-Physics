#ifndef __FCmatrixT__
#define __FCmatrixT__

#include "Vec.h" 
#include <vector>
#include <iostream>
using namespace std;

class FCmatrixT {

 public:

	// constructors
	FCmatrixT();                            //Default Constructor
	~FCmatrixT();							//Destructor

	FCmatrixT(double**, int, int); 			//matrix m rows x n columns given from pointer of pointers
	FCmatrixT(double*, int, int);           //matrix m rows x n columns given as single pointer  

	FCmatrixT(const vector<Vec>&);			//matrix m rows x n columns given as vector of Vec, by reference
	FCmatrixT(const FCmatrixT&);			//Copy Constructor

	// methods
	int GetRowN() const; 					//number of m rows of M
	int GetColN() const; 					//number of n columns of M 

	Vec GetRow(int) const;        		//return row i
	Vec GetCol(int) const;     		    //return column i

	Vec &operator[](int);           //get a row by giving index inside []
	Vec operator[](int) const;      //para mudar o valor de um elemento da matriz (este operador, nesta classe, acessa ao vec i da matriz; dentro da classe Vec há outro operador [] que acessa à posição i do vec)
 	
 	void operator=(const FCmatrixT&);
 	void Print() const;                 //print row by row 

 	//friend methods
 	//friend	ostream& operator << (ostream&, const FCmatrixT& ); //INVENÇÃO DO BAROON QUE NAO FUNCIONA


 private:
  int mrows;// nb of rows = vector.size()
  int ncols; // nb of columns = Vec.size() 
  vector<Vec> M; //the matrix is a vector of Vec objects...
  
};

#endif