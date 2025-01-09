#ifndef __FCmatrixAlgorithm__
#define __FCmatrixAlgorithm__


#include "FCmatrix.h"
#include "Vec.h" 
#include <cmath>
using namespace std;


class FCmatrixAlgorithm 
{ public:
	/*
    Gauss Elimination
    - it can receive a simple matrix
    - linear system: augmented matrix (A | b)
  */

  static void GaussElimination(FCmatrix&);

  /*
    Gauss Elimination with pivoting
    - it can receive a simple matrix
    - linear system: augmented matrix (A | b)
    - return: (A | b | Index)
  */

  //static void GaussEliminationPivot(FCmatrix&);

 // static void LUdecomposition(FCmatrix&);
private:
};
#endif