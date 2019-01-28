/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: inv_6TJweJmr.c
 *
 * Code generated for Simulink model 'motoraiHIL'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Mon Jan 28 23:02:08 2019
 */

#include "rtwtypes.h"
#include <math.h>
#include "inv_6TJweJmr.h"

/* Function for MATLAB Function: '<S7>/MATLAB Function' */
void inv_6TJweJmr(const real_T x[4], real_T y[4])
{
  real_T r;
  real_T t;
  if (fabs(x[1]) > fabs(x[0])) {
    r = x[0] / x[1];
    t = 1.0 / ((r * x[3]) - x[2]);
    y[0] = (x[3] / x[1]) * t;
    y[1] = -t;
    y[2] = ((-x[2]) / x[1]) * t;
    y[3] = r * t;
  } else {
    r = x[1] / x[0];
    t = 1.0 / (x[3] - (r * x[2]));
    y[0] = (x[3] / x[0]) * t;
    y[1] = (-r) * t;
    y[2] = ((-x[2]) / x[0]) * t;
    y[3] = t;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
