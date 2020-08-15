// Version: 001
// Date:    2020/03/19
// Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>

#include <stdio.h>
#include <float.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>

// Compile usando el siguiente comando
// compile: gcc -Wall -O3 -std=c99 ex_04.c -o ex_04 -lm -march=corei7 -frounding-math -fsignaling-nans

#define _GNU_SOURCE 1
#define _ISOC99_SOURCE
#include <fenv.h>

void show_fe_exceptions(void)
{
	int raised;
	
    printf("Current exceptions raised: ");
    
    raised = fetestexcept (FE_DIVBYZERO);
    if(raised & FE_DIVBYZERO)     printf("FE_DIVBYZERO");
    
    raised = fetestexcept (FE_INEXACT);
    if(raised & FE_INEXACT)       printf("FE_INEXACT");
    
    raised = fetestexcept (FE_INVALID);
    if(raised & FE_INVALID)       printf("FE_INVALID");
    
    raised = fetestexcept (FE_OVERFLOW);
    if(raised & FE_OVERFLOW)      printf("FE_OVERFLOW");
    
    raised = fetestexcept (FE_UNDERFLOW);
    if(raised & FE_UNDERFLOW)     printf("FE_UNDERFLOW");
    
    raised = fetestexcept (FE_ALL_EXCEPT);
    if( (raised & FE_ALL_EXCEPT) == 0) printf("None exceptions");
    
    printf("\n");
}
     
int main(void)
{	
	int ROUND_MODE;
	
	ROUND_MODE = fegetround();		
	printf("Current Round Mode = %d \n", ROUND_MODE );
		
  show_fe_exceptions();
      
  /* Temporarily raise other exceptions */
  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_INEXACT);
  show_fe_exceptions();
    
  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_INVALID);
  show_fe_exceptions();

  feclearexcept(FE_ALL_EXCEPT);    
  feraiseexcept(FE_DIVBYZERO);
  show_fe_exceptions();

  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_OVERFLOW);
  show_fe_exceptions();

  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_UNDERFLOW);
  show_fe_exceptions();

	return 0;	
}
