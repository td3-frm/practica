

#include <math.h>
#include <stdio.h>

#define INTEGER_BITS 15
#define FRACTIONAL_BITS 16

typedef char  int8_t;
typedef short int16_t;
typedef int   int32_t;
typedef unsigned int   uint32_t;
typedef long long int   int64_t;

typedef float fp_t;
typedef int32_t integer;

integer fp2fx ( fp_t x, uint32_t n)
{
	integer X;

	X =  (integer) ( ( x * (1 << n) ) );
	
	return	X; 
}


fp_t fx2fp ( integer X, uint32_t n)
{
	fp_t x;

	x = (fp_t) (X) / (1 << n); 

	return	x; 
}

void main (void)
{
	fp_t a, b;
	integer X;
	uint32_t N;

	a = -455.2458;

	X = fp2fx (a, FRACTIONAL_BITS);
	b = fx2fp (X, FRACTIONAL_BITS);

	printf("X = %d \n", X );
	printf("b = %f \n", b );
}

