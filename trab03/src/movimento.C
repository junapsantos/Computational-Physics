#include "movimento.h"

movimento::movimento(double **m, double step, double t_max){ // dim = 203

	double k = 1.38 * pow(10, -23);
	double M = 6.69 * pow(10, -26);


	Step = step;
	int nr_estados = t_max/step;      			    // (t_max/step) espaços para x e (t_max/step + 1) para y

	double* x_aux = new double [100];
	double* y_aux = new double [100];

	double* vaux = new double [200];

	for(int i = 1; i <  201 ; i++)
		vaux[i - 1] = m[0][i];


	for(int i = 0; i < 100; i++){
		x_aux[i] = vaux[2*i];
		y_aux[i] = vaux[2*i + 1];
	}

   	//distancia entre particulas
   	double *U_Pot = new double[nr_estados];

   	double** d_aux = new double* [100];

 	for(int i = 0; i < 100; i++)
 		d_aux[i] = new double[99];
 	
 	//
   	for(int i = 0; i < 100; i++){
		vaux = m[i];

			for(int j = 0; j < 99; j++)
				d_aux[i][j] = sqrt((vaux[1] - vaux[2*j + 3])*(vaux[1] - vaux[2*j + 3]) + (vaux[2] - vaux[2*j + 4])*(vaux[2] - vaux[2*j + 4]));
   	}


	//Calcular aceleracao Inicial de cada particula a partir de da formula do potecial lennard-jones em que r é a distancia entre particulas
	double* aceleracao = new double[100];
	double* potencial  = new double[100];
	double soma_grad = 0;
	double soma_pot = 0;
	
	for(int i = 0; i < 100; i ++){
		for(int j = 0; j < 99; j++){
			soma_grad += 24*( 2/pow(d_aux[i][j], 13) - 1/pow(d_aux[i][j], 7) );
			soma_pot  +=  4*( 1/pow(d_aux[i][j], 12) - 1/pow(d_aux[i][j], 6) );
		}

		aceleracao[i] = soma_grad;
		potencial[i]  = soma_pot;
	}
	//
	soma_pot = 0;
	for(int i = 0; i < 100; i++)
		soma_pot += potencial[i];
 	
 	U_Pot[0] = soma_pot;

	//Calcular Posicao seguinte - calcular x1 e y1 de cada particula - Nao foram tidas em conta as paredes do recipiente
	double** posicoes_X = new double* [nr_estados];

 	for(int i = 0; i < nr_estados; i++)
 		posicoes_X[i] = new double[100];

 	double** posicoes_Y = new double* [nr_estados];

 	for(int i = 0; i < nr_estados; i++)
 		posicoes_Y[i] = new double[100];

 	double** vel_X = new double* [nr_estados];

 	for(int i = 0; i < nr_estados; i++)
 		vel_X[i] = new double[100];

 	double** vel_Y = new double* [nr_estados];

 	for(int i = 0; i < nr_estados; i++)
 		vel_Y[i] = new double[100];

 
	double* x_aux1 = new double [100];
	double* y_aux1 = new double [100];

	double* vx_aux = new double [100];
	double* vy_aux = new double [100];

	double *Kcin_aux = new double[nr_estados];
	double Ecinetica;

	double *E_Total_aux = new double[nr_estados];
	double *EREL = new double[nr_estados];
	double *Temperatura = new double[nr_estados];

	for(int i = 1; i <  201 ; i++)
		vaux[i - 1] = m[0][i];


	for(int i = 0; i < 100; i++){
		x_aux[i] = vaux[2*i];
		y_aux[i] = vaux[2*i + 1];
	}

	posicoes_X[0] = x_aux;
	posicoes_Y[0] = y_aux;
	for(int i = 0; i < 100; i++){
		vel_X[0][i] = 0;
		vel_Y[0][i] = 0;
	}
	

	for(int i = 0; i < 100; i++){
		x_aux1[i] =  2 * x_aux[i] + (step)*(step) * aceleracao[i];
		y_aux1[i] =  2 * y_aux[i] + (step)*(step) * aceleracao[i];

		if(x_aux1[i] >= 22){
			x_aux1[i] = 22  - (x_aux1[i]  - 22);
		}

		if(y_aux1[i] > 22){
			y_aux1[i] = 22  - (y_aux1[i]  - 22);
		}	
	}

	posicoes_X[1] = x_aux1;
	posicoes_Y[1] = y_aux1;

	//Primeiros dois t's
	double* t_aux = new double[nr_estados];
	t = t_aux;
	t[0] = 0;
	t[1] = step;



	for(int k = 2; k < nr_estados; k++){
		Ecinetica = 0;
		//Calcular poscioes para todos os t's  e Calcular novos potencias 
	   	//distancia entre particulas - cada vez que as particulas mudam de posicao é necessario voltar a calcular a distancia entre elas e a sua aceleracao

	   	for(int i = 0; i < 100; i++){
			for(int j = 0; j < 100; j++){
				if( i != j){
					d_aux[i][j] = sqrt((posicoes_X[k-1][i] - posicoes_X[k-1][j])*(posicoes_X[k-1][i] - posicoes_X[k-1][j]) + (posicoes_Y[k-1][i] - posicoes_Y[k-1][j])*(posicoes_Y[k-1][i] - posicoes_Y[k-1][j]));
				}

				if(d_aux[i][j] < 0.5){
					d_aux[i][j] = 1;
				}
			}
	   	}
	   	//cout << endl;

		//Calcular aceleracao  de cada particula
		soma_grad = 0;
		
		for(int i = 0; i < 100; i ++){
			soma_grad = 0;
			soma_pot = 0;
			for(int j = 0; j < 99; j++){
				soma_grad +=  -24 * (  2 / pow(d_aux[i][j], 13) - 1 / pow(d_aux[i][j], 7) );
				soma_pot  +=  -1*4 * ( 1/pow(d_aux[i][j], 12) - 1/pow(d_aux[i][j], 6) );
			}

			aceleracao[i] = soma_grad;
			potencial[i] = soma_pot;
		}

		soma_pot = 0;
		for(int i = 0; i < 100; i++)
			soma_pot += potencial[i];

 		U_Pot[k - 1] = soma_pot;


		double* x_aux2 = new double [100];
		double* y_aux2 = new double [100];

		for(int j = 0; j < 100; j++){
			x_aux2[j] =  2 * posicoes_X[k - 1][j] - posicoes_X[k - 2][j] + (step)*(step)*aceleracao[j];
			y_aux2[j] =  2 * posicoes_Y[k - 1][j] - posicoes_Y[k - 2][j] + (step)*(step)*aceleracao[j];

			vx_aux[j] =  (x_aux2[j] - posicoes_X[k-2][j]) / (sqrt(2) * step);
			vy_aux[j] =  (y_aux2[j] - posicoes_Y[k-2][j]) / (sqrt(2) * step);

			while(x_aux2[j] >= 22 || y_aux2[j] >= 22 || x_aux2[j] <= 0 || y_aux2[j] <= 0){
				if(x_aux2[j] >= 22)
					x_aux2[j] = 22  - (x_aux2[j]  - 22);

				if(y_aux2[j] > 22)
					y_aux2[j] = 22  - (y_aux2[j]  - 22);
				
				if(x_aux2[j] <= 0)
					x_aux2[j] = -(x_aux2[j]);
				
				if(y_aux2[j] <= 0)
					y_aux2[j] = -(y_aux2[j]);

				vx_aux[j] =  - (x_aux2[j] - posicoes_X[k-2][j]) / (2 * step);
				vy_aux[j] =  - (y_aux2[j] - posicoes_Y[k-2][j]) / (2 * step);
			}

		}
		for(int i = 0; i < 100; i++){
			Ecinetica += sqrt((vx_aux[i]*vx_aux[i]) + (vy_aux[i]*vy_aux[i])) * sqrt((vx_aux[i]*vx_aux[i]) + (vy_aux[i]*vy_aux[i])) /2;
		}
		
		posicoes_X[k] = x_aux2;
		posicoes_Y[k] = y_aux2;

		vel_X[k - 1] = vx_aux;
		vel_Y[k - 1] = vy_aux;
		Kcin_aux[k - 1] = Ecinetica;
		Temperatura[k - 1] = Ecinetica/(100 * k);

		t[k] = t[k - 1] + step;

		E_Total_aux[k - 1] = -1*(Kcin_aux[k - 1] + U_Pot[k - 1]);
		EREL[k - 1] = (E_Total_aux[k - 1] - E_Total_aux[1]) /(E_Total_aux[1]);
	}

	Posicoes_X = posicoes_X;
	Posicoes_Y = posicoes_Y;
	Kcin = Kcin_aux;
	E_REL = EREL;
	TemperaturaT = Temperatura;
	E_Total = E_Total_aux;
	Vel_X = vel_X;
	Vel_Y = vel_Y;

	double *Desvio_Quadratico = new double[100];
	double Desvio_Quadratico_mediox, Desvio_Quadratico_medioy ;
	for(int i = 0; i < 100; i++){
		Desvio_Quadratico_mediox = 0.;
		Desvio_Quadratico_medioy = 0.;
		for(int j = 1; j < nr_estados; j++){
			if(i != j){
				Desvio_Quadratico_mediox +=  (Posicoes_X[i][j] - Posicoes_X[i][0])*(Posicoes_X[i][j] - Posicoes_X[i][0]);
				Desvio_Quadratico_medioy +=  (Posicoes_Y[i][j] - Posicoes_Y[i][0])*(Posicoes_Y[i][j] - Posicoes_Y[i][0]);
			}
		
		}
		Desvio_Quadratico[i] = sqrt((Desvio_Quadratico_mediox + Desvio_Quadratico_medioy))/ nr_estados;
	}

	desvio_quadratico = Desvio_Quadratico;
}

movimento::~movimento(){}

double* movimento::GetT(){
	return t;
}

double* movimento::GetPOS_X_EM_T(int t){
	int k = t/Step;
	return Posicoes_X[k];
}

double* movimento::GetPOS_Y_EM_T(int t){
	int k = t/Step;
	return Posicoes_Y[k];
}

double* movimento::GetVEL_X_EM_T(int t){
	int k = t/Step;
	return Vel_X[k];
}

double* movimento::GetVEL_Y_EM_T(int t){
	int k = t/Step;
	return Vel_Y[k];
}

double* movimento::GetVEL_EM_T(int t){
	int k = t/Step;
	double* velocidades= new double [100];

	for (int i=0; i<100; i++){
		velocidades[i]= sqrt( Vel_X[k][i]*Vel_X[k][i] + Vel_Y[k][i]*Vel_Y[k][i] );
	}
	
	return velocidades;
}



double** movimento::GetPOS_X(){
	return Posicoes_X;
}
double** movimento::GetPOS_Y(){
	return Posicoes_Y;
}








