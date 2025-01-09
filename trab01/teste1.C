#include <fstream>
#include <vector>
#include <numeric>
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <algorithm>


using namespace std;

//Nota: Falta ler ficheiro a partir da linha em que tem *'s
int FileExists(string file_name){

	ifstream ifile;
    ifile.open(file_name);

    if(ifile) {
      cout<<"O ficheiro existe";
      return NULL;

    } else {
      cout<<"ERRO! O ficheiro nao existe";
      return NULL;
    }

    ifile.close();

}

bool sortbysecdesc(const pair<double,int> &a, const pair<double,int> &b)
{
       return a.second > b.second;
}

bool sortbysecasc(const pair<double,int> &a, const pair<double,int> &b)
{
       return a.second < b.second;
}

vector<pair<double, int>> GetDataVectorSorted(int order, vector<pair<double, int>> V){

	if(order == 0){
		sort(V.begin(), V.end(), sortbysecdesc);
	}
	if(order == 1){
		sort(V.begin(), V.end(), sortbysecasc);
	}

	if(order > 1){
		cout << "ERRO! Insira: 0 - decrescente, 1 - crescente" << endl;
	}

	return V;
}

vector<pair<double, int>> GetDataDerivativeVector(vector<pair<double, int>> V){

	int n = V.size();
	vector<pair<double, int>> V_1;

	vector<double> V_2;  //timer
	vector<double> V_2_2;
	vector<double> V_2_3;

	vector<int> V_3;  	//sunspot number


 	printf("ola\n");

 	for(int i=0; i<n; i++){
		V_2.push_back(V[i].first);
		V_2_3.push_back(V[i].first);
		V_3.push_back(V[i].second);
	}

	printf("mangas\n");

	adjacent_difference(V_2.begin(),V_2.end(), V_2.begin());

	adjacent_difference(V_3.begin(),V_3.end(), V_3.begin());

	printf("bananas\n");

	for(int i=0; i<n; i++){
		V_2_2.push_back(V_3[i]/V_2[i]);
	}



	printf("laranjas\n");

	for(int i=0; i<n; i++){
		V_1.push_back(make_pair(V_2_3[i],V_2_2[i]));
	}

	printf("abacates\n");

	for(int i=0; i<n; i++){
		cout<<V[i].second<<"   "<<V_1[i].second<<"\n";
	}

	return V_1;
}

int main(){

	ifstream file("SunspotNumberDATA2020.txt");
	string file_name = "SunspotNumberDATA2020.txt";

	double c_1, c_2, c_3, c_4, c_5, c_6, c_7, c_8;
	vector<pair<double, int>> V;
	int i = 0;


	while((file >> c_1 >>  c_2 >> c_3 >> c_4 >> c_5 >> c_6 >> c_7) || (file >> c_1 >>  c_2 >> c_3 >> c_4 >> c_5 >> c_6 >> c_7 >> c_8)){	
		V.push_back(make_pair(c_4,c_5));
	}


	for(int i = 0; i < V.size(); i++)
	{
		//cout  << V[i].first << " "<< V[i].second << "\n" ;
		printf("%.3f        %d \n ", V[i].first, V[i].second);
	}
	//cout << " "<< endl;

	cout << V.size() << endl;

	V = GetDataVectorSorted(2,V);

		for(int i = 0; i < V.size(); i++)
	{
		//cout  << V[i].first << " "<< V[i].second << "\n" ;
		printf("SORT\n %.3f        %d \n ", V[i].first, V[i].second);
	}

	vector<pair<double, int>> V1=GetDataDerivativeVector(V);
	for(int i = 0; i < V.size(); i++)
	{
		//cout  << V[i].first << " "<< V[i].second << "\n" ;
		//printf("DERIVADA\n %.3f        %d \n ", V1[i].first, V1[i].second);
	}
	printf("%d %d \n",V1.size(),V.size());
	V = GetDataVectorSorted(1,V);


	if(!FileExists(file_name)) exit(1);

}

