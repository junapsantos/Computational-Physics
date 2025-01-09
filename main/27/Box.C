#include <algorithm> // std::swap
#include <utility> // std::exchange
#include "Box.h"
#include <cstdio>


Box Box::operator+(const Box& A) {
return Box(x+A.x , y+A.y, z+A.z);}


Box* Box::Add(Box *A){
	Box* B= new Box (); 
	B->x=x+A->x;
	B->y=y+A->y;
	B->z=z+A->z;
return B; 
}

void Box::Addv(Box *A){
	this->x+=A->x;
	this->y+=A->y;
	this->z+=A->z;
}

