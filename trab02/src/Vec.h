#ifndef __Vec__
#define __Vec__

#include <iomanip>
#include <cmath>
#include <vector>
#include <stdio.h>
#include <string>
#include <fstream> // ifstream
#include <sstream> // stringstream
#include <iostream> // ostream
#include <algorithm> 

class Vec {

 public:
  // constructors
  Vec(int i=0, double x=0); // Vec v;
  Vec(int i, const double*);
  Vec(const Vec&);

  //destructor
  ~Vec();
  void SetEntries(int n, double*); 
  double  operator[](int i) const;
  double& operator[](int i);

  //void operator=(const Vec&); // A=B
  Vec & operator= (const Vec &);
  const Vec& operator+=(const Vec&);
  Vec operator+(const Vec&);
  const Vec&  operator -=(const Vec&); 
  Vec operator -(const Vec&);
  Vec operator*(double); //Vec.operator*(double) <=> A*5.
  Vec operator*(const Vec&);
  Vec operator- ();
  Vec operator+();

  double *data();
  double dot(const Vec&); // double result = a.dot(b)
  void swap(int, int);
  int size() const;
  double sumAbs();
  double maxAbs(); // maximal abs(value) of Vec
  void Print();
  double At(int);

  //(...)
  /*
  the overloading of then * operator allows multiply a vector by a
  scalar:
  Vec * scalar
  */
  
  // friend methods
  friend std::ostream& operator<<(std::ostream&, const Vec&);
  /*
  in order to multiply a scalar to a vector (scalar*Vec) we need
  to implement a friend method:*/
  friend Vec operator*(double, const Vec&);
  
  
 private:
  int N; // number of elements
  double *entries; // array
  
};
#endif