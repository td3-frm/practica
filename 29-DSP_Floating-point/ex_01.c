#include <stdio.h>
#include <float.h>
#include <math.h>
#include <fenv.h>

int main(void)
{	
	float a, b, c, r1, r2;
	double ad, bd, cd, r1d, r2d;

	a = 1000000000.0;
	b = 20000000.0;
	c = 20000000.0;
	
	ad = 1000000000.0;
	bd = 20000000.0;
	cd = 20000000.0;	
	
	r1= (a * b) * c;
	r2 = a * (b * c);
	
	r1d = (ad * bd) * cd;
	r2d = ad * (bd * cd);
	
	printf("r1 = %f \n", r1 );
	printf("r2 = %f \n", r2 );
	printf("error = %f \n", r1 - r2 );

	printf("r1d = %f \n", r1d );
	printf("r2d = %f \n", r2d );
	printf("size of float  = %ld \n", sizeof(float) );
	printf("size of double = %ld \n", sizeof(double) );	

	return 0;
}
