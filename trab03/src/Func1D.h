#ifndef Func1D_H
#define Func1D_H

#include "TGraph.h"
#include "TApplication.h"
#include "TRootCanvas.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TStyle.h"
#include <cstdio>
using namespace std;

class Func1D {

 public:
  // constructor, destructor
  Func1D(const TF1* fp=nullptr);
  Func1D(const TF1&);
  virtual ~Func1D();

  // drawing
  void Draw() const;

  // evaluate
  double Eval(double) const;

  //more methods
  TF1* GetFunc() const; 	//Retorna a função associada
  void SetFunc(TF1*); 		//Altera a função associada
  
 protected:

  void Settings();
  
  TF1* f;
  
};

#endif