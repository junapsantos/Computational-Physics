#include <cstdio>

double sum(double* v, int n){

	double sum;

	for(int i = 0; i < n; i++){

		sum += v[i];
	}

	return sum;
}


int main(){

	int n;
	double *v;
	double soma;

	n = sizeof(v);

	soma = sum(v, n);

	printf("%lf\n", soma);

	return 0;
}