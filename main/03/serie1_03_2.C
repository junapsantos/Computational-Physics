#include <cstdio>
#include <iostream>

int main()
{	
	int inteiro;
	double duplo;
	short int sint;
	unsigned int usint;
	long int longint;
	float flutuante;
	long double ldouble;

	printf("Inteiro: %lu \n", sizeof(inteiro));
	printf("Double: %lu \n", sizeof(duplo));
	printf("short int: %lu \n", sizeof(sint));
	printf("unsigned int: %lu \n", sizeof(usint));
	printf("long int: %lu \n", sizeof(longint));
	printf("float: %lu \n", sizeof(flutuante));
	printf("Long double: %lu\n", sizeof(ldouble));

	return 0;
}