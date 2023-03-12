/* ========================================================================
 * fir_wrapper.c: interface MATLAB-TO-C functions for FIR
 * filtering.
 *
 * INPUT
 *      input  : NX1 input vector.
 *
 *  OUTPUT
 *      output : NX1 output (filtered) vector.
 *
 * Version: 002
 * Date:    2021/10/27
 * Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
 * URL:     https://github.com/rodralez/control
 *
 * compile: mex fir_wrapper.c fir_filter.c
 * ===================================================================== */

#include <stdio.h>
#include "mex.h"
#include "fir_filter.h"

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
/*const float * input, const float * coefficients, const unsigned int N, float * output) */

	float * input;	
	float * output;
	size_t N;
	
    /* check for proper number of arguments */
    if(nrhs != 1) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:nrhs","One input required.");
    }
    if(nlhs != 1) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:nlhs","One output required.");
    }
    
//     /* make sure the first input argument is vector */
//     if( !mxIsSingle(prhs[0]) || 
//          mxIsComplex(prhs[0]) ||
//          mxGetNumberOfElements(prhs[0])==1 ) {
//         mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:notScalar","Input multiplier must be a vector.");
//     }
    
    /* make sure the first input argument is type single */
    if( !mxIsSingle(prhs[0]) || 
         mxIsComplex(prhs[0])) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:notSingle","Input matrix must be type single.");
    }
    
    /* check that number of columns in input matrix argument is 1 */
    if(mxGetN(prhs[0])!=1) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:notColumnVector","Input matrix must be a column vector.");
    }
    
    /* create a pointer to the real data in input matrix  */
    input = mxGetData(prhs[0]);

    /* get number of rows in input matrix */
    N = mxGetM(prhs[0]);

    /* create the output matrix */
    plhs[0] = mxCreateNumericArray(mxGetNumberOfDimensions(prhs[0]), mxGetDimensions(prhs[0]),
        mxSINGLE_CLASS, (mxIsComplex(prhs[0]) ? mxCOMPLEX : mxREAL));

    /* get a pointer to the real data in the output matrix */
    output = mxGetData(plhs[0]);

    /* call the computational C routine */
    
    fir_online_float(input, output);
//     fir_online_fixed(input, output);
    
 }
