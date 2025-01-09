	#include <cstdio> 
	#include <iostream>
	#include <cstdlib>
	#include <cmath>

int descobertadoano(int x)
{
int quadrado=0,i;

for (i=0; i<x;i++)
	{
		quadrado+=x;
	}

return quadrado;
}


int main ()
{
	int quadrado;

	quadrado= descobertadoano(6);

	printf("%d\n",quadrado);

	return 0;

}
