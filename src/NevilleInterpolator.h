#ifndef NevilleInterpolator_H
#define NevilleInterpolator_H

#include <iostream>
#include "DataPoints.h"
#include <vector>
#include <iomanip>
 
using namespace std;

class NevilleInterpolator : public DataPoints {

public:
	// constructors and destructor
	NevilleInterpolator(unsigned int N=0, const double *x=nullptr, const double *y=nullptr, const TF1* fF0=nullptr);
	~NevilleInterpolator();

	// copy constructor
	NevilleInterpolator(const NevilleInterpolator&);

	// interpolation methods
	double Interpolate(double) const;
    const TF1& GetInterpolationFunction() const { return *FInterpolator; }

	void SetResolution(int n=200) const { FInterpolator->SetNpx(n); } // deals with SetNpx method of TF1
    void Draw() const; //draw everything (points and interpolation function)
    
    const TCanvas& GetCanvas();
	
	 // underlying function
    void SetFunction(const TF1*);

	// output
	//void Print(string FILE="") const; // print results

friend ostream& operator<< (ostream&, const NevilleInterpolator&);

private:
	TF1* F0; //eventual underlying function
	TF1* FInterpolator; //interpolation function
	TCanvas* cInterpolator; // includes data points and curve

	double fInterpolator(double *fx, double *par) {return Interpolate(fx[0]);}
};

#endif