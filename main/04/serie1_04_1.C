	#include <cstdio> 
	#include <iostream>
	#include <cstdlib>
	#include <cmath>


int main()
{

double pidobro;
float piflutuante;

pidobro = atan(1.0)*4.0;

piflutuante = atan(1.0)*4.0;

printf("O pi dobro é %.15lf\nO pi flutuante é %.15f\n", pidobro, piflutuante);

printf("pi-float= %.15f\npi-double= %.567f\n", M_PI-piflutuante, M_PI-pidobro );

printf("%.16f\n",M_PI );

return 0;
}


