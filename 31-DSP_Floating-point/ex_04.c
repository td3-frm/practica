// Version: 002
// Date:    2022/04/05
// Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>

#include <stdio.h>
#include <float.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>

// Compile usando el siguiente comando
// compile: gcc -Wall -O3 -std=c99 ex_04.c -o ex_04 -lm -frounding-math -fsignaling-nans

#define _GNU_SOURCE 1
#define _ISOC99_SOURCE
#include <fenv.h>

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
  
  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_OVERFLOW | FE_INEXACT);
  show_fe_exceptions();

	return 0;	
}
