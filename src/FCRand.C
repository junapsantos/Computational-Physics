/*#include "FCRand.h"

FCrand::FCrand(int s, double a, double c, double m) : seed(s), a_multiplicador(a), c_incremento(c), modulo(m) {

	seed = (a_multiplicador * seed + c_incremento) / modulo;
}


//gerar nr entre 0 e 1 - distribuicao uniforme
float FCrand::GetRandom(){
	//distribuicao uniforme de floats
	uniform_real_distribution <float> x_distribuicao(0.f, 1.f);
	x = x_distribuicao(); 

	return x;
}

//gerar nr entre min e max - distribuicao uniforme
float FCrand::GetRandom(float min, float max){
	uniform_real_distribution <float> x_distribuicao(min, max);
	x = x_distribuicao(); 

	return x;
}


//gerar N nrs entre 0 e 1
float* FCrand::GetRandom(int N){

	for(int i = 0; i < N; i++){
		uniform_real_distribution <float> x_distribuicao(0.f, 1.f);
		y[i] = x_distribuicao(); 
	}

	return y;
}

float* FCrand::GetRandom(int N, float min, float max){

	for(int i = 0; i < N; i++){
		uniform_real_distribution <float> x_distribuicao(min, max);
		y[i] = x_distribuicao(); 
	}

	return y;
}*/
