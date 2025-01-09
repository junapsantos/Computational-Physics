#include <cstdio>  
#include <iostream> //cout
#include <vector>
#include <utility>
#include <algorithm>
#include <list> // list
#include <string>
#include "box.h"
using namespace std;

class Box {
public:
Box(){
	x=1;
	y=1;
	z=1;
} //cubo de lado 1

~Box()=default;

Box(float fx, float fy, float fz):x(fx), y(fy), z(fz){;}

float GetVolume(){return x*y*z;};

Box operator+(const Box&);

Box* Add(Box*);

void Addv(Box*);

private:
float x;
float y;
float z;
};


