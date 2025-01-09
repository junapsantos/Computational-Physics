#include "Material.h"	
#include <iostream>
#include <string>
#include <cstdio>
#include <iostream>

using namespace std;

Material::~Material(){
	cout << __PRETTY_FUNCTION__ << "\n";
}

void Material::Print(){
	cout << "Material: "<<this->name << "\n Densidade: " << this->density << "\n";  
	cout << __PRETTY_FUNCTION__ << "\n";
}



