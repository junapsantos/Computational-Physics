#ifndef __FCmatrixFull__
#define __FCmatrixFull__

#include "FCmatrix.h"
#include "Vec.h" 
#include <cmath>
using namespace std;

class FCmatrixFull : public FCmatrix
{ 
public:
	// constructors
    FCmatrixFull();                                 //Default Full Constructor
    ~FCmatrixFull();                                //Destructor

    FCmatrixFull(double**, int, int);     			//matrix m rows x n columns given from pointer of pointers
    FCmatrixFull(double*, int, int);       			//matrix m rows x n columns given as single pointer
    
    FCmatrixFull(vector<Vec>);                      //matrix m rows x n columns given as vector of Vec, by reference
    FCmatrixFull(const FCmatrixFull &);             //Copy Constructor
    
    // operators
    Vec& operator[](int);                           //get a row by giving index inside []
    Vec  operator[] (int) const;
    												//FUNCIONAM OS 2: equal 2 matrices of any kind
	//FCmatrixFull &operator=(const FCmatrix &);      //EU QUE FIZ! 
	void operator=(const FCmatrix&);				//BAROON QUE FEZ!!

	FCmatrixFull operator+(const FCmatrix &) const; //add 2 matrices of any kind
	FCmatrixFull operator-(const FCmatrix &) const; //sub 2 matrices of any kind
	    
	FCmatrixFull operator*(const FCmatrix &)const;  //mul 2 matrices of any kind
	FCmatrixFull operator*(double) const;   	    //mul matrix of any kind by scalar
	Vec operator*(const Vec &)const;                //mul matrix by Vec
    
    //methods
    int GetRowN() const;                           //number of rows of M
    int GetColN() const;                           //number of columns of M
    string GetName() const;                         //retrieve name
    
    Vec GetRow(int) const;                          //retrieve row i
    Vec GetCol(int) const;                        //retrieve column i
    
    
    int GetRowMax(int);                		//in row-i, return column-index of max element (in absolute value)
    int GetColMax(int);                 		//in column-i, return row-index of max element (in absolute value)
    	
    double Determinant() const;                     //calculate determinant    
    //FCmatrixFull matrizcofatores(const FCmatrixFull &, int);
    FCmatrixFull getInverse (const FCmatrixFull& ) ;
    FCmatrixFull getTranspose(const FCmatrixFull& );
    FCmatrixFull getCofactor(const FCmatrixFull& );
    void swapRows(int, int);                        //swap 2 given rows in the matrix

    void Print() const;                             		//prints the matrix

    friend FCmatrixFull operator*(double, const FCmatrixFull&);        //m = d.m1
    //friend methods
 	friend std::ostream& operator<<(std::ostream&, const FCmatrixFull& ); // NAO FUNCIONA

};
#endif