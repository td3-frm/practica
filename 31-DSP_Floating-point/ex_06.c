// Version: 003
// Date:    2021/10/22
// Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>

#define _GNU_SOURCE 1
#define _ISOC99_SOURCE
#include <fenv.h>

#include <stdio.h>
#include <float.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>

// Compile usando el siguiente comando
// compile: gcc -Wall -std=c99 ex_06.c -o ex_06 -lm -frounding-math -fsignaling-nans

void show_fe_exceptions(void)
{
	int raised;
	
    printf("Current exceptions raised: ");
    
    raised = fetestexcept (FE_DIVBYZERO);
    if(raised & FE_DIVBYZERO)     printf("FE_DIVBYZERO ");
    
    raised = fetestexcept (FE_INEXACT);
    if(raised & FE_INEXACT)       printf("FE_INEXACT ");
    
    raised = fetestexcept (FE_INVALID);
    if(raised & FE_INVALID)       printf("FE_INVALID ");
    
    raised = fetestexcept (FE_OVERFLOW);
    if(raised & FE_OVERFLOW)      printf("FE_OVERFLOW ");
    
    raised = fetestexcept (FE_UNDERFLOW);
    if(raised & FE_UNDERFLOW)     printf("FE_UNDERFLOW ");
    
    raised = fetestexcept (FE_ALL_EXCEPT);
    if( (raised & FE_ALL_EXCEPT) == 0) printf("None exceptions 	");
    
    printf("\n");
    printf("raised = %d \n", raised);
    printf("\n");
}

void test_fe_exceptions(int FE_EXCEPT)
{
  printf ("Forcing fe exceptions %d \n", FE_EXCEPT); 	
  
  feclearexcept(FE_EXCEPT);
  feenableexcept(FE_EXCEPT);  
  feraiseexcept(FE_EXCEPT);
  fedisableexcept(FE_EXCEPT); 
}
	    
void fpe_handler(int sig){
	
  printf ("UPS! Floating Point Exception \n");
  printf ("sig = %d \n", sig);
  
  show_fe_exceptions();
  
  exit(EXIT_FAILURE);
}

int main(void)
{	
  feclearexcept (FE_ALL_EXCEPT);
	
  signal(SIGFPE, fpe_handler);
  
  test_fe_exceptions(FE_INVALID);
  
  // test_fe_exceptions(FE_DIVBYZERO);

  // test_fe_exceptions(FE_OVERFLOW);

  // test_fe_exceptions(FE_UNDERFLOW);

  // test_fe_exceptions(FE_INEXACT);  
 
  return 0;
	
}
