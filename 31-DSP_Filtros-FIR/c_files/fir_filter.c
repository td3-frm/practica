
#include "fir_filter.h"
#include "fdacoefs.h"
#include "mex.h"

// #define DEBUG

void fir_online_float(float *input, float *output)
{
    static uint32_t counter = 0;
    static float cir_buff[101] = {0.0};
    static float * start = &cir_buff[0];   // pointer to the start of the circular buffer
    static float * end = &cir_buff[BL-1];  // pointer to the end of the circular buffer
    static float * head;                    // pointer to the new element at the circular buffer
    
    uint32_t j, idx;
    float acc;
    
#ifdef  DEBUG
    mexPrintf("input = %f \n", *(input) );
#endif
    
#ifdef  DEBUG
    mexPrintf("output = %f \n", *(input) );
#endif
    
    idx = counter % BL;             // modulus operator
    counter++;

    cir_buff[idx] = *(input);       // load new element to the circular buffer
    head = &cir_buff[idx];          // pointer new element at the circular buffer
    
    acc = 0.0;
    
    for (j = 0; j < BL; j++)
    {
        acc = acc + ( *(head--) * B[j] );
        
        if(head < start){
            head = end;
        }        
    }
    
#ifdef  DEBUG
    mexPrintf("acc = %f \n", acc);
#endif
    
    *(output) = acc;
}


void fir_offline_float(float *input, uint32_t N, float *output)
{
	uint32_t i, j;

    float acc;

	for (i=0; i < N; i++)
	{
		output[i] = 0.0;
	}

	for (i=0; i < N-BL; i++)
	{
		acc = 0.0;

		for (j=0; j < BL; j++)
		{
			acc = acc + (input[j+i] * B[j]);
		}

		output[i+BL] = acc;
	}
}

void fir_online_fixed(float *input, uint32_t N, float *output)
{
	uint32_t i;

	for (i=0; i < N; i++)
	{
		output[i] = input[i];
	}

}


