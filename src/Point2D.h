#ifndef __Point2D__
#define __Point2D__

#include <iostream> // ostream
#include <cstdio>
#include <algorithm> // std::swap
#include <utility> // std::exchange
using namespace std;

class Point2D {

public:

	Point2D(float fx=0., float fy=0.);
	~Point2D(); 									//destructor

	Point2D(const Point2D&); 						// copy constructor
	const Point2D& operator=(const Point2D&); 		// copy assignment
	Point2D(Point2D&&); 							// move constructor
   
	const Point2D& GetObject() {return *this;}

	// ------- operators

	Point2D operator+(const Point2D&) const;
	Point2D operator-(const Point2D&) const;
	const Point2D& operator+=(const Point2D&);  
	const Point2D& operator/=(float);    

	float operator!(); 								// norma sqrt(x^2 + y^2)

	// -------- access operator

	float& operator[](int n); 						// Point2D P, P[0]=10;
	const float& operator[](int n) const;   
	  
	// -------- friends

	friend ostream& operator<<(ostream& s, const Point2D& );
	friend Point2D operator*(float, const Point2D&); // Point2D P2 = 4*P1
	  
	// ------- other
	void Dump() const;

	void PrintObject();
	void Print();

private:
	double x; // x coo
	double y; // y coo
	float* coo; // Point2Der 
};


#endif