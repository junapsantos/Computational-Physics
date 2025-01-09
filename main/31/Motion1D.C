#include"Motion1D.h"
#include <string>
#include <iostream>
#include <math.h> 
using namespace std;


Motion1D::Motion1D (int n){
	this-> N = n;
	t= new float[n];
	x= new float[n];
  	cout << __PRETTY_FUNCTION__ << "\n";
}

Motion1D::~Motion1D(){
	cout << __PRETTY_FUNCTION__ << "\n";
}

void Motion1D::SetMotion(float* t0, float* x0, int n){
	this-> t = t0;
	this-> x = x0;
	this-> N = n;
  	cout << __PRETTY_FUNCTION__ << "\n";
}


int Motion1D::GetN(){
	int n;
	n = this->N;
	cout << __PRETTY_FUNCTION__ << "\n";
	return n;
}

float* Motion1D:: GetTimes(){
	float* times;
	times=this->t;
	cout << __PRETTY_FUNCTION__ << "\n";
	return times;
} 

float* Motion1D:: GetPositions(){
	float* positions;
	positions=this->x;
	cout << __PRETTY_FUNCTION__ << "\n";
	return positions;
} 

void Motion1D::Print(){
	printf("Numero de pontos: %d\n",N );
	printf("tempo(s):         posições:\n");
	for (int i=0; i<N;i++){
		printf("%4.5lf         %10.7lf\n",t[i],x[i]);
	}
	cout << __PRETTY_FUNCTION__ << "\n";
}

float Motion1D::TotalDistance(){
	float totald=x[0],d;
	for (int i=0; i<N-1; i++){
		d=x[i+1]-x[i];
		totald=totald+fabs(d);
	}
	return totald;
}

void Motion1D::QuedaLivre(){
	for (int i=0; i<N; i++) {
		t[i]=i+1;	
		x[i]=4.9*t[i]*t[i];					//fill here t and x arrays
	}
}


