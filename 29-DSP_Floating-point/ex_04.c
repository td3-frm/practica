#include <stdio.h>
#include <float.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>

// compile: gcc -Wall -O3 -std=c99 ex_04.c -o ex_04 -lm -march=corei7 -frounding-math -fsignaling-nans

#define _GNU_SOURCE 1
#define _ISOC99_SOURCE
#include <fenv.h>

/*  FUNCTION DECLARED IN fenv.h */

// int feclearexcept(int excepts);
// int fegetexceptflag(fexcept_t *flagp, int excepts);
// int feraiseexcept(int excepts);
// int fesetexceptflag(const fexcept_t *flagp, int excepts);
// int fetestexcept(int excepts);
// int fegetround(void);
// int fesetround(int rounding_mode);
// int fegetenv(fenv_t *envp);
// int feholdexcept(fenv_t *envp);
// int fesetenv(const fenv_t *envp);
// int feupdateenv(const fenv_t *envp);
       
void show_fe_exceptions(void);
        
int main(void)
{	
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

void show_fe_exceptions(void)
{
	int raised;
	
  // FE_DIVBYZERO	Pole error: division by zero, or some other asymptotically infinite result (from finite arguments).
  // FE_INEXACT	Inexact: the result is not exact.
  // FE_INVALID	Domain error: At least one of the arguments is a value for which the function is not defined.
  // FE_OVERFLOW	Overflow range error: The result is too large in magnitude to be represented as a value of the return type.
  // FE_UNDERFLOW	Underflow range error: The result is too small in magnitude to be represented as a value of the return type.

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

