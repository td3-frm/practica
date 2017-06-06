/*
 * El objetivo de este programa es el de ver cómo se establecen los diferentes
 * modos de redondeo en punto flotante.
 * 
 */

#include <stdio.h>
#include <float.h>
#include <math.h>
#include <fenv.h>

// compile: gcc -Wall -O3 -std=c99 ex_02.c -o ex_02 -lm -march=corei7 -frounding-math -fsignaling-nans

void test_rounding (void)
{
  	float fp1, fp2;

 	fp1 = exp(1.1);
 	printf(" exp(1.1) = %0.8f\n", fp1);
 
 	fp2 = -exp(1.1); 
 	printf("-exp(1.1) = %0.8f\n", fp2);
}

void test_rounding_double (void)
{
  	double fp1, fp2;

	printf("DOUBLE precision\n");

 	fp1 = exp(1.1);
 	printf(" exp(1.1) = %0.16f\n", fp1);
 
 	fp2 = -exp(1.1); 
 	printf("-exp(1.1) = %0.16f\n", fp2);
}


void current_rounding (void)
{
	int ROUND_MODE;
	
	ROUND_MODE = fegetround();	
	printf("Current Round Mode = %d \n", ROUND_MODE );
}

void change_rounding (int rounding_mode)
{
	fesetround (rounding_mode);	
}

int main(void)
{	
	printf("** Floating point constants ** \n");
	printf("FLT_MIN 	= %E \n", 	FLT_MIN );
	printf("FLT_MAX 	= %E \n", 	FLT_MAX );
	printf("FLT_EPSILON	= %E \n", 	FLT_EPSILON );
	printf("\n");

	printf("** Floating point rounding modes ** \n");
	printf("Rounding Mode FE_TONEAREST	= %d \n", 	FE_TONEAREST );
	printf("Rounding Mode FE_DOWNWARD	= %d \n", 	FE_DOWNWARD );
	printf("Rounding Mode FE_UPWARD		= %d \n", 	FE_UPWARD );
	printf("Rounding Mode FE_TOWARDZERO	= %d \n", 	FE_TOWARDZERO );
	printf("\n");
	
	test_rounding_double();
	printf("\n");

	current_rounding();
	test_rounding();
	printf("\n");

	change_rounding(FE_DOWNWARD);
	current_rounding();
	test_rounding();
	printf("\n");
	
	change_rounding(FE_UPWARD);
	current_rounding();
	test_rounding();
	printf("\n");

	change_rounding(FE_TOWARDZERO);
	current_rounding();
	test_rounding();
	printf("\n");
	
	return 0;
}
