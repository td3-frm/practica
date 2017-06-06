#include <math.h>
#include <stdio.h>

typedef char  int8_t;
typedef short int16_t;

void main(void)
{	
	signed char  a, b, f;
	short c, d;

	a = 127;
	b = 127;
	
	c =  (short)a + (short)b;
	d =  (short)a * (short)b;
	
	f = (-8) >> 2;

	printf("c = %d \n", c );
	printf("d = %d \n", d );
	printf("f = %d \n", f );
}
