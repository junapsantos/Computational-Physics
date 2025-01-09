	#include <cstdio> 
	#include <iostream>
	#include <cstdlib>
	#include <cmath>

int main(){
	double sum = 0.0;
	for (double x=0.0; x<5.4; x=x+ 0.1) 
	{
		sum += x;
	}
	printf("o resultado é %lf\n",sum );
	return 0;
}