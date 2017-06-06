#include <stdio.h>
#include <float.h>
#include <math.h>
#include <fenv.h>

int main(void)
{	
	float a, b, c, r1, r2;
	double ad, bd, cd, rd;

	a = 1000000000.0;
	b = 20000000.0;
	c = 20000000.0;
	
	ad = 1000000000.0;
	bd = 20000000.0;
	cd = 20000000.0;	
	
	r1= (a * b) * c;
	r2 = a * (b * c);
	
	rd = ad * (bd * cd);
	
	printf("r1 = %f \n", r1 );
	printf("r2 = %f \n", r2 );
	printf("rd = %f \n", rd );
	printf("err_rd1 = %f \n", rd - (double) r1 );	
	printf("err_rd2 = %f \n", rd - (double) r2 );	
	printf("error = %f \n", r1 - r2 );

	return 0;
}
