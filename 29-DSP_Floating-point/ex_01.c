// Version: 001
// Date:    2020/03/19
// Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>

#include <stdio.h>
#include <float.h>
#include <math.h>
#include <fenv.h>

typedef long int int64_t

int main(void)
{	
	float a, b, c, f1, f2;
	double d1;

	a = 1000000000.0;
	b =   20000000.0;
	c =   20000000.0;
	
	f1 = (a * b) * c;
	f2 = a * (b * c);

	d1 = (double) (a) * (double) (b) * (double) (c);

	printf("f1 = %f \n", f1 );
	printf("f2 = %f \n", f2 );
	printf("d1 = %lf \n", d1 );
	
	printf("Error en f1 = %10e \n", f1 - 400000000000000000000000.0 );
	printf("Error en f2 = %10e \n", f2 - 400000000000000000000000.0 );
	printf("Error en d1 = %20e \n", d1 - 400000000000000000000000.0 );
	
	double acum_1, acum_2;
	
	acum_1 = 0.0;
	for (int64_t i = 0; i < 10000000; i++){ acum_1 += 0.01; } 

	acum_2 = 0.0;
	b = 0.01;
	for (int64_t i = 0; i < 10000000; i++){ acum_2 += b / b; }
	
	printf("acum_1 = %f \n", acum_1 );
	printf("acum_2 = %f \n", acum_2 );
	
	printf("Error en acum_1 = %.20lf \n", acum_1 - (10000000.0 * 0.01));
	printf("Error en acum_2 = %.20lf \n", acum_2 - (10000000.0));
	
	return 0;
}
