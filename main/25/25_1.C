	#include <cstdio>    //printf
	#include <iostream> //cout
	#include <cstdlib>  //exit, rand, getchar
	#include <cmath>    //sin, cos
    #include <ctime>    //time()
	#include <map>
	#include <vector>
	#include <utility>
	#include <algorithm> //sort
	#include <list> // list
	#include <string>

    using namespace std;


int main(){
 	  
	//usei 2 formas de criar um vetor:

 	//vetor a com inicialização
	vector<int> va={3, 2, 1, 6, 5, 4, 9, 8, 7};
	cout << "\na:";
	for(auto it = va.begin(); it != va.end(); ++it) {
   		cout <<*it << " " ;
	}
  	cout << endl;

  	//vetor b a partir do array b
  	int b[] = {10, 12, 15, 18, 24, 32, 40, 45, 50};
  	vector<int> vb(sizeof(b)/sizeof(int));
  	copy(b, b+9, vb.begin());
  	cout << "\nb:";
  	for(auto it = vb.begin(); it != vb.end(); ++it) {
    	cout <<*it << " " ;
  	}
  	cout << endl;

  	//array aa
  	int aa[9];
  	for (int i=0; i<9; i++){
  		if (va[i]%2!=0){
  			aa[i]=2*va[i];
  		}else{
  			aa[i]=va[i];
  		}
  	}
  	//vetor aa a partir do array aa
  	vector<int> vaa(sizeof(aa)/sizeof(int));
  	copy(aa, aa+9, vaa.begin());
  	cout << "\naa:";
  	for(auto it = vaa.begin(); it != vaa.end(); ++it) {
    	cout<<*it << " " ;
  	}
  	cout << endl;

  	//vetor c com os valores de va seguidos dos numeros de vb que são seus multiplos correspondentes
  	vector <int> vc;
  	for (int i = 0; i!=va.size();++i){
		vc.push_back(va[i]); 
			for (int j = 0;j !=vb.size();++j){
				if (vb[j]%va[i]==0){
					vc.push_back(vb[j]);
				}
			}
	}
	cout << "\nc(valores de va seguidos dos numeros de vb que são seus multiplos correspondentes):\n";
  	for(auto it = vc.begin(); it != vc.end(); ++it) {
    	cout<<*it << " " ;
  	}
  	cout << endl;


  	//sort do vetor c no sentido crescente
	sort(vc.begin(), vc.end(), [](int a, int b){ return a<b; } );

	cout<<"\nc(ordem crescente):"<<endl;
	for(auto it = vc.begin(); it != vc.end(); ++it) {
    	cout<<*it << " " ;
  	}
  	cout << endl;

  	//construçao do vetor c no sentido decrescente
  	for (int i = 0; i!=vc.size();++i){
  		for (int j = 0; j!=vc.size()-i;j++){
  			if(vc[i+j]>vc[i]){
  				int gaveta=vc[i+j];
  				vc[i+j]=vc[i];
  				vc[i]=gaveta;
  			}
  		}
  		
  	}
	cout<<"\nc(ordem decrescente):"<<endl;
	for(auto it = vc.begin(); it != vc.end(); ++it) {
    	cout<<*it << " " ;
  	}
  	cout << endl;


  	va.clear();
  	vb.clear();
  	vaa.clear();
  	vc.clear();
	return 0;
}