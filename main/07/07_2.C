
	#include <cstdio> 
	#include <iostream>
	int addnumbersS1 (int a, int b )
	{
	  int sum = 0;

	  for (int i = a; i <= b; i++)
	  {
	  	sum += i*i;
	  }

	  return sum;
	}

int addnumbersS2 (int a, int b )
	{
	  double sum = 0;

	  for (int i = a; i <= b; i++)
	  {
	  	sum += i*i;
	  }
	  return sum;
	}

	int main (){
		int sumint,a,b,test;
		double sumdobro;

		test=scanf("%d %d", &a,&b);

		while (test!=2 || a<0 || b<0)
		{
			while(getchar()!=10);
   			printf("Insira 2 numeros inteiros!\n");
   			test=scanf("%d %d", &a,&b);
   		}
   		
		sumint=addnumbersS1(a,b);
		sumdobro=addnumbersS2(a,b);

		printf("%d \n", sumint);
		printf("%lf \n", sumdobro);

		return 0;
	}

	