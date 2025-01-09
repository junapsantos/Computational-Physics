#ifndef __Uniform1D__
#define __Uniform1D__

#include"Motion1D.h"
#include <string>
#include <iostream>
#include <math.h> 
using namespace std;

class Uniform1D : public Motion1D {
public:

	Uniform1D( // default constructor
	int fN=0, // number of points (number of steps + 1)

	float ti=0., // initial time

	float xi=0., // initial position

	float dt=0., // time range

	float vel=0.); // velocity

	~Uniform1D();

	void Print();

private:
	float ti;  // initial time
	float dt;  // time duration
	float xi;  // initial position
	float vel; // velocity (m/s)
};
#endif