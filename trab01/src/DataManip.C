#include "DataReader.h"
#include "DataManip.h"

using namespace std;

bool sortbysecdesc(const pair<double,double> &a, const pair<double,double> &b)
{
       return a.second > b.second;
}

bool sortbysecasc(const pair<double,double> &a, const pair<double,double> &b)
{
       return a.second < b.second;
}

void PrintHisto(TH1F* h){
	cout << "Impressão do Histograma" << h -> GetName() << endl;

	for(int bin = 0; bin < h -> GetNbinsX() + 2; bin ++){

		if(bin == 0) cout << "Underflow:";
		if(bin == h -> GetNbinsX() + 1) cout << "Overflow:";
		double content = h -> GetBinContent(bin);
		cout << "Conteudo[" << bin << "] = " << content << endl;
	}

	cout << endl;
}

DataManip::~DataManip(){
	cout << __PRETTY_FUNCTION__ << endl;
}

vector<pair<double, double>> DataManip::GetDataVector(){

  vector<pair<double, double>> dataVector;
  dataVector= V;

  cout << __PRETTY_FUNCTION__ << endl;

  return dataVector;
}

TGraph* DataManip::GetDataGraph(){

	TCanvas *c1 = new TCanvas("GData", "GData", 600,400);
	c1 -> SetGrid();
	int n = V.size();

	TGraph* GData  = new TGraph(n);

	for(int i = 0; i < n; i++){
		GData -> SetPoint(i, V[i].first, V[i].second);
	}

	GData -> SetMarkerColor(kBlue+1);
	GData -> SetMarkerStyle(20);
	c1 -> cd();     //ir para canvas 
	GData -> Draw("AP");
	c1 -> SaveAs("GData.pdf");

	cout << __PRETTY_FUNCTION__ << endl;

	return GData;
}

vector<pair<double, double>> DataManip::GetDataVectorSorted(int order){

	vector<pair<double, double>> V_1;
	V_1 = V;

	if(order == 0){
		sort(V_1.begin(), V_1.end(), sortbysecdesc);
	}
	if(order == 1){
		sort(V_1.begin(), V_1.end(), sortbysecasc);
	}

	if(order > 1){
		cout << "ERRO! Insira: 0 - decrescente, 1 - crescente" << endl;
	}

	cout << __PRETTY_FUNCTION__ << endl;

	return V_1;
}

vector<pair<double, double>> DataManip::GetDataDerivativeVector(){

	int n = V.size();
	vector<pair<double, double>> V_1;

	vector<double> V_2, V_3, V_2_2, V_2_3 ;  //timer

 	for(int i=0; i<n; i++){
		V_2.push_back(V[i].first);
		V_2_3.push_back(V[i].first);
		V_3.push_back(V[i].second);
	}

	adjacent_difference(V_2.begin(),V_2.end(), V_2.begin());

	adjacent_difference(V_3.begin(),V_3.end(), V_3.begin());


	for(int i=0; i<n; i++){
		V_2_2.push_back(V_3[i]/V_2[i]);
	}

	for(int i=0; i<n; i++){
		V_1.push_back(make_pair(V_2_3[i],V_2_2[i]));	
	}

	DevV = V_1;

	/*for(int i=0; i<n; i++){
		cout<< V[i].second <<"   "<< V_1[i].second <<"\n";
	}*/

	cout << __PRETTY_FUNCTION__ << endl;

	return V_1;
}

TGraph* DataManip::GetDataDerivativeGraph(){
	TCanvas *c1 = new TCanvas("GdataDeriv", "GdataDeriv", 600,400);
	c1->SetGrid();
	int n = DevV.size();

	TGraph* GdataDeriv  = new TGraph(n);

	for(int i = 0; i < n; i++){
		GdataDeriv -> SetPoint(i, DevV[i].first, DevV[i].second);
	}

	GdataDeriv -> SetMarkerColor(kGreen+1);
	GdataDeriv -> SetMarkerStyle(20);
	GdataDeriv -> SetMarkerSize(0.4);
	c1 -> cd();     //ir para canvas 
	GdataDeriv -> Draw("AP");
	c1 -> SaveAs("GdataDeriv.pdf");

	cout << __PRETTY_FUNCTION__ << endl;

	return GdataDeriv;

}

TH1F* DataManip::GetDataDerivativeHisto(){

	TCanvas *c1 = new TCanvas("GdataDeriv", "GdataDeriv", 600,400);
	c1->SetGrid();

	int n = DevV.size();

	TH1F* HdataDeriv= new TH1F("HdataDeriv", "HdataDeriv", n, 1800, 2020); 


	for(int i=0; i<n; i++){
	 HdataDeriv->Fill(DevV[i].first,DevV[i].second);
	}

	//PrintHisto(HdataDeriv);

	c1 -> cd();     //ir para canvas 
	HdataDeriv -> Draw();
	c1 -> SaveAs("HdataDeriv.pdf");

	cout << __PRETTY_FUNCTION__ << endl;

	return HdataDeriv;
}

vector<pair<double, double>> DataManip::GetMovingAverage(int M){

	vector<pair<double, double>> V1;
	int N = V.size();

	//	Primeiros M/2 -1 termos são iguais a S
	for(int i = 0; i < (M/2); i++){
		V1.push_back(V[i]);
	}

	int j = M -1;
	double soma_elementos = 0;


	for(int j = 0; j < N - M + 1; j++){

		for(int i = j; i < (M - 1 + j); i++){
		soma_elementos = soma_elementos + V[i].second;
		}
		soma_elementos = (soma_elementos/M);

		V1.push_back(make_pair(V[j + M/2].first ,soma_elementos));
	}

	for(int i = N - M/2; i < N; i++){
		V1.push_back(V[i]);
	}

	/*for(int i = 0; i < N; i++){
		cout << " " << V1[i].first << " " << V1[i].second << "\n";
	}

	cout << "Tamanho do vetor: " << V1.size() << endl;*/

	V_Signal = V1; 

	cout << __PRETTY_FUNCTION__ << endl;

	return V_Signal;

}

TGraph* DataManip::GetMovingAverageGraph(int nr_days, const char* GraphName){

	V_Signal = GetMovingAverage(nr_days);
	 const char* graph_name_pdf;

	TCanvas *c2 = new TCanvas(GraphName, GraphName, 600,400);
	c2->SetGrid();
	int n = V_Signal.size();

	TGraph* Graph = new TGraph(n);
	Graph -> SetTitle(GraphName);

	for(int i = 0; i < n; i++){
		Graph -> SetPoint(i, V_Signal[i].first, V_Signal[i].second);
	}

	if(nr_days == 11){
		Graph -> SetMarkerColor(kYellow);
		graph_name_pdf = "Graph_11.pdf";
	}
	else{
		Graph -> SetMarkerColor(kMagenta);
		graph_name_pdf = "Graph.pdf";
	}

	Graph -> SetMarkerStyle(20);
	Graph -> SetMarkerSize(0.4);

	c2 -> cd();     //ir para canvas 
	Graph -> Draw("AP");
	c2 -> SaveAs(graph_name_pdf);

	cout << __PRETTY_FUNCTION__ << endl;

	return Graph;
}

TGraph* DataManip::GetAutocorrelationGraph(double k_min, double k_max, double delta_t, const char* file_name){


	TCanvas *c2 = new TCanvas(file_name, file_name, 600,400);
	c2->SetGrid();
	int n;
	int ano = 365;
	vector<double> intervalo_k, auxiliar;
	vector<pair<double, double>> V_K;
	vector<double> soma_elementosx, soma_elementosxlinha;

	soma_elementosx.reserve((k_max - k_min + 1)/delta_t);
	soma_elementosxlinha.reserve((k_max - k_min + 1)/delta_t);

	int dif_ano = 2020 - 1849 +1;
	
	const char* graph_name_pdf;
	TGraph* Graph = new TGraph(n);

	for(double k = k_min; k <= k_max; k+=delta_t)
	{	
		
		for(int j = 0; j < ano*(dif_ano - k); j++)
		{	
				soma_elementosx[k - k_min] += V[j].second;

		}

		n = ano*(2020 - 1849 - k + 1);
		soma_elementosx[k - k_min] = soma_elementosx[k - k_min]/n;
	}
    
	int size = V.size();

	for(double k = k_min; k <= k_max; k+=delta_t)
	{
		for(int j = (1949 + k)*ano; j < size; j++)
		{
				soma_elementosxlinha[k - k_min] += V[j].second;
		}

		n = ano*(2020 - 1849 - k + 1);
		soma_elementosxlinha[k - k_min] = soma_elementosxlinha[k - k_min]/n;
	}

    int size_1 = soma_elementosx.size();
    int size_2 = soma_elementosxlinha.size();

    cout << size_1 << "  " << size_2 << endl;
	
	for(int i = 0; i < (k_max - k_min)/delta_t ; i++){
		Graph -> SetPoint(i, soma_elementosx[i], soma_elementosxlinha[i]);
	}

	const char* char1 = "Gcorr";
	const char* char2 = "Gcorr_detailed";

	if(file_name == char1){
		Graph -> SetMarkerStyle(22);
		Graph -> SetMarkerSize(0.4);
		Graph -> SetMarkerColor(kGreen+2);
		graph_name_pdf = "Gcorr.pdf";

	}

	if(file_name == char2){
		Graph -> SetMarkerStyle(22);
		Graph -> SetMarkerSize(0.4);
		Graph -> SetMarkerColor(kGreen+4);
		graph_name_pdf = "Gcorr_detailed.pdf";

	}

	c2 -> cd();     //ir para canvas 
	Graph -> Draw("AP");
	c2 -> SaveAs(graph_name_pdf);

	cout << __PRETTY_FUNCTION__ << endl;

	return Graph;
}


