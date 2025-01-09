	#include <cstdio> 
	#include <iostream>
	#include <cstdlib>
	#include <cmath>

double Sum(int* vi, int* vj){
	double sum;
	for (int i=vi[0]; i<vi[1];i++){
			for (int j=vj[0]; j<vj[1]; j++){
				sum+=cos(i*i+sqrt(j));
			}

		}	
	return sum;
}

int main(){
	double result;
	int vi[]={0,100},vj[]={5,300};

	result= Sum(vi, vj);
	printf("%lf\n",result );

	return 0;
}