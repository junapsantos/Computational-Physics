	#include <cstdio> 
	#include <iostream>
	#include <cstdlib>
	#include <cmath>

double sen2 (double x)
{
double f;
f= sin(x)*sin(x);
return f;
}

int main()
{
double z,x=0.4;
z=x+ sen2(x);
printf("z(%3.2f)=%f\n",x,z );

x=2.1;
z=x+ sen2(x);
printf("z(%3.2f)=%f\n",x,z );

x=1.5;
z=x+ sen2(x);
printf("z(%3.2f)=%f\n",x,z );
return 0;
}