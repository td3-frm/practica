/* ========================================================================
 * iir_wrapper.c.c: interface MATLAB-TO-C functions for 2nd order
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
 * Date:    2021/10/28
 * Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
 * URL:     https://github.com/rodralez/control
 *
 * ===================================================================== */

#include "mex.h"
#include "iir_filter.h"

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
	float * input;	
	float * output;
	
    /* check for proper number of arguments */
    if(nrhs != 1) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:nrhs","One input required.");
    }
    if(nlhs != 1) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:nlhs","One output required.");
    }
    
    /* make sure the first input argument is type single */
    if( !mxIsSingle(prhs[0]) || 
         mxIsComplex(prhs[0])) {
        mexErrMsgIdAndTxt("MyToolbo2x:iir_matlab_wrapper:notSingle","Input matrix must be type single.");
    }
    
    /* check that number of columns in input matrix argument is 1 */
    if(mxGetN(prhs[0])!=1) {
        mexErrMsgIdAndTxt("MyToolbox:iir_matlab_wrapper:notColumnVector","Input matrix must be a column vector.");
    }
    
    /* create a pointer to the real data in input matrix  */
    input = mxGetData(prhs[0]);

    /* create the output matrix */
    plhs[0] = mxCreateNumericArray(mxGetNumberOfDimensions(prhs[0]), mxGetDimensions(prhs[0]),
        mxSINGLE_CLASS, (mxIsComplex(prhs[0]) ? mxCOMPLEX : mxREAL));

    /* get a pointer to the real data in the output matrix */
    output = mxGetData(plhs[0]);

    /* call the computational C routine */
    iir_2nd_df1_float(input, output);
//     iir_2nd_df2_float(input, output);
//     iir_nth_df1_float(input, output);
//     iir_nth_df2_float(input, output);
     

}
