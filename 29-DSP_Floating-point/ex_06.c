// Version: 001
// Date:    2020/03/19
// Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>

#include <stdio.h>
#include <float.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>

#define _GNU_SOURCE 1
#define _ISOC99_SOURCE
#include <fenv.h>

// Compile usando el siguiente comando
// compile: gcc -Wall -O3 -std=c99 ex_05.c -o ex_05 -lm -march=corei7 -frounding-math -fsignaling-nans
    
void fpe_handler(int sig){
	
  if (sig != SIGFPE)
    return;
	
  printf ("UPS! Floating Point Exception \n");

  if(fetestexcept(FE_INVALID)) printf("FE_INVALID\n");
  if(fetestexcept(FE_INEXACT)) printf("FE_INEXACT\n");
  if(fetestexcept(FE_DIVBYZERO)) printf("FE_DIVBYZERO\n");
  if(fetestexcept(FE_OVERFLOW)) printf("FE_OVERFLOW\n");
  if(fetestexcept(FE_UNDERFLOW)) printf("FE_UNDERFLOW\n");
  if(fetestexcept(FE_ALL_EXCEPT) == 0) printf("None exceptions\n");
		
  exit(EXIT_FAILURE);
}

int main(void)
{	
  int ROUND_MODE;
	
  feclearexcept (FE_ALL_EXCEPT);
	
  // signal(SIGFPE, fpe_handler);
  
  // feenableexcept(FE_INVALID   | 
		   // FE_INEXACT   | 
                   // FE_DIVBYZERO | 
                   // FE_OVERFLOW  | 
                   // FE_UNDERFLOW);
	                 
  ROUND_MODE = fegetround();		
  printf("Current Round Mode = %d \n", ROUND_MODE );
		
  /* Temporarily raise other exceptions. */
  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_INEXACT);
    
  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_INVALID);

  feclearexcept(FE_ALL_EXCEPT);    
  feraiseexcept(FE_DIVBYZERO);

  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_OVERFLOW);

  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_UNDERFLOW);

  return 0;
	
}
