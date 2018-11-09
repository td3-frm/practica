#include <stdio.h>
#include <float.h>
#include <math.h>
#include <fenv.h>

typedef float fp32_t;
typedef double fp64_t;

int main(void)
{	
	fp32_t a, b, c, r1, r2;
	fp64_t dr3;

	a = 1000000000.0;
	b =   20000000.0;
	c =   20000000.0;

	r1 = (a * b) * c;
	r2 = a * (b * c);

	dr3 = (double) (a) * ( (double) (b) * (double) (c) );

	printf("r1 = %f \n", r1 );
	printf("r2 = %f \n", r2 );
	printf("dr3 = %lf \n", dr3 );
	
	printf("error r1 = %10e \n", r1 - 400000000000000000000000.0 );
	printf("error r2 = %10e \n", r2 - 400000000000000000000000.0 );
	
	return 0;
}
