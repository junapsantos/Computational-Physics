#include "ODEPoint.h"

#include <stdexcept>
#include <cstdio>
#include <cmath>
#include <math.h> 
#include <iostream>
#include <iomanip>
#include <utility>
#include <complex>
#include <vector>

ODEPoint::ODEPoint(){
	t = 0;
	ndim = 1;
	double* a1 = new double[ndim];
	v = a1; 

	double* a2 = new double[2];
	vel= a2;

	r= 0.;

	double* a3 = new double[4];
	d= a3;

	a=0;

}

ODEPoint::~ODEPoint(){
	
}

ODEPoint::ODEPoint(const ODEPoint& ODE){
	t = ODE.t;
	ndim = ODE.ndim;
	v= ODE.v;
	
	r= ODE.r;

	d= ODE.d;
	a= ODE.a;
	
	vel= ODE.vel;
	
} 

ODEPoint::ODEPoint(int fndim, const double* x){
	ndim = fndim;

	double* vaux=new double [ndim];
	t=x[0];

	for(int i = 1; i < ndim+1; i++)
		vaux[i-1] = x[i];

	v=vaux;

	double* vel_aux=new double [2];
	vel_aux[0]= x[ndim-1];
	vel_aux[1]= x[ndim-2];
	vel=vel_aux;

	double* d_aux = new double[4];

	r = sqrt(v[0]*v[0] + v[1]*v[1]);

	for(int i = 0; i < 4; i++)
		d_aux[i] = sqrt((v[0] - v[2*i + 2])*(v[0] - v[2*i + 2]) + (v[1] - v[2*i + 3])*(v[1] - v[2*i + 3]));

	d = d_aux;

	a = 0;

	for(int i = 0; i < ndim - 1; i++){
		r = sqrt(v[2*i]*v[2*i] + v[2*i+1]*v[2*i+1]);
		a += 24*( (2./pow(r, 13)) - (1./pow(r, 7)) );
	}
}	 
 //4*1.6568e-21*(12.*2.386e-90/pow(r, 13) - 6.*1.5448e-45/pow(r, 7));
/*ODEPoint::ODEPoint(int fndim = 0, vector<double> a){
	ndim = fndim;
	delete[] v;

	for(int i = 0; i < ndim; i++)
		v[i] = a[i];
}*/

void ODEPoint::SetT(const double ft){
	t=ft;
}

void ODEPoint::SetX(int i, const double fx){
	v[i]=fx;
}

void ODEPoint::SetV(const double* fv){
	double* vaux= new double[sizeof(fv)];
	
	for(int i=0; i<sizeof(fv); i++)
		vaux[i]=fv[i];

	v=vaux;
}

void ODEPoint::SetVel(int i ,const double fvel){
	vel[i]=fvel;
}

double* ODEPoint::R_ptr() const{
	double* vaux= new double[1];
	
	vaux[0]=sqrt(v[0]*v[0] + v[1]*v[1]);;

	return vaux;

} 


void ODEPoint::SetR(const double fr){
	r=fr;
}


void ODEPoint::Setd(const double* fv){
	double* vaux= new double[sizeof(fv)];
	
	for(int i=0; i<sizeof(fv); i++)
		vaux[i]=fv[i];

	d=vaux;
}

void ODEPoint::Dod(){
double* d_aux = new double[4];
	for(int i = 0; i < 4; i++)
		d_aux[i] = sqrt((v[0] - v[2*i + 2])*(v[0] - v[2*i + 2]) + (v[1] - v[2*i + 3])*(v[1] - v[2*i + 3]));

	d = d_aux;

}

void ODEPoint::Dor(){

	r = sqrt(v[0]*v[0] + v[1]*v[1]);

}

double* ODEPoint::Getd() const { 

	/*double* vaux=new double [ndim-3];
	for(int i = 0; i < ndim-3; i++){
		vaux[i]=d[i];
	}*/

	return d;
}

vector<double> ODEPoint::Get_T_X(){
	vector<double> v_help;

	v_help.push_back(t);

	for(int i = 0; i < ndim + 1; i++){
		v_help.push_back(v[i]);
	}

	return v_help;
}

double ODEPoint::Get_a() {
	return a;
}

double* ODEPoint::Get_T_X_ptr(){

	double* vaux=new double [ndim+1];
	vaux[0]=t;
	for(int i = 0; i < ndim; i++){
		vaux[i+1]=v[i];
	}

	return vaux;
}


void ODEPoint::operator=(const ODEPoint& ODE)
{
	 if (this != &ODE) {
        ndim = ODE.ndim;
        v = ODE.v;
        t = ODE.t;
        r= ODE.r;
	d= ODE.d;
	a= ODE.a;
	
	vel= ODE.vel;
    }
}

const double& ODEPoint::operator[] (int i) const{
	return v[i];
}

double& ODEPoint::operator[] (int i){
	return v[i];
}


ODEPoint ODEPoint::operator*(double a) const{
	ODEPoint ODE;
	for(int i = 0; i < ndim; i++)
		v[i] = a*v[i];

	ODE.t = t;
	ODE.v = v;
	ODE.ndim = ndim;
	return ODE;
}

ODEPoint ODEPoint::operator+(const ODEPoint& ODE) const{
	ODEPoint SOMA(*this);
	if(ODE.ndim != ndim)
		cout << "ERRO! É necessário que as ODE's tenham as mesmas dimensoes" << endl;
	else{
		for(int i = 0; i < ndim; i++)
			SOMA[i] += ODE[i];
	}

	/*
	double dim_max, dim_min;
	if(ODE.ndim != ndim){
		if(ndim > ODE.ndim)
			dim_max = ndim;
			dim_min = ODE.ndim

		else(){
			dim_max = ODE.ndim;
			dim_min = ndim;
		}
	}
	if(ndim == dim_max){
		for(int i = 0; i < dim_min; i++)
			v[i] = v[i] + ODE.v[i];
	}

	if(ODE.ndim == dim_max){
		for(int i = 0; i < dim_min; i++)
			v[i] = v[i] + ODE.v[i];
		for(int j = dim_min; j < dim_max; j++)
			v[j] = ODE.v[j];
	}
	*/

	return SOMA;
}

ODEPoint ODEPoint::operator-(const ODEPoint& ODE) const{
	ODEPoint SUBTRACAO(*this);
	if(ODE.ndim != ndim)
		cout << "ERRO! É necessário que as ODE's tenham as mesmas dimensoes" << endl;	
	else{
		SUBTRACAO = SUBTRACAO + ODE*(-1);
	}

	/*
	double dim_max, dim_min;
	if(ODE.ndim != ndim){
		if(ndim > ODE.ndim)
			dim_max = ndim;
			dim_min = ODE.ndim

		else(){
			dim_max = ODE.ndim;
			dim_min = ndim;
		}
	}
	if(ndim == dim_max){
		for(int i = 0; i < dim_min; i++)
			v[i] = v[i] - ODE.v[i];
	}

	if(ODE.ndim == dim_max){
		for(int i = 0; i < dim_min; i++)
			v[i] = v[i] - ODE.v[i];
		for(int j = dim_min; j < dim_max; j++)
			v[j] = - ODE.v[j];
	}
	*/
	return SUBTRACAO;
}

void ODEPoint::Print() const{
	cout<<endl;
	for(int i = 0; i < ndim; i++){
		cout << "Variavel " << i << ":" << v[i]<<endl;
	}

	cout << "Tempo: " << t << endl;

	cout << "Dimensão: " << ndim << endl;
}







