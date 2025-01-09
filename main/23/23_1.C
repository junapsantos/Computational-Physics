	#include <cstdio>    //printf
	#include <iostream> //cout
	#include <cstdlib>  //exit, rand, getchar
	#include <cmath>    //sin, cos
    #include <ctime>    //time()
	#include <map>
	#include <vector>
	#include <utility>
	#include <algorithm>
	#include <list> // list
	#include <string>
    using namespace std;

    
struct Matrix{ //estrutura da matrix
  string name;
  int nrows;
  int mcols;
  int** mx;
};


Matrix GetMatrix (int n, int m, int**Mx){ //função para preencher as matrizes com os elementos inseridos
	Matrix M;
	M.nrows=n;
	M.mcols=m;
	M.mx=Mx;
  	printf("\nIntroduza os elementros da matriz %dx%d: \n",M.nrows,M.mcols);
    for(int i = 0; i < M.nrows; i++){
        for(int j = 0; j < M.mcols; j++){
            cin>>M.mx[i][j];	
        }
    }

return M;
}

Matrix Mmapfind(Mmap<string, Matrix> , string d){
	Matrix M;

 	M.mx=Mmap.find(d)->second;
 	return matrix;
}


int main(){

	map <string, Matrix > Mmap; //Criação do map com base num par de string e struct
  	map <string, Matrix >::iterator i = Mmap.begin();; //Criação de um iterator para indicar a posição das structs dentro do map
  	//map<string,Matrix>::key_compare mycomp = Mmap.key_comp();


	Matrix A;  //criar a matriz
	A.name= "a";
	int**MA=new int *[2];  //alocar a memoria para a matriz com as dimensoes pedidas
	for (int i = 0; i < 2; ++i){
  		 MA[i] = new int[3];
  	}

	A= GetMatrix (2, 3, MA); //chamar a funçao para preencher a matrix

	Matrix B;
	B.name= "b";
	int**MB=new int *[3];
	for (int i = 0; i < 3; ++i){
  		 MB[i] = new int[3];
  	}

	B= GetMatrix (3, 3, MB);

	Matrix C;
	C.name= "c";
	int**MC=new int *[3];
	for (int i = 0; i < 3; ++i){
  		 MC[i] = new int[2];
  	}

	C= GetMatrix (3,2, MC);


  //print do conteudo de cada uma das estruturas matrix
  for (i=Mmap.begin(); i!=Mmap.end(); ++i){
     	cout << i->first <<"=> Name: "<< i->second.name <<"; nrows: "<<i->second.nrows<<"; mcols: "<< i->second.mcols<<"; matrix: ";

  		for(int i2 = 0; i2 < i->second.nrows; i2++){
  			cout<<"\n";

       		for(int j = 0; j < i->second.mcols; j++){    

     		 	cout<<i->second.mx[i2][j]<<" ";
    		}
    	}

    	cout<<"\n";
	}

	cout<<endl; 
	
	Mmap.insert (pair<string,Matrix>("A",A));
	Mmap.insert (pair<string,Matrix>("b",B));
	Mmap.insert (pair<string,Matrix>("c",C));

	string mr; 
 	cout<<"Que matriz quer imprimir: "<<endl;
 	cin>>mr;



//libertar memoria
	for (int i=0; i<2; ++i){ 
        delete A.mx[i];
    }
	delete [] A.mx;


	for (int i=0; i<3; ++i){  
        delete B.mx[i];
    }
	delete [] B.mx;

	for (int i=0; i<3; ++i){ 
        delete C.mx[i];
    }
	delete [] C.mx;


return 0;
}

