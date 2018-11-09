#include <stdio.h>
#include <float.h>
#include <math.h>
#include <fenv.h>

typedef float fp32_t;
typedef double fp64_t;

int main(void)
{	
	fp32_t acc1, acc2;	
	
	acc1 = 0.0;
	for (int i = 0; i < 10000; i++){ acc1 += 0.100; } 

	acc2 = 0.0;
	for (int i = 0; i < 10000; i++){ acc2 += 0.125; }
	
	printf("acc1 = %.20lf \n", acc1 );
	printf("acc2 = %.20lf \n", acc2 );
	
	printf("acc1 error = %.20e \n", 1000 - acc1 );
	printf("acc2 error = %.20e \n", 1250 - acc2 );
	
	return 0;
}
