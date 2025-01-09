#ifndef __Material__
#define __Material__

#include <string>
#include <cstdio>
#include <iostream>
#include <iostream>
using namespace std;

class Material {

public:

Material(string fname=" ", double fdens=0): name(fname), density(fdens){;}
~Material();

string GetName() {return name;}

double GetDensity() {return density;}

virtual void Print();


protected:

string name;

double density;

};

#endif

