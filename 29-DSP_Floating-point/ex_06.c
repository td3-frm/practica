// Version: 002
// Date:    2020/08/20
// Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>

#ifdef LINUX
/* _GNU_SOURCE is needed (supposedly) for the feenableexcept
 * prototype to be defined in fenv.h on GNU systems.
 * Presumably it will do no harm on other systems.
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#endif // LINUX

#include <fenv.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// compile: gcc -Wall -O3 ex_06.c -o ex_06 -lm -DLINUX

//~ jmp_buf fpe;
    
void fpe_handler(int sig){
	
  //~ longjmp(fpe, 1);
  
  exit(EXIT_FAILURE);
}

int main(void)
{	
  feclearexcept (FE_ALL_EXCEPT);
	
  signal(SIGFPE, fpe_handler);
  //~ signal(SIGFPE, SIG_DFL);
  
  feenableexcept(
                 FE_INVALID   | 
             //~ FE_INEXACT   | 
                 FE_DIVBYZERO | 
                 FE_OVERFLOW  | 
                 FE_UNDERFLOW);
	                 
  /* Temporarily raise other exceptions. */
  
  printf("Force FE_INEXACT exception.\n");
  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_INEXACT);
  
  printf("Force FE_INVALID exception.\n");    
  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_INVALID);

  printf("Force FE_DIVBYZERO exception.\n");
  feclearexcept(FE_ALL_EXCEPT);    
  feraiseexcept(FE_DIVBYZERO);

  printf("Force FE_OVERFLOW exception.\n");
  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_OVERFLOW);

  printf("Force FE_UNDERFLOW exception.\n");
  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_UNDERFLOW);

  return 0;
	
}
