#ifndef __Motion1D__
#define __Motion1D__

#include <string>
#include <iostream>
#include <math.h> 
using namespace std;


class Motion1D {
public:

	Motion1D(int n=0);

	virtual ~Motion1D();

	void SetMotion(float* t0, float* x0, int n);

	int GetN(); //returns number of points

	float* GetTimes(); // returns array of times

	float* GetPositions(); //returns array of positions

	virtual void Print();

	virtual void QuedaLivre();

	virtual float TotalDistance(); //total distance

	//virtual float MeanVelocity(); //mean velocity

protected:
	int N; //number of points
	float* t; //time array
	float* x; //position array
};

#endif