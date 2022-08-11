/* =====================================================================
 * iir_filter.c
 *
 * Functions inspired in IIR_filters_fourth_order.c (v 1.00) by Richard
 * Sikora from Texas Instruments.
 *
 * Version: 001
 * Date:    2021/11/05
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

#include "iir_filter.h"
#include "mex.h"
#include "fdacoefs.h"

#define GAINS (MWSPT_NSEC/2 + MWSPT_NSEC%2)
#define STAGES (GAINS-1)

/* Numerator coefficients */
#define B0 0
#define B1 1
#define B2 2

/* Denominator coefficients */
#define A0 3
#define A1 4
#define A2 5

// #define DEBUG

struct irr_coeff
{
    float gain[GAINS];
    float sos[STAGES][6];
};

// GLOBAL VARIABLES
iir_st iir_g;

/**************************************************************************/
/* irr_stru * iir_get_sos(void)                                           */
/*------------------------------------------------------------------------*/
/*                                                                        */
/* Gets IIR filter coefficients from the file fdacoefs.h provided by      */
/* FilterDesigner.                                                        */
/*                                                                        */
/**************************************************************************/

iir_st * iir_get_sos(void)
{
    unsigned int i, j, k, g;
    iir_st * ptr_iir_g;
    
    k = 0;
    g = 0;
    
    for (i=0; i < MWSPT_NSEC; i++)
    {
        if ( (i%2) == 0)
        {
            iir_g.gain[k] = NUM[i][0];
            k ++ ;
        }
        else
        {
            for (j=0; j < 3; j++)
            {
                iir_g.sos[g][j]   = NUM[i][j];
                iir_g.sos[g][j+3] = DEN[i][j];
            }
            
            g ++ ;
        }
    }
    
    ptr_iir_g = &iir_g;
    
    return ptr_iir_g;
}

/**************************************************************************/
/* void iir_2nd_df1_float(float *input, float *output)                    */
/*------------------------------------------------------------------------*/
/*                                                                        */
/* Second order direct form I IIR filter.                                 */
/*                                                                        */
/* This implementation uses 2 buffers, one for x[n] and another for y[n]. */
/*                                                                        */
/**************************************************************************/

void iir_2nd_df1_float(float *input, float *output)
{
    float acc;
    static float x[3] = { 0.0 };  /* x(n), x(n-1), x(n-2). Must be static */
    static float y[3] = { 0.0 };  /* y(n), y(n-1), y(n-2). Must be static */
    iir_st * iir_c;
    
    iir_c =  iir_get_sos();
    
#ifdef  DEBUG
    unsigned int i, j;
    
    mexPrintf("sizeof gain = %d \n", GAIN_D );
    
    for (i=0; i < GAIN_D; i++)
    {
        mexPrintf("gain[%d] = %f \n", i, iir_c->gain[i]);
    }
    
    for (i=0; i < COEFF_D; i++)
    {
        for (j=0; j < 6; j++)
        {
            mexPrintf("sos[%d][%d] = %f \n", i, j, iir_c->sos[i][j] );
        }
    }
#endif
    
    x[0] = *(input) * iir_c->gain[0]; /* Copy input to x[0] */
    
    acc =  ( (float) iir_c->sos[0][B0] * x[0]) ;   /* B0 * x(n)    */
    acc += ( (float) iir_c->sos[0][B1] * x[1]);    /* B1 * x(n-1)  */
    acc += ( (float) iir_c->sos[0][B2] * x[2]);    /* B2 * x(n-2)  */
    acc -= ( (float) iir_c->sos[0][A1] * y[1]);    /* A1 * y(n-1)  */
    acc -= ( (float) iir_c->sos[0][A2] * y[2]);    /* A2 * y(n-2)  */
    
    y[0] = acc * iir_c->gain[1];
    
    /* Shuffle values along one place for next execution */
    
    y[2] = y[1];   /* y(n-2) = y(n-1) */
    y[1] = y[0];   /* y(n-1) = y(n)   */
    x[2] = x[1];   /* x(n-2) = x(n-1) */
    x[1] = x[0];   /* x(n-1) = x(n)   */
    
    *(output) = acc;
}

/*****************************************************************************/
/* void iir_2nd_df2_float(float *input, float *output)                       */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Fourth order direct form II IIR filter.                                   */
/*                                                                           */
/* This implementation uses one buffer for x[n] and y[n].                    */
/*                                                                           */
/*****************************************************************************/

void iir_2nd_df2_float(float *input, float *output)
{
    float acc;
    static float delay[3] = { 0.0 };
    iir_st * iir_c;
    
    iir_c =  iir_get_sos();
    
#ifdef  DEBUG
    
    unsigned int i, j;
    
    mexPrintf("sizeof gain = %d \n", GAIN_D );
    
    for (i=0; i < GAIN_D; i++)
    {
        mexPrintf("gain[%d] = %f \n", i, iir_c->gain[i]);
    }
    
    for (i=0; i < COEFF_D; i++)
    {
        for (j=0; j < 6; j++)
        {
            mexPrintf("sos[%d][%d] = %f \n", i, j, iir_c->sos[i][j] );
        }
    }
#endif
    
    /* Copy input to acc for temporary storage */
    acc = *(input) * iir_c->gain[0];
    
    /* Process denominator coefficients */
    delay[0] = acc;
    
    acc =  ( iir_c->sos[0][A0] * delay[0] );
    
    acc -= ( iir_c->sos[0][A1] * delay[1] );
    
    acc -= ( iir_c->sos[0][A2] * delay[2] );
    
    delay[0] = acc;
    
    /* Process numerator coefficients */
    acc =  (iir_c->sos[0][B0] * delay[0] );
    
    acc += (iir_c->sos[0][B1] * delay[1] ) ;
    
    acc += (iir_c->sos[0][B2] * delay[2] ) ;
    
    delay[2] = delay[1];
    delay[1] = delay[0];
    
    /* Temp will be fed into input of filter next time through */
    *(output) = acc * iir_c->gain[1];
}

/**************************************************************************/
/* void iir_nth_df1_float(float *input, float *output)                   */
/*------------------------------------------------------------------------*/
/*                                                                        */
/* Nth order direct form I IIR filter.                                 */
/*                                                                        */
/* This implementation uses 2 buffers, one for x[n] and another for y[n]. */
/*                                                                        */
/**************************************************************************/
void iir_nth_df1_float(float *input, float *output)
{
    static float x[STAGES][3] = { 0 };  /* x(n), x(n-1), x(n-2). Must be static */
    static float y[STAGES][3] = { 0 };  /* y(n), y(n-1), y(n-2). Must be static */
    float acc;
    unsigned int stage;
    iir_st * iir_c;
    
    iir_c =  iir_get_sos();
    
    acc = *(input); /* Copy input to acc */
    
    for ( stage = 0 ; stage < STAGES ; stage++)
    {
        x[stage][0] = acc  * iir_c->gain[stage]; /* Copy input to x[stage][0] */
        
        acc =  ( (float) iir_c->sos[stage][B0] * x[stage][0]);   /* B0 * x(n)    */
        acc += ( (float) iir_c->sos[stage][B1] * x[stage][1]);    /* B1 * x(n-1)  */
        acc += ( (float) iir_c->sos[stage][B2] * x[stage][2]);     /* B2 * x(n-2)  */
        acc -= ( (float) iir_c->sos[stage][A1] * y[stage][1]);;    /* A1 * y(n-1)  */
        acc -= ( (float) iir_c->sos[stage][A2] * y[stage][2]);    /* A2 * y(n-2)  */
        
        y[stage][0] =  acc;
        
        /* Shuffle values along one place for next time */
        
        y[stage][2] = y[stage][1];   /* y(n-2) = y(n-1) */
        y[stage][1] = y[stage][0];   /* y(n-1) = y(n)   */
        
        x[stage][2] = x[stage][1];   /* x(n-2) = x(n-1) */
        x[stage][1] = x[stage][0];   /* x(n-1) = x(n)   */
        
        /* acc is used as input next time through */
    }
    
    *(output) = acc  * iir_c->gain[STAGES];
}

/**************************************************************************/
/* void iir_nth_df2_float(float *input, float *output)                    */
/*------------------------------------------------------------------------*/
/*                                                                        */
/* Nth order direct form II IIR filter.                                */
/*                                                                        */
/* This implementation uses one buffer for x[n] and y[n].                 */
/*                                                                        */
/**************************************************************************/
void iir_nth_df2_float(float *input, float *output)
{
    static float delay[STAGES][3] = { 0 };
    float acc;
    unsigned int stage;
    iir_st * iir_c;
    
    iir_c =  iir_get_sos();
    
    acc = *(input);
    
    for ( stage = 0 ; stage < STAGES ; stage++)
    {   
        /* Process denominator coefficients */
        delay[stage][0] = acc * iir_c->gain[stage];
        
        acc =  iir_c->sos[stage][A0] * delay[stage][0];
        
        acc -= iir_c->sos[stage][A1] * delay[stage][1];
        
        acc -= iir_c->sos[stage][A2] * delay[stage][2];
        
        delay[stage][0] = acc;
        
        /* Process numerator coefficients */
        acc =  iir_c->sos[stage][B0] * delay[stage][0];
        
        acc += iir_c->sos[stage][B1] * delay[stage][1];
        
        acc += iir_c->sos[stage][B2] * delay[stage][2];
        
        delay[stage][2] = delay[stage][1];
        delay[stage][1] = delay[stage][0];        
    }
    
    *(output) = acc * iir_c->gain[STAGES];
}
