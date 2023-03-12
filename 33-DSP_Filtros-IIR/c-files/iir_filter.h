/* ========================================================================
 * iir_filter.h
 *
 * Functions inspired in IIR_filters_fourth_order.c (v 1.00) by Richard Sikora
 * from Texas Instruments.
 * 
 * Version: 001
 * Date:    2021/11/05
 * Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
 * URL:     https://github.com/rodralez/td3
 *
 * ===================================================================== */
 
#ifndef IIR_FILTERS_H
#define IIR_FILTERS_H

typedef struct irr_coeff iir_st;

iir_st * iir_get_sos(void);

void iir_2nd_df1_float(float *input, float *output);
void iir_2nd_df2_float(float *input, float *output);
void iir_nth_df1_float(float *input, float *output);
void iir_nth_df2_float(float *input, float *output);

#endif
