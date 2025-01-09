#ifndef Integrator_H
#define Integrator_H

#include "Derivator.h"
#include <cmath>
 
class Integrator: public Func1D {

 public:

  // construtors and destructor 
  Integrator(double fx0=0., double fx1=1., const TF1 *fp=nullptr) : x0(fx0), x1(fx1), Func1D(fp) {};

  Integrator(double fx0, double fx1, const TF1& fp) : Integrator(fx0, fx1, &fp) {};  

  ~Integrator() = default;
 
  // integrator methods
  /*
    n ............. number of slices (input)
    Integral ...... integral value by reference (input/output)
    error ......... error value by reference (input/output)
  */
  
  void SetRange(double, double);

  void Trapezoidal(int n, double& Integral, double& Error);

  void TrapezoidalAdaptive(double& Integral, double& Error);

  void Simpson(int n, double& Integral, double& Error);
  
  void Romberg(int n, double& Integral, double& Error);
  
protected:
  double x0; // function range for integration
  double x1;
};

#endif