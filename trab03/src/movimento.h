#ifndef __movimento__
#define __movimento__

#include <stdexcept>
#include <cstdio>
#include <cmath>
#include <math.h> 
#include <iostream>
#include <iomanip>
#include <utility>
#include <complex>
#include <vector>
#include "TH2F.h"			 //histogramas
#include "TCanvas.h"

#include "TObject.h"

#include "TPad.h"
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TF1.h"
#include "TFile.h"			 //criar e escrever num ficheiro
#include "TH1F.h"			 //histogramas
#include "TCanvas.h"		 //canvas

using namespace std;

class movimento {
	public:

	movimento(double **m, double step, double t_max); //
	~movimento(); //
	double* GetT();

	double* GetPOS_X_EM_T(int t);
	double* GetPOS_Y_EM_T(int t);

	double* GetVEL_X_EM_T(int t);
	double* GetVEL_Y_EM_T(int t);

	double* GetVEL_EM_T(int t);

	double** GetPOS_X();
	double** GetPOS_Y();
	double** GetVel_X(){ return Vel_X;};
	double** GetVel_Y(){ return Vel_Y;};
	double* GetKcin(){ return Kcin;};
	double* GetE_Total(){ return E_Total;};
	double* GetE_REL(){ return E_REL;};
	double* GetTemperatura(){ return TemperaturaT;};
	double* Get_Desvio(){ return desvio_quadratico;};

	private:

	double Step;
	double** Posicoes_X;
	double** Posicoes_Y;
	double** Vel_X;
	double** Vel_Y;
	double* t;
	double* Kcin;
	double* E_Total;
	double* E_REL;
	double* desvio_quadratico;
	double* TemperaturaT;
};

#endif