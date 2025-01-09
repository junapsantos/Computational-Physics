#ifndef __IntegratorMC__
#define __IntegratorMC__

#include "Integrator.h"
#include "TFormula.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TF1.h"
#include "TH1.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "THStack.h"
#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;


class IntegratorMC : public Integrator {

	public:
	IntegratorMC() = default;
	IntegratorMC(TF1& f); 
	IntegratorMC(TF1* f);
	IntegratorMC(IntegratorMC& MC);
	IntegratorMC(double inicio, double final, TF1& f);
	IntegratorMC(double inicio, double final, TF1* f);
	IntegratorMC(double* xbeg, double* xend, TFormula* tf = NULL, int M = 1);
    //IntegratorMC(double inicio, double final, int NSamples);
    ~IntegratorMC() = default;
    int GetN();
    void IntegralMC(double inicio, double final, int NSamples, double& res, double& err);
	void SetBoundaries(double inicio, double final);
	void SetIntegrandFunction(TF1*);
	void UniformRandom(double &res, double &err, int nsamples);
	void UniformRandom(double inicio, double final, double &res, double &erro, int NSamples);
	void UniformRandom_Multiplo(double &res, double &err, int NSamples);
	void ImportanceSampling(int N, double& value, double& error, const TF1& px, const TF1& xy);
	static void  RandomGen(TF1& px, TF1& xy);
	void AcceptanceRejection(int NSamples, double& result, double& error);
	
	private:
	int NSamp; 
	TF1* F;
	double x;
	double y;
	//para integrais multiplos
	double *x0;
	double *x1;
	int dim;
	TFormula* TForm;
};

#endif
