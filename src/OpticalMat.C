#include "TROOT.h"
#include "TF1.h"       //funcoes
#include "TFile.h"       //criar e escrever num ficheiro
#include "TCanvas.h"     //canvas
#include "TGraph.h"      //graficos
#include "TFrame.h"
#include "TH1F.h"

#include <cstdio>
#include <iostream> 
#include <string>
#include <vector>
#include <utility>
using namespace std;

#include "Material.h"
#include "OpticalMat.h"

// construtor

OpticalMat::OpticalMat( vector<pair<float,float>> v, string fname, double fdens, TF1* ff) : Material(fname, fdens), f(ff) {
  RefIndex = v;
  if (!f) {
    f = new TF1("f", this, &OpticalMat::FitRefIndex, 0.1, 0.8, 5); // 5 params
  }
  cout << __PRETTY_FUNCTION__ << "\n";
}

// destructor
OpticalMat::~OpticalMat() {
  delete f;
}



void OpticalMat::DrawRefIndexPoints(){ //draw points
  TCanvas *c1 = new TCanvas("graph1", "Graph1", 600, 400); //Criação dos canvas
  c1->SetGrid();
  int n = RefIndex.size();
//////////metodo 1//////////
/*  Double_t x[n], y[n];

   for (Int_t i=0;i<n;i++) {
     x[i] = RefIndex[i].first;
     y[i] = RefIndex[i].second;
   }
  TGraph* gr1 = new TGraph(n,x,y);
*/
//////////metodo 2////////////
  TGraph* gr1  = new TGraph();

  for(int i = 0; i < n; i++){
    gr1->SetPoint(i, RefIndex[i].first, RefIndex[i].second);
  }
/////////////////////////////

  gr1->SetMarkerColor(kBlue);
  gr1->SetMarkerStyle(21);
  gr1->Draw();
  c1->SaveAs("draw_graph1.pdf");
}

void OpticalMat::DrawFitRefIndex(){ //draw points and function
  TCanvas *c2 = new TCanvas("graph2", "Graph2", 600, 400); //Criação dos canvas
  c2->SetGrid();
  int n = RefIndex.size();

  TGraph* gr2  = new TGraph(); //metodo 2 referido acima, para criar pontos do grafico

  for(int i = 0; i < n; i++){
    gr2->SetPoint(i, RefIndex[i].first, RefIndex[i].second);
  }

  gr2->Fit("f","R");
  gr2->SetMarkerColor(kBlue);
  gr2->SetMarkerStyle(21);
  c2 -> cd();     //ir para canvas 
  gr2->Draw();
  c2->SaveAs("draw_graph2_fit.pdf");
}

void OpticalMat::SetRefIndex(vector<pair<float,float>> v){
  this->RefIndex = v;
  cout << __PRETTY_FUNCTION__ << "\n";
}

vector<pair<float,float> > OpticalMat::GetRefIndex(){
  vector<pair<float,float> >  v;
  v = this->RefIndex;
  cout << __PRETTY_FUNCTION__ << "\n";
  return v;
}

void OpticalMat::SetFitRefIndex(TF1*ff){ //provide function to be fitted through TF1
  this->f = ff;
  cout << __PRETTY_FUNCTION__ << "\n";
}

TF1* OpticalMat::GetFitRefIndex(){ //return TF1 pointer to fit function
  TF1* ff;
  ff = this->f;
  cout << __PRETTY_FUNCTION__ << "\n";
  return ff;
}



void OpticalMat::Print(){
  Material::Print();
  int n = RefIndex.size();
  cout<<"Comprimento de onda(μm)      Index  "<< name <<endl;
  for(int i = 0; i < n; i++){
    cout << "  " << RefIndex[i].first << "                   "<< RefIndex[i].second << endl;
  }
}

 
// ref index functor
double OpticalMat:: FitRefIndex(double* x, double* par) {
  // parameters: A = par[0]
  //             B = par[1]
  //             C = par[2]
  //             D = par[3]
  //             E = par[4]
  // variable: x[0] = lambda (mu m)
  return par[0] + par[1]/(x[0]*x[0]-0.028) + par[2]/(x[0]*x[0]-0.028)/(x[0]*x[0]-0.028) + par[3]*x[0]*x[0] + par[4]*x[0]*x[0]*x[0]*x[0] ;
}


/*auto DataManip::GetDataVector(){
  auto dataVector;
  dataVector= this->V;
  cout << __PRETTY_FUNCTION__ << endl;
  return dataVector;
}*/
