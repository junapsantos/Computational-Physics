#include "Integrator.h"
#include "IntegratorMC.h"
#include "ODEsolver.h"
#include "movimento.h"

#include "TMath.h"
#include "TApplication.h"
#include "TH1.h"
#include "TRandom.h"
#include "TObject.h"
#include "TPad.h"
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TF1.h"
#include "TFile.h"			 //criar e escrever num ficheiro
#include "TH1F.h"			 //histogramas
#include "TCanvas.h"
#include "TH2.h"		 //canvas

#include <stdexcept>
#include <cstdio>
#include <cmath>
#include <math.h> 
#include <iostream>
#include <iomanip>
#include <utility>
#include <complex>
#include <vector>

//Foi utilizado um step de 10^-2
using namespace std;

int main(){
	
	int N=100;
	double d=1.;
	double v0=0.;
	double t0=0;
	double step=1e-2;
	double range_min= -1 * 1e-17;
	double range_max= 1 * 1e1;
	double t_max = 50;
	int nr_estados = 5000;

 	double** m = new double* [N];
 	for(int i = 0; i < N; i++)
 		m[i] = new double[2*N+3];    //mx[0] - t //mx[1] - r //mx[2] -v
 	
 	int aux;
 	double gaveta; 
	
	m[0][0] = 0; //t
	m[0][1] = 6 + (0%10);
	m[0][2] = 6 + (0/10.);
	aux = 2;
	for(int j=3;j<2*N; j+=2)//x's sao impares
		if( 0!=(j-aux) ){
			m[0][j]  = 6 + ((j-aux)%10);
			aux++;
		} 
	aux = 2;
	for(int j=4;j<2*N+1; j+=2)//y's sao pares
		if(0!=(j-aux-1)) {
			m[0][j]  = 6 + ((j-aux-1)/10.);  
			aux++;
		}

	m[0][2*N + 1]  = 0; //vx
	m[0][2*N + 2]  = 0; //vy

	int j=0;
	for (int i=0;i<N-1;i++){
		j=2*i+3;
		m[i+1][0] = 0;
		for(int j=1;j<2*N+1;j++){
			m[i+1][j]=m[0][j];
			m[i+1][j+1]=m[0][j+1];
		}
		if(m[i+1][1]==m[0][1] && m[i+1][2]==m[0][2]){
			gaveta=m[i+1][j];
			m[i+1][j]=m[i+1][1];
			m[i+1][1]=gaveta;
			gaveta=m[i+1][j+1];
			m[i+1][j+1]=m[i+1][2];
			m[i+1][2]=gaveta;
		}
		m[i+1][2*N+1]=0.;
		m[i+1][2*N+2]=0.;
	}

 	movimento MOV(m, step, t_max);
 	cout << "_______________________________________________________2a)_________________________________________________\n" << endl;
 	/////// Localização Das Particulas em t = 0 //////////////////
    TCanvas *c4 = new TCanvas("canvas_sistema", "canvas_sistema", 600,400);
	c4->SetGrid();
	
	double* x= new double [N];
	double* y= new double [N];

	for(int i=0; i<N; i++){
	  x[i]=6 + (i%10);
	  y[i]=6 + (i/10);
	}

	TGraph* Posicao_Inicial= new TGraph(N, x, y); 
	Posicao_Inicial -> SetMarkerStyle(8);
	Posicao_Inicial -> SetMarkerSize(0.5);
	Posicao_Inicial -> SetMarkerColor(kBlue);
	Posicao_Inicial -> SetTitle("Sistema Inicial");
  	Posicao_Inicial -> GetXaxis()->SetTitle("X");
  	Posicao_Inicial -> GetYaxis()->SetTitle("Y");
	//Posicao_Inicial -> GetYaxis()->SetRangeUser(0, 22);
	//Posicao_Inicial -> GetXaxis()->SetLimits(0,22);

    Posicao_Inicial -> Draw("AP");
    Posicao_Inicial -> GetYaxis()->SetRangeUser(0, 22);
	Posicao_Inicial -> GetXaxis()->SetLimits(0,22); 

    c4->Modified();                  //sem os nomes dos graficos
	c4 -> SaveAs("trab03_2a_sistema_inicial.pdf");

 	double M = 6.69 * pow(10, -26);

 	double *E_Total_aux = new double[nr_estados];
	double *EREL = new double[nr_estados];
	double *Temperatura = new double[nr_estados];
	double *T = new double[nr_estados];

	Temperatura = MOV.GetTemperatura();
	E_Total_aux = MOV.GetE_Total();
	EREL =  MOV.GetE_REL();
	T = MOV.GetT();


	//TCanvas *cc = new TCanvas("c", "E_Total & Variacao Relativa Energia", 0, 0, 800, 1000);

	TCanvas *cc1 = new TCanvas("c", "E_Total", 0, 0,1500 , 700);

	//TCanvas *cc2 = new TCanvas("c", "Variacao Relativa Energia", 0, 0, 800, 1000);


	TGraph* grp1 = new TGraph();

	 	for(int i = 0; i < nr_estados; i++)
   			grp1->SetPoint(i,T[i], E_Total_aux[i]*M);
   
   	cc1 -> cd();
	cc1 -> Divide(2, 1, 0.03, 0.03, 0 );
	cc1 -> cd(1); 

   	grp1->SetMarkerColor(kOrange+7);
  	grp1->SetMarkerStyle(39);
    grp1->SetTitle("E_Total");
    grp1 -> GetXaxis()->SetTitle("t");
    grp1 -> GetYaxis()->SetTitle("E(J)");
    grp1 -> GetYaxis()->SetRangeUser(-4e-18, 3e-18);
    grp1 -> GetXaxis()->SetLimits(0,50);
    grp1->Draw("AP");
    //cc1->SaveAs("trab03_2a_E_Total.pdf");	  //guardar em pdf

    TGraph* grp = new TGraph();
	 	for(int i = 0; i < nr_estados; i++)
   			grp->SetPoint(i,T[i], EREL[i]);

   	cc1->cd(2); 
   	grp->SetMarkerColor(kViolet+4);
  	grp->SetMarkerStyle(2);
    grp->SetTitle("Variacao Relativa Energia");
    grp -> GetXaxis()->SetTitle("t");
    grp -> GetYaxis()->SetTitle("*");
    grp -> GetXaxis()->SetLimits(0,50);
    grp->Draw("AP");
    cc1->SaveAs("trab03_2a_energiatotal.pdf");	  //guardar em pdf

    cout << "O Sistema conserva a sua Energia total a cerca de -1E-18 J. É possivel verificar no pdf - trab03_2a_energiatotal.pdf\n" << endl;
   


	TCanvas *c3 = new TCanvas("c1","A Simple Graph Example",200,10,500,300);
    Double_t c[nr_estados], dd[nr_estados];
    for (Int_t i=0;i<nr_estados;i++) {
      c[i] = T[i];
      dd[i] = Temperatura[i];
    }

    TGraph* gr2 = new TGraph(nr_estados,c, dd);
    gr2 -> SetMarkerStyle(3);
    gr2 -> SetMarkerSize(0.2);
	gr2 -> SetMarkerColor(kRed+1);
	gr2 -> SetTitle("Temperatura");
  	gr2 -> GetXaxis()->SetTitle("t");
  	gr2 -> GetYaxis()->SetTitle("T");
	gr2 -> GetYaxis()->SetRangeUser(0, 1000);
	gr2 -> GetXaxis()->SetLimits(0, t_max); 
	gr2 -> Draw("AP");
	c3  -> Modified();
	c3  -> SaveAs("trab03_2a_temperatura.pdf");



	double *Desvio = new double[100];
	Desvio = MOV.Get_Desvio();


	TCanvas *ca = new TCanvas("ca","A Simple Graph Example",200,10,500,300);
    Double_t a_0[nr_estados], a_1[nr_estados];
    for (Int_t i = 0;i < N; i++) {
      a_0[i] = i;
      a_1[i] = Desvio[i];
    }

    TGraph* gr3 = new TGraph(nr_estados,a_0, a_1);
    gr3 -> SetMarkerStyle(1);
    gr3 -> SetMarkerSize(10);
	gr3 -> SetMarkerColor(kRed);
	gr3 -> SetTitle("Desvio Quadratico Medio");
  	gr3 -> GetXaxis()->SetTitle("N");
  	gr3 -> GetYaxis()->SetTitle("D^2");
	gr3 -> GetYaxis()->SetRangeUser(0, 1);
	gr3 -> GetXaxis()->SetLimits(0, N); 
	gr3 -> Draw("AP");
	ca  -> Modified();
	ca  -> SaveAs("trab03_2a_desvioquadratico.pdf");

	cout << "O Sistema demora cerca t = 35 para atingir o equilibro. É possivel verificar no pdf - trab03_2a_temperatura\n" << endl;
    

	TCanvas *c5 = new TCanvas("canvas_sistema", "canvas_sistema", 600,400);
	c5->SetGrid();
	
	double* x2= new double [N];
	double* y2= new double [N];

	x2=MOV.GetPOS_X_EM_T(45); 
	y2=MOV.GetPOS_Y_EM_T(45);

	TGraph* Posicao_Equilibrio= new TGraph(N, x2, y2); 

	Posicao_Equilibrio -> SetMarkerStyle(8);
	Posicao_Equilibrio -> SetMarkerSize(0.5);
	Posicao_Equilibrio -> SetMarkerColor(kBlue);
	Posicao_Equilibrio -> SetTitle("Sistema em equilibrio");
  	Posicao_Equilibrio -> GetXaxis()->SetTitle("X");
  	Posicao_Equilibrio -> GetYaxis()->SetTitle("Y");
	//Posicao_Equilibrio -> GetYaxis()->SetRangeUser(0, 22);
	//Posicao_Equilibrio -> GetXaxis()->SetLimits(0,22); 
    Posicao_Equilibrio -> Draw("AP");
    Posicao_Equilibrio -> GetYaxis()->SetRangeUser(0, 22);
	Posicao_Equilibrio -> GetXaxis()->SetLimits(0,22); 

    c5->Modified();                  //sem os nomes dos graficos
	c5 -> SaveAs("trab03_2a_sistema_equilibrio.pdf");

	cout << "Uma vez que o t de equilibrio, referido anteriormente, é apenas uma estimativa, neste plot, consideramos a posição das particulas em t=45, pois temos a certeza que o sistema se encontra na posição de equilibrio. É possivel verificar no pdf - trab03_2a_energiatotal.pdf\n" << endl;



////////////////////////////////////////////////////// 2 b) //////////////////////////////////////////////////////////////
	int Temp = 45; //T quando sistema entra em equilibrio
	double k = 1.380649 * pow(10, -23);
	double v;


////////////////////////////////////////////////////// 2 b) //////////////////////////////////////////////////////////////
	cout << "_______________________________________________________2b)_________________________________________________\n" << endl;
 	
	TF1* F = new TF1("Distribuicao_Maxwell_Boltzman", "4*[0]*pow([1]/(2*[0]*[2]*[3]), 1.5)*x*x*TMath::Exp((-0.5*[1]*x*x)/([2]*[3]))", 0, 350);
	F -> SetParameter(0, M_PI);
	F -> SetParameter(1, M);
	F -> SetParameter(2, k);
	F -> SetParameter(3, Temp);
	F -> Draw("AL");
	F -> SetLineColor(kRed+1);
	F -> SetTitle("Funcao MB");


////////////ROOT
	Func1D funcaoMB(F);


	TGraph* grafic_funcaoMB  = new TGraph(funcaoMB.GetFunc());
	grafic_funcaoMB -> Draw("AL");
	grafic_funcaoMB -> SetLineColor(kRed+1);
	grafic_funcaoMB -> SetTitle("Funcao MB");
	grafic_funcaoMB -> GetXaxis()->SetTitle("v");
    grafic_funcaoMB -> GetYaxis()->SetTitle("dP/dv");

	//c6->Modified();  
  	//c6->SaveAs("trab03_2b_MB.pdf");	  //guardar em pdf

  	TCanvas *c7 = new TCanvas("c6", "funcaoMB", 0, 0, 900, 600);



  	double* velocidades= new double [100];
  	velocidades=MOV.GetVEL_EM_T(45);

  	int nbins=20;
  	double* limits= new double[nbins+1];
  	int * values = new int [nbins]{0};
  	

  	double vel_max, vel_min;
  	for (int i=0; i<99; i++){
  		vel_max= velocidades[i];
  		vel_min=velocidades[i];

  		if(velocidades[i+1]>vel_max)
  			vel_max= velocidades[i+1];

  		if(velocidades[i+1]<vel_min)
  			vel_min=velocidades[i+1];
  	}

  	double step3= (vel_max-vel_min)/(double)nbins;
  	double step2=(vel_max-vel_min)/1000.;

  	for (int i =0; i<nbins+1 ;i++) 
  		limits[i]=i*step3;
  	//TH1F* Hist = new TH1F("ola", "Distribuicao de Velocidades",20, 0, 350);
  	TH1F* Hist = new TH1F("ola", "Distribuicao de Velocidades",nbins, 0,350);
  	Hist->SetFillColor(kBlue+1);
  	

  	for (int i=0; i<100; i++){
  		for(int j=0; j<nbins;j++){
  			if(velocidades[i]>limits[j] && velocidades[i]< limits[j+1]){
  				values[j]++;
  				break;
  			}
  		}
    	
  	}

  	for(int j=0; j<nbins;j++){
  		Hist->Fill(limits[j], (double)values[j]/(step3*100));
  	}

  	//for (int i=0; i<100; i++)
  		//Hist->Fill(velocidades[i]);

  	Hist->Draw("Hist");
  	F->Draw("SAME");
  	c7->Modified();                  //sem os nomes dos graficos
  	c7->SaveAs("trab03_2b_MB.pdf");	  //guardar em pdf

    for(int j = 0; j < N; ++j) {
        delete[] m[j];   
    }
    //Free the array of pointers
    delete[] m;
    
    return 0;
    
}