#ifndef __EqSolver__
#define __EqSolver__

#include <iostream>
#include "FCmatrixFull.h"
#include "FCmatrix.h"
#include "Vec.h" 
#include "FCmatrixAlgorithm.h"
#include <vector>
#include <cstdio>

class EqSolver {
public:
  EqSolver();
  ~EqSolver();
  EqSolver( const FCmatrixFull&, const Vec&); // matriz M e vector de constantes B
  // set
  void SetConstants(const Vec&);
  void SetMatrix(const FCmatrixFull&);
  //eliminação de Gauss:
  //resolução do sistema pelo método de eliminação de Gauss
  Vec GaussEliminationSolver();
  Vec LUdecompositionSolver();
  void Print();

private:
  //decomposição LU com |L|=1
  void LUdecomposition(FCmatrixFull&, vector<int>& index);
  /* return triangular matrix and changed vector of constants */
  void GaussElimination(FCmatrixFull&, Vec&);
  FCmatrixFull M1;
  FCmatrixFull* M ; //matriz de coeffs
  Vec b; //vector de constantes
};

#endif