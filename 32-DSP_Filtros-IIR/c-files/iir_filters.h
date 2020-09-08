/* ========================================================================
 * iir_filters.h
 *
 * Functions inspired in IIR_filters_fourth_order.c (v 1.00) by Richard Sikora
 * from Texas Instruments.
 * 
 * Version: 001
 * Date:    2016/11/10
 * Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
 * URL:     https://github.com/rodralez/td3
 *
 * ===================================================================== */
 
#ifndef IIR_FILTERS_H
#define IIR_FILTERS_H

void iir_filter_I_float (const float * input, const float * coeff,  const float * gain, const unsigned int N, float * output);
void iir_filter_II_float(const float * input, const float * coeff,  const float * gain, const unsigned int N, float * output);

float second_order_IIR_direct_form_I_float  (const float input, const float * coeff, const float * gain);
float second_order_IIR_direct_form_II_float (const float input, const float * coeff, const float * gain);

signed int second_order_IIR_direct_form_I_fixed  (const signed int * coefficients, signed int input, const signed int * gain);
signed int second_order_IIR_direct_form_II_fixed (const signed int * coefficients, signed int input, const signed int * gain);

#endif
