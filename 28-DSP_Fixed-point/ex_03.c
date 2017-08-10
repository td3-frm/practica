#include <math.h>
#include <stdio.h>

#define FRACTIONAL_BITS 4

typedef char  int8_t;
typedef short int16_t;
typedef int   int32_t;
typedef unsigned int   uint32_t;
typedef long long int  int64_t;

typedef double fp_t;
typedef int64_t integer;

int32_t truncation ( int64_t x, uint32_t n)
{
	int32_t x_t;
	
	x_t = (int32_t) ( x  >> n);
	 
	return	x_t;  
}

int32_t roundoff ( int64_t x, uint32_t n)
{
	int32_t x_t;
	int64_t x_r;
	
	x_r = x + (int64_t) ( 1 << (n-1) )  ;
	
	x_t = (int32_t) ( x_r  >> n);
	 
	return	x_t; 
}

int32_t fp2fx ( fp_t x, uint32_t n)
{
	int32_t X;

	X =  (int32_t) ( ( x * (1 << n) ) );
	
	return	X; 
}


fp_t fx2fp ( int64_t X, uint32_t n)
{
	fp_t x;

	x = (fp_t) (X) / (1 << n); 

	return	x; 
}

void main (void)
{
	fp_t a, b, c_test, c_trunc, c_round, c_test_fx;
	int32_t A, B, C1, C2, C3;
	int64_t C;
	uint32_t N;	

	a =  1.11;
	// b =  2.0; 	// c = 2.22
	// b =  2.2532; // c = 2.5010
	// b =  2.24; 	// c = 2.48
	// b =  2.46; 		// c = 2.74
	b =  2.51; 		// c = 2.7861
	
	
	A = fp2fx (a, FRACTIONAL_BITS);
	B = fp2fx (b, FRACTIONAL_BITS);

	C = (A * B);
	
	C1 = truncation ( C , FRACTIONAL_BITS);	
	C2 = roundoff   ( C , FRACTIONAL_BITS);	
	
	c_test = a * b;
	c_test_fx = fx2fp ( C, 2*FRACTIONAL_BITS);
	c_trunc = fx2fp ( C1, FRACTIONAL_BITS);
	c_round = fx2fp ( C2, FRACTIONAL_BITS);
	
	printf("A = %d \n", A );
	printf("B = %d \n", B );
	printf("C = %lld \n", (long long unsigned int) C );

	// printf("C1 = 0x%X \n", C1 );
	// printf("C2 = 0x%X \n", C2 );
			
	printf("C test double = %.20f \n", c_test );
	printf("C test fixed  = %.20f \n", c_test_fx );
	printf("C truncation  = %.20f \n", c_trunc );
	printf("C roundoff    = %.20f \n", c_round );
}



