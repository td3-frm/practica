/*
 * El objetivo de este programa es ver cómo se habilitan habilitan las
 * diferentes excepciones y cómo se manejan con una señal.
 * 
 */ 


#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <float.h>
#include <math.h>
#include <fenv.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/* COMPILA CON
	
	gcc -o ex_05 ex_05.c -lm 
*/

void show_fe_exceptions(void)
{
    printf("current exceptions raised: ");
    if(fetestexcept(FE_DIVBYZERO))     printf(" FE_DIVBYZERO");
    if(fetestexcept(FE_INEXACT))       printf(" FE_INEXACT");
    if(fetestexcept(FE_INVALID))       printf(" FE_INVALID");
    if(fetestexcept(FE_OVERFLOW))      printf(" FE_OVERFLOW");
    if(fetestexcept(FE_UNDERFLOW))     printf(" FE_UNDERFLOW");
    if(fetestexcept(FE_ALL_EXCEPT)==0) printf(" none");
    printf("\n");
}
 
 
void fpe_handler(int sig){
	
	//~ if (sig != SIGFPE)
		//~ return;
	printf ("UPS! Floating Point Exception \n");
	
	show_fe_exceptions();
	
	exit(EXIT_FAILURE);
}

int main(void)
{	
	float c;

	signal(SIGFPE, fpe_handler);

	feenableexcept(FE_INVALID   | 
				   FE_INEXACT   | 
                   FE_DIVBYZERO | 
                   FE_OVERFLOW  | 
                   FE_UNDERFLOW);
                   
	//feclearexcept(FE_ALL_EXCEPT);
	// c = 0.0/0.0;
	//~ printf ("c =  %f \n", c);
	
	//~ feclearexcept(FE_ALL_EXCEPT);
	//~ c = 2.0/3.0; 
	//~ printf ("c =  %f \n", c);	
		
	//~ feclearexcept(FE_ALL_EXCEPT);
	//~ c = 1.17549435e-38 / 3.0;
		
	// feclearexcept(FE_ALL_EXCEPT);
	//~ c = 3.40282347e+38 * 3.40282347e+38;

	//~ feclearexcept(FE_ALL_EXCEPT);
	//~ c = 1.0 / 0.0;

	exit(EXIT_SUCCESS);
}
