#include <cstdio>
#include <limits>

// numeric_limits<type>::max() //largest type value
// numeric_limits<type>::min() //smallest type value
using namespace std;


int main()
{

	printf( "Maximo Int: %d\n", numeric_limits<int>::max());
	printf( "Mínimo Int: %d\n", numeric_limits<int>::min());
	printf( "Maximo Unsigned Int: %u\n", numeric_limits<unsigned int>::max());
	printf( "Mínimo Unsigned Int: %u\n", numeric_limits<unsigned int>::min());
	printf( "Maximo float: %f\n", numeric_limits<float>::max());
	printf( "Mínimo float: %.40f\n", numeric_limits<float>::min());
	printf( "Maximo double: %lf\n", numeric_limits<double>::max());
	printf( "Mínimo double: %.400lf\n", numeric_limits<double>::min());

	return 0;
}