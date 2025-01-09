#ifndef __ODEPoint__
#define __ODEPoint__

#include <iostream>
#include <vector>

using namespace std;

class ODEPoint {
	public:

	ODEPoint(); //
	~ODEPoint(); //
	ODEPoint(const ODEPoint&); // 
	//ODEPoint(int fndim = 0, vector<double> v1); //
	ODEPoint(int fndim , const double* x); //

	int Ndim() const {return ndim;}; 			//retorna nr de variaveis dependentes
	double T() const {return t;}; 				//retorna t
	double X(int i) const {return v[i];};		//retorna elemento i do vetor de variaveis dependentes
	double* V() const {return v;};				//retorna array com as variaveis dependentes
	
	double Vel( int i) const {return vel[i];};
	double* R_ptr() const ;
	double R() const {return r;};
	double* Vel() const {return vel;};
	double* Getd() const;

	void SetT(const double);
	void SetX(int i, const double fx);
	void SetV(const double*);

	void SetR(const double);
	void Setd(const double*);
	void SetVel(const int i ,const double fvel);

	void Dod();
	void Dor();

	vector<double> Get_T_X();					//retorna vetor com variaveis dependentes associados ao t (=v[0])
	double* Get_T_X_ptr();						//igual ao anterior mas como ponteiro
	double Get_a();

	ODEPoint operator*(double) const;
	ODEPoint operator+(const ODEPoint&) const;
	ODEPoint operator-(const ODEPoint&) const;
	void operator=(const ODEPoint&); 

	const double& operator[] (int) const;
	double& operator[] (int);
	
	void Print() const;

	private:

	int ndim; //nb of dependent variables
	double* v; //dependent variables (ndim)
	double t;
	double r;

	double* d;
	double a;
	double* vel;
};

#endif