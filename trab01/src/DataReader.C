#include "DataReader.h"

using namespace std;


int DataReader::FileExists(string file_name){

  vector<pair<double, double>> V;
  string filename;

	cout << __PRETTY_FUNCTION__ << "\n";

	ifstream ifile;
    ifile.open(file_name);

    if(ifile) {

      //cout<<"O ficheiro existe\n";
      return 1;

    } else {

      cout<<"ERRO! O ficheiro " <<file_name<< " nao foi encontrado\n" << endl;
      return 0;
    }

    ifile.close();
}

DataReader::DataReader(string file_name){

	cout << __PRETTY_FUNCTION__ << "\n";
	
	filename = file_name;

	ifstream file(filename);

	double c_1, c_2, c_3, c_4, c_5, c_6, c_7;
    char c_8;

    
    while(file >> c_1 >>  c_2 >> c_3 >> c_4 >> c_5 >> c_6 >> c_7 >> c_8){  

        if (c_1 >= 1849 || c_4 <= 2020.499 || c_8 == '\n'){
            V.push_back(make_pair(c_4,c_5));
        }
    }

    while(file >> c_1 >>  c_2 >> c_3 >> c_4 >> c_5 >> c_6 >> c_7 >> c_8){  

        if (c_4 > 2020.499 || c_8 == '*'){
            V.push_back(make_pair(c_4,c_5));
        }
    }


	/*for(int i = 0; i < V.size(); i++)
	{
		//cout  << V[i].first << " "<< V[i].second << "\n" ;
		printf("%.3f        %.3f \n ", V[i].first, V[i].second);
	}
    cout << " "<< endl;
    */
	file.close();

}
DataReader::~DataReader() {

  cout << __PRETTY_FUNCTION__ << "\n";

}
