/* =====================================================================
 * iir_filters.c
 * 
 * Functions inspired in IIR_filters_fourth_order.c (v 1.00) by Richard 
 * Sikora from Texas Instruments.
 * 
 * Version: 001
 * Date:    2016/11/10
 * Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
 * URL:     https://github.com/rodralez/td3
 *
 * ================================================================== */
 
/*****************************************************************************/
/*                                                                           */
/* A second infinite impulse response (IIR) filter can be represented by     */
/* the following equation:                                                   */
/*                                                                           */
/* H(z) = b0 + b1.z^-1 + b2.z^-2                                             */
/*        ----------------------                                             */
/*        a0 + a1.z^-1 + a2.z^-2                                             */
/*                                                                           */
/* where H(z) is the transfer function. a0 is always 1.000                   */
/*                                                                           */
/*                                                                           */
/* In order to implement this function on a fixed point processor, the value */
/* 32767 is used to represent 1.000                                          */
/*                                                                           */
/* Because the coefficients b1 and a1 can lie in the range -2.000 to +2.000, */
/* the coeffients supplied to the function are b1/2 and a1/2.                */
/*                                                                           */
/*****************************************************************************/

#include "iir_filters.h"

/* Numerator coefficients */
#define B0 0
#define B1 1
#define B2 2

/* Denominator coefficients */
#define A0 3
#define A1 4
#define A2 5

// #define DEBUG 

/*****************************************************************************/
/* iir_filter_I_float()                                                      */
/*---------------------------------------------------------------------------*/
/* iir_filter_II_float()                                                     */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

void iir_filter_I_float(const float * input, const float * coeff,  const float * gain, const unsigned int N, float * output)
{
    unsigned int i;
    
#ifdef  DEBUG
    mexPrintf("N = %d \n", N);
#endif
    
    for (i=0; i < N; i++)
    {
        *(output + i) = second_order_IIR_direct_form_I_float  ( *(input + i), coeff, gain);
        
#ifdef  DEBUG
    mexPrintf("output [%d] = %f \n", i, *(output + i));
#endif        
    }
}

void iir_filter_II_float(const float * input, const float * coeff,  const float * gain, const unsigned int N, float * output)
{
    unsigned int i;
    
#ifdef  DEBUG
    mexPrintf("N = %d \n", N);
#endif
    
    for (i=0; i < N; i++)
    {
        *(output + i) = second_order_IIR_direct_form_II_float ( *(input + i), coeff, gain) ;

#ifdef  DEBUG
    mexPrintf("output [%d] = %f \n", i, *(output + i));
#endif        
    }
}

/*****************************************************************************/
/* second_order_IIR_direct_form_I()                                          */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Second order direct form I IIR filter.                                    */
/*                                                                           */
/* This implementation uses two buffers, one for x[n] and the other for y[n] */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Float version                                                             */
/*****************************************************************************/

float second_order_IIR_direct_form_I_float(const float input, const float * coeff, const float * gain)
{
    float temp;
    static float x[3] = { 0.0 };  /* x(n), x(n-1), x(n-2). Must be static */
    static float y[3] = { 0.0 };  /* y(n), y(n-1), y(n-2). Must be static */
    
#ifdef  DEBUG
    unsigned int i;
    static unsigned int flag = 0;
    
    if (flag == 0)
    {
        for (i=0; i < 6; i++)
        {
            mexPrintf("coeff [%d] = %f \n", i, *(coeff + i) );
        }
        for (i=0; i < 2; i++)
        {
            mexPrintf("gain [%d] = %f \n", i, *(gain + i) );
        }
        flag = 1;
    }
#endif
    
    x[0] = input * gain[0]; /* Copy input to x[0] */
    
    temp =  ( (float) *(coeff + B0) * x[0]) ;   /* B0 * x(n)    */
    temp += ( (float) *(coeff + B1) * x[1]);    /* B1 * x(n-1) 	*/
    temp += ( (float) *(coeff + B2) * x[2]);    /* B2 * x(n-2)  */
    temp -= ( (float) *(coeff + A1) * y[1]);    /* A1 * y(n-1) 	*/
    temp -= ( (float) *(coeff + A2) * y[2]);    /* A2 * y(n-2)  */
    
    y[0] = temp * gain[1];
    
    /* Shuffle values along one place for next execution */
    
    y[2] = y[1];   /* y(n-2) = y(n-1) */
    y[1] = y[0];   /* y(n-1) = y(n)   */
    
    x[2] = x[1];   /* x(n-2) = x(n-1) */
    x[1] = x[0];   /* x(n-1) = x(n)   */
    
    return ( temp );
}

/*****************************************************************************/
/* Fixed-point version                                                       */
/*****************************************************************************/

signed int second_order_IIR_direct_form_I_fixed(const signed int * coefficients, signed int input, const signed int * gain)
{
    long temp;
    static signed int x[3] = { 0 };  /* x(n), x(n-1), x(n-2). Must be static */
    static signed int y[3] = { 0 };  /* y(n), y(n-1), y(n-2). Must be static */
    
    x[0] = input; /* Copy input to x[0] */
    
    /* Divide temp by coefficients[A0] to remove fractional part */

    /* Shuffle values along one place for next execution */
    
    return ( (short int) temp );
}

/*****************************************************************************/
/* second_order_IIR_direct_form_II()                                         */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Cascades two second order IIR filters.                                    */
/* Uses 32767 to represent 1.000.                                            */
/* Note that input is divided by 128 to prevent overload.                    */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Float version                                                             */
/*****************************************************************************/

float second_order_IIR_direct_form_II_float ( const float input, const float * coeff, const float * gain)
{
    float temp;
    static float delay[3] = { 0.0 };
    
    /* Copy input to temp for temporary storage */
    temp = input * gain[0];
    
    /* Process denominator coefficients */
    delay[0] = temp;
    
    temp =  ( coeff[A0] * delay[0] );
    
    temp -= ( coeff[A1] * delay[1] );  /* A1 */
    
    temp -= ( coeff[A2] * delay[2] );
    
    delay[0] = temp;
    
    /* Process numerator coefficients */
    temp =  (coeff[B0] * delay[0] );
    
    temp += (coeff[B1] * delay[1] ) ;  /* B1 */
    
    temp += (coeff[B2] * delay[2] ) ;

    delay[2] = delay[1];
    delay[1] = delay[0];

    /* Temp will be fed into input of filter next time through */
    return ( temp * gain[1] );
}

/*****************************************************************************/
/* Fixed-point version                                                       */
/*****************************************************************************/

signed int second_order_IIR_direct_form_II_fixed ( const signed int * coefficients, signed int input, const signed int * gain)
{
    long temp;
    static short int delay[3] = { 0 };
    
    /* Copy input to temp for temporary storage */
    
    temp = (long) input;
    
    /* Process denominator coefficients */

    
    /* Process numerator coefficients */

    
    /* Temp will be fed into input of filter next time through */
    
    return ( (short int) temp );
}
