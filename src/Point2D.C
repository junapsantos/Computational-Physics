#include "Point2D.h"
#include <cstdio>

// constructor
Point2D::Point2D(float fx, float fy) : coo(new float[2] {fx, fy}), x(fx), y(fy) {
  // allocate memory + init values
  printf("constructor called (%p) \n", this);
  //  coo = new float[2];
  //  coo[0] = x;
  //  coo[1] = y;  
}

// destructor
Point2D::~Point2D() {
  // deallocate memory
  printf("destructor called (%p) \n", this);
  delete [] coo;
}

// copy constructor
Point2D::Point2D(const Point2D& other) : coo(new float[2] {other.coo[0], other.coo[1]}), x(other.coo[0]), y(other.coo[1]) {
  printf("copy constructor called (obj=%p, other=%p) \n", this, &other);
}

// copy assignment
const Point2D& Point2D::operator=(const Point2D& other) {
  printf("copy assignment (operator=) called (obj=%p, other=%p) \n", this, &other);
  if (this != &other) {
    coo[0] = other.coo[0];
    coo[1] = other.coo[1];    
  }
  x=coo[0];
  y=coo[1];
  return *this;
}

// move  
Point2D::Point2D(Point2D&& other) : coo(other.coo) {
    printf("move constructor called (obj=%p, other=%p) \n", this, &other);  
    other.coo = nullptr;
    x=coo[0];
    y=coo[1];
}  

// ============== operators

Point2D Point2D::operator+(const Point2D& p) const {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  return Point2D(coo[0]+p.coo[0], coo[1]+p.coo[1]);
}

Point2D Point2D::operator-(const Point2D& p) const {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  return Point2D(coo[0]-p.coo[0], coo[1]-p.coo[1]);
}

const Point2D& Point2D::operator+=(const Point2D& p) {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  coo[0] += p.coo[0];
  coo[1] += p.coo[1];
  x=coo[0];
  y=coo[1];
  return *this;
}

const Point2D& Point2D::operator/=(float a) {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  coo[0] /= a;
  coo[1] /= a;
  x=coo[0];
  y=coo[1];
  return *this;
}

float Point2D::operator!() {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  return sqrt(pow(x,2.) + pow(y, 2.));
}

float& Point2D::operator[](int n) {
  printf("[%s]\n", __PRETTY_FUNCTION__);  
  return coo[n];
}

const float& Point2D::operator[](int n) const {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  return coo[n];
}


// ============== friends

ostream& operator<<( ostream& s, const Point2D& p) {
  printf("[%s]\n", __PRETTY_FUNCTION__);  
  s << "[" << p.x << " , " << p.y << "]";
  return s;
}

Point2D operator*(float k, const Point2D& p) {
  float a = k*p.x;
  float b = k*p.y;  
  return Point2D(a, b);
}

// ==============

void Point2D::PrintObject() {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  this->Print();  
}

void Point2D::Print() {
  printf("[%s]\n", __PRETTY_FUNCTION__);
  cout << *this;
}



void Point2D::Dump() const {
  printf("Dump(): this=%p [%f , %f] (%p)\n", this, x, y, coo);
}