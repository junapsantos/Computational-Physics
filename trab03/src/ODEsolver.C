#include "ODEsolver.h"

ODEsolver::ODEsolver()
{
    vector<TF1> F0;
    F=F0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

ODEsolver::ODEsolver(const vector<TF1>& F1) //Constructor
{
	F.clear();
    for (int i = 0; i < F1.size(); i++) //Passagem das TF1 para o vector F
    {
        F.push_back(F1[i]);
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

ODEsolver::~ODEsolver() //Destructor
{
    F.clear(); //Limpeza dos valores do vector de TF1
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

TF1& ODEsolver::GetODEfunc(int i) //Constructor
{
    return F[i];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ODEsolver::SetODEfunc(const vector<TF1>& F2) //Constructor
{
    F.clear();
    for (int i = 0; i < F2.size(); i++) //Passagem das TF1 para o vector F
    {
        F.push_back(F2[i]);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
vector<ODEPoint> ODEsolver::Euler(ODEPoint iPoint, double step, double T){

 int Nstep = 1 + int(T/step); // nb steps, foi o prof que fez mas eu acho que tem 1 a mais

 vector<ODEPoint> vP;
 vP.reserve(Nstep+1);

 int N=iPoint.Ndim();

 double* nextv= new double [N];

 vP[0]=iPoint;

 for (int i = 0; i <Nstep; ++i) {

 	vP[i+1]=iPoint; //para kinda alocar espaço

 	vP[i+1].SetT(vP[i].T() + step);

 	for(int j=0; j<N; j++)
		nextv[j] = vP[i].X(j) + step*F[j].EvalPar(vP[i].Get_T_X_ptr());

 	vP[i+1].SetV(nextv);
 
 }

 /*for (int i = 1; i <=Nstep; ++i) {

 	vaux=cPoint.Get_T_X_ptr();

 	vP[i]=iPoint;

 	nextt = cPoint.T() + step;
 	vP[i].SetT(nextt);

	nextv[1] = cPoint.X(1) + step*F[1].EvalPar(vaux);
 	nextv[0] = cPoint.X(0) + step*F[0].EvalPar(vaux);
 	vP[i].SetV(nextv);
 
	cPoint=vP[i];
 }*/
 
 return vP;


}

//////////////////////////////////////////////////////////////////////////////////////////////////////
vector<ODEPoint> ODEsolver::PredictorCorrector(ODEPoint iPoint, double step, double T){ //parecido com os outros  mas usa euler para prever i+1 
																			//PRECISA DE CORREÇAO DE ALGUNS PORMENORES E TESTAR
int Nstep = 1 + int(T/step); // nb steps

 vector<ODEPoint> vP;
 vP.reserve(Nstep+1);

 int N=iPoint.Ndim();

 double* nextv= new double [N];

 vector<ODEPoint> veuler;
 veuler= Euler(iPoint, step, T+step);

 vP[0]=iPoint;

 for (int i = 0; i <Nstep; ++i) {

 	vP[i+1]=iPoint;

 	vP[i+1].SetT(vP[i].T() + step);

 	for(int j=0; j<N; j++) // isto e para quando tem varias funcoes(mais que 1 variavel dependente)
		nextv[j] = vP[i].X(j) + 0.5*step*( F[j].EvalPar( vP[i].Get_T_X_ptr() ) + F[j].EvalPar( veuler[i+1].Get_T_X_ptr() ) );

 	vP[i+1].SetV(nextv);
 	
 }

 return vP;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////
vector<ODEPoint> ODEsolver::LeapFrog(ODEPoint iPoint, double step, double T){ //NAO TEM ERROS DE COMPILAÇÃO, MAS NAO SEI SE FUNCIONA BEM, MAS AGORA VOU DORMIR!!

 int Nstep = 1 + int(T/step); // nb steps

 vector<ODEPoint> vP;
 vP.reserve(Nstep+1);

 int N=iPoint.Ndim();

 double* nextv= new double [N];

 vP[0]=iPoint;

 vP[1]=iPoint;			//1ª iteração
 vP[1].SetT(iPoint.T() + step); 

 for(int i1=0; i1<N; i1++)
	nextv[i1] = iPoint.X(i1) + step*F[i1].EvalPar(iPoint.Get_T_X_ptr());
 vP[1].SetV(nextv);
 
 for (int i = 1; i <Nstep; ++i) {

 	vP[i+1]=iPoint;

 	vP[i+1].SetT(vP[i].T() + step);

 	for(int j=0; j<N; j++) // isto e para quando tem varias funcoes(mais que 1 variavel dependente)
		nextv[j] = vP[i-1].X(j) + 2*step*F[j].EvalPar(vP[i].Get_T_X_ptr());
 	vP[i+1].SetV(nextv);
 	
 }
 return vP;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////
vector<ODEPoint> ODEsolver::RK2(ODEPoint iPoint, double step, double T){

//TENHO SONO

	int Nstep = 1 + int(T/step); // nb steps, foi o prof que fez mas eu acho que tem 1 a mais

	vector<ODEPoint> vP;
	vP.reserve(Nstep+1);

	int N=iPoint.Ndim();
	double* nextv= new double [N];

	double K1, K2;
	double* vK2=new double [N];;

	vP[0]=iPoint;

	for (int i = 0; i <Nstep; ++i) {

		vP[i+1]=iPoint; //para kinda alocar espaço

	 	vP[i+1].SetT(vP[i].T() + step);

	 	for(int j=0; j<N; j++){

		 	K1 = step*F[j].EvalPar(vP[i].Get_T_X_ptr());//K1 = step*f(ti,yi)

		 	vK2[0] = vP[i].T() + step*0.5;				//t(i+1/2) = ti + 1/2step

		 	for(int k=1; k<=N; k++)						//y(i+1/2) = yi + (K1)/2
		 		vK2[k] = vP[i].X(k-1) + K1*0.5;

		 	K2= step*F[j].EvalPar(vK2);					//K2 = step * f( t(i+1/2) , y(i+1/2) )

			nextv[j] = vP[i].X(j) + K2;					//yi+1= yi + K2

		}

	 	vP[i+1].SetV(nextv);
	 
	}

	return vP;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////
vector<ODEPoint> ODEsolver::RK4(ODEPoint iPoint, double step, double T){

//TENHO SONO
 
	int Nstep = 1 + int(T/step); // nb steps, foi o prof que fez mas eu acho que tem 1 a mais
	
	vector<ODEPoint> vP;
	vP.reserve(Nstep+1);

	int N=iPoint.Ndim();
	double* nextv= new double [N];

	double K1, K2, K3, K4;
	double* vK2=new double [N];
	double* vK3=new double [N];
	double* vK4=new double [N];

	vP[0]=iPoint;

	for (int i = 0; i <Nstep; ++i) {

		vP[i+1]=iPoint; 												//para kinda alocar espaço

	 	vP[i+1].SetT(vP[i].T() + step); 								//ti+1

	 	for(int j=0; j<N; j++){

	 		/////K1
		 	K1 = step*F[j].EvalPar(vP[i].Get_T_X_ptr());				//K1 = step*f(ti,yi)

		 	////K2
		 	vK2[0] = vP[i].T() + step*0.5;								//t(i+1/2) = ti + 1/2step
		 	for(int k=1; k<=N; k++)										//y(i+1/2) = yi + (K1)/2
		 		vK2[k] = vP[i].X(k-1) + K1*0.5;
		 	K2= step*F[j].EvalPar(vK2);									//K2 = step * f( t(i+1/2) , y(i+1/2) )

		 	////K3
		 	vK3[0]=vK2[0];												//t(i+1/2) = ti + 1/2step
		 	for(int k=1; k<=N; k++)										//y(i+1/2) = yi + (K2)/2
		 		vK3[k] = vP[i].X(k-1) + K2*0.5;
		 	K3= step*F[j].EvalPar(vK3);

		 	////K4
		 	vK4[0]= vP[i].T() + step;									//t(i+1/2) = ti + step
		 	for(int k=1; k<=N; k++)										//y(i+1/2) = yi + K3
		 		vK4[k] = vP[i].X(k-1) + K3;
		 	K4= step*F[j].EvalPar(vK4);									//K2 = step * f( t(i+1/2) , y(i+1/2) )

			nextv[j] = vP[i].X(j) + (1./6)*( K1+ 2*K2 + 2*K3 + K4 );	 //yi+1= yi + 1/6*( K1 + 2K2 + 2K3 + K4)

		}

	 	vP[i+1].SetV(nextv);
	 
	}

	return vP;


}


//////////////////////////////////////////////////////////////////////////////////////////////////////
vector<ODEPoint> ODEsolver::LoopVerlet(ODEPoint iPoint, double step, double T){ //só funciona para para OdePoints: x[0]=t/x[1]=v[0]=r/x[2]=v[1]=v

 int Nstep = 1 + int(T/step); // nb steps

 vector<ODEPoint> vP;
 vP.reserve(Nstep+1);


 int N=iPoint.Ndim();

 double nextx=0.;
 double nexty=0.;


//t=t0
 vP[0]=iPoint;
 

//t=t0+1*step

 vP[1]=iPoint;			//1ª iteração
 vP[1].SetT(vP[0].T() + step); 

 nextx = vP[0].X(0)  + vP[0].Vel(0)*step+ 0.5*step*step*iPoint.Get_a();
 nexty = vP[0].X(1) + vP[0].Vel(1)*step + 0.5*step*step*iPoint.Get_a();

 cout<<"x: "<<vP[0].X(0)<<"\nvx: "<<0.5*step*step*iPoint.Get_a()<<endl;
 cout<<"x: "<<nextx<<"\ny: "<<nexty<<endl;

 vP[1].SetX(0,nextx);
 vP[1].SetX(1,nexty);

 cout<<"bnanas"<<endl;

 for (int i = 1; i < Nstep; ++i) {
	
 	vP[i+1] = iPoint;
 
 	vP[i+1].SetT(vP[i].T() + step);

	nextx = 2*vP[i].X(0) - vP[i-1].X(0) + step*step*F[0].EvalPar( vP[i].R_ptr() );
	nexty = 2*vP[i].X(1) - vP[i-1].X(1) + step*step*F[0].EvalPar( vP[i].R_ptr() );

	cout<<"x: "<<nextx<<"\ny: "<<nexty<<endl;

 	vP[i+1].SetX(0,nextx);
 	vP[i+1].SetX(1,nexty);
 	
 }


 double nextvelx= 0.;
 double nextvely= 0.;
 for (int i = 1; i <Nstep; ++i){

 	nextvelx = (vP[i+1].X(0)-vP[i-1].X(0))/(2*step);
 	nextvely = (vP[i+1].X(1)-vP[i-1].X(1))/(2*step);
 	vP[i].SetVel(0,nextvelx);
 	vP[i].SetVel(1,nextvely);
 }

 return vP;

}




//////////////////////////////////////////////////////////////////////////////////////////////////////2*vP[i].R() - vP[i-1].R() + step*step*





//////////////////////////////////////////////////////////////////////////////////////////////////////



















