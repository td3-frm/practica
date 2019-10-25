#include <stdio.h>
#include <float.h>
#include <math.h>
#include <fenv.h>

// compile: gcc -Wall -O3 -std=c99 ex_01.c -o ex_01
 
float mysum(float x, unsigned int N);

int main(void)
{	
	float a, b, c, f1, f2;
	double d1;
	unsigned long int N;
	
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
	printf("Error en d1 = %10e \n", d1 - 400000000000000000000000.0 );
	
	float acum_1, acum_2;
	
	N = 10000;
	
	acum_1 = 0.0;
	acum_1 = mysum( 0.01, N );
	printf("\nacum_1 = %.20f \n", acum_1 );
	printf("Error en acum_1 = %.20f \n", acum_1 - ( 100 ));

	acum_2 = 0.0;
	acum_2 = fabsf ( (N/10) - mysum(0.1, N) ) ;
	printf("Error en acum_2 = %.20f \n", acum_2 - (0.0));
	
	return 0;
}

float mysum(float x, unsigned int N)
{
		float acum;
		unsigned int i;
		
		acum = 0.0;
		
		for (i = 0; i < N; i++)
		{ 
			acum += x;
		}
	
	return acum;
}

