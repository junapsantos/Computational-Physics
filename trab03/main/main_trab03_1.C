#include "Integrator.h"
#include "IntegratorMC.h"

#include "TObject.h"

#include "TPad.h"
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TF1.h"
#include "TFile.h"			 //criar e escrever num ficheiro
#include "TH1F.h"			 //histogramas
#include "TCanvas.h"		 //canvas

#include <stdexcept>
#include <iomanip>      // std::setprecision
#include <cstdio>
#include <cmath>
#include <math.h> 
#include <iostream>
#include <utility>
#include <complex>
#include <vector>
#include <limits>
 
using namespace std;
//numeric_limits<double>::max()
//4*[0]*pow([1]/(2*[0]*[2]*[3]), 3/2)*x*x*
int main(){ 
//////////////////////////////////////// alinea a) ////////////////////////////////////////////////////////////////////////////
	int T = 300.;
	double k = 0.2478*0.001;
	double v;
	int nsamples;
	double erro = 0.01;
	double valor_integral;
	double xmin = 0.;
	double xmax = 10000.;


	TF1* F = new TF1("Distribuicao_Maxwell_Boltzman", "4*[0]*pow([1]/(2*[0]*[2]), 1.5)*x*x*TMath::Exp((-0.5*[1]*x*x)/[2])", xmin, xmax);
	F -> SetParameter(0, M_PI);
	F -> SetParameter(1, k);
	F -> SetParameter(2, T);

////////////ROOT
	Func1D funcaoMB(F);
	//funcaoMB.Draw();
	TCanvas *c = new TCanvas("c", "funcaoMB", 0, 0, 900, 600);

	TGraph* grafic_funcaoMB  = new TGraph(funcaoMB.GetFunc());
	grafic_funcaoMB -> Draw("AL");
	grafic_funcaoMB -> SetTitle("Funcao MB");
	grafic_funcaoMB -> GetXaxis()->SetTitle("v");
    grafic_funcaoMB -> GetYaxis()->SetTitle("dP/dv");

	c->Modified();  
  	c->SaveAs("trab03_1a.pdf");	  //guardar em pdf


	IntegratorMC MC(xmin, xmax, F);
	Integrator I(xmin, xmax, F);

	double Integral=0.;
	double Error=0.01;

//////////////////ROMBERG
	cout<<"\n//// Romberg - Alínea_a/////"<<endl;
	int j=1;
	while(fabs(Error/Integral)>1e-3){
		I.Romberg(j+1, Integral, Error);
		j++;
	}

	cout<<"\nOrdem de Integração: "<<j;
	cout<<"\nNúmero de fatias: "<<pow(2,j);
	cout << setprecision(8) << fixed;
	cout<<"\nIntegral: "<<Integral<<"\nErro: "<<Error/Integral<<endl;

/*//////////OUTROS METODOS
	I.Trapezoidal(30, Integral, Error);
	cout<<"\n//// Trapézio /////\nIntegral: "<<Integral<<"\nErro: "<<Error<<endl;
	 
	I.TrapezoidalAdaptive(Integral, Error);
	cout<<"\n//// Trapézio Adaptável /////\nIntegral: "<<Integral<<"\nErro: "<<Error<<endl;

	Error=2.;
	int i=1;
	while(fabs(Error)>1e-3){
		I.Simpson(i, Integral, Error);
		i++;
	}
	cout<<"\nN: "<<i<<endl;
	cout << setprecision(5) << fixed<<endl;
	cout<<"\n//// Simpson /////\nIntegral: " <<Integral<<"\nErro: " << Error <<endl;
*/

//////////////////MONTE CARLO

	/*Error=0.1;
	int i=1;
	Integral = 0;

	while(fabs(Error/Integral) > 1e-3){
		MC.UniformRandom(Integral, Error, i);
		i++;
	}

	cout<<"\n//// Método UniformRandom-MC - Alínea_a/////"<<endl;
  	cout << "\nIntegral: " << Integral << "\nErro = " << Error/Integral << "NSampes" << i <<"\n";

  	/*double d = 1./(1 + (xmax-xmin)*(xmax-xmin));
  	TF1 p("p(x)", "[0]", xmin, xmax); //Função p(x)
    p.SetParameter(0, d);

    TF1 xofy("x(y)", "tan(x/[0] + atan(xmin))", xmin, xmax); //Função x(y)
    xofy.SetParameter(0, 1/(atan(xmax) - atan(xmin)));*/

  	/*auto p = [xmin, xmax](double* x, double* par) {
	return (1/(atan(xmax) - atan(xmin)))*(atan(x[0])- atan(xmin));
	};
	TF1 P("P", p, xmin, xmax, 0); // npar=0, ndim=1 (default)
	P.SetNpx(1000);

	auto pi = [xmin, xmax](double* x, double* par) {
	return  tan(x[0]/(1/(atan(xmax) - atan(xmin))) + atan(xmin));
	};

	TF1 PI("PI", pi, xmin, xmax, 0); // npar=0, ndim=1 (default)
	PI.SetNpx(1000);*/

  	auto p = [xmin, xmax](double* x, double* par) {
	return 1./(xmax-xmin);
	};
	TF1 P("P", p, xmin, xmax, 0); // npar=0, ndim=1 (default)
	TF1* P2=new TF1(P);
	P.SetNpx(1000);

	auto pi = [xmin, xmax](double* x, double* par) {
	return xmin + x[0]*(xmax - xmin);
	};
	TF1 PI("PI", pi, xmin, xmax, 0); // npar=0, ndim=1 (default)
	PI.SetNpx(1000);

	Error = 0.01;
	Integral = 0;
	j=2845000;
	while(Error>1e-3){
 		MC.ImportanceSampling(j ,Integral,Error, P, PI);
 		j++;
	}
 	cout<<"\n//// Método ImportanceSampling - MC - alinea a) /////"<<endl;
  	cout << "\nIntegral = " << Integral << "\nErro = " << Error/Integral <<  "\nNsamples = " << j << endl;


//////////////////////////////////////// alinea b) ////////////////////////////////////////////////////////////////////////////
 	
 	TF1* F1 = new TF1("Distribuicao_Maxwell_Boltzman", "4*[0]*pow([1]/(2*[0]*[2]), 1.5)*x*x*x*TMath::Exp((-0.5*[1]*x*x)/[2])", xmin, xmax);
	F1 -> SetParameter(0, M_PI);
	F1 -> SetParameter(1, k);
	F1 -> SetParameter(2, T);

	Func1D funcaovfv(F1);
	IntegratorMC MC1(xmin, xmax, F1);

////////////////// UNIFORM RANDOM

	MC1.UniformRandom(Integral, Error, 100000);
  	cout<<"\n//// Método UniformRandom - MC  - Alínea_b/////"<<endl;
  	cout << "\nIntegral: " << Integral << "\nErro = " << Error/Integral << "\n";

////////////////// IMPORTANCE SAMPLING

  	double error = 0.01;
  	Integral = 0;

  	j=2770000;
	while(fabs(error/Integral)>1e-3){
  		MC1.ImportanceSampling(j ,Integral,error, P, PI);
  		j+=100;
  	}
  	cout<<"\n//// Método ImportanceSampling -  - Alínea_b/////"<<endl;
 	cout << "\nIntegral = " << Integral << "\nErro = " << error/Integral <<  "\nNsamples = " << j << "\n";

////////////// ROMBERG

  	Integrator I1(xmin, xmax, F1);
	I1.Romberg(7, Integral, Error);
	cout << setprecision(8) << fixed<<endl;
	cout<<"\n//// Romberg  - Alínea_b/////\nIntegral: "<<Integral<<"\nErro: "<<Error/Integral<<endl;

////////ROOT
	TCanvas *c2 = new TCanvas("c2", "funcaovfv", 0, 0, 900, 500);

	TGraph* grafic_funcaovfv  = new TGraph(funcaovfv.GetFunc());
	grafic_funcaovfv -> SetTitle("funcaovfv");
	grafic_funcaovfv->SetLineColor(kRed);

	TGraph* grafic_pdf  = new TGraph(P2);
	grafic_pdf -> SetTitle("funcaopdf");
	grafic_pdf->SetLineColor(kGreen);

  	TMultiGraph *G2 = new TMultiGraph("cPoly", "Exercicio_1b");
  	G2 -> Add(grafic_funcaovfv, "AL");
  	G2 -> Add(grafic_pdf, "AL");
	G2 -> SetTitle("Exercicio_1b");
  	G2 -> GetXaxis()->SetTitle("v");
  	G2 -> GetYaxis()->SetTitle("<v>");

  	//G2 -> GetYaxis()->SetRangeUser(0, 3500);
	G2->Draw("AL");
	//G2->GetXaxis()->SetLimits(0,2.2); //por algum motivo isto so funciona com o eixo dos x, depois do draw

	c2->Modified();  
  	c2->SaveAs("trab03_1b.pdf");	  //guardar em pdf

//////////////////////////////////////// alinea c) ////////////////////////////////////////////////////////////////////////////
	Integral=0;
	xmax=1;

    Integral=0;
	xmax=1;
	while(Integral<0.95){
		I.SetRange(xmin,xmax);
		I.Romberg(7, Integral, Error);
		xmax+=0.05;
	}
	cout << setprecision(8) << fixed<<endl;
	cout<<"\n//// Romberg  - Alínea_c/////\nIntegral: " <<Integral<<"\nErro: " << Error/Integral; 
	cout<<"\nv0: "<<xmax<<"\nErro v0: "<<0.05/xmax<<endl;
	
	return 0;
}
