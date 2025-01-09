#include <cstdio> //printf

int addnumbers(int a , int b )
{
	int sum = 0;
	for(int i = a; i<=b; i++) {
	sum += i;
	}

	return sum;
}

int main()
{
	int sum;

	sum = addnumbers(3, 5);

	printf("%d\n", sum);

	return 0;
}

