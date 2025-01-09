#ifndef __NewtonInterpolator__
#define __NewtonInterpolator__

#include<iostream>
#include "DataPoints.h"
#include <vector>
#include <iomanip>
 
using namespace std;

class NewtonInterpolator : public DataPoints{

	public:
	NewtonInterpolator(unsigned int=0, const double* x=nullptr, const double* y=nullptr, const TF1* fF0=nullptr);
	~NewtonInterpolator();
	NewtonInterpolator(const NewtonInterpolator&);
	double Interpolate(double) const;
	double DiffTable(int, int) const;
	const TF1& GetInterpolationFunction() const { return * FInterpolator; }
	void SetResolution(int n=200) const { FInterpolator->SetNpx(n); }
	void Draw() const;
	const TCanvas& GetCanvas();
	void SetFunction(const TF1*);

	friend std::ostream& operator<< (std::ostream&, const NewtonInterpolator&);

	protected:
 	TF1* F0; // underlying function
    TF1* FInterpolator; // interpolator function
    TCanvas* cInterpolator;
    double fInterpolator(double *fx, double *par)  {
     return Interpolate(fx[0]);
    }
};

#endif