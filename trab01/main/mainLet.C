#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <complex>
#include <vector>
#include "TObject.h"
#include "TFile.h"
#include "TGraph.h"
#include "TMultiGraph.h"

void DataReader(string file_name, vector<pair<double, double>> V){
  	string filename;

	cout << __PRETTY_FUNCTION__ << "\n";
	
	filename = file_name;

	ifstream file(filename);

	double c_1, c_2, c_3, c_4, c_5, c_6, c_7;

    
    while(file >> c_1 >>  c_2 >> c_3 >> c_4 >> c_5 >> c_6 >> c_7 ){    
            V.push_back(make_pair(c_4,c_5));
      
    }

	file.close();
}


using namespace std;

int main(){

	vector<pair<double, double>> V

	DataReader("ola.txt", V);

	return 0;
}