#ifndef Derivator_H
#define Derivator_H

#include "Func1D.h"
#include <math.h>

class Derivator : public Func1D{

public:

    Derivator(TF1* fp=nullptr): Func1D(fp){}; 	   //Default Constructor
    ~Derivator()= default; 					   	   //Destructor

    double Deriv_1(double x0, double h, int type);  //1ª Derivada
    double Deriv_2(double x0, double h, int type);  //2ª Derivada
    double Deriv_3(double x0, double h, int type);  //3ª Derivada

};
#endif