/*#ifndef __FCRand__
#define __FCRand__

#include <random>			 //uniform_real_distribution
#include <iostream>
#include <ctime>

using namespace std;


class FCrand {
	public:
	//seed number 
	FCrand(int s, double a, double c, double m);
	//generate one random between [0,1]
	float GetRandom();
	//generate one random between [min,max]
	float GetRandom(float min, float max);
	//generate N randoms between [0,1]
	float* GetRandom(int N);
	//generate N randoms between [min,max]
	float* GetRandom(int N, float min, float max);

	private:
	// 0 < a < m
	double a_multiplicador;
	// 0 < c < m
	double c_incremento;
	// m > 0
	double modulo;
	//seed/valor inicial
	int seed;
	//nr aleatorio
	float x;
	//array de nrs aleatorios
	float* y;
	//gerador de nrs pseudo aleatorios
	srand(time(NULL));
};
#endif
*/