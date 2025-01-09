#include "FCtools.h"
#include "Vec.h"

#include "TROOT.h" //Form()
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1D.h"

#include <cmath>
#include <iomanip> //setprecision()
#include <utility> //swap()
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> //stringstream
using namespace std;

double FCtools::RoundOffError(int i){// retorna o erro relativo de arredondamento de (float)sqrt(i) para (double)sqrt(i)
	if ( i < 0)
		throw invalid_argument(Form("[%s] sqrt requires i<=0\n", __PRETTY_FUNCTION__));
	float x = sqrt(i);
	double y = sqrt(i);
	double error = abs(y-(double)x) / y;
	//cout<<setprecision(8)<<x<<"  "<<y<<"  "<<error<<endl;
	return error;
}

TGraph* FCtools::RoundOffErrorG(int imin, int imax){//Um método que retorne um objecto TGraph cuja abcissa seja o valor de i e a ordenada o erro de arredondamento
	if ( imin< 0 || imax<0)
		throw invalid_argument(Form("[%s] sqrt requires i<=0\n", __PRETTY_FUNCTION__));
	if (imin > imax) std::swap(imax,imin);
	TCanvas *c1 = new TCanvas("c1","Graph Ref_Index", 600, 400);
	c1->SetGrid();
	TGraph* gr1  = new TGraph();

	for(int i = imin; i <=imax ; i++){
		gr1->SetPoint(i-imin, i,FCtools::RoundOffError(i));
    //std::cout << i << "  " << par_refi[i].first << "  " << par_refi[i].second << std::endl;
  }
  gr1->SetMarkerColor(kBlue);
  gr1->SetMarkerStyle(21);
  gr1->Draw();
  c1->SaveAs("RoundOffErrorG.pdf");
  return gr1;
}

TH1D* FCtools::RoundOffErrorH (int imin, int imax){
	if ( imin< 0 || imax<0)
		throw invalid_argument(Form("[%s] sqrt requires i<=0\n", __PRETTY_FUNCTION__));
	if (imin > imax) std::swap(imax,imin);
	TCanvas *c2 = new TCanvas("c1","Graph Ref_Index", 600, 400);
	c2->SetGrid();
	TH1D* h1 = new TH1D("histo1", "My First Histogram", 100000 /*bins*/, -1e-9, 1e-7);

	// filling the histogram
	for (int i = imin; i <= imax; i++)  
		h1->Fill(RoundOffError(i));

	h1->Draw();
	c2->SaveAs("RoundOffErrorH.pdf");
	return h1;

}


vector<string> FCtools::ReadFile2String(string filename){//file name, returns lines
	ifstream myfile(filename);
	if(!myfile)
		throw invalid_argument(Form("[%s] error opening file\n", __PRETTY_FUNCTION__));
	cout<<__PRETTY_FUNCTION__<<endl;

	vector <string> LineVector;
	string Line;
	while(getline(myfile,Line))
		if(Line!="")
			LineVector.push_back(Line);

	return LineVector;

}

vector<Vec> FCtools::ReadFile2Vec(string filename){
	cout<<__PRETTY_FUNCTION__<<endl;
	vector <string> LineVector;
	LineVector=FCtools::ReadFile2String(filename);
	vector<Vec> VV;

	//auxiliar
	double d;
	double a[LineVector.size()];
	int j=0;//columns read by line
	Vec V;

	for (int i=0; i<LineVector.size();i++)
	{
		istringstream ss(LineVector[i]);
		while(ss>>a[j])
			j++;
		V.SetEntries(j,a);
		VV.push_back(V);
		j=0;
	}
	return VV;
}

Vec* FCtools::ReadFile2Vecp(string filename, int& n){
	if(n<1)
		throw invalid_argument(Form("[%s] invalid argument...\n", __PRETTY_FUNCTION__));
	
	cout<<__PRETTY_FUNCTION__<<endl;
	vector <string> LineVector;
	LineVector=FCtools::ReadFile2String(filename);

	if(n>LineVector.size())
		throw invalid_argument(Form("[%s] invalid argument...\n", __PRETTY_FUNCTION__));

	Vec* V =new Vec[n];

	//auxiliar
	double a[LineVector.size()];
	int j=0;//columns read by line
	//cout<<"tou aqui2"<<endl;
	for (int i=0; i<n;i++)
	{
		istringstream ss(LineVector[i]);
		while(ss>>a[j])
			j++;
		V[i].SetEntries(j,a);
		j=0;
	}
	return V;
}

/* ESTOU A ESCOLHER N UTILIZAR ESTE METODO PQ CHAMA A ReadFile2Vec Q CHAMA A ReadFile2String E PARECE ME MEBIS EFICIENTE
Vec* FCtools::ReadFile2Vecp(string filename, int& n){
	if(n<1)
		throw invalid_argument(Form("[%s] invalid argument...\n", __PRETTY_FUNCTION__));
	cout<<__PRETTY_FUNCTION__<<endl;

	vector<Vec> VV = ReadFile2Vec(filename);
	Vec *V = new Vec[n];

	for (int i=0;i<n;i++)
		V[i]=VV[i];
	return V;
}*/
