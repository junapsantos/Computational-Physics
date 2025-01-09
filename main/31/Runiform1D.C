	#include <cstdio>    //printf
	#include <iostream> //cout
	#include <string>
	#include <math.h> 
	#include "Motion1D.h"
	#include "Uniform1D.h"
    using namespace std;


int main(){     // instantiate object Uniform1D
 
//////////7//// 31 a) /////////////7////////////////////////////
	cout<<"/////////////////MOVIMENTO UNIFORME a)//////////////"<<endl;
	Uniform1D *p1D = new Uniform1D(100, 0., 0., 1000., 10.); // 1000 sec
	p1D->Print();


/////////////// 31 b) //////////////////////////////////////
	// make an array with Motion1D derived objects
	Motion1D* pm[2] = {
	new Uniform1D(100, 0., 0., 500., 20.),
	new Motion1D(400)
	};

	cout<<"/////////////////MOVIMENTO UNIFORME b)//////////////"<<endl;
	pm[0]->Print();
	// fill Motion1D object with values
	
	cout<<"/////////////////QUEDA LIVRE b)//////////////"<<endl;
	int N=pm[1]->GetN();
	printf("Numero de pontos: %d\n",N );

	float*  x=new float [N]; //fiz primeiro a funçao na main, mas depois fiz uma função na classe para a queda livre
	float*  t=new float [N];

	for (int i=0; i<N; i++) {
		t[i]=i+1;	
		x[i]=4.9*t[i]*t[i];					
	}
	pm[1]->SetMotion(t, x, N);
	
	pm[1]->Print();

	cout<<"distância total: "<<pm[1]->TotalDistance()<<endl;


/////////////////31 d)/////////////////
	Motion1D quedalivre(400);
	Motion1D lancamento(400);

	Motion1D m[2]{
		quedalivre,
		lancamento
	};

cout<<"/////////////////QUEDA LIVRE d)//////////////"<<endl;
	m[0].QuedaLivre(); //agora utilizando a função
	m[0].Print();
	
cout<<"/////////////////LANÇAMENTO//////////////"<<endl;
	float*  xd=new float [N];
	float*  td=new float [N];

	float vi;
	cout<<"Qual vai ser a velocidade inicial? "<<endl;
	cin>>vi;

	float tf1=vi/9.8,            //v(t)=v0-9.8t
		  hmax=vi*tf1-4.9*tf1*tf1, //x(t)=x0+v0t-4.9t*t
	      tf2=sqrt(hmax/4.9)+tf1,   //tempo que demora a voltar ao chao
	      dt=tf2/N;             //intervalos de tempo

	for (int i=0; i<N; i++) {
		td[i]=(i+1)*dt;	                //incremento de tempos
		if (td[i]<=tf1){                //preecher array de posicoes (de subida) até atingir hmax
			xd[i]=vi*td[i]-4.9*td[i]*td[i];	
		}
		if(td[i]>tf1){                  //preencher array de posicoes em queda livre a partir de hmax
			xd[i]=hmax-4.9*(td[i]-tf1)*(td[i]-tf1);
		}
						
	}

	m[1].SetMotion(td, xd, N);
	m[1].Print();

	cout<<"distância total: "<<m[1].TotalDistance();
	cout<<"\naltura maxima: " << hmax<<endl;


   /* for(int i = 0; i < 2; i++)  //Destruição dos ponteiros do array gerado (ainda nao consegui)
        delete m[i];
    delete []m;


   /* for(int i = 0; i < N; i++)  //Destruição dos ponteiros do array gerado
      {
        delete t[i];
      }
    delete []t;*/

	return 0;
}

