	#include <cstdio>    //printf
	#include <iostream> //cout
	#include <string>
#include <math.h> 

	#include "Motion1D.h"
	#include "Uniform1D.h"
    using namespace std;


Uniform1D::Uniform1D(int fN0, float ti0, float xi0, float dt0, float vel0) :
Motion1D(fN0) {// t and x arrays are created by Motion1D constructor
 	this->N = fN0;
 	this->ti = ti0;
 	this->xi =xi0;
 	this->dt = dt0;
 	this->vel = vel0;

	float intervalot=dt/N;

	for (int i=0; i<N; i++) {
		t[i]=ti+intervalot*(i+1);	
		x[i]=xi+vel*t[i];					//fill here t and x arrays
	}
}

Uniform1D::~Uniform1D(){
	cout << __PRETTY_FUNCTION__ << "\n";
}


void Uniform1D::Print() {
	Motion1D::Print(); //call Print from base class
	printf("ti=%f, xi=%f, vel=%f \n", ti, xi, vel);
}
