#include <TF1.h>
#include "TFile.h"			 //criar e escrever num ficheiro
#include "TH1F.h"			 //histogramas
#include "TCanvas.h"		 //canvas
#include <iostream>	
#include <cstdlib>		 
#include <tgmath.h>		   	 //exponecial
#include <math.h>			 //PI
#include <time.h>		     //gerar nrs aleatórios
#include <random>
#include <TRandom.h>
#include <TH2.h>
#include "PixelDet.h"

using namespace std;

/*void PrintHisto(TH2C* htwoD){
	cout << "Impressão do Histograma" << htwoD -> GetName() << endl;

	for(int bin = 0; bin < htwoD -> GetNbinsX() + 2; bin ++){
		if(bin == 0) cout << "Underflow:";
		if(bin == htwoD -> GetNbinsX() + 1) cout << "Overflow:";
		double content = htwoD -> GetBinContent(bin);
		cout << "content[" << bin << "] = " << content << endl;
	}

	cout << endl;
}*/
// PixelDet::PixelDet(){
// 	h = new TH2C("h", "2D Histograma", 100, 0.0, 20.0, 100, 0.0, 20.0);
// 	cout << __PRETTY_FUNCTION__ << endl;
// }

PixelDet::PixelDet(TH2C *hist){
	pixel_min = 0;
	pixel_max = 50.;
	N_pixel_side = 100;

	cout << __PRETTY_FUNCTION__ << endl;
	if (h != nullptr)
		h = hist;
	else
		h = new TH2C("h", "2D Histograma", 100, 0.0, 20.0, 100, 0.0, 20.0);
}

int PixelDet::EventNoise(float probability){

	int n = 0;

	//TH2C* htwoD = new TH2C("htwoD", "2D Histograma", 100, 0.0, 20.0, 100, 0.0, 20.0);

	for(int i = 0; i < 1000; i++){

		if( (rand() % 100) < probability) {
			h -> Fill( gRandom -> Uniform(0.0,20.0), gRandom -> Uniform(0.0,20.0)); 
			n = n + 1;
		}
	}

	//h -> Draw("colz");

	cout << "Numero de Pixeis Ativos:" << n << endl;

	return n;	
}

int PixelDet::EventSignal(float a_0[2], float signal){

	int n = 0;

	a[0] = a_0[0];
	a[1] = a_0[1];

	//TH2C* h = new TH2C("h", "2D Histograma", 100, 0.0, 20.0, 100, 0.0, 20.0);

	/*for(int i = 0; i < 1000; i++){

		if( (rand() % 100) < .5) {
		htwoD -> Fill( gRandom -> Uniform(0.0,20.0), gRandom -> Uniform(0.0,20.0)); 
		n = n + 1;
		}
	}*/

	for(int i = 0; i < signal; i++){

		h -> Fill( gRandom -> Uniform(a[0] - 2.0, a[0] + 2.0), gRandom -> Uniform(a[1] - 2.0, a[1] + 2.0)); 
		n = n + 1;
	}

	//htwoD -> Draw("colz");

	cout << "Numero de Pixeis Ativos: " << n << endl;

	//PrintHisto(htwoD);

	return n;	
}

void PixelDet::DrawEvent(){

	h -> Draw("col");

}