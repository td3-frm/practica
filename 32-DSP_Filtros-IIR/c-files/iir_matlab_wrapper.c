/* ========================================================================
 * iir_matlab_wrapper.c: interface MATLAB-TO-C functions for 2nd order
 * filtering.
 *
 * INPUT
 *      input  : NX1 input vector.
 *      coeff  : 6x1 2nd-order IIR coefficients vector. 
 *      gain   : 2X1 2nd-order IIR gains vector. 
 *
 *  OUTPUT
 *      output : NX1 output (filtered) vector.
 *
 * Version: 001
 * Date:    2016/11/10
 * Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
 * URL:     https://github.com/rodralez/td3
 *
 * ===================================================================== */

#include "mex.h"
#include "iir_filters.h"

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
/*const float * input, const float * coefficients, const unsigned int N, float * output) */

	float * input;	
	float * output;
    float * gain;
	float * coeff;
	size_t N;
	
    /* check for proper number of arguments */
    if(nrhs != 3) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:nrhs","Three inputs required.");
    }
    if(nlhs != 1) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:nlhs","One output required.");
    }
    /* make sure the first input argument is vector */
    if( !mxIsSingle(prhs[0]) || 
         mxIsComplex(prhs[0]) ||
         mxGetNumberOfElements(prhs[0])==1 ) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:notScalar","Input multiplier must be a vector.");
    }
    
    /* make sure the second input argument is vector */
    if( !mxIsSingle(prhs[1]) || 
         mxIsComplex(prhs[1]) ||
         mxGetNumberOfElements(prhs[1])==1 ) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:notScalar","Input coefficients must be a vector.");
    }
    
    /* make sure the third input argument is vector */
    if( !mxIsSingle(prhs[2]) || 
         mxIsComplex(prhs[2]) ||
         mxGetNumberOfElements(prhs[2])==1 ) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:notScalar","Input gain must be a vector.");
    }
    
    /* make sure the first input argument is type single */
    if( !mxIsSingle(prhs[0]) || 
         mxIsComplex(prhs[0])) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:notSingle","Input matrix must be type single.");
    }
    
    /* make sure the second input argument is type single */
    if( !mxIsSingle(prhs[1]) || 
         mxIsComplex(prhs[1])) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:notSingle","Input coefficients must be type single.");
    }
    
    /* make sure the third input argument is type single */
    if( !mxIsSingle(prhs[2]) || 
         mxIsComplex(prhs[2])) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:notSingle","Input gain must be type single.");
    }    
    
    /* check that number of colums in input matrix argument is 1 */
    if(mxGetN(prhs[0])!=1) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:notColumnVector","Input matrix must be a column vector.");
    }
    
    /* check that number of colums in input coefficients argument is 1 */
//     if(mxGetN(prhs[1])!=1) {
//         mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:notColumnVector","Input coefficients must be a column vector.");
//     }
    
        /* check that number of colums in input gain argument is 1 */
    if(mxGetN(prhs[2])!=1) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:notColumnVector","Input gain must be a column vector.");
    }
    
    /* create a pointer to the real data in input matrix  */
    input = mxGetData(prhs[0]);

    /* create a pointer to the real data in coeff matrix  */
    coeff = mxGetData(prhs[1]);

    /* create a pointer to the real data in input gain  */
    gain = mxGetData(prhs[2]);

    /* get number of rows in input matrix */
    N = mxGetM(prhs[0]);

    /* create the output matrix */
    plhs[0] = mxCreateNumericArray(mxGetNumberOfDimensions(prhs[0]), mxGetDimensions(prhs[0]),
        mxSINGLE_CLASS, (mxIsComplex(prhs[0]) ? mxCOMPLEX : mxREAL));

    /* get a pointer to the real data in the output matrix */
    output = mxGetData(plhs[0]);

    /* call the computational C routine */
    iir_filter_I_float(input, coeff, gain, N, output);   
//    	(input, coeff, gain, N, output); 
     
    
}
