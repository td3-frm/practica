
#include "fir_filter.h"
#include "fir_coefs.h"


void fir_filter_float(float *input, uint32_t N, float *output)
{
	uint32_t i, j;
	
    float acc;
	
	for (i=0; i < N; i++)
	{
		output[i] = 0.0;
	}	
	
	for (i=0; i < N-M; i++)
	{
		acc = 0.0;
	
		for (j=0; j < M; j++)
		{
			acc = acc + (input[j+i] * fir_coef_f[j]);
		}
		
		output[i+M] = acc;
	}
}

void fir_filter_fixed(float *input, uint32_t N, float *output)
{
	uint32_t i;

	for (i=0; i < N; i++)
	{
		output[i] = input[i];
	}
	
}


