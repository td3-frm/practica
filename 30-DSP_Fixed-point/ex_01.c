#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

// Para usar la biblioteca <math.h>, compilar con "-lm", por ejemplo:
// gcc ex_01.c -o ex_01 -lm

int main(void)
{	
	int8_t a, b, c, d, s1, s2;
	 
	a = 127;
	b = 127;
	
	c = a + b;	
	d = a * b;
	
	s1 = (-8) >> 2;
	s2 = (-1) >> 5;

	printf("INT_MAX = %d \n" , INT_MAX);
	printf("INT_MIN = %d \n" , INT_MIN);
	
	printf("c = %d \n", c );
	printf("d = %d \n", d );
	printf("s1 = %d \n", s1 );
	printf("s2 = %d \n", s2 );
	
	return 0;
}
