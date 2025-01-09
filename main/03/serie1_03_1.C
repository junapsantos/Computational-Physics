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

	printf("Inteiro: %lu", sizeof(inteiro));
	printf("Double: %lu", sizeof(duplo));
	printf("short int: %lu", sizeof(sint));
	printf("unsigned int: %lu", sizeof(usint));
	printf("long int: %lu", sizeof(longint));
	printf("float: %lu", sizeof(flutuante));

	return 0;
}