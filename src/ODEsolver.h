#ifndef ODESOLVER_H
#define ODESOLVER_H

#include "ODEPoint.h"

#include "TF1.h"

#include <cstdio>
using namespace std;

class ODEsolver {
 
public:
	ODEsolver();
	ODEsolver(const vector<TF1>&); 
	~ODEsolver(); //Destructor

	void SetODEfunc(const vector<TF1>&);
	TF1& GetODEfunc (int n); 

	vector<ODEPoint> Euler(ODEPoint iPoint, double step, double T);
	vector<ODEPoint> PredictorCorrector(ODEPoint iPoint, double step, double T);
	vector<ODEPoint> LeapFrog(ODEPoint iPoint, double step, double T);
	vector<ODEPoint> RK2(ODEPoint iPoint, double step, double T);
	vector<ODEPoint> RK4(ODEPoint iPoint, double step, double T);
	vector<ODEPoint> RK4_Projetil(ODEPoint iPoint, double step, double T, double* par);
	//vector<ODEPoint> LoopVerlet(ODEPoint iPoint, double step, double T);


private:
	vector<TF1> F; //Vector que contém as funções a serem utilizadas

};
#endif