#include "Vandermonde.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* log10 */
using namespace std;

Vandermonde::Vandermonde():n(0), 					// nb of elements = 0
x(nullptr), y(nullptr), // set null pointers
fPoly(nullptr) {

	Vec v;				//set default vec
	PolCoefs=v;

	FCmatrixFull M;		//set default Matrix
	MatrixCoefs=M; 
};
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////

Vandermonde::Vandermonde(unsigned int Npontos, double x_min, double x_max, const TF1& funcao){
	n = Npontos;

	x = new double [n];
	y = new double [n];

	//calculo do incremento entre os pontos x
	double incremento = (x_max-x_min)/(Npontos-1);

	//atribuir ao x0 o valor inicial, ou seja o primeiro valor do intervalo dado (x_min)
	//preencher array com os pontos x
	for (int i = 0; i < Npontos; i++){

		x[i] = x_min + i*incremento;		F //preenchimento do array que contem os pontos x
		y[i] = funcao.Eval(x[i]);			 //preenchimento do array que contem os pontos y
	}

	vector<Vec> vv;
    Vec v;
    for (int i=0; i<n; i++){
        double* array= new double[n];		 //arrays que vão ser cada um dos Vecs e, posteriormente, cada uma das linhas da matriz
        array[0]=1;							//o primeiro elemento de cada linha é sempre 1

        for(int j=1; j<n; j++)				//preenchimento de cada um dos arrays, sendo o valor de cada um dos elementos, o produto do elemento anterior com o valor de xi 
            array[j] = x[i]*array[j-1];		//(equivalente a xi elevado a k=0, 1..., n-1)    
        
        v.SetEntries(n,array); 				//set entradas do vec= linha i da matriz
        vv.push_back(v);					//colocar esse vec no vetor de vecs
        delete[]array;
    }
    FCmatrixFull MatrixCoefs2(vv);			//criação de uma matriz a partir do vetor de vecs
    MatrixCoefs=MatrixCoefs2;

    Vec vecy(n,y);
    EqSolver E1(MatrixCoefs,vecy);
    PolCoefs = E1.GaussEliminationSolver();	 //=a, Vec resultado da resolucao do sistema Linear Ca=y
   
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

Vandermonde::~Vandermonde(){
	delete[]x;
	delete[]y;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

const Vec& Vandermonde::GetCoefficients(){
	return PolCoefs;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

const FCmatrixFull& Vandermonde::GetMatrix(){
	return MatrixCoefs; 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

//retorna e imprime os valores de x 
const double* Vandermonde::GetX(){
	return x;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

//retorna e imprime os valores de y
const double* Vandermonde::GetY(){
	return y;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

double Vandermonde::GetCoeffError(){
	Vec v(n, y);
	Vec D1 = MatrixCoefs*PolCoefs - v;

	return fabs(D1.maxAbs());
} 

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void Vandermonde::GetInverseMatrix(FCmatrixFull& MatrixCoefs){
	FCmatrixFull invertMC;
	invertMC = MatrixCoefs.getInverse(MatrixCoefs);
	MatrixCoefs=invertMC;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

TGraph& Vandermonde::GetGraphPoints(){
	SetGraphicsPoints();

	TCanvas *gPoints_canvas = new TCanvas("gPoints_canvas", "gPoints_canvas",500,600);
	gPoints_canvas->SetGrid();
	gPoints_canvas -> cd();     //ir para canvas 
	gPoints.Draw("AP");
	gPoints_canvas -> Update();
	gPoints_canvas -> SaveAs("gPoints1.pdf");

	return gPoints;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

TF1* Vandermonde::GetPolyFunc(){
	SetPolynomialFunction();

	TCanvas *cPoly = new TCanvas("cPoly", "cPoly");
	fPoly -> GetXaxis()->SetTitle("X");
	fPoly -> GetYaxis()->SetTitle("Y");
    cPoly -> cd();   									  //ir para canvas 
    fPoly -> Draw();      							      //desenhar func1
    cPoly -> SaveAs("PolyFunc.pdf");

    return fPoly;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void Vandermonde::SetGraphicsPoints(){
	TGraph gPoints_aux(10, x, y);
	gPoints = gPoints_aux;
	gPoints.SetMarkerColor(38);
	gPoints.SetMarkerStyle(20);
	gPoints.SetMarkerSize(2);
	gPoints.SetLineStyle(3);
	gPoints.SetTitle("gPoints");
	gPoints.GetXaxis()->SetTitle("X");
	gPoints.GetXaxis()->SetRangeUser(x[0], x[n]);

	double *y_aux = new double [n];
	y_aux = y;
	for(int i = 0; i < n; i++){
		if(y_aux[0] < y_aux[i])
			y_aux[0] = y_aux[i];
	}

	gPoints.GetXaxis()->SetRangeUser(0.0, y_aux[0]);
	gPoints.GetYaxis()->SetTitle("Y");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void Vandermonde::SetPolynomialFunction(){

	fPoly = new TF1("fPoly", 
		
			[&](double*x, double *a){
				double Px=0;
				for(int i = 0; i < n; i++)
					Px+=PolCoefs[i]*pow(x[0], i);
				return Px;},

			x[0],x[n-1],0); 

    fPoly -> SetTitle("fPoly");
    fPoly->SetLineColor(kRed+2);
    fPoly -> SetLineStyle(1);
}

