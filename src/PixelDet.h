#include <TF1.h>
#include "TFile.h"			 //criar e escrever num ficheiro
#include "TH1F.h"			 //histogramas
#include "TCanvas.h"		 //canvas
#include <iostream>			 
#include <tgmath.h>		   	 //exponecial
#include <math.h>			 //PI
#include <time.h>		     //gerar nrs aleatórios

using namespace std;

// Bool_t = true ou false 
class PixelDet {

public:
	//PixelDet();
	PixelDet(TH2C* hist = nullptr);
	~PixelDet() = default;
	int EventSignal(float *a_0, float = 10.0);
	int EventNoise(float = 0.5);
	void DrawEvent();

private:
	float a[2];
	float signal;
	TH2C* h;

	float pixel_min, pixel_max;
	int N_pixel_side;
};