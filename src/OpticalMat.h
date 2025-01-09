#ifndef __OpticalMat__
#define __OpticalMat__
 
#include "TROOT.h"
#include "TF1.h"			 //funcoes
#include "TFile.h"			 //criar e escrever num ficheiro
#include "TCanvas.h"		 //canvas
#include "TGraph.h"			 //graficos

#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

#include "Material.h"

class OpticalMat : public Material {
public:

OpticalMat (string fname="", double fdens=0., TF1* ff=nullptr) : Material(fname, fdens), f(ff){;}

OpticalMat (vector<pair<float,float>> v, string fname="", double fdens=0., TF1* ff=nullptr);

~OpticalMat();

void SetRefIndex(vector<pair<float,float> >); //pair(wavelength, ref index)

vector<pair<float,float> > GetRefIndex();

void SetFitRefIndex(TF1*ff); //provide function to be fitted through TF1

TF1* GetFitRefIndex(); //return TF1 pointer to fit function

void DrawRefIndexPoints(); //draw points

void DrawFitRefIndex(); //draw points and function

void Print(); //define print for this class

private:
// method with the fit function
double FitRefIndex(double* x, double* par);
// we need to store the refractive index characteric of the material
vector<pair<float,float>> RefIndex;
// we need to store a TF1 pointer to the fit Ref Index function
TF1* f;
};

#endif