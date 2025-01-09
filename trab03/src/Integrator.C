#include "Integrator.h"
 
void Integrator::SetRange(double x0_2,double x1_2){
   
    x0 = x0_2;
    x1 = x1_2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
void Integrator::Trapezoidal(int n, double& Integral, double& Error){

	double h = (x1 - x0)/n;
	Integral=0.;

	 //Cálculo do valor do Integral
 
	for(int i=0; i<=n; i++){

		if( i==0 )
    		Integral += Eval(x0);   

    	if( i!=0 && i!=n )
    		Integral += 2*Eval(x0 + (i*h) );

    	if( i==n )
    		Integral += Eval(x1);
    }

    Integral *= h/2.;

    //Calculo do erro, sendo x0  2ª derivada calculada através do teorema do valor medio: f´´(c)*(x1-x0)= f'(x1)-f'(x0)
    Error = 0.;
    Derivator Deriv(f);
    Error= -( (h*h) / 12. ) * ( ( Deriv.Deriv_1(x1, 1e-6, 0) - Deriv.Deriv_1(x0, 1e-6, 0) ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Integrator::TrapezoidalAdaptive(double& Integral, double& Error){  //NAO SEI SE FUNCIONA!

	Integral= (x1 - x0)*( Eval(x1) + Eval(x0) )/2.; //=F1
	Error=1;
	double n, sum, prevIntegral;

	for(int k=2; Error>1e-6; k++){          
		n=pow(2,k-1);
		sum=0.;
		for (int i=1; i<=pow(2, k-2); i++)				//somatorio
			sum += Eval( x0 + ( 2*i - 1)*(x1 - x0)/n);

		prevIntegral = Integral;						//guardar ordem anterior
		Integral = prevIntegral/2. + ((x1 - x0)/ n)*sum;	//=Fk

		Error = fabs (prevIntegral - Integral);				//erro é x0 diferença da ordem anterior com x0 seguinte

	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Integrator::Simpson(int n, double& Integral, double& Error){
	double h = (x1 - x0)/n;
	Integral = 0.;

	//Cálculo do valor do Integral
	//n par
	if(n%2==0){

		for(int i=0; i<=n; i++){

			if( i==0 )
            	Integral += Eval(x0);

            if( i!=0 && i!=n && i%2==1 )
                Integral += 4*Eval(x0 + (double)i*h );

            if( i!=0 && i!=n && i%2==0 )
            	Integral += 2*Eval(x0 + (i*h) );

            if( i==n )
            	Integral += Eval(x1);

        }

        Integral *= h/3.;

    }

    //n impar
	if(n%2==1){

		//n-1 slices
		for(int i=0; i<n; i++){

			if(i==0)
            	Integral += Eval(x0);

            if(i!=0 && i!=(n-1) && i%2==1)
                Integral += 4*Eval(x0 + (i*h) );

            if(i!=0 && i!=(n-1) && i%2==0)
            	Integral += 2*Eval(x0 + (i*h) );

            if(i==(n-1))
            	Integral += Eval(x0 + (i*h) );
        }

        Integral *= h/3.;

        //ultima slice (n)
       
        Integral+= (h/12.)*( -Eval(x1 - 2*h) + 8*Eval(x1 - h) + 5*Eval(x1) );

    }

    //Calculo do erro, sendo a  4ª derivada calculada através do teorema do valor medio: f''''(c)*(x1-x0)= f'''(x1)-f'''(x0)
    Error = 0.;
    Derivator Deriv(f);
    Error= ( (h*h*h*h) / 180. ) * ( Deriv.Deriv_3(x1, 1e-6, 0) - Deriv.Deriv_3(x0, 1e-6, 0) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Integrator::Romberg(int N, double& Integral, double& Error){

	Integral=0.;

	double h[N+1], r[N+1][N+1];

    for (int i = 1; i < N + 1; ++i)
        h[i] = (x1 - x0) / pow(2, i - 1);
    

    r[1][1] = (h[1] / 2.) * (Eval(x0) + Eval(x1));

    Derivator Deriv(f);
    Error= -( (h[1]*h[1]) / 12. ) * ( ( Deriv.Deriv_1(x1, 1e-5, 0) - Deriv.Deriv_1(x0, 1e-5, 0) ) );

    if(N>1){

        for (int i = 2; i < N + 1; ++i) {

            double coeff = 0;

            for (int k = 1; k <= pow(2, i - 2); ++k) 
                coeff += Eval(x0 + (2 * k - 1) * h[i]);
            
            r[i][1] = 0.5 * (r[i - 1][1] + h[i - 1] * coeff);
        }
        
        for (int i = 2; i < N + 1; ++i) {
            
            for (int j = 2; j <= i; ++j)
                r[i][j] = r[i][j - 1] + (r[i][j - 1] - r[i - 1][j - 1]) / (pow(4, j - 1) - 1);
            
        }

        //Error= (r[N][N]-r[N-1][N-1]) / ( (h[N-1]/h[N]) * (h[N-1]/h[N]) - 1);
        Error= (r[N][N]-r[N-1][N-1]) / r[N][N];
    }

   Integral=r[N][N];

}
/*
void Integrator::Romberg(int N, double& Integral, double& Error){

    Integral=0.;
    Error=0.;

    double h[N], r[N][N];

    for (int i = 0; i < N ; ++i)
        h[i] = (x1 - x0) / pow(2, i);
    

    r[0][0] = h[0] / 2 * (Eval(x0) + Eval(x1));

    for (int i = 1; i < N ; ++i) {

        double coeff = 0;

        for (int k = 1; k <= pow(2, i - 1); ++k) 
            coeff += Eval(x0 + (2 * k - 1) * h[i]);
        
        r[i][1] = 0.5 * (r[i][1] + h[i] * coeff);
    }
    
    for (int i = 1; i < N; ++i) {
        
        for (int j = 1; j <= i; ++j)
            r[i][j] = r[i][j] + (r[i][j] - r[i][j]) / (pow(4, j) - 1);
        
    }

   Integral=r[N][N];

}*/