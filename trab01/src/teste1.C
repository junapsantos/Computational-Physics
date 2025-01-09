#include <fstream>
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std

int main(){
ifstream file("SunspotNumberDATA2020.txt");

double c_1, c_2, c_3, c_4, c_5, c_6, c_7;
vector<pair<double, double>> V;
int i = 0;

while(file >> c_1 >>  c_2 >> c_3 >> c_4 >> c_5 >> c_6 >> c_7)
{	
V.push_back(make_pair(c_4,c_5));
}

for(int i = 0; i < V.size(); i++)
	{
		cout << V[i].first << " " << V[i].second << "\n" ;
	}
	cout << " "<< endl;

file.close();
}