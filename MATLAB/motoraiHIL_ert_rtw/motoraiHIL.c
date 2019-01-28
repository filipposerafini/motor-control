/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: motoraiHIL.c
 *
 * Code generated for Simulink model 'motoraiHIL'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Mon Jan 28 13:34:17 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. RAM efficiency
 *    2. Execution efficiency
 * Validation result: Not run
 */

#include "motoraiHIL.h"
#include <math.h>
#include <stdlib.h>

/* Named constants for Chart: '<Root>/Logic Brain1' */
#define IN_button_wait                 ((uint8_T)1U)
#define IN_idle                        ((uint8_T)2U)
#define IN_start_estimation            ((uint8_T)3U)
#define NumBitsPerChar                 8U
#define MAX_BUFFER_SIZE                32768
#ifndef ssGetFixedStepSize
#define ssGetFixedStepSize(S)          (S).stepSize
#endif                                 /* ssGetFixedStepSize */

/* Block signals and states (default storage) */
DW rtDW;

/* Previous zero-crossings (trigger) states */
PrevZCX rtPrevZCX;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern uint32_T MWDSP_EPH_R_B(boolean_T evt, uint32_T *sta);
extern real_T rt_powd_snf(real_T u0, real_T u1);

/* Forward declaration for local functions */
static real_T inv_f(real_T x);
static void inv(const real_T x[4], real_T y[4]);
static real_T xnrm2(int32_T n, const real_T x[16], int32_T ix0);
static real_T rt_hypotd_snf_a(real_T u0, real_T u1);
static void xzlarf(int32_T m, int32_T n, int32_T iv0, real_T tau, real_T C[16],
                   int32_T ic0, real_T work[4]);
static void xgehrd(real_T a[16], real_T tau[3]);
static real_T xnrm2_g(int32_T n, const real_T x[3]);
static real_T xzlarfg(int32_T n, real_T *alpha1, real_T x[3]);
static void xdlanv2(real_T *a, real_T *b, real_T *c, real_T *d, real_T *rt1r,
                    real_T *rt1i, real_T *rt2r, real_T *rt2i, real_T *cs, real_T
                    *sn);
static void xrot(int32_T n, real_T x[16], int32_T ix0, int32_T iy0, real_T c,
                 real_T s);
static void xrot_k(int32_T n, real_T x[16], int32_T ix0, int32_T iy0, real_T c,
                   real_T s);
static void xrot_kc(real_T x[16], int32_T ix0, int32_T iy0, real_T c, real_T s);
static int32_T eml_dlahqr(real_T h[16], real_T z[16]);
static void schur(const real_T A[16], real_T V[16], real_T T[16]);
static void SystemCore_release_aomx(const mbed_DigitalRead *obj);
static void SystemCore_delete_aomx(const mbed_DigitalRead *obj);
static void matlabCodegenHandle_matlab_aomx(mbed_DigitalRead *obj);
static void SystemCore_release_a(const mbed_DigitalWrite *obj);
static void SystemCore_delete_a(const mbed_DigitalWrite *obj);
static void matlabCodegenHandle_matlabCod_a(mbed_DigitalWrite *obj);
static void SystemCore_release_aom(const mbed_PWMOutput *obj);
static void SystemCore_delete_aom(const mbed_PWMOutput *obj);
static void matlabCodegenHandle_matlabC_aom(mbed_PWMOutput *obj);
static void SystemCore_release(const mbed_AnalogInput *obj);
static void SystemCore_delete(const mbed_AnalogInput *obj);
static void matlabCodegenHandle_matlabCodeg(mbed_AnalogInput *obj);
static void rate_scheduler(void);
extern real_T rtGetInf(void);
extern real32_T rtGetInfF(void);
extern real_T rtGetMinusInf(void);
extern real32_T rtGetMinusInfF(void);
extern real_T rtGetNaN(void);
extern real32_T rtGetNaNF(void);
extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
extern void rt_InitInfAndNaN(size_t realSize);
extern boolean_T rtIsInf(real_T value);
extern boolean_T rtIsInfF(real32_T value);
extern boolean_T rtIsNaN(real_T value);
extern boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0 } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
boolean_T rtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = rtIsNaNF((real32_T)value);
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.fltVal = value;
    result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
                         ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                          (tmpVal.bitVal.words.wordL != 0) ));
  }

  return result;
}

/* Test if single-precision value is not a number */
boolean_T rtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (rtM->Timing.TaskCounters.TID[1])++;
  if ((rtM->Timing.TaskCounters.TID[1]) > 199) {/* Sample time: [0.002s, 0.0s] */
    rtM->Timing.TaskCounters.TID[1] = 0;
  }
}

uint32_T MWDSP_EPH_R_B(boolean_T evt, uint32_T *sta)
{
  uint32_T retVal;
  int32_T curState;
  int32_T newState;
  int32_T newStateR;
  int32_T lastzcevent;
  uint32_T previousState;

  /* S-Function (sdspcount2): '<S8>/Counter' */
  /* Detect rising edge events */
  previousState = *sta;
  retVal = 0U;
  lastzcevent = 0;
  newState = 5;
  newStateR = 5;
  if (evt) {
    curState = 2;
  } else {
    curState = 1;
  }

  if (*sta == 5U) {
    newStateR = curState;
  } else {
    if ((uint32_T)curState != *sta) {
      if (*sta == 3U) {
        if ((uint32_T)curState == 1U) {
          newStateR = 1;
        } else {
          lastzcevent = 2;
          previousState = 1U;
        }
      }

      if (previousState == 4U) {
        if ((uint32_T)curState == 1U) {
          newStateR = 1;
        } else {
          lastzcevent = 3;
          previousState = 1U;
        }
      }

      if ((previousState == 1U) && ((uint32_T)curState == 2U)) {
        retVal = 2U;
      }

      if (previousState == 0U) {
        retVal = 2U;
      }

      if (retVal == (uint32_T)lastzcevent) {
        retVal = 0U;
      }

      if (((uint32_T)curState == 1U) && (retVal == 2U)) {
        newState = 3;
      } else {
        newState = curState;
      }
    }
  }

  if ((uint32_T)newStateR != 5U) {
    *sta = (uint32_T)newStateR;
    retVal = 0U;
  }

  if ((uint32_T)newState != 5U) {
    *sta = (uint32_T)newState;
  }

  /* End of S-Function (sdspcount2): '<S8>/Counter' */
  return retVal;
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S7>/MATLAB Function' */
static real_T inv_f(real_T x)
{
  return 1.0 / x;
}

/* Function for MATLAB Function: '<S7>/MATLAB Function' */
static void inv(const real_T x[4], real_T y[4])
{
  real_T r;
  real_T t;
  if (fabs(x[1]) > fabs(x[0])) {
    r = x[0] / x[1];
    t = 1.0 / (r * x[3] - x[2]);
    y[0] = x[3] / x[1] * t;
    y[1] = -t;
    y[2] = -x[2] / x[1] * t;
    y[3] = r * t;
  } else {
    r = x[1] / x[0];
    t = 1.0 / (x[3] - r * x[2]);
    y[0] = x[3] / x[0] * t;
    y[1] = -r * t;
    y[2] = -x[2] / x[0] * t;
    y[3] = t;
  }
}

/* Function for MATLAB Function: '<S7>/MATLAB Function' */
static real_T xnrm2(int32_T n, const real_T x[16], int32_T ix0)
{
  real_T y;
  real_T scale;
  int32_T kend;
  real_T absxk;
  real_T t;
  int32_T k;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

static real_T rt_hypotd_snf_a(real_T u0, real_T u1)
{
  real_T y;
  rtDW.a = fabs(u0);
  y = fabs(u1);
  if (rtDW.a < y) {
    rtDW.a /= y;
    y *= sqrt(rtDW.a * rtDW.a + 1.0);
  } else if (rtDW.a > y) {
    y /= rtDW.a;
    y = sqrt(y * y + 1.0) * rtDW.a;
  } else {
    if (!rtIsNaN(y)) {
      y = rtDW.a * 1.4142135623730951;
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S7>/MATLAB Function' */
static void xzlarf(int32_T m, int32_T n, int32_T iv0, real_T tau, real_T C[16],
                   int32_T ic0, real_T work[4])
{
  int32_T lastv;
  int32_T lastc;
  int32_T coltop;
  int32_T ix;
  int32_T iac;
  int32_T d;
  int32_T b_ia;
  int32_T jy;
  int32_T exitg1;
  boolean_T exitg2;
  if (tau != 0.0) {
    lastv = m;
    lastc = iv0 + m;
    while ((lastv > 0) && (C[lastc - 2] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = n - 1;
    exitg2 = false;
    while ((!exitg2) && (lastc + 1 > 0)) {
      coltop = (lastc << 2) + ic0;
      jy = coltop;
      do {
        exitg1 = 0;
        if (jy <= (coltop + lastv) - 1) {
          if (C[jy - 1] != 0.0) {
            exitg1 = 1;
          } else {
            jy++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = -1;
  }

  if (lastv > 0) {
    if (lastc + 1 != 0) {
      for (coltop = 0; coltop <= lastc; coltop++) {
        work[coltop] = 0.0;
      }

      coltop = 0;
      jy = (lastc << 2) + ic0;
      for (iac = ic0; iac <= jy; iac += 4) {
        ix = iv0;
        rtDW.c = 0.0;
        d = (iac + lastv) - 1;
        for (b_ia = iac; b_ia <= d; b_ia++) {
          rtDW.c += C[b_ia - 1] * C[ix - 1];
          ix++;
        }

        work[coltop] += rtDW.c;
        coltop++;
      }
    }

    if (!(-tau == 0.0)) {
      coltop = ic0 - 1;
      jy = 0;
      for (iac = 0; iac <= lastc; iac++) {
        if (work[jy] != 0.0) {
          rtDW.c = work[jy] * -tau;
          ix = iv0;
          d = lastv + coltop;
          for (b_ia = coltop; b_ia < d; b_ia++) {
            C[b_ia] += C[ix - 1] * rtDW.c;
            ix++;
          }
        }

        jy++;
        coltop += 4;
      }
    }
  }
}

/* Function for MATLAB Function: '<S7>/MATLAB Function' */
static void xgehrd(real_T a[16], real_T tau[3])
{
  int32_T lastc;
  int32_T rowleft;
  int32_T iac;
  int32_T g;
  int32_T b_ia;
  int32_T jy;
  int32_T b_ix;
  int32_T exitg1;
  boolean_T exitg2;
  rtDW.work_c[0] = 0.0;
  rtDW.work_c[1] = 0.0;
  rtDW.work_c[2] = 0.0;
  rtDW.work_c[3] = 0.0;
  rtDW.alpha1 = a[1];
  rtDW.b = 0.0;
  rtDW.xnorm = xnrm2(2, a, 3);
  if (rtDW.xnorm != 0.0) {
    rtDW.xnorm = rt_hypotd_snf_a(a[1], rtDW.xnorm);
    if (a[1] >= 0.0) {
      rtDW.xnorm = -rtDW.xnorm;
    }

    if (fabs(rtDW.xnorm) < 1.0020841800044864E-292) {
      rtDW.knt = -1;
      do {
        rtDW.knt++;
        for (lastc = 3; lastc < 5; lastc++) {
          a[lastc - 1] *= 9.9792015476736E+291;
        }

        rtDW.xnorm *= 9.9792015476736E+291;
        rtDW.alpha1 *= 9.9792015476736E+291;
      } while (!(fabs(rtDW.xnorm) >= 1.0020841800044864E-292));

      rtDW.xnorm = rt_hypotd_snf_a(rtDW.alpha1, xnrm2(2, a, 3));
      if (rtDW.alpha1 >= 0.0) {
        rtDW.xnorm = -rtDW.xnorm;
      }

      rtDW.b = (rtDW.xnorm - rtDW.alpha1) / rtDW.xnorm;
      rtDW.alpha1 = 1.0 / (rtDW.alpha1 - rtDW.xnorm);
      for (lastc = 3; lastc < 5; lastc++) {
        a[lastc - 1] *= rtDW.alpha1;
      }

      for (lastc = 0; lastc <= rtDW.knt; lastc++) {
        rtDW.xnorm *= 1.0020841800044864E-292;
      }

      rtDW.alpha1 = rtDW.xnorm;
    } else {
      rtDW.b = (rtDW.xnorm - a[1]) / rtDW.xnorm;
      rtDW.alpha1 = 1.0 / (a[1] - rtDW.xnorm);
      rtDW.knt = 3;
      while (rtDW.knt <= 4) {
        a[rtDW.knt - 1] *= rtDW.alpha1;
        rtDW.knt++;
      }

      rtDW.alpha1 = rtDW.xnorm;
    }
  }

  tau[0] = rtDW.b;
  a[1] = 1.0;
  if (rtDW.b != 0.0) {
    rtDW.knt = 2;
    lastc = 3;
    while ((rtDW.knt + 1 > 0) && (a[lastc] == 0.0)) {
      rtDW.knt--;
      lastc--;
    }

    lastc = 4;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      rowleft = 4 + lastc;
      jy = rowleft;
      do {
        exitg1 = 0;
        if (jy <= (rtDW.knt << 2) + rowleft) {
          if (a[jy - 1] != 0.0) {
            exitg1 = 1;
          } else {
            jy += 4;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    rtDW.knt = -1;
    lastc = 0;
  }

  if (rtDW.knt + 1 > 0) {
    if (lastc != 0) {
      for (rowleft = 0; rowleft < lastc; rowleft++) {
        rtDW.work_c[rowleft] = 0.0;
      }

      rowleft = 1;
      jy = (rtDW.knt << 2) + 5;
      for (iac = 5; iac <= jy; iac += 4) {
        b_ix = 0;
        g = (iac + lastc) - 1;
        for (b_ia = iac; b_ia <= g; b_ia++) {
          rtDW.work_c[b_ix] += a[b_ia - 1] * a[rowleft];
          b_ix++;
        }

        rowleft++;
      }
    }

    if (!(-rtDW.b == 0.0)) {
      rowleft = 4;
      jy = 1;
      for (iac = 0; iac <= rtDW.knt; iac++) {
        if (a[jy] != 0.0) {
          rtDW.xnorm = a[jy] * -rtDW.b;
          b_ix = 0;
          g = lastc + rowleft;
          for (b_ia = rowleft; b_ia < g; b_ia++) {
            a[b_ia] += rtDW.work_c[b_ix] * rtDW.xnorm;
            b_ix++;
          }
        }

        jy++;
        rowleft += 4;
      }
    }
  }

  xzlarf(3, 3, 2, rtDW.b, a, 6, rtDW.work_c);
  a[1] = rtDW.alpha1;
  rtDW.alpha1 = a[6];
  rtDW.b = 0.0;
  rtDW.xnorm = xnrm2(1, a, 8);
  if (rtDW.xnorm != 0.0) {
    rtDW.xnorm = rt_hypotd_snf_a(a[6], rtDW.xnorm);
    if (a[6] >= 0.0) {
      rtDW.xnorm = -rtDW.xnorm;
    }

    if (fabs(rtDW.xnorm) < 1.0020841800044864E-292) {
      rtDW.knt = -1;
      do {
        rtDW.knt++;
        a[7] *= 9.9792015476736E+291;
        rtDW.xnorm *= 9.9792015476736E+291;
        rtDW.alpha1 *= 9.9792015476736E+291;
      } while (!(fabs(rtDW.xnorm) >= 1.0020841800044864E-292));

      rtDW.xnorm = rt_hypotd_snf_a(rtDW.alpha1, xnrm2(1, a, 8));
      if (rtDW.alpha1 >= 0.0) {
        rtDW.xnorm = -rtDW.xnorm;
      }

      rtDW.b = (rtDW.xnorm - rtDW.alpha1) / rtDW.xnorm;
      rtDW.alpha1 = 1.0 / (rtDW.alpha1 - rtDW.xnorm);
      a[7] *= rtDW.alpha1;
      for (lastc = 0; lastc <= rtDW.knt; lastc++) {
        rtDW.xnorm *= 1.0020841800044864E-292;
      }

      rtDW.alpha1 = rtDW.xnorm;
    } else {
      rtDW.b = (rtDW.xnorm - a[6]) / rtDW.xnorm;
      a[7] *= 1.0 / (a[6] - rtDW.xnorm);
      rtDW.alpha1 = rtDW.xnorm;
    }
  }

  tau[1] = rtDW.b;
  a[6] = 1.0;
  if (rtDW.b != 0.0) {
    rtDW.knt = 1;
    lastc = 7;
    while ((rtDW.knt + 1 > 0) && (a[lastc] == 0.0)) {
      rtDW.knt--;
      lastc--;
    }

    lastc = 4;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      rowleft = 8 + lastc;
      jy = rowleft;
      do {
        exitg1 = 0;
        if (jy <= (rtDW.knt << 2) + rowleft) {
          if (a[jy - 1] != 0.0) {
            exitg1 = 1;
          } else {
            jy += 4;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    rtDW.knt = -1;
    lastc = 0;
  }

  if (rtDW.knt + 1 > 0) {
    if (lastc != 0) {
      for (rowleft = 0; rowleft < lastc; rowleft++) {
        rtDW.work_c[rowleft] = 0.0;
      }

      rowleft = 6;
      jy = (rtDW.knt << 2) + 9;
      for (iac = 9; iac <= jy; iac += 4) {
        b_ix = 0;
        g = (iac + lastc) - 1;
        for (b_ia = iac; b_ia <= g; b_ia++) {
          rtDW.work_c[b_ix] += a[b_ia - 1] * a[rowleft];
          b_ix++;
        }

        rowleft++;
      }
    }

    if (!(-rtDW.b == 0.0)) {
      rowleft = 8;
      jy = 6;
      for (iac = 0; iac <= rtDW.knt; iac++) {
        if (a[jy] != 0.0) {
          rtDW.xnorm = a[jy] * -rtDW.b;
          b_ix = 0;
          g = lastc + rowleft;
          for (b_ia = rowleft; b_ia < g; b_ia++) {
            a[b_ia] += rtDW.work_c[b_ix] * rtDW.xnorm;
            b_ix++;
          }
        }

        jy++;
        rowleft += 4;
      }
    }
  }

  xzlarf(2, 2, 7, rtDW.b, a, 11, rtDW.work_c);
  a[6] = rtDW.alpha1;
  rtDW.alpha1 = a[11];
  rtDW.b = 0.0;
  rtDW.xnorm_tmp = xnrm2(0, a, 12);
  if (rtDW.xnorm_tmp != 0.0) {
    rtDW.xnorm = rt_hypotd_snf_a(a[11], rtDW.xnorm_tmp);
    if (a[11] >= 0.0) {
      rtDW.xnorm = -rtDW.xnorm;
    }

    if (fabs(rtDW.xnorm) < 1.0020841800044864E-292) {
      rtDW.knt = -1;
      do {
        rtDW.knt++;
        rtDW.xnorm *= 9.9792015476736E+291;
        rtDW.alpha1 *= 9.9792015476736E+291;
      } while (!(fabs(rtDW.xnorm) >= 1.0020841800044864E-292));

      rtDW.xnorm = rt_hypotd_snf_a(rtDW.alpha1, rtDW.xnorm_tmp);
      if (rtDW.alpha1 >= 0.0) {
        rtDW.xnorm = -rtDW.xnorm;
      }

      rtDW.b = (rtDW.xnorm - rtDW.alpha1) / rtDW.xnorm;
      for (lastc = 0; lastc <= rtDW.knt; lastc++) {
        rtDW.xnorm *= 1.0020841800044864E-292;
      }

      rtDW.alpha1 = rtDW.xnorm;
    } else {
      rtDW.b = (rtDW.xnorm - a[11]) / rtDW.xnorm;
      rtDW.alpha1 = rtDW.xnorm;
    }
  }

  tau[2] = rtDW.b;
  a[11] = 1.0;
  if (rtDW.b != 0.0) {
    rtDW.knt = 0;
    lastc = 11;
    while ((rtDW.knt + 1 > 0) && (a[lastc] == 0.0)) {
      rtDW.knt--;
      lastc--;
    }

    lastc = 4;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      rowleft = 12 + lastc;
      jy = rowleft;
      do {
        exitg1 = 0;
        if (jy <= (rtDW.knt << 2) + rowleft) {
          if (a[jy - 1] != 0.0) {
            exitg1 = 1;
          } else {
            jy += 4;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    rtDW.knt = -1;
    lastc = 0;
  }

  if (rtDW.knt + 1 > 0) {
    if (lastc != 0) {
      for (rowleft = 0; rowleft < lastc; rowleft++) {
        rtDW.work_c[rowleft] = 0.0;
      }

      rowleft = 11;
      jy = (rtDW.knt << 2) + 13;
      for (iac = 13; iac <= jy; iac += 4) {
        b_ix = 0;
        g = (iac + lastc) - 1;
        for (b_ia = iac; b_ia <= g; b_ia++) {
          rtDW.work_c[b_ix] += a[b_ia - 1] * a[rowleft];
          b_ix++;
        }

        rowleft++;
      }
    }

    if (!(-rtDW.b == 0.0)) {
      rowleft = 12;
      jy = 11;
      for (iac = 0; iac <= rtDW.knt; iac++) {
        if (a[jy] != 0.0) {
          rtDW.xnorm = a[jy] * -rtDW.b;
          b_ix = 0;
          g = lastc + rowleft;
          for (b_ia = rowleft; b_ia < g; b_ia++) {
            a[b_ia] += rtDW.work_c[b_ix] * rtDW.xnorm;
            b_ix++;
          }
        }

        jy++;
        rowleft += 4;
      }
    }
  }

  xzlarf(1, 1, 12, rtDW.b, a, 16, rtDW.work_c);
  a[11] = rtDW.alpha1;
}

/* Function for MATLAB Function: '<S7>/MATLAB Function' */
static real_T xnrm2_g(int32_T n, const real_T x[3])
{
  real_T y;
  int32_T k;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[1]);
    } else {
      rtDW.scale_p = 3.3121686421112381E-170;
      for (k = 2; k <= 1 + n; k++) {
        rtDW.absxk = fabs(x[k - 1]);
        if (rtDW.absxk > rtDW.scale_p) {
          rtDW.t = rtDW.scale_p / rtDW.absxk;
          y = y * rtDW.t * rtDW.t + 1.0;
          rtDW.scale_p = rtDW.absxk;
        } else {
          rtDW.t = rtDW.absxk / rtDW.scale_p;
          y += rtDW.t * rtDW.t;
        }
      }

      y = rtDW.scale_p * sqrt(y);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S7>/MATLAB Function' */
static real_T xzlarfg(int32_T n, real_T *alpha1, real_T x[3])
{
  real_T tau;
  int32_T knt;
  int32_T c_k;
  tau = 0.0;
  if (n > 0) {
    rtDW.xnorm_b = xnrm2_g(n - 1, x);
    if (rtDW.xnorm_b != 0.0) {
      rtDW.xnorm_b = rt_hypotd_snf_a(*alpha1, rtDW.xnorm_b);
      if (*alpha1 >= 0.0) {
        rtDW.xnorm_b = -rtDW.xnorm_b;
      }

      if (fabs(rtDW.xnorm_b) < 1.0020841800044864E-292) {
        knt = -1;
        do {
          knt++;
          for (c_k = 1; c_k < n; c_k++) {
            x[c_k] *= 9.9792015476736E+291;
          }

          rtDW.xnorm_b *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while (!(fabs(rtDW.xnorm_b) >= 1.0020841800044864E-292));

        rtDW.xnorm_b = rt_hypotd_snf_a(*alpha1, xnrm2_g(n - 1, x));
        if (*alpha1 >= 0.0) {
          rtDW.xnorm_b = -rtDW.xnorm_b;
        }

        tau = (rtDW.xnorm_b - *alpha1) / rtDW.xnorm_b;
        *alpha1 = 1.0 / (*alpha1 - rtDW.xnorm_b);
        for (c_k = 1; c_k < n; c_k++) {
          x[c_k] *= *alpha1;
        }

        for (c_k = 0; c_k <= knt; c_k++) {
          rtDW.xnorm_b *= 1.0020841800044864E-292;
        }

        *alpha1 = rtDW.xnorm_b;
      } else {
        tau = (rtDW.xnorm_b - *alpha1) / rtDW.xnorm_b;
        *alpha1 = 1.0 / (*alpha1 - rtDW.xnorm_b);
        for (knt = 1; knt < n; knt++) {
          x[knt] *= *alpha1;
        }

        *alpha1 = rtDW.xnorm_b;
      }
    }
  }

  return tau;
}

/* Function for MATLAB Function: '<S7>/MATLAB Function' */
static void xdlanv2(real_T *a, real_T *b, real_T *c, real_T *d, real_T *rt1r,
                    real_T *rt1i, real_T *rt2r, real_T *rt2i, real_T *cs, real_T
                    *sn)
{
  int32_T b_0;
  int32_T c_0;
  if (*c == 0.0) {
    *cs = 1.0;
    *sn = 0.0;
  } else if (*b == 0.0) {
    *cs = 0.0;
    *sn = 1.0;
    rtDW.bcmax = *d;
    *d = *a;
    *a = rtDW.bcmax;
    *b = -*c;
    *c = 0.0;
  } else {
    rtDW.tau_c = *a - *d;
    if ((rtDW.tau_c == 0.0) && ((*b < 0.0) != (*c < 0.0))) {
      *cs = 1.0;
      *sn = 0.0;
    } else {
      rtDW.p = 0.5 * rtDW.tau_c;
      rtDW.bcmis = fabs(*b);
      rtDW.z = fabs(*c);
      if ((rtDW.bcmis > rtDW.z) || rtIsNaN(rtDW.z)) {
        rtDW.bcmax = rtDW.bcmis;
      } else {
        rtDW.bcmax = rtDW.z;
      }

      if ((rtDW.bcmis < rtDW.z) || rtIsNaN(rtDW.z)) {
        rtDW.z = rtDW.bcmis;
      }

      if (!(*b < 0.0)) {
        b_0 = 1;
      } else {
        b_0 = -1;
      }

      if (!(*c < 0.0)) {
        c_0 = 1;
      } else {
        c_0 = -1;
      }

      rtDW.bcmis = rtDW.z * (real_T)b_0 * (real_T)c_0;
      rtDW.scale = fabs(rtDW.p);
      if ((!(rtDW.scale > rtDW.bcmax)) && (!rtIsNaN(rtDW.bcmax))) {
        rtDW.scale = rtDW.bcmax;
      }

      rtDW.z = rtDW.p / rtDW.scale * rtDW.p + rtDW.bcmax / rtDW.scale *
        rtDW.bcmis;
      if (rtDW.z >= 8.8817841970012523E-16) {
        if (!(rtDW.p < 0.0)) {
          rtDW.tau_c = sqrt(rtDW.scale) * sqrt(rtDW.z);
        } else {
          rtDW.tau_c = -(sqrt(rtDW.scale) * sqrt(rtDW.z));
        }

        rtDW.z = rtDW.p + rtDW.tau_c;
        *a = *d + rtDW.z;
        *d -= rtDW.bcmax / rtDW.z * rtDW.bcmis;
        rtDW.tau_c = rt_hypotd_snf_a(*c, rtDW.z);
        *cs = rtDW.z / rtDW.tau_c;
        *sn = *c / rtDW.tau_c;
        *b -= *c;
        *c = 0.0;
      } else {
        rtDW.bcmax = *b + *c;
        rtDW.tau_c = rt_hypotd_snf_a(rtDW.bcmax, rtDW.tau_c);
        *cs = sqrt((fabs(rtDW.bcmax) / rtDW.tau_c + 1.0) * 0.5);
        if (!(rtDW.bcmax < 0.0)) {
          b_0 = 1;
        } else {
          b_0 = -1;
        }

        *sn = -(rtDW.p / (rtDW.tau_c * *cs)) * (real_T)b_0;
        rtDW.p = *a * *cs + *b * *sn;
        rtDW.tau_c = -*a * *sn + *b * *cs;
        rtDW.bcmax = *c * *cs + *d * *sn;
        rtDW.bcmis = -*c * *sn + *d * *cs;
        *b = rtDW.tau_c * *cs + rtDW.bcmis * *sn;
        *c = -rtDW.p * *sn + rtDW.bcmax * *cs;
        rtDW.bcmax = ((rtDW.p * *cs + rtDW.bcmax * *sn) + (-rtDW.tau_c * *sn +
          rtDW.bcmis * *cs)) * 0.5;
        *a = rtDW.bcmax;
        *d = rtDW.bcmax;
        if (*c != 0.0) {
          if (*b != 0.0) {
            if ((*b < 0.0) == (*c < 0.0)) {
              rtDW.z = sqrt(fabs(*b));
              rtDW.bcmis = sqrt(fabs(*c));
              if (!(*c < 0.0)) {
                rtDW.p = rtDW.z * rtDW.bcmis;
              } else {
                rtDW.p = -(rtDW.z * rtDW.bcmis);
              }

              rtDW.tau_c = 1.0 / sqrt(fabs(*b + *c));
              *a = rtDW.bcmax + rtDW.p;
              *d = rtDW.bcmax - rtDW.p;
              *b -= *c;
              *c = 0.0;
              rtDW.p = rtDW.z * rtDW.tau_c;
              rtDW.tau_c *= rtDW.bcmis;
              rtDW.bcmax = *cs * rtDW.p - *sn * rtDW.tau_c;
              *sn = *cs * rtDW.tau_c + *sn * rtDW.p;
              *cs = rtDW.bcmax;
            }
          } else {
            *b = -*c;
            *c = 0.0;
            rtDW.bcmax = *cs;
            *cs = -*sn;
            *sn = rtDW.bcmax;
          }
        }
      }
    }
  }

  *rt1r = *a;
  *rt2r = *d;
  if (*c == 0.0) {
    *rt1i = 0.0;
    *rt2i = 0.0;
  } else {
    *rt1i = sqrt(fabs(*b)) * sqrt(fabs(*c));
    *rt2i = -*rt1i;
  }
}

/* Function for MATLAB Function: '<S7>/MATLAB Function' */
static void xrot(int32_T n, real_T x[16], int32_T ix0, int32_T iy0, real_T c,
                 real_T s)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (n >= 1) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      rtDW.temp_c = c * x[ix] + s * x[iy];
      x[iy] = c * x[iy] - s * x[ix];
      x[ix] = rtDW.temp_c;
      iy += 4;
      ix += 4;
    }
  }
}

/* Function for MATLAB Function: '<S7>/MATLAB Function' */
static void xrot_k(int32_T n, real_T x[16], int32_T ix0, int32_T iy0, real_T c,
                   real_T s)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (n >= 1) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      rtDW.temp = c * x[ix] + s * x[iy];
      x[iy] = c * x[iy] - s * x[ix];
      x[ix] = rtDW.temp;
      iy++;
      ix++;
    }
  }
}

/* Function for MATLAB Function: '<S7>/MATLAB Function' */
static void xrot_kc(real_T x[16], int32_T ix0, int32_T iy0, real_T c, real_T s)
{
  int32_T ix;
  int32_T iy;
  ix = ix0 - 1;
  iy = iy0 - 1;
  rtDW.temp_f = c * x[ix] + s * x[iy];
  x[iy] = c * x[iy] - s * x[ix];
  x[ix] = rtDW.temp_f;
  iy++;
  ix++;
  rtDW.temp_f = c * x[ix] + s * x[iy];
  x[iy] = c * x[iy] - s * x[ix];
  x[ix] = rtDW.temp_f;
  iy++;
  ix++;
  rtDW.temp_f = c * x[ix] + s * x[iy];
  x[iy] = c * x[iy] - s * x[ix];
  x[ix] = rtDW.temp_f;
  iy++;
  ix++;
  rtDW.temp_f = c * x[ix] + s * x[iy];
  x[iy] = c * x[iy] - s * x[ix];
  x[ix] = rtDW.temp_f;
}

/* Function for MATLAB Function: '<S7>/MATLAB Function' */
static int32_T eml_dlahqr(real_T h[16], real_T z[16])
{
  int32_T info;
  int32_T i;
  int32_T L;
  boolean_T goto150;
  int32_T k;
  int32_T m;
  int32_T nr;
  int32_T its;
  int32_T j;
  int32_T b_j;
  int32_T s_tmp;
  int32_T hoffset_tmp;
  int32_T sum1_tmp_tmp;
  int32_T sum1_tmp_tmp_0;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T exitg3;
  info = 0;
  rtDW.v[0] = 0.0;
  rtDW.v[1] = 0.0;
  rtDW.v[2] = 0.0;
  h[2] = 0.0;
  h[3] = 0.0;
  h[7] = 0.0;
  i = 3;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    L = 1;
    goto150 = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its < 301)) {
      k = i;
      exitg3 = false;
      while ((!exitg3) && (k + 1 > L)) {
        j = ((k - 1) << 2) + k;
        rtDW.ba = fabs(h[j]);
        if (rtDW.ba <= 4.0083367200179456E-292) {
          exitg3 = true;
        } else {
          m = (k << 2) + k;
          rtDW.bb = fabs(h[m]);
          rtDW.s = h[j - 1];
          rtDW.tst = fabs(rtDW.s) + rtDW.bb;
          if (rtDW.tst == 0.0) {
            if (k - 1 >= 1) {
              rtDW.tst = fabs(h[(((k - 2) << 2) + k) - 1]);
            }

            if (k + 2 <= 4) {
              rtDW.tst += fabs(h[m + 1]);
            }
          }

          if (rtDW.ba <= 2.2204460492503131E-16 * rtDW.tst) {
            rtDW.htmp2 = fabs(h[m - 1]);
            if (rtDW.ba > rtDW.htmp2) {
              rtDW.tst = rtDW.ba;
              rtDW.ba = rtDW.htmp2;
            } else {
              rtDW.tst = rtDW.htmp2;
            }

            rtDW.htmp2 = fabs(rtDW.s - h[(k << 2) + k]);
            if (rtDW.bb > rtDW.htmp2) {
              rtDW.aa = rtDW.bb;
              rtDW.bb = rtDW.htmp2;
            } else {
              rtDW.aa = rtDW.htmp2;
            }

            rtDW.s = rtDW.aa + rtDW.tst;
            rtDW.bb = rtDW.aa / rtDW.s * rtDW.bb * 2.2204460492503131E-16;
            if ((4.0083367200179456E-292 > rtDW.bb) || rtIsNaN(rtDW.bb)) {
              rtDW.bb = 4.0083367200179456E-292;
            }

            if (rtDW.tst / rtDW.s * rtDW.ba <= rtDW.bb) {
              exitg3 = true;
            } else {
              k--;
            }
          } else {
            k--;
          }
        }
      }

      L = k + 1;
      if (k + 1 > 1) {
        h[k + ((k - 1) << 2)] = 0.0;
      }

      if (k + 1 >= i) {
        goto150 = true;
        exitg2 = true;
      } else {
        switch (its) {
         case 10:
          rtDW.s = fabs(h[(((k + 1) << 2) + k) + 2]) + fabs(h[((k << 2) + k) + 1]);
          rtDW.ba = h[(k << 2) + k] + 0.75 * rtDW.s;
          rtDW.aa = -0.4375 * rtDW.s;
          rtDW.htmp2 = rtDW.s;
          rtDW.tst = rtDW.ba;
          break;

         case 20:
          rtDW.s = fabs(h[(((i - 2) << 2) + i) - 1]) + fabs(h[((i - 1) << 2) + i]);
          rtDW.ba = h[(i << 2) + i] + 0.75 * rtDW.s;
          rtDW.aa = -0.4375 * rtDW.s;
          rtDW.htmp2 = rtDW.s;
          rtDW.tst = rtDW.ba;
          break;

         default:
          m = ((i - 1) << 2) + i;
          rtDW.ba = h[m - 1];
          rtDW.htmp2 = h[m];
          m = (i << 2) + i;
          rtDW.aa = h[m - 1];
          rtDW.tst = h[m];
          break;
        }

        rtDW.s = ((fabs(rtDW.ba) + fabs(rtDW.aa)) + fabs(rtDW.htmp2)) + fabs
          (rtDW.tst);
        if (rtDW.s == 0.0) {
          rtDW.ba = 0.0;
          rtDW.tst = 0.0;
          rtDW.bb = 0.0;
          rtDW.htmp2 = 0.0;
        } else {
          rtDW.ba /= rtDW.s;
          rtDW.htmp2 /= rtDW.s;
          rtDW.aa /= rtDW.s;
          rtDW.tst /= rtDW.s;
          rtDW.bb = (rtDW.ba + rtDW.tst) / 2.0;
          rtDW.ba = (rtDW.ba - rtDW.bb) * (rtDW.tst - rtDW.bb) - rtDW.aa *
            rtDW.htmp2;
          rtDW.htmp2 = sqrt(fabs(rtDW.ba));
          if (rtDW.ba >= 0.0) {
            rtDW.ba = rtDW.bb * rtDW.s;
            rtDW.bb = rtDW.ba;
            rtDW.tst = rtDW.htmp2 * rtDW.s;
            rtDW.htmp2 = -rtDW.tst;
          } else {
            rtDW.ba = rtDW.bb + rtDW.htmp2;
            rtDW.bb -= rtDW.htmp2;
            if (fabs(rtDW.ba - rtDW.tst) <= fabs(rtDW.bb - rtDW.tst)) {
              rtDW.ba *= rtDW.s;
              rtDW.bb = rtDW.ba;
            } else {
              rtDW.bb *= rtDW.s;
              rtDW.ba = rtDW.bb;
            }

            rtDW.tst = 0.0;
            rtDW.htmp2 = 0.0;
          }
        }

        m = i - 1;
        exitg3 = false;
        while ((!exitg3) && (m >= k + 1)) {
          s_tmp = ((m - 1) << 2) + m;
          rtDW.aa = h[s_tmp - 1];
          rtDW.sum1 = rtDW.aa - rtDW.bb;
          rtDW.s = (fabs(rtDW.sum1) + fabs(rtDW.htmp2)) + fabs(h[s_tmp]);
          rtDW.h21s = h[((m - 1) << 2) + m] / rtDW.s;
          s_tmp = (m << 2) + m;
          rtDW.v[0] = (rtDW.sum1 / rtDW.s * (rtDW.aa - rtDW.ba) + h[s_tmp - 1] *
                       rtDW.h21s) - rtDW.htmp2 / rtDW.s * rtDW.tst;
          rtDW.v[1] = (((rtDW.aa + h[s_tmp]) - rtDW.ba) - rtDW.bb) * rtDW.h21s;
          rtDW.v[2] = h[s_tmp + 1] * rtDW.h21s;
          rtDW.s = (fabs(rtDW.v[0]) + fabs(rtDW.v[1])) + fabs(rtDW.v[2]);
          rtDW.v[0] /= rtDW.s;
          rtDW.v[1] /= rtDW.s;
          rtDW.v[2] /= rtDW.s;
          if (k + 1 == m) {
            exitg3 = true;
          } else {
            j = ((m - 2) << 2) + m;
            if (fabs(h[j - 1]) * (fabs(rtDW.v[1]) + fabs(rtDW.v[2])) <= ((fabs
                  (h[j - 2]) + fabs(rtDW.aa)) + fabs(h[(m << 2) + m])) *
                (2.2204460492503131E-16 * fabs(rtDW.v[0]))) {
              exitg3 = true;
            } else {
              m--;
            }
          }
        }

        for (s_tmp = m; s_tmp <= i; s_tmp++) {
          nr = (i - s_tmp) + 2;
          if (3 < nr) {
            nr = 3;
          }

          if (s_tmp > m) {
            hoffset_tmp = (((s_tmp - 2) << 2) + s_tmp) - 1;
            for (j = 0; j < nr; j++) {
              rtDW.v[j] = h[j + hoffset_tmp];
            }
          }

          rtDW.ba = rtDW.v[0];
          rtDW.b_v[0] = rtDW.v[0];
          rtDW.b_v[1] = rtDW.v[1];
          rtDW.b_v[2] = rtDW.v[2];
          rtDW.s = xzlarfg(nr, &rtDW.ba, rtDW.b_v);
          rtDW.v[1] = rtDW.b_v[1];
          rtDW.v[2] = rtDW.b_v[2];
          rtDW.v[0] = rtDW.ba;
          if (s_tmp > m) {
            h[(s_tmp + ((s_tmp - 2) << 2)) - 1] = rtDW.ba;
            h[s_tmp + ((s_tmp - 2) << 2)] = 0.0;
            if (s_tmp < i) {
              h[(s_tmp + ((s_tmp - 2) << 2)) + 1] = 0.0;
            }
          } else {
            if (m > k + 1) {
              h[(s_tmp + ((s_tmp - 2) << 2)) - 1] *= 1.0 - rtDW.s;
            }
          }

          rtDW.ba = rtDW.b_v[1];
          rtDW.tst = rtDW.s * rtDW.b_v[1];
          switch (nr) {
           case 3:
            rtDW.bb = rtDW.b_v[2];
            rtDW.htmp2 = rtDW.s * rtDW.b_v[2];
            for (b_j = s_tmp - 1; b_j + 1 < 5; b_j++) {
              j = b_j << 2;
              nr = j + s_tmp;
              hoffset_tmp = nr - 1;
              sum1_tmp_tmp = nr + 1;
              rtDW.sum1 = (h[hoffset_tmp] + h[nr] * rtDW.ba) + h[sum1_tmp_tmp] *
                rtDW.bb;
              j += s_tmp;
              h[j - 1] = h[hoffset_tmp] - rtDW.sum1 * rtDW.s;
              h[j] = h[nr] - rtDW.sum1 * rtDW.tst;
              h[j + 1] = h[sum1_tmp_tmp] - rtDW.sum1 * rtDW.htmp2;
            }

            nr = s_tmp + 3;
            j = i + 1;
            if (nr < j) {
              j = nr;
            }

            for (b_j = 0; b_j < j; b_j++) {
              rtDW.aa = h[((s_tmp - 1) << 2) + b_j];
              nr = (s_tmp << 2) + b_j;
              hoffset_tmp = ((s_tmp + 1) << 2) + b_j;
              rtDW.sum1 = (rtDW.aa + h[nr] * rtDW.ba) + h[hoffset_tmp] * rtDW.bb;
              h[b_j + ((s_tmp - 1) << 2)] = rtDW.aa - rtDW.sum1 * rtDW.s;
              h[b_j + (s_tmp << 2)] = h[nr] - rtDW.sum1 * rtDW.tst;
              h[b_j + ((s_tmp + 1) << 2)] = h[hoffset_tmp] - rtDW.sum1 *
                rtDW.htmp2;
            }

            for (b_j = 0; b_j < 4; b_j++) {
              j = (s_tmp - 1) << 2;
              rtDW.aa = z[j + b_j];
              sum1_tmp_tmp = s_tmp << 2;
              nr = sum1_tmp_tmp + b_j;
              sum1_tmp_tmp_0 = (s_tmp + 1) << 2;
              hoffset_tmp = sum1_tmp_tmp_0 + b_j;
              rtDW.sum1 = (rtDW.aa + z[nr] * rtDW.ba) + z[hoffset_tmp] * rtDW.bb;
              z[b_j + j] = rtDW.aa - rtDW.sum1 * rtDW.s;
              z[b_j + sum1_tmp_tmp] = z[nr] - rtDW.sum1 * rtDW.tst;
              z[b_j + sum1_tmp_tmp_0] = z[hoffset_tmp] - rtDW.sum1 * rtDW.htmp2;
            }
            break;

           case 2:
            for (b_j = s_tmp - 1; b_j + 1 < 5; b_j++) {
              j = b_j << 2;
              nr = j + s_tmp;
              hoffset_tmp = nr - 1;
              rtDW.sum1 = h[hoffset_tmp] + h[nr] * rtDW.ba;
              j += s_tmp;
              h[j - 1] = h[hoffset_tmp] - rtDW.sum1 * rtDW.s;
              h[j] = h[nr] - rtDW.sum1 * rtDW.tst;
            }

            for (j = 0; j <= i; j++) {
              nr = ((s_tmp - 1) << 2) + j;
              hoffset_tmp = (s_tmp << 2) + j;
              rtDW.sum1 = h[nr] + h[hoffset_tmp] * rtDW.ba;
              h[j + ((s_tmp - 1) << 2)] = h[nr] - rtDW.sum1 * rtDW.s;
              h[j + (s_tmp << 2)] = h[hoffset_tmp] - rtDW.sum1 * rtDW.tst;
            }

            for (j = 0; j < 4; j++) {
              nr = ((s_tmp - 1) << 2) + j;
              hoffset_tmp = (s_tmp << 2) + j;
              rtDW.sum1 = z[nr] + z[hoffset_tmp] * rtDW.ba;
              z[j + ((s_tmp - 1) << 2)] = z[nr] - rtDW.sum1 * rtDW.s;
              z[j + (s_tmp << 2)] = z[hoffset_tmp] - rtDW.sum1 * rtDW.tst;
            }
            break;
          }
        }

        its++;
      }
    }

    if (!goto150) {
      info = i + 1;
      exitg1 = true;
    } else {
      if ((i + 1 != L) && (L == i)) {
        rtDW.s = h[(((i - 1) << 2) + i) - 1];
        rtDW.ba = h[((i << 2) + i) - 1];
        rtDW.tst = h[((i - 1) << 2) + i];
        rtDW.bb = h[(i << 2) + i];
        xdlanv2(&rtDW.s, &rtDW.ba, &rtDW.tst, &rtDW.bb, &rtDW.htmp2, &rtDW.aa,
                &rtDW.sum1, &rtDW.h21s, &rtDW.cs, &rtDW.sn);
        j = i + ((i - 1) << 2);
        h[j - 1] = rtDW.s;
        its = i + (i << 2);
        h[its - 1] = rtDW.ba;
        h[j] = rtDW.tst;
        h[its] = rtDW.bb;
        if (4 > i + 1) {
          xrot(3 - i, h, i + ((i + 1) << 2), (i + ((i + 1) << 2)) + 1, rtDW.cs,
               rtDW.sn);
        }

        xrot_k(i - 1, h, 1 + ((i - 1) << 2), 1 + (i << 2), rtDW.cs, rtDW.sn);
        xrot_kc(z, 1 + ((i - 1) << 2), 1 + (i << 2), rtDW.cs, rtDW.sn);
      }

      i = L - 2;
    }
  }

  return info;
}

/* Function for MATLAB Function: '<S7>/MATLAB Function' */
static void schur(const real_T A[16], real_T V[16], real_T T[16])
{
  boolean_T p;
  p = true;
  for (rtDW.k_g = 0; rtDW.k_g < 16; rtDW.k_g++) {
    p = (p && ((!rtIsInf(A[rtDW.k_g])) && (!rtIsNaN(A[rtDW.k_g]))));
  }

  if (!p) {
    for (rtDW.k_g = 0; rtDW.k_g < 16; rtDW.k_g++) {
      V[rtDW.k_g] = (rtNaN);
    }

    rtDW.k_g = 2;
    while (rtDW.k_g < 5) {
      V[rtDW.k_g - 1] = 0.0;
      rtDW.k_g++;
    }

    rtDW.k_g = 3;
    while (rtDW.k_g < 5) {
      V[rtDW.k_g + 3] = 0.0;
      rtDW.k_g++;
    }

    V[11] = 0.0;
    for (rtDW.k_g = 0; rtDW.k_g < 16; rtDW.k_g++) {
      T[rtDW.k_g] = (rtNaN);
    }
  } else {
    memcpy(&T[0], &A[0], sizeof(real_T) << 4U);
    xgehrd(T, rtDW.tau);
    memcpy(&V[0], &T[0], sizeof(real_T) << 4U);
    rtDW.k_g = 0;
    while (rtDW.k_g <= 2) {
      V[12 + rtDW.k_g] = 0.0;
      rtDW.k_g++;
    }

    rtDW.k_g = 0;
    while (rtDW.k_g <= 1) {
      V[8 + rtDW.k_g] = 0.0;
      rtDW.k_g++;
    }

    rtDW.k_g = 1;
    while (rtDW.k_g + 3 <= 4) {
      V[rtDW.k_g + 10] = V[rtDW.k_g + 6];
      rtDW.k_g++;
    }

    V[4] = 0.0;
    rtDW.k_g = 0;
    while (rtDW.k_g + 3 <= 4) {
      V[rtDW.k_g + 6] = V[rtDW.k_g + 2];
      rtDW.k_g++;
    }

    rtDW.work[0] = 0.0;
    V[1] = 0.0;
    rtDW.work[1] = 0.0;
    V[2] = 0.0;
    rtDW.work[2] = 0.0;
    V[3] = 0.0;
    rtDW.work[3] = 0.0;
    V[0] = 1.0;
    V[15] = 1.0 - rtDW.tau[2];
    rtDW.k_g = 0;
    while (rtDW.k_g <= 1) {
      V[14 - rtDW.k_g] = 0.0;
      rtDW.k_g++;
    }

    V[10] = 1.0;
    xzlarf(2, 1, 11, rtDW.tau[1], V, 15, rtDW.work);
    rtDW.k_g = 11;
    while (rtDW.k_g + 1 <= 12) {
      V[rtDW.k_g] *= -rtDW.tau[1];
      rtDW.k_g++;
    }

    V[10] = 1.0 - rtDW.tau[1];
    V[9] = 0.0;
    V[5] = 1.0;
    xzlarf(3, 2, 6, rtDW.tau[0], V, 10, rtDW.work);
    rtDW.k_g = 6;
    while (rtDW.k_g + 1 <= 8) {
      V[rtDW.k_g] *= -rtDW.tau[0];
      rtDW.k_g++;
    }

    V[5] = 1.0 - rtDW.tau[0];
    eml_dlahqr(T, V);
    T[3] = 0.0;
  }
}

static void SystemCore_release_aomx(const mbed_DigitalRead *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_digitalIO_close(obj->MW_DIGITALIO_HANDLE);
  }
}

static void SystemCore_delete_aomx(const mbed_DigitalRead *obj)
{
  SystemCore_release_aomx(obj);
}

static void matlabCodegenHandle_matlab_aomx(mbed_DigitalRead *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    SystemCore_delete_aomx(obj);
  }
}

static void SystemCore_release_a(const mbed_DigitalWrite *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_digitalIO_close(obj->MW_DIGITALIO_HANDLE);
  }
}

static void SystemCore_delete_a(const mbed_DigitalWrite *obj)
{
  SystemCore_release_a(obj);
}

static void matlabCodegenHandle_matlabCod_a(mbed_DigitalWrite *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    SystemCore_delete_a(obj);
  }
}

static void SystemCore_release_aom(const mbed_PWMOutput *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_PWM_Stop(obj->MW_PWM_HANDLE);
    MW_PWM_Close(obj->MW_PWM_HANDLE);
  }
}

static void SystemCore_delete_aom(const mbed_PWMOutput *obj)
{
  SystemCore_release_aom(obj);
}

static void matlabCodegenHandle_matlabC_aom(mbed_PWMOutput *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    SystemCore_delete_aom(obj);
  }
}

static void SystemCore_release(const mbed_AnalogInput *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_AnalogIn_Stop(obj->MW_ANALOGIN_HANDLE);
    MW_AnalogIn_Close(obj->MW_ANALOGIN_HANDLE);
  }
}

static void SystemCore_delete(const mbed_AnalogInput *obj)
{
  SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(mbed_AnalogInput *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    SystemCore_delete(obj);
  }
}

/* Model step function */
void motoraiHIL_step(void)
{
  boolean_T rtb_ENC_A_0;
  boolean_T rtb_Counter1;
  boolean_T exitg1;

  /* RateTransition: '<Root>/Rate Transition8' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    rtDW.RateTransition8 = rtDW.RateTransition8_Buffer0;
  }

  /* End of RateTransition: '<Root>/Rate Transition8' */

  /* MATLABSystem: '<S9>/Digital Read' */
  if (rtDW.obj_h.SampleTime != -1.0) {
    rtDW.obj_h.SampleTime = -1.0;
  }

  rtb_Counter1 = MW_digitalIO_read(rtDW.obj_h.MW_DIGITALIO_HANDLE);

  /* Chart: '<Root>/Logic Brain1' incorporates:
   *  Delay: '<Root>/Delay3'
   *  MATLABSystem: '<S9>/Digital Read'
   */
  if (rtDW.bitsForTID0.is_active_c1_motoraiHIL == 0U) {
    rtDW.bitsForTID0.is_active_c1_motoraiHIL = 1;
    rtDW.bitsForTID0.is_c1_motoraiHIL = IN_idle;
    rtDW.start_signal = 0.0;
  } else {
    switch (rtDW.bitsForTID0.is_c1_motoraiHIL) {
     case IN_button_wait:
      if (rtb_Counter1) {
        rtDW.bitsForTID0.is_c1_motoraiHIL = IN_button_wait;
      } else {
        rtDW.reset = 0.0;
        rtDW.n_stop_motor = 1.0;
        rtDW.bitsForTID0.is_c1_motoraiHIL = IN_start_estimation;
        rtDW.start_signal = 1.0;
      }
      break;

     case IN_idle:
      rtDW.start_signal = 0.0;
      if (rtb_Counter1) {
        rtDW.n_stop_motor = 0.0;
        rtDW.bitsForTID0.is_c1_motoraiHIL = IN_button_wait;
      }
      break;

     default:
      rtDW.start_signal = 1.0;
      if (rtDW.bitsForTID0.Delay3_DSTATE) {
        rtDW.reset = 1.0;
        rtDW.bitsForTID0.is_c1_motoraiHIL = IN_idle;
        rtDW.start_signal = 0.0;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Logic Brain1' */

  /* S-Function (sdspcount2): '<Root>/Counter1' */
  rtb_Counter1 = false;
  if (rtDW.reset != 0.0) {
    rtDW.Counter1_Count = 0U;
  }

  if (rtDW.RateTransition8 != 0.0) {
    if (rtDW.Counter1_Count < 10000) {
      rtDW.Counter1_Count++;
    } else {
      rtDW.Counter1_Count = 0U;
    }
  }

  if (rtDW.Counter1_Count == 10000) {
    rtb_Counter1 = true;
  }

  /* End of S-Function (sdspcount2): '<Root>/Counter1' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (sdspsreg2): '<Root>/Delay Line2' */
    rtDW.k = 0;
    while (rtDW.k < 50 - rtDW.DelayLine2_BUFF_OFFSET) {
      rtDW.DelayLine2[rtDW.k] = rtDW.DelayLine2_Buff[rtDW.DelayLine2_BUFF_OFFSET
        + rtDW.k];
      rtDW.k++;
    }

    rtDW.idx1 = -rtDW.DelayLine2_BUFF_OFFSET;
    rtDW.k = 0;
    while (rtDW.k < rtDW.DelayLine2_BUFF_OFFSET) {
      rtDW.DelayLine2[(rtDW.idx1 + rtDW.k) + 50] = rtDW.DelayLine2_Buff[rtDW.k];
      rtDW.k++;
    }

    /* End of S-Function (sdspsreg2): '<Root>/Delay Line2' */

    /* S-Function (sdspsreg2): '<Root>/Delay Line3' */
    rtDW.k = 0;
    while (rtDW.k < 50 - rtDW.DelayLine3_BUFF_OFFSET) {
      rtDW.DelayLine3[rtDW.k] = rtDW.DelayLine3_Buff[rtDW.DelayLine3_BUFF_OFFSET
        + rtDW.k];
      rtDW.k++;
    }

    rtDW.idx1 = -rtDW.DelayLine3_BUFF_OFFSET;
    rtDW.k = 0;
    while (rtDW.k < rtDW.DelayLine3_BUFF_OFFSET) {
      rtDW.DelayLine3[(rtDW.idx1 + rtDW.k) + 50] = rtDW.DelayLine3_Buff[rtDW.k];
      rtDW.k++;
    }

    /* End of S-Function (sdspsreg2): '<Root>/Delay Line3' */

    /* MATLABSystem: '<S8>/ENC_A' */
    if (rtDW.obj_e.SampleTime != 0.002) {
      rtDW.obj_e.SampleTime = 0.002;
    }

    rtb_ENC_A_0 = MW_digitalIO_read(rtDW.obj_e.MW_DIGITALIO_HANDLE);

    /* DataTypeConversion: '<S255>/Data Type Conversion' incorporates:
     *  MATLABSystem: '<S8>/ENC_A'
     */
    rtDW.DataTypeConversion = rtb_ENC_A_0;

    /* S-Function (discreteNLastSamples): '<S257>/S-Function ' */
    /* S-Function block: <S257>/S-Function  */
    {
      int nSamples = 2 ;
      int io = 0;
      int iv;
      int ind_Ps = rtDW.SFunction_IWORK.indPs;

      /* Input present value(s) */
      ((real_T *)rtDW.SFunction_PWORK.uBuffers)[ind_Ps] =
        rtDW.DataTypeConversion;

      /* Output past value(s) */
      /* Output from present sample index to 0 */
      for (iv = ind_Ps; iv >= 0; --iv)
        (&rtDW.SFunction[0])[io++] = ((real_T *)rtDW.SFunction_PWORK.uBuffers)
          [iv];

      /* Output from end of buffer to present sample index excl. */
      for (iv = nSamples-1; iv > ind_Ps; --iv)
        (&rtDW.SFunction[0])[io++] = ((real_T *)rtDW.SFunction_PWORK.uBuffers)
          [iv];

      /* Update ring buffer index */
      if (++(rtDW.SFunction_IWORK.indPs) == nSamples)
        rtDW.SFunction_IWORK.indPs = 0;
    }

    /* MATLABSystem: '<S8>/ENC_B' */
    if (rtDW.obj_k.SampleTime != 0.002) {
      rtDW.obj_k.SampleTime = 0.002;
    }

    rtb_ENC_A_0 = MW_digitalIO_read(rtDW.obj_k.MW_DIGITALIO_HANDLE);

    /* DataTypeConversion: '<S255>/Data Type Conversion1' incorporates:
     *  MATLABSystem: '<S8>/ENC_B'
     */
    rtDW.DataTypeConversion1 = rtb_ENC_A_0;

    /* S-Function (discreteNLastSamples): '<S258>/S-Function ' */
    /* S-Function block: <S258>/S-Function  */
    {
      int nSamples = 2 ;
      int io = 0;
      int iv;
      int ind_Ps = rtDW.SFunction_IWORK_p.indPs;

      /* Input present value(s) */
      ((real_T *)rtDW.SFunction_PWORK_m.uBuffers)[ind_Ps] =
        rtDW.DataTypeConversion1;

      /* Output past value(s) */
      /* Output from present sample index to 0 */
      for (iv = ind_Ps; iv >= 0; --iv)
        (&rtDW.SFunction_j[0])[io++] = ((real_T *)
          rtDW.SFunction_PWORK_m.uBuffers)[iv];

      /* Output from end of buffer to present sample index excl. */
      for (iv = nSamples-1; iv > ind_Ps; --iv)
        (&rtDW.SFunction_j[0])[io++] = ((real_T *)
          rtDW.SFunction_PWORK_m.uBuffers)[iv];

      /* Update ring buffer index */
      if (++(rtDW.SFunction_IWORK_p.indPs) == nSamples)
        rtDW.SFunction_IWORK_p.indPs = 0;
    }

    /* S-Function (sdspcount2): '<S8>/Counter' incorporates:
     *  DataTypeConversion: '<S255>/Data Type Conversion2'
     *  DataTypeConversion: '<S255>/Data Type Conversion3'
     *  Logic: '<S256>/XOR'
     *  Logic: '<S256>/XOR1'
     *  Logic: '<S256>/XOR2'
     */
    if (MWDSP_EPH_R_B((boolean_T)((boolean_T)((rtDW.SFunction[1] != 0.0) ^
           (rtDW.SFunction[0] != 0.0)) ^ (boolean_T)((rtDW.SFunction_j[0] != 0.0)
           ^ (rtDW.SFunction_j[1] != 0.0))), &rtDW.Counter_ClkEphState) != 0U) {
      if (rtDW.Counter_Count < 255) {
        rtDW.Counter_Count++;
      } else {
        rtDW.Counter_Count = 0U;
      }
    }

    /* Gain: '<S8>/Gain' incorporates:
     *  S-Function (sdspcount2): '<S8>/Counter'
     */
    rtDW.rad = 0.0062831853071795866 * (real_T)rtDW.Counter_Count;
  }

  /* MATLABSystem: '<S2>/Digital Write' incorporates:
   *  Logic: '<S2>/NOT'
   */
  MW_digitalIO_write(rtDW.obj_bu.MW_DIGITALIO_HANDLE, !(rtDW.n_stop_motor != 0.0));

  /* Switch: '<Root>/Switch3' incorporates:
   *  Constant: '<Root>/Constant5'
   */
  if (rtDW.n_stop_motor > 0.0) {
    /* Switch: '<Root>/Switch2' incorporates:
     *  Constant: '<Root>/Constant4'
     */
    if (rtDW.start_signal > 0.0) {
      rtDW.Delay5_DSTATE = 1000.0;
    }

    /* End of Switch: '<Root>/Switch2' */
  } else {
    rtDW.Delay5_DSTATE = 0.0;
  }

  /* MATLABSystem: '<S6>/PWM Output' incorporates:
   *  Constant: '<S6>/Actuation voltage'
   *  Constant: '<S6>/to percentage'
   *  Product: '<S6>/Divide'
   *  Product: '<S6>/Divide1'
   */
  MW_PWM_SetDutyCycle(rtDW.obj_ko.MW_PWM_HANDLE, rtDW.Delay5_DSTATE / 1000.0 *
                      100.0);

  /* RateTransition: '<Root>/Rate Transition1' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    memcpy(&rtDW.RateTransition1[0], &rtDW.RateTransition1_Buffer0[0], 100U *
           sizeof(real_T));
  }

  /* End of RateTransition: '<Root>/Rate Transition1' */

  /* Outputs for Triggered SubSystem: '<Root>/Parameter Estimation & LQR 1' incorporates:
   *  TriggerPort: '<S7>/Trigger'
   */
  /* Delay: '<Root>/Delay4' */
  if (rtDW.Delay4_DSTATE[0U] && (rtPrevZCX.ParameterEstimationLQR1_Trig_ZC !=
       POS_ZCSIG)) {
    /* DotProduct: '<S21>/Dot Product' */
    rtDW.denAccum = 0.0;

    /* DotProduct: '<S99>/Dot Product' */
    rtDW.A_idx_0 = 0.0;

    /* DotProduct: '<S110>/Dot Product' */
    rtDW.A_idx_2 = 0.0;

    /* DotProduct: '<S121>/Dot Product' */
    rtDW.A_idx_1 = 0.0;

    /* DotProduct: '<S132>/Dot Product' */
    rtDW.A_idx_3 = 0.0;

    /* DotProduct: '<S143>/Dot Product' */
    rtDW.B_idx_1 = 0.0;

    /* DotProduct: '<S154>/Dot Product' */
    rtDW.R = 0.0;

    /* DotProduct: '<S165>/Dot Product' */
    rtDW.A_tmp = 0.0;

    /* DotProduct: '<S176>/Dot Product' */
    rtDW.d0 = 0.0;

    /* DotProduct: '<S22>/Dot Product' */
    rtDW.d1 = 0.0;

    /* DotProduct: '<S33>/Dot Product' */
    rtDW.d2 = 0.0;

    /* DotProduct: '<S44>/Dot Product' */
    rtDW.d3 = 0.0;

    /* DotProduct: '<S55>/Dot Product' */
    rtDW.d4 = 0.0;

    /* DotProduct: '<S66>/Dot Product' */
    rtDW.d5 = 0.0;

    /* DotProduct: '<S77>/Dot Product' */
    rtDW.d6 = 0.0;

    /* DotProduct: '<S88>/Dot Product' */
    rtDW.d7 = 0.0;

    /* DotProduct: '<S96>/Dot Product' */
    rtDW.d8 = 0.0;

    /* DotProduct: '<S97>/Dot Product' */
    rtDW.d9 = 0.0;

    /* DotProduct: '<S98>/Dot Product' */
    rtDW.d10 = 0.0;

    /* DotProduct: '<S100>/Dot Product' */
    rtDW.d11 = 0.0;

    /* DotProduct: '<S101>/Dot Product' */
    rtDW.d12 = 0.0;

    /* DotProduct: '<S102>/Dot Product' */
    rtDW.d13 = 0.0;

    /* DotProduct: '<S103>/Dot Product' */
    rtDW.d14 = 0.0;

    /* DotProduct: '<S104>/Dot Product' */
    rtDW.d15 = 0.0;

    /* DotProduct: '<S105>/Dot Product' */
    rtDW.d16 = 0.0;

    /* DotProduct: '<S106>/Dot Product' */
    rtDW.d17 = 0.0;

    /* DotProduct: '<S107>/Dot Product' */
    rtDW.d18 = 0.0;

    /* DotProduct: '<S108>/Dot Product' */
    rtDW.d19 = 0.0;

    /* DotProduct: '<S109>/Dot Product' */
    rtDW.d20 = 0.0;

    /* DotProduct: '<S111>/Dot Product' */
    rtDW.d21 = 0.0;

    /* DotProduct: '<S112>/Dot Product' */
    rtDW.d22 = 0.0;

    /* DotProduct: '<S113>/Dot Product' */
    rtDW.d23 = 0.0;

    /* DotProduct: '<S114>/Dot Product' */
    rtDW.d24 = 0.0;

    /* DotProduct: '<S115>/Dot Product' */
    rtDW.d25 = 0.0;

    /* DotProduct: '<S116>/Dot Product' */
    rtDW.d26 = 0.0;

    /* DotProduct: '<S117>/Dot Product' */
    rtDW.d27 = 0.0;

    /* DotProduct: '<S118>/Dot Product' */
    rtDW.d28 = 0.0;

    /* DotProduct: '<S119>/Dot Product' */
    rtDW.d29 = 0.0;

    /* DotProduct: '<S120>/Dot Product' */
    rtDW.d30 = 0.0;

    /* DotProduct: '<S122>/Dot Product' */
    rtDW.d31 = 0.0;

    /* DotProduct: '<S123>/Dot Product' */
    rtDW.d32 = 0.0;

    /* DotProduct: '<S124>/Dot Product' */
    rtDW.d33 = 0.0;

    /* DotProduct: '<S125>/Dot Product' */
    rtDW.d34 = 0.0;

    /* DotProduct: '<S126>/Dot Product' */
    rtDW.d35 = 0.0;

    /* DotProduct: '<S127>/Dot Product' */
    rtDW.d36 = 0.0;

    /* DotProduct: '<S128>/Dot Product' */
    rtDW.d37 = 0.0;

    /* DotProduct: '<S129>/Dot Product' */
    rtDW.d38 = 0.0;

    /* DotProduct: '<S130>/Dot Product' */
    rtDW.d39 = 0.0;

    /* DotProduct: '<S131>/Dot Product' */
    rtDW.d40 = 0.0;

    /* DotProduct: '<S133>/Dot Product' */
    rtDW.d41 = 0.0;

    /* DotProduct: '<S134>/Dot Product' */
    rtDW.d42 = 0.0;

    /* DotProduct: '<S135>/Dot Product' */
    rtDW.d43 = 0.0;

    /* DotProduct: '<S136>/Dot Product' */
    rtDW.d44 = 0.0;

    /* DotProduct: '<S137>/Dot Product' */
    rtDW.d45 = 0.0;

    /* DotProduct: '<S138>/Dot Product' */
    rtDW.rtb_netsum_k = 0.0;

    /* DotProduct: '<S139>/Dot Product' */
    rtDW.d46 = 0.0;

    /* DotProduct: '<S140>/Dot Product' */
    rtDW.d47 = 0.0;

    /* DotProduct: '<S141>/Dot Product' */
    rtDW.d48 = 0.0;

    /* DotProduct: '<S142>/Dot Product' */
    rtDW.d49 = 0.0;

    /* DotProduct: '<S144>/Dot Product' */
    rtDW.d50 = 0.0;

    /* DotProduct: '<S145>/Dot Product' */
    rtDW.d51 = 0.0;

    /* DotProduct: '<S146>/Dot Product' */
    rtDW.d52 = 0.0;

    /* DotProduct: '<S147>/Dot Product' */
    rtDW.d53 = 0.0;

    /* DotProduct: '<S148>/Dot Product' */
    rtDW.d54 = 0.0;

    /* DotProduct: '<S149>/Dot Product' */
    rtDW.d55 = 0.0;

    /* DotProduct: '<S150>/Dot Product' */
    rtDW.d56 = 0.0;

    /* DotProduct: '<S151>/Dot Product' */
    rtDW.d57 = 0.0;

    /* DotProduct: '<S152>/Dot Product' */
    rtDW.d58 = 0.0;

    /* DotProduct: '<S153>/Dot Product' */
    rtDW.d59 = 0.0;

    /* DotProduct: '<S155>/Dot Product' */
    rtDW.d60 = 0.0;

    /* DotProduct: '<S156>/Dot Product' */
    rtDW.d61 = 0.0;

    /* DotProduct: '<S157>/Dot Product' */
    rtDW.d62 = 0.0;

    /* DotProduct: '<S158>/Dot Product' */
    rtDW.d63 = 0.0;

    /* DotProduct: '<S159>/Dot Product' */
    rtDW.d64 = 0.0;

    /* DotProduct: '<S160>/Dot Product' */
    rtDW.d65 = 0.0;

    /* DotProduct: '<S161>/Dot Product' */
    rtDW.d66 = 0.0;

    /* DotProduct: '<S162>/Dot Product' */
    rtDW.d67 = 0.0;

    /* DotProduct: '<S163>/Dot Product' */
    rtDW.d68 = 0.0;

    /* DotProduct: '<S164>/Dot Product' */
    rtDW.d69 = 0.0;

    /* DotProduct: '<S166>/Dot Product' */
    rtDW.d70 = 0.0;

    /* DotProduct: '<S167>/Dot Product' */
    rtDW.d71 = 0.0;

    /* DotProduct: '<S168>/Dot Product' */
    rtDW.d72 = 0.0;

    /* DotProduct: '<S169>/Dot Product' */
    rtDW.d73 = 0.0;

    /* DotProduct: '<S170>/Dot Product' */
    rtDW.d74 = 0.0;

    /* DotProduct: '<S171>/Dot Product' */
    rtDW.d75 = 0.0;

    /* DotProduct: '<S172>/Dot Product' */
    rtDW.d76 = 0.0;

    /* DotProduct: '<S173>/Dot Product' */
    rtDW.d77 = 0.0;

    /* DotProduct: '<S174>/Dot Product' */
    rtDW.d78 = 0.0;

    /* DotProduct: '<S175>/Dot Product' */
    rtDW.d79 = 0.0;

    /* DotProduct: '<S177>/Dot Product' */
    rtDW.d80 = 0.0;

    /* DotProduct: '<S178>/Dot Product' */
    rtDW.d81 = 0.0;

    /* DotProduct: '<S179>/Dot Product' */
    rtDW.d82 = 0.0;

    /* DotProduct: '<S180>/Dot Product' */
    rtDW.d83 = 0.0;

    /* DotProduct: '<S181>/Dot Product' */
    rtDW.d84 = 0.0;

    /* DotProduct: '<S182>/Dot Product' */
    rtDW.d85 = 0.0;

    /* DotProduct: '<S183>/Dot Product' */
    rtDW.d86 = 0.0;

    /* DotProduct: '<S184>/Dot Product' */
    rtDW.d87 = 0.0;

    /* DotProduct: '<S185>/Dot Product' */
    rtDW.d88 = 0.0;

    /* DotProduct: '<S186>/Dot Product' */
    rtDW.d89 = 0.0;

    /* DotProduct: '<S23>/Dot Product' */
    rtDW.d90 = 0.0;

    /* DotProduct: '<S24>/Dot Product' */
    rtDW.d91 = 0.0;

    /* DotProduct: '<S25>/Dot Product' */
    rtDW.d92 = 0.0;

    /* DotProduct: '<S26>/Dot Product' */
    rtDW.d93 = 0.0;

    /* DotProduct: '<S27>/Dot Product' */
    rtDW.d94 = 0.0;

    /* DotProduct: '<S28>/Dot Product' */
    rtDW.d95 = 0.0;

    /* DotProduct: '<S29>/Dot Product' */
    rtDW.d96 = 0.0;

    /* DotProduct: '<S30>/Dot Product' */
    rtDW.d97 = 0.0;

    /* DotProduct: '<S31>/Dot Product' */
    rtDW.d98 = 0.0;

    /* DotProduct: '<S32>/Dot Product' */
    rtDW.d99 = 0.0;

    /* DotProduct: '<S34>/Dot Product' */
    rtDW.d100 = 0.0;

    /* DotProduct: '<S35>/Dot Product' */
    rtDW.d101 = 0.0;

    /* DotProduct: '<S36>/Dot Product' */
    rtDW.d102 = 0.0;

    /* DotProduct: '<S37>/Dot Product' */
    rtDW.d103 = 0.0;

    /* DotProduct: '<S38>/Dot Product' */
    rtDW.d104 = 0.0;

    /* DotProduct: '<S39>/Dot Product' */
    rtDW.d105 = 0.0;

    /* DotProduct: '<S40>/Dot Product' */
    rtDW.d106 = 0.0;

    /* DotProduct: '<S41>/Dot Product' */
    rtDW.d107 = 0.0;

    /* DotProduct: '<S42>/Dot Product' */
    rtDW.d108 = 0.0;

    /* DotProduct: '<S43>/Dot Product' */
    rtDW.d109 = 0.0;

    /* DotProduct: '<S45>/Dot Product' */
    rtDW.d110 = 0.0;

    /* DotProduct: '<S46>/Dot Product' */
    rtDW.d111 = 0.0;

    /* DotProduct: '<S47>/Dot Product' */
    rtDW.d112 = 0.0;

    /* DotProduct: '<S48>/Dot Product' */
    rtDW.d113 = 0.0;

    /* DotProduct: '<S49>/Dot Product' */
    rtDW.d114 = 0.0;

    /* DotProduct: '<S50>/Dot Product' */
    rtDW.d115 = 0.0;

    /* DotProduct: '<S51>/Dot Product' */
    rtDW.d116 = 0.0;

    /* DotProduct: '<S52>/Dot Product' */
    rtDW.d117 = 0.0;

    /* DotProduct: '<S53>/Dot Product' */
    rtDW.d118 = 0.0;

    /* DotProduct: '<S54>/Dot Product' */
    rtDW.d119 = 0.0;

    /* DotProduct: '<S56>/Dot Product' */
    rtDW.d120 = 0.0;

    /* DotProduct: '<S57>/Dot Product' */
    rtDW.d121 = 0.0;

    /* DotProduct: '<S58>/Dot Product' */
    rtDW.d122 = 0.0;

    /* DotProduct: '<S59>/Dot Product' */
    rtDW.d123 = 0.0;

    /* DotProduct: '<S60>/Dot Product' */
    rtDW.d124 = 0.0;

    /* DotProduct: '<S61>/Dot Product' */
    rtDW.d125 = 0.0;

    /* DotProduct: '<S62>/Dot Product' */
    rtDW.d126 = 0.0;

    /* DotProduct: '<S63>/Dot Product' */
    rtDW.d127 = 0.0;

    /* DotProduct: '<S64>/Dot Product' */
    rtDW.d128 = 0.0;

    /* DotProduct: '<S65>/Dot Product' */
    rtDW.d129 = 0.0;

    /* DotProduct: '<S67>/Dot Product' */
    rtDW.d130 = 0.0;

    /* DotProduct: '<S68>/Dot Product' */
    rtDW.d131 = 0.0;

    /* DotProduct: '<S69>/Dot Product' */
    rtDW.d132 = 0.0;

    /* DotProduct: '<S70>/Dot Product' */
    rtDW.d133 = 0.0;

    /* DotProduct: '<S71>/Dot Product' */
    rtDW.d134 = 0.0;

    /* DotProduct: '<S72>/Dot Product' */
    rtDW.d135 = 0.0;

    /* DotProduct: '<S73>/Dot Product' */
    rtDW.d136 = 0.0;

    /* DotProduct: '<S74>/Dot Product' */
    rtDW.d137 = 0.0;

    /* DotProduct: '<S75>/Dot Product' */
    rtDW.d138 = 0.0;

    /* DotProduct: '<S76>/Dot Product' */
    rtDW.d139 = 0.0;

    /* DotProduct: '<S78>/Dot Product' */
    rtDW.d140 = 0.0;

    /* DotProduct: '<S79>/Dot Product' */
    rtDW.d141 = 0.0;

    /* DotProduct: '<S80>/Dot Product' */
    rtDW.d142 = 0.0;

    /* DotProduct: '<S81>/Dot Product' */
    rtDW.d143 = 0.0;

    /* DotProduct: '<S82>/Dot Product' */
    rtDW.d144 = 0.0;

    /* DotProduct: '<S83>/Dot Product' */
    rtDW.d145 = 0.0;

    /* DotProduct: '<S84>/Dot Product' */
    rtDW.d146 = 0.0;

    /* DotProduct: '<S85>/Dot Product' */
    rtDW.d147 = 0.0;

    /* DotProduct: '<S86>/Dot Product' */
    rtDW.d148 = 0.0;

    /* DotProduct: '<S87>/Dot Product' */
    rtDW.d149 = 0.0;

    /* DotProduct: '<S89>/Dot Product' */
    rtDW.d150 = 0.0;

    /* DotProduct: '<S90>/Dot Product' */
    rtDW.d151 = 0.0;

    /* DotProduct: '<S91>/Dot Product' */
    rtDW.d152 = 0.0;

    /* DotProduct: '<S92>/Dot Product' */
    rtDW.d153 = 0.0;

    /* DotProduct: '<S93>/Dot Product' */
    rtDW.d154 = 0.0;

    /* DotProduct: '<S94>/Dot Product' */
    rtDW.d155 = 0.0;

    /* DotProduct: '<S95>/Dot Product' */
    rtDW.d156 = 0.0;
    for (rtDW.k = 0; rtDW.k < 100; rtDW.k++) {
      /* Bias: '<S252>/Add min y' incorporates:
       *  Bias: '<S252>/Subtract min x'
       *  Gain: '<S252>/range y // range x'
       */
      rtDW.rtb_netsum_tmp = (rtDW.RateTransition1[rtDW.k] +
        rtConstP.Subtractminx_Bias[rtDW.k]) * rtConstP.rangeyrangex_Gain[rtDW.k]
        + -1.0;

      /* DotProduct: '<S21>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(1,:)''
       */
      rtDW.denAccum += rtConstP.IW111_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S99>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(2,:)''
       */
      rtDW.A_idx_0 += rtConstP.IW112_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S110>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(3,:)''
       */
      rtDW.A_idx_2 += rtConstP.IW113_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S121>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(4,:)''
       */
      rtDW.A_idx_1 += rtConstP.IW114_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S132>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(5,:)''
       */
      rtDW.A_idx_3 += rtConstP.IW115_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S143>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(6,:)''
       */
      rtDW.B_idx_1 += rtConstP.IW116_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S154>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(7,:)''
       */
      rtDW.R += rtConstP.IW117_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S165>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(8,:)''
       */
      rtDW.A_tmp += rtConstP.IW118_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S176>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(9,:)''
       */
      rtDW.d0 += rtConstP.IW119_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S22>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(10,:)''
       */
      rtDW.d1 += rtConstP.IW1110_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S33>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(11,:)''
       */
      rtDW.d2 += rtConstP.IW1111_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S44>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(12,:)''
       */
      rtDW.d3 += rtConstP.IW1112_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S55>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(13,:)''
       */
      rtDW.d4 += rtConstP.IW1113_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S66>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(14,:)''
       */
      rtDW.d5 += rtConstP.IW1114_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S77>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(15,:)''
       */
      rtDW.d6 += rtConstP.IW1115_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S88>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(16,:)''
       */
      rtDW.d7 += rtConstP.IW1116_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S96>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(17,:)''
       */
      rtDW.d8 += rtConstP.IW1117_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S97>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(18,:)''
       */
      rtDW.d9 += rtConstP.IW1118_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S98>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(19,:)''
       */
      rtDW.d10 += rtConstP.IW1119_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S100>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(20,:)''
       */
      rtDW.d11 += rtConstP.IW1120_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S101>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(21,:)''
       */
      rtDW.d12 += rtConstP.IW1121_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S102>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(22,:)''
       */
      rtDW.d13 += rtConstP.IW1122_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S103>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(23,:)''
       */
      rtDW.d14 += rtConstP.IW1123_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S104>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(24,:)''
       */
      rtDW.d15 += rtConstP.IW1124_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S105>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(25,:)''
       */
      rtDW.d16 += rtConstP.IW1125_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S106>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(26,:)''
       */
      rtDW.d17 += rtConstP.IW1126_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S107>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(27,:)''
       */
      rtDW.d18 += rtConstP.IW1127_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S108>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(28,:)''
       */
      rtDW.d19 += rtConstP.IW1128_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S109>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(29,:)''
       */
      rtDW.d20 += rtConstP.IW1129_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S111>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(30,:)''
       */
      rtDW.d21 += rtConstP.IW1130_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S112>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(31,:)''
       */
      rtDW.d22 += rtConstP.IW1131_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S113>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(32,:)''
       */
      rtDW.d23 += rtConstP.IW1132_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S114>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(33,:)''
       */
      rtDW.d24 += rtConstP.IW1133_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S115>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(34,:)''
       */
      rtDW.d25 += rtConstP.IW1134_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S116>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(35,:)''
       */
      rtDW.d26 += rtConstP.IW1135_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S117>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(36,:)''
       */
      rtDW.d27 += rtConstP.IW1136_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S118>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(37,:)''
       */
      rtDW.d28 += rtConstP.IW1137_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S119>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(38,:)''
       */
      rtDW.d29 += rtConstP.IW1138_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S120>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(39,:)''
       */
      rtDW.d30 += rtConstP.IW1139_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S122>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(40,:)''
       */
      rtDW.d31 += rtConstP.IW1140_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S123>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(41,:)''
       */
      rtDW.d32 += rtConstP.IW1141_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S124>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(42,:)''
       */
      rtDW.d33 += rtConstP.IW1142_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S125>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(43,:)''
       */
      rtDW.d34 += rtConstP.IW1143_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S126>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(44,:)''
       */
      rtDW.d35 += rtConstP.IW1144_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S127>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(45,:)''
       */
      rtDW.d36 += rtConstP.IW1145_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S128>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(46,:)''
       */
      rtDW.d37 += rtConstP.IW1146_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S129>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(47,:)''
       */
      rtDW.d38 += rtConstP.IW1147_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S130>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(48,:)''
       */
      rtDW.d39 += rtConstP.IW1148_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S131>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(49,:)''
       */
      rtDW.d40 += rtConstP.IW1149_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S133>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(50,:)''
       */
      rtDW.d41 += rtConstP.IW1150_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S134>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(51,:)''
       */
      rtDW.d42 += rtConstP.IW1151_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S135>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(52,:)''
       */
      rtDW.d43 += rtConstP.IW1152_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S136>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(53,:)''
       */
      rtDW.d44 += rtConstP.IW1153_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S137>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(54,:)''
       */
      rtDW.d45 += rtConstP.IW1154_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S138>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(55,:)''
       */
      rtDW.rtb_netsum_k += rtConstP.IW1155_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S139>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(56,:)''
       */
      rtDW.d46 += rtConstP.IW1156_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S140>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(57,:)''
       */
      rtDW.d47 += rtConstP.IW1157_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S141>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(58,:)''
       */
      rtDW.d48 += rtConstP.IW1158_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S142>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(59,:)''
       */
      rtDW.d49 += rtConstP.IW1159_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S144>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(60,:)''
       */
      rtDW.d50 += rtConstP.IW1160_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S145>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(61,:)''
       */
      rtDW.d51 += rtConstP.IW1161_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S146>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(62,:)''
       */
      rtDW.d52 += rtConstP.IW1162_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S147>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(63,:)''
       */
      rtDW.d53 += rtConstP.IW1163_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S148>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(64,:)''
       */
      rtDW.d54 += rtConstP.IW1164_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S149>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(65,:)''
       */
      rtDW.d55 += rtConstP.IW1165_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S150>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(66,:)''
       */
      rtDW.d56 += rtConstP.IW1166_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S151>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(67,:)''
       */
      rtDW.d57 += rtConstP.IW1167_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S152>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(68,:)''
       */
      rtDW.d58 += rtConstP.IW1168_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S153>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(69,:)''
       */
      rtDW.d59 += rtConstP.IW1169_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S155>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(70,:)''
       */
      rtDW.d60 += rtConstP.IW1170_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S156>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(71,:)''
       */
      rtDW.d61 += rtConstP.IW1171_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S157>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(72,:)''
       */
      rtDW.d62 += rtConstP.IW1172_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S158>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(73,:)''
       */
      rtDW.d63 += rtConstP.IW1173_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S159>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(74,:)''
       */
      rtDW.d64 += rtConstP.IW1174_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S160>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(75,:)''
       */
      rtDW.d65 += rtConstP.IW1175_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S161>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(76,:)''
       */
      rtDW.d66 += rtConstP.IW1176_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S162>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(77,:)''
       */
      rtDW.d67 += rtConstP.IW1177_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S163>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(78,:)''
       */
      rtDW.d68 += rtConstP.IW1178_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S164>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(79,:)''
       */
      rtDW.d69 += rtConstP.IW1179_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S166>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(80,:)''
       */
      rtDW.d70 += rtConstP.IW1180_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S167>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(81,:)''
       */
      rtDW.d71 += rtConstP.IW1181_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S168>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(82,:)''
       */
      rtDW.d72 += rtConstP.IW1182_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S169>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(83,:)''
       */
      rtDW.d73 += rtConstP.IW1183_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S170>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(84,:)''
       */
      rtDW.d74 += rtConstP.IW1184_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S171>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(85,:)''
       */
      rtDW.d75 += rtConstP.IW1185_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S172>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(86,:)''
       */
      rtDW.d76 += rtConstP.IW1186_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S173>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(87,:)''
       */
      rtDW.d77 += rtConstP.IW1187_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S174>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(88,:)''
       */
      rtDW.d78 += rtConstP.IW1188_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S175>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(89,:)''
       */
      rtDW.d79 += rtConstP.IW1189_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S177>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(90,:)''
       */
      rtDW.d80 += rtConstP.IW1190_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S178>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(91,:)''
       */
      rtDW.d81 += rtConstP.IW1191_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S179>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(92,:)''
       */
      rtDW.d82 += rtConstP.IW1192_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S180>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(93,:)''
       */
      rtDW.d83 += rtConstP.IW1193_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S181>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(94,:)''
       */
      rtDW.d84 += rtConstP.IW1194_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S182>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(95,:)''
       */
      rtDW.d85 += rtConstP.IW1195_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S183>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(96,:)''
       */
      rtDW.d86 += rtConstP.IW1196_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S184>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(97,:)''
       */
      rtDW.d87 += rtConstP.IW1197_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S185>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(98,:)''
       */
      rtDW.d88 += rtConstP.IW1198_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S186>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(99,:)''
       */
      rtDW.d89 += rtConstP.IW1199_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S23>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(100,:)''
       */
      rtDW.d90 += rtConstP.IW11100_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S24>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(101,:)''
       */
      rtDW.d91 += rtConstP.IW11101_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S25>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(102,:)''
       */
      rtDW.d92 += rtConstP.IW11102_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S26>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(103,:)''
       */
      rtDW.d93 += rtConstP.IW11103_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S27>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(104,:)''
       */
      rtDW.d94 += rtConstP.IW11104_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S28>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(105,:)''
       */
      rtDW.d95 += rtConstP.IW11105_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S29>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(106,:)''
       */
      rtDW.d96 += rtConstP.IW11106_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S30>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(107,:)''
       */
      rtDW.d97 += rtConstP.IW11107_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S31>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(108,:)''
       */
      rtDW.d98 += rtConstP.IW11108_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S32>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(109,:)''
       */
      rtDW.d99 += rtConstP.IW11109_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S34>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(110,:)''
       */
      rtDW.d100 += rtConstP.IW11110_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S35>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(111,:)''
       */
      rtDW.d101 += rtConstP.IW11111_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S36>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(112,:)''
       */
      rtDW.d102 += rtConstP.IW11112_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S37>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(113,:)''
       */
      rtDW.d103 += rtConstP.IW11113_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S38>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(114,:)''
       */
      rtDW.d104 += rtConstP.IW11114_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S39>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(115,:)''
       */
      rtDW.d105 += rtConstP.IW11115_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S40>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(116,:)''
       */
      rtDW.d106 += rtConstP.IW11116_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S41>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(117,:)''
       */
      rtDW.d107 += rtConstP.IW11117_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S42>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(118,:)''
       */
      rtDW.d108 += rtConstP.IW11118_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S43>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(119,:)''
       */
      rtDW.d109 += rtConstP.IW11119_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S45>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(120,:)''
       */
      rtDW.d110 += rtConstP.IW11120_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S46>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(121,:)''
       */
      rtDW.d111 += rtConstP.IW11121_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S47>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(122,:)''
       */
      rtDW.d112 += rtConstP.IW11122_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S48>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(123,:)''
       */
      rtDW.d113 += rtConstP.IW11123_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S49>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(124,:)''
       */
      rtDW.d114 += rtConstP.IW11124_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S50>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(125,:)''
       */
      rtDW.d115 += rtConstP.IW11125_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S51>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(126,:)''
       */
      rtDW.d116 += rtConstP.IW11126_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S52>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(127,:)''
       */
      rtDW.d117 += rtConstP.IW11127_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S53>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(128,:)''
       */
      rtDW.d118 += rtConstP.IW11128_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S54>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(129,:)''
       */
      rtDW.d119 += rtConstP.IW11129_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S56>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(130,:)''
       */
      rtDW.d120 += rtConstP.IW11130_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S57>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(131,:)''
       */
      rtDW.d121 += rtConstP.IW11131_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S58>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(132,:)''
       */
      rtDW.d122 += rtConstP.IW11132_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S59>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(133,:)''
       */
      rtDW.d123 += rtConstP.IW11133_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S60>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(134,:)''
       */
      rtDW.d124 += rtConstP.IW11134_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S61>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(135,:)''
       */
      rtDW.d125 += rtConstP.IW11135_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S62>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(136,:)''
       */
      rtDW.d126 += rtConstP.IW11136_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S63>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(137,:)''
       */
      rtDW.d127 += rtConstP.IW11137_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S64>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(138,:)''
       */
      rtDW.d128 += rtConstP.IW11138_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S65>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(139,:)''
       */
      rtDW.d129 += rtConstP.IW11139_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S67>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(140,:)''
       */
      rtDW.d130 += rtConstP.IW11140_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S68>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(141,:)''
       */
      rtDW.d131 += rtConstP.IW11141_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S69>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(142,:)''
       */
      rtDW.d132 += rtConstP.IW11142_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S70>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(143,:)''
       */
      rtDW.d133 += rtConstP.IW11143_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S71>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(144,:)''
       */
      rtDW.d134 += rtConstP.IW11144_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S72>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(145,:)''
       */
      rtDW.d135 += rtConstP.IW11145_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S73>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(146,:)''
       */
      rtDW.d136 += rtConstP.IW11146_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S74>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(147,:)''
       */
      rtDW.d137 += rtConstP.IW11147_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S75>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(148,:)''
       */
      rtDW.d138 += rtConstP.IW11148_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S76>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(149,:)''
       */
      rtDW.d139 += rtConstP.IW11149_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S78>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(150,:)''
       */
      rtDW.d140 += rtConstP.IW11150_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S79>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(151,:)''
       */
      rtDW.d141 += rtConstP.IW11151_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S80>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(152,:)''
       */
      rtDW.d142 += rtConstP.IW11152_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S81>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(153,:)''
       */
      rtDW.d143 += rtConstP.IW11153_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S82>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(154,:)''
       */
      rtDW.d144 += rtConstP.IW11154_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S83>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(155,:)''
       */
      rtDW.d145 += rtConstP.IW11155_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S84>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(156,:)''
       */
      rtDW.d146 += rtConstP.IW11156_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S85>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(157,:)''
       */
      rtDW.d147 += rtConstP.IW11157_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S86>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(158,:)''
       */
      rtDW.d148 += rtConstP.IW11158_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S87>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(159,:)''
       */
      rtDW.d149 += rtConstP.IW11159_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S89>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(160,:)''
       */
      rtDW.d150 += rtConstP.IW11160_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S90>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(161,:)''
       */
      rtDW.d151 += rtConstP.IW11161_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S91>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(162,:)''
       */
      rtDW.d152 += rtConstP.IW11162_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S92>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(163,:)''
       */
      rtDW.d153 += rtConstP.IW11163_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S93>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(164,:)''
       */
      rtDW.d154 += rtConstP.IW11164_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S94>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(165,:)''
       */
      rtDW.d155 += rtConstP.IW11165_Value[rtDW.k] * rtDW.rtb_netsum_tmp;

      /* DotProduct: '<S95>/Dot Product' incorporates:
       *  Constant: '<S19>/IW{1,1}(166,:)''
       */
      rtDW.d156 += rtConstP.IW11166_Value[rtDW.k] * rtDW.rtb_netsum_tmp;
    }

    /* Sum: '<S13>/netsum' incorporates:
     *  DotProduct: '<S100>/Dot Product'
     *  DotProduct: '<S101>/Dot Product'
     *  DotProduct: '<S102>/Dot Product'
     *  DotProduct: '<S103>/Dot Product'
     *  DotProduct: '<S104>/Dot Product'
     *  DotProduct: '<S105>/Dot Product'
     *  DotProduct: '<S106>/Dot Product'
     *  DotProduct: '<S107>/Dot Product'
     *  DotProduct: '<S108>/Dot Product'
     *  DotProduct: '<S109>/Dot Product'
     *  DotProduct: '<S110>/Dot Product'
     *  DotProduct: '<S111>/Dot Product'
     *  DotProduct: '<S112>/Dot Product'
     *  DotProduct: '<S113>/Dot Product'
     *  DotProduct: '<S114>/Dot Product'
     *  DotProduct: '<S115>/Dot Product'
     *  DotProduct: '<S116>/Dot Product'
     *  DotProduct: '<S117>/Dot Product'
     *  DotProduct: '<S118>/Dot Product'
     *  DotProduct: '<S119>/Dot Product'
     *  DotProduct: '<S120>/Dot Product'
     *  DotProduct: '<S121>/Dot Product'
     *  DotProduct: '<S122>/Dot Product'
     *  DotProduct: '<S123>/Dot Product'
     *  DotProduct: '<S124>/Dot Product'
     *  DotProduct: '<S125>/Dot Product'
     *  DotProduct: '<S126>/Dot Product'
     *  DotProduct: '<S127>/Dot Product'
     *  DotProduct: '<S128>/Dot Product'
     *  DotProduct: '<S129>/Dot Product'
     *  DotProduct: '<S130>/Dot Product'
     *  DotProduct: '<S131>/Dot Product'
     *  DotProduct: '<S132>/Dot Product'
     *  DotProduct: '<S133>/Dot Product'
     *  DotProduct: '<S134>/Dot Product'
     *  DotProduct: '<S135>/Dot Product'
     *  DotProduct: '<S136>/Dot Product'
     *  DotProduct: '<S137>/Dot Product'
     *  DotProduct: '<S138>/Dot Product'
     *  DotProduct: '<S139>/Dot Product'
     *  DotProduct: '<S140>/Dot Product'
     *  DotProduct: '<S141>/Dot Product'
     *  DotProduct: '<S142>/Dot Product'
     *  DotProduct: '<S143>/Dot Product'
     *  DotProduct: '<S144>/Dot Product'
     *  DotProduct: '<S145>/Dot Product'
     *  DotProduct: '<S146>/Dot Product'
     *  DotProduct: '<S147>/Dot Product'
     *  DotProduct: '<S148>/Dot Product'
     *  DotProduct: '<S149>/Dot Product'
     *  DotProduct: '<S150>/Dot Product'
     *  DotProduct: '<S151>/Dot Product'
     *  DotProduct: '<S152>/Dot Product'
     *  DotProduct: '<S153>/Dot Product'
     *  DotProduct: '<S154>/Dot Product'
     *  DotProduct: '<S155>/Dot Product'
     *  DotProduct: '<S156>/Dot Product'
     *  DotProduct: '<S157>/Dot Product'
     *  DotProduct: '<S158>/Dot Product'
     *  DotProduct: '<S159>/Dot Product'
     *  DotProduct: '<S160>/Dot Product'
     *  DotProduct: '<S161>/Dot Product'
     *  DotProduct: '<S162>/Dot Product'
     *  DotProduct: '<S163>/Dot Product'
     *  DotProduct: '<S164>/Dot Product'
     *  DotProduct: '<S165>/Dot Product'
     *  DotProduct: '<S166>/Dot Product'
     *  DotProduct: '<S167>/Dot Product'
     *  DotProduct: '<S168>/Dot Product'
     *  DotProduct: '<S169>/Dot Product'
     *  DotProduct: '<S170>/Dot Product'
     *  DotProduct: '<S171>/Dot Product'
     *  DotProduct: '<S172>/Dot Product'
     *  DotProduct: '<S173>/Dot Product'
     *  DotProduct: '<S174>/Dot Product'
     *  DotProduct: '<S175>/Dot Product'
     *  DotProduct: '<S176>/Dot Product'
     *  DotProduct: '<S177>/Dot Product'
     *  DotProduct: '<S178>/Dot Product'
     *  DotProduct: '<S179>/Dot Product'
     *  DotProduct: '<S180>/Dot Product'
     *  DotProduct: '<S181>/Dot Product'
     *  DotProduct: '<S182>/Dot Product'
     *  DotProduct: '<S183>/Dot Product'
     *  DotProduct: '<S184>/Dot Product'
     *  DotProduct: '<S185>/Dot Product'
     *  DotProduct: '<S186>/Dot Product'
     *  DotProduct: '<S21>/Dot Product'
     *  DotProduct: '<S22>/Dot Product'
     *  DotProduct: '<S23>/Dot Product'
     *  DotProduct: '<S24>/Dot Product'
     *  DotProduct: '<S25>/Dot Product'
     *  DotProduct: '<S26>/Dot Product'
     *  DotProduct: '<S27>/Dot Product'
     *  DotProduct: '<S28>/Dot Product'
     *  DotProduct: '<S29>/Dot Product'
     *  DotProduct: '<S30>/Dot Product'
     *  DotProduct: '<S31>/Dot Product'
     *  DotProduct: '<S32>/Dot Product'
     *  DotProduct: '<S33>/Dot Product'
     *  DotProduct: '<S34>/Dot Product'
     *  DotProduct: '<S35>/Dot Product'
     *  DotProduct: '<S36>/Dot Product'
     *  DotProduct: '<S37>/Dot Product'
     *  DotProduct: '<S38>/Dot Product'
     *  DotProduct: '<S39>/Dot Product'
     *  DotProduct: '<S40>/Dot Product'
     *  DotProduct: '<S41>/Dot Product'
     *  DotProduct: '<S42>/Dot Product'
     *  DotProduct: '<S43>/Dot Product'
     *  DotProduct: '<S44>/Dot Product'
     *  DotProduct: '<S45>/Dot Product'
     *  DotProduct: '<S46>/Dot Product'
     *  DotProduct: '<S47>/Dot Product'
     *  DotProduct: '<S48>/Dot Product'
     *  DotProduct: '<S49>/Dot Product'
     *  DotProduct: '<S50>/Dot Product'
     *  DotProduct: '<S51>/Dot Product'
     *  DotProduct: '<S52>/Dot Product'
     *  DotProduct: '<S53>/Dot Product'
     *  DotProduct: '<S54>/Dot Product'
     *  DotProduct: '<S55>/Dot Product'
     *  DotProduct: '<S56>/Dot Product'
     *  DotProduct: '<S57>/Dot Product'
     *  DotProduct: '<S58>/Dot Product'
     *  DotProduct: '<S59>/Dot Product'
     *  DotProduct: '<S60>/Dot Product'
     *  DotProduct: '<S61>/Dot Product'
     *  DotProduct: '<S62>/Dot Product'
     *  DotProduct: '<S63>/Dot Product'
     *  DotProduct: '<S64>/Dot Product'
     *  DotProduct: '<S65>/Dot Product'
     *  DotProduct: '<S66>/Dot Product'
     *  DotProduct: '<S67>/Dot Product'
     *  DotProduct: '<S68>/Dot Product'
     *  DotProduct: '<S69>/Dot Product'
     *  DotProduct: '<S70>/Dot Product'
     *  DotProduct: '<S71>/Dot Product'
     *  DotProduct: '<S72>/Dot Product'
     *  DotProduct: '<S73>/Dot Product'
     *  DotProduct: '<S74>/Dot Product'
     *  DotProduct: '<S75>/Dot Product'
     *  DotProduct: '<S76>/Dot Product'
     *  DotProduct: '<S77>/Dot Product'
     *  DotProduct: '<S78>/Dot Product'
     *  DotProduct: '<S79>/Dot Product'
     *  DotProduct: '<S80>/Dot Product'
     *  DotProduct: '<S81>/Dot Product'
     *  DotProduct: '<S82>/Dot Product'
     *  DotProduct: '<S83>/Dot Product'
     *  DotProduct: '<S84>/Dot Product'
     *  DotProduct: '<S85>/Dot Product'
     *  DotProduct: '<S86>/Dot Product'
     *  DotProduct: '<S87>/Dot Product'
     *  DotProduct: '<S88>/Dot Product'
     *  DotProduct: '<S89>/Dot Product'
     *  DotProduct: '<S90>/Dot Product'
     *  DotProduct: '<S91>/Dot Product'
     *  DotProduct: '<S92>/Dot Product'
     *  DotProduct: '<S93>/Dot Product'
     *  DotProduct: '<S94>/Dot Product'
     *  DotProduct: '<S95>/Dot Product'
     *  DotProduct: '<S96>/Dot Product'
     *  DotProduct: '<S97>/Dot Product'
     *  DotProduct: '<S98>/Dot Product'
     *  DotProduct: '<S99>/Dot Product'
     */
    rtDW.dv0[0] = rtDW.denAccum;
    rtDW.dv0[1] = rtDW.A_idx_0;
    rtDW.dv0[2] = rtDW.A_idx_2;
    rtDW.dv0[3] = rtDW.A_idx_1;
    rtDW.dv0[4] = rtDW.A_idx_3;
    rtDW.dv0[5] = rtDW.B_idx_1;
    rtDW.dv0[6] = rtDW.R;
    rtDW.dv0[7] = rtDW.A_tmp;
    rtDW.dv0[8] = rtDW.d0;
    rtDW.dv0[9] = rtDW.d1;
    rtDW.dv0[10] = rtDW.d2;
    rtDW.dv0[11] = rtDW.d3;
    rtDW.dv0[12] = rtDW.d4;
    rtDW.dv0[13] = rtDW.d5;
    rtDW.dv0[14] = rtDW.d6;
    rtDW.dv0[15] = rtDW.d7;
    rtDW.dv0[16] = rtDW.d8;
    rtDW.dv0[17] = rtDW.d9;
    rtDW.dv0[18] = rtDW.d10;
    rtDW.dv0[19] = rtDW.d11;
    rtDW.dv0[20] = rtDW.d12;
    rtDW.dv0[21] = rtDW.d13;
    rtDW.dv0[22] = rtDW.d14;
    rtDW.dv0[23] = rtDW.d15;
    rtDW.dv0[24] = rtDW.d16;
    rtDW.dv0[25] = rtDW.d17;
    rtDW.dv0[26] = rtDW.d18;
    rtDW.dv0[27] = rtDW.d19;
    rtDW.dv0[28] = rtDW.d20;
    rtDW.dv0[29] = rtDW.d21;
    rtDW.dv0[30] = rtDW.d22;
    rtDW.dv0[31] = rtDW.d23;
    rtDW.dv0[32] = rtDW.d24;
    rtDW.dv0[33] = rtDW.d25;
    rtDW.dv0[34] = rtDW.d26;
    rtDW.dv0[35] = rtDW.d27;
    rtDW.dv0[36] = rtDW.d28;
    rtDW.dv0[37] = rtDW.d29;
    rtDW.dv0[38] = rtDW.d30;
    rtDW.dv0[39] = rtDW.d31;
    rtDW.dv0[40] = rtDW.d32;
    rtDW.dv0[41] = rtDW.d33;
    rtDW.dv0[42] = rtDW.d34;
    rtDW.dv0[43] = rtDW.d35;
    rtDW.dv0[44] = rtDW.d36;
    rtDW.dv0[45] = rtDW.d37;
    rtDW.dv0[46] = rtDW.d38;
    rtDW.dv0[47] = rtDW.d39;
    rtDW.dv0[48] = rtDW.d40;
    rtDW.dv0[49] = rtDW.d41;
    rtDW.dv0[50] = rtDW.d42;
    rtDW.dv0[51] = rtDW.d43;
    rtDW.dv0[52] = rtDW.d44;
    rtDW.dv0[53] = rtDW.d45;
    rtDW.dv0[54] = rtDW.rtb_netsum_k;
    rtDW.dv0[55] = rtDW.d46;
    rtDW.dv0[56] = rtDW.d47;
    rtDW.dv0[57] = rtDW.d48;
    rtDW.dv0[58] = rtDW.d49;
    rtDW.dv0[59] = rtDW.d50;
    rtDW.dv0[60] = rtDW.d51;
    rtDW.dv0[61] = rtDW.d52;
    rtDW.dv0[62] = rtDW.d53;
    rtDW.dv0[63] = rtDW.d54;
    rtDW.dv0[64] = rtDW.d55;
    rtDW.dv0[65] = rtDW.d56;
    rtDW.dv0[66] = rtDW.d57;
    rtDW.dv0[67] = rtDW.d58;
    rtDW.dv0[68] = rtDW.d59;
    rtDW.dv0[69] = rtDW.d60;
    rtDW.dv0[70] = rtDW.d61;
    rtDW.dv0[71] = rtDW.d62;
    rtDW.dv0[72] = rtDW.d63;
    rtDW.dv0[73] = rtDW.d64;
    rtDW.dv0[74] = rtDW.d65;
    rtDW.dv0[75] = rtDW.d66;
    rtDW.dv0[76] = rtDW.d67;
    rtDW.dv0[77] = rtDW.d68;
    rtDW.dv0[78] = rtDW.d69;
    rtDW.dv0[79] = rtDW.d70;
    rtDW.dv0[80] = rtDW.d71;
    rtDW.dv0[81] = rtDW.d72;
    rtDW.dv0[82] = rtDW.d73;
    rtDW.dv0[83] = rtDW.d74;
    rtDW.dv0[84] = rtDW.d75;
    rtDW.dv0[85] = rtDW.d76;
    rtDW.dv0[86] = rtDW.d77;
    rtDW.dv0[87] = rtDW.d78;
    rtDW.dv0[88] = rtDW.d79;
    rtDW.dv0[89] = rtDW.d80;
    rtDW.dv0[90] = rtDW.d81;
    rtDW.dv0[91] = rtDW.d82;
    rtDW.dv0[92] = rtDW.d83;
    rtDW.dv0[93] = rtDW.d84;
    rtDW.dv0[94] = rtDW.d85;
    rtDW.dv0[95] = rtDW.d86;
    rtDW.dv0[96] = rtDW.d87;
    rtDW.dv0[97] = rtDW.d88;
    rtDW.dv0[98] = rtDW.d89;
    rtDW.dv0[99] = rtDW.d90;
    rtDW.dv0[100] = rtDW.d91;
    rtDW.dv0[101] = rtDW.d92;
    rtDW.dv0[102] = rtDW.d93;
    rtDW.dv0[103] = rtDW.d94;
    rtDW.dv0[104] = rtDW.d95;
    rtDW.dv0[105] = rtDW.d96;
    rtDW.dv0[106] = rtDW.d97;
    rtDW.dv0[107] = rtDW.d98;
    rtDW.dv0[108] = rtDW.d99;
    rtDW.dv0[109] = rtDW.d100;
    rtDW.dv0[110] = rtDW.d101;
    rtDW.dv0[111] = rtDW.d102;
    rtDW.dv0[112] = rtDW.d103;
    rtDW.dv0[113] = rtDW.d104;
    rtDW.dv0[114] = rtDW.d105;
    rtDW.dv0[115] = rtDW.d106;
    rtDW.dv0[116] = rtDW.d107;
    rtDW.dv0[117] = rtDW.d108;
    rtDW.dv0[118] = rtDW.d109;
    rtDW.dv0[119] = rtDW.d110;
    rtDW.dv0[120] = rtDW.d111;
    rtDW.dv0[121] = rtDW.d112;
    rtDW.dv0[122] = rtDW.d113;
    rtDW.dv0[123] = rtDW.d114;
    rtDW.dv0[124] = rtDW.d115;
    rtDW.dv0[125] = rtDW.d116;
    rtDW.dv0[126] = rtDW.d117;
    rtDW.dv0[127] = rtDW.d118;
    rtDW.dv0[128] = rtDW.d119;
    rtDW.dv0[129] = rtDW.d120;
    rtDW.dv0[130] = rtDW.d121;
    rtDW.dv0[131] = rtDW.d122;
    rtDW.dv0[132] = rtDW.d123;
    rtDW.dv0[133] = rtDW.d124;
    rtDW.dv0[134] = rtDW.d125;
    rtDW.dv0[135] = rtDW.d126;
    rtDW.dv0[136] = rtDW.d127;
    rtDW.dv0[137] = rtDW.d128;
    rtDW.dv0[138] = rtDW.d129;
    rtDW.dv0[139] = rtDW.d130;
    rtDW.dv0[140] = rtDW.d131;
    rtDW.dv0[141] = rtDW.d132;
    rtDW.dv0[142] = rtDW.d133;
    rtDW.dv0[143] = rtDW.d134;
    rtDW.dv0[144] = rtDW.d135;
    rtDW.dv0[145] = rtDW.d136;
    rtDW.dv0[146] = rtDW.d137;
    rtDW.dv0[147] = rtDW.d138;
    rtDW.dv0[148] = rtDW.d139;
    rtDW.dv0[149] = rtDW.d140;
    rtDW.dv0[150] = rtDW.d141;
    rtDW.dv0[151] = rtDW.d142;
    rtDW.dv0[152] = rtDW.d143;
    rtDW.dv0[153] = rtDW.d144;
    rtDW.dv0[154] = rtDW.d145;
    rtDW.dv0[155] = rtDW.d146;
    rtDW.dv0[156] = rtDW.d147;
    rtDW.dv0[157] = rtDW.d148;
    rtDW.dv0[158] = rtDW.d149;
    rtDW.dv0[159] = rtDW.d150;
    rtDW.dv0[160] = rtDW.d151;
    rtDW.dv0[161] = rtDW.d152;
    rtDW.dv0[162] = rtDW.d153;
    rtDW.dv0[163] = rtDW.d154;
    rtDW.dv0[164] = rtDW.d155;
    rtDW.dv0[165] = rtDW.d156;

    /* DotProduct: '<S190>/Dot Product' */
    rtDW.denAccum = 0.0;

    /* DotProduct: '<S201>/Dot Product' */
    rtDW.A_idx_0 = 0.0;

    /* DotProduct: '<S212>/Dot Product' */
    rtDW.A_idx_2 = 0.0;

    /* DotProduct: '<S223>/Dot Product' */
    rtDW.A_idx_1 = 0.0;

    /* DotProduct: '<S234>/Dot Product' */
    rtDW.A_idx_3 = 0.0;

    /* DotProduct: '<S240>/Dot Product' */
    rtDW.B_idx_1 = 0.0;

    /* DotProduct: '<S241>/Dot Product' */
    rtDW.R = 0.0;

    /* DotProduct: '<S242>/Dot Product' */
    rtDW.A_tmp = 0.0;

    /* DotProduct: '<S243>/Dot Product' */
    rtDW.d0 = 0.0;

    /* DotProduct: '<S191>/Dot Product' */
    rtDW.d1 = 0.0;

    /* DotProduct: '<S192>/Dot Product' */
    rtDW.d2 = 0.0;

    /* DotProduct: '<S193>/Dot Product' */
    rtDW.d3 = 0.0;

    /* DotProduct: '<S194>/Dot Product' */
    rtDW.d4 = 0.0;

    /* DotProduct: '<S195>/Dot Product' */
    rtDW.d5 = 0.0;

    /* DotProduct: '<S196>/Dot Product' */
    rtDW.d6 = 0.0;

    /* DotProduct: '<S197>/Dot Product' */
    rtDW.d7 = 0.0;

    /* DotProduct: '<S198>/Dot Product' */
    rtDW.d8 = 0.0;

    /* DotProduct: '<S199>/Dot Product' */
    rtDW.d9 = 0.0;

    /* DotProduct: '<S200>/Dot Product' */
    rtDW.d10 = 0.0;

    /* DotProduct: '<S202>/Dot Product' */
    rtDW.d11 = 0.0;

    /* DotProduct: '<S203>/Dot Product' */
    rtDW.d12 = 0.0;

    /* DotProduct: '<S204>/Dot Product' */
    rtDW.d13 = 0.0;

    /* DotProduct: '<S205>/Dot Product' */
    rtDW.d14 = 0.0;

    /* DotProduct: '<S206>/Dot Product' */
    rtDW.d15 = 0.0;

    /* DotProduct: '<S207>/Dot Product' */
    rtDW.d16 = 0.0;

    /* DotProduct: '<S208>/Dot Product' */
    rtDW.d17 = 0.0;

    /* DotProduct: '<S209>/Dot Product' */
    rtDW.d18 = 0.0;

    /* DotProduct: '<S210>/Dot Product' */
    rtDW.d19 = 0.0;

    /* DotProduct: '<S211>/Dot Product' */
    rtDW.d20 = 0.0;

    /* DotProduct: '<S213>/Dot Product' */
    rtDW.d21 = 0.0;

    /* DotProduct: '<S214>/Dot Product' */
    rtDW.d22 = 0.0;

    /* DotProduct: '<S215>/Dot Product' */
    rtDW.d23 = 0.0;

    /* DotProduct: '<S216>/Dot Product' */
    rtDW.d24 = 0.0;

    /* DotProduct: '<S217>/Dot Product' */
    rtDW.d25 = 0.0;

    /* DotProduct: '<S218>/Dot Product' */
    rtDW.d26 = 0.0;

    /* DotProduct: '<S219>/Dot Product' */
    rtDW.d27 = 0.0;

    /* DotProduct: '<S220>/Dot Product' */
    rtDW.d28 = 0.0;

    /* DotProduct: '<S221>/Dot Product' */
    rtDW.d29 = 0.0;

    /* DotProduct: '<S222>/Dot Product' */
    rtDW.d30 = 0.0;

    /* DotProduct: '<S224>/Dot Product' */
    rtDW.d31 = 0.0;

    /* DotProduct: '<S225>/Dot Product' */
    rtDW.d32 = 0.0;

    /* DotProduct: '<S226>/Dot Product' */
    rtDW.d33 = 0.0;

    /* DotProduct: '<S227>/Dot Product' */
    rtDW.d34 = 0.0;

    /* DotProduct: '<S228>/Dot Product' */
    rtDW.d35 = 0.0;

    /* DotProduct: '<S229>/Dot Product' */
    rtDW.d36 = 0.0;

    /* DotProduct: '<S230>/Dot Product' */
    rtDW.d37 = 0.0;

    /* DotProduct: '<S231>/Dot Product' */
    rtDW.d38 = 0.0;

    /* DotProduct: '<S232>/Dot Product' */
    rtDW.d39 = 0.0;

    /* DotProduct: '<S233>/Dot Product' */
    rtDW.d40 = 0.0;

    /* DotProduct: '<S235>/Dot Product' */
    rtDW.d41 = 0.0;

    /* DotProduct: '<S236>/Dot Product' */
    rtDW.d42 = 0.0;

    /* DotProduct: '<S237>/Dot Product' */
    rtDW.d43 = 0.0;

    /* DotProduct: '<S238>/Dot Product' */
    rtDW.d44 = 0.0;

    /* DotProduct: '<S239>/Dot Product' */
    rtDW.d45 = 0.0;
    for (rtDW.k = 0; rtDW.k < 166; rtDW.k++) {
      /* Sum: '<S20>/Sum1' incorporates:
       *  Constant: '<S13>/b{1}'
       *  Constant: '<S20>/one'
       *  Constant: '<S20>/one1'
       *  Gain: '<S20>/Gain'
       *  Gain: '<S20>/Gain1'
       *  Math: '<S20>/Exp'
       *  Math: '<S20>/Reciprocal'
       *  Sum: '<S13>/netsum'
       *  Sum: '<S20>/Sum'
       *
       * About '<S20>/Exp':
       *  Operator: exp
       *
       * About '<S20>/Reciprocal':
       *  Operator: reciprocal
       */
      rtDW.rtb_netsum_k = 1.0 / (exp((rtDW.dv0[rtDW.k] +
        rtConstP.b1_Value[rtDW.k]) * -2.0) + 1.0) * 2.0 - 1.0;

      /* DotProduct: '<S190>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(1,:)''
       */
      rtDW.denAccum += rtConstP.IW211_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S201>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(2,:)''
       */
      rtDW.A_idx_0 += rtConstP.IW212_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S212>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(3,:)''
       */
      rtDW.A_idx_2 += rtConstP.IW213_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S223>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(4,:)''
       */
      rtDW.A_idx_1 += rtConstP.IW214_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S234>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(5,:)''
       */
      rtDW.A_idx_3 += rtConstP.IW215_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S240>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(6,:)''
       */
      rtDW.B_idx_1 += rtConstP.IW216_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S241>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(7,:)''
       */
      rtDW.R += rtConstP.IW217_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S242>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(8,:)''
       */
      rtDW.A_tmp += rtConstP.IW218_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S243>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(9,:)''
       */
      rtDW.d0 += rtConstP.IW219_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S191>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(10,:)''
       */
      rtDW.d1 += rtConstP.IW2110_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S192>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(11,:)''
       */
      rtDW.d2 += rtConstP.IW2111_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S193>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(12,:)''
       */
      rtDW.d3 += rtConstP.IW2112_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S194>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(13,:)''
       */
      rtDW.d4 += rtConstP.IW2113_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S195>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(14,:)''
       */
      rtDW.d5 += rtConstP.IW2114_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S196>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(15,:)''
       */
      rtDW.d6 += rtConstP.IW2115_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S197>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(16,:)''
       */
      rtDW.d7 += rtConstP.IW2116_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S198>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(17,:)''
       */
      rtDW.d8 += rtConstP.IW2117_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S199>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(18,:)''
       */
      rtDW.d9 += rtConstP.IW2118_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S200>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(19,:)''
       */
      rtDW.d10 += rtConstP.IW2119_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S202>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(20,:)''
       */
      rtDW.d11 += rtConstP.IW2120_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S203>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(21,:)''
       */
      rtDW.d12 += rtConstP.IW2121_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S204>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(22,:)''
       */
      rtDW.d13 += rtConstP.IW2122_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S205>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(23,:)''
       */
      rtDW.d14 += rtConstP.IW2123_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S206>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(24,:)''
       */
      rtDW.d15 += rtConstP.IW2124_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S207>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(25,:)''
       */
      rtDW.d16 += rtConstP.IW2125_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S208>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(26,:)''
       */
      rtDW.d17 += rtConstP.IW2126_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S209>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(27,:)''
       */
      rtDW.d18 += rtConstP.IW2127_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S210>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(28,:)''
       */
      rtDW.d19 += rtConstP.IW2128_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S211>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(29,:)''
       */
      rtDW.d20 += rtConstP.IW2129_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S213>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(30,:)''
       */
      rtDW.d21 += rtConstP.IW2130_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S214>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(31,:)''
       */
      rtDW.d22 += rtConstP.IW2131_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S215>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(32,:)''
       */
      rtDW.d23 += rtConstP.IW2132_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S216>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(33,:)''
       */
      rtDW.d24 += rtConstP.IW2133_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S217>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(34,:)''
       */
      rtDW.d25 += rtConstP.IW2134_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S218>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(35,:)''
       */
      rtDW.d26 += rtConstP.IW2135_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S219>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(36,:)''
       */
      rtDW.d27 += rtConstP.IW2136_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S220>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(37,:)''
       */
      rtDW.d28 += rtConstP.IW2137_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S221>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(38,:)''
       */
      rtDW.d29 += rtConstP.IW2138_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S222>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(39,:)''
       */
      rtDW.d30 += rtConstP.IW2139_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S224>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(40,:)''
       */
      rtDW.d31 += rtConstP.IW2140_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S225>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(41,:)''
       */
      rtDW.d32 += rtConstP.IW2141_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S226>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(42,:)''
       */
      rtDW.d33 += rtConstP.IW2142_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S227>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(43,:)''
       */
      rtDW.d34 += rtConstP.IW2143_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S228>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(44,:)''
       */
      rtDW.d35 += rtConstP.IW2144_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S229>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(45,:)''
       */
      rtDW.d36 += rtConstP.IW2145_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S230>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(46,:)''
       */
      rtDW.d37 += rtConstP.IW2146_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S231>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(47,:)''
       */
      rtDW.d38 += rtConstP.IW2147_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S232>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(48,:)''
       */
      rtDW.d39 += rtConstP.IW2148_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S233>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(49,:)''
       */
      rtDW.d40 += rtConstP.IW2149_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S235>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(50,:)''
       */
      rtDW.d41 += rtConstP.IW2150_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S236>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(51,:)''
       */
      rtDW.d42 += rtConstP.IW2151_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S237>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(52,:)''
       */
      rtDW.d43 += rtConstP.IW2152_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S238>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(53,:)''
       */
      rtDW.d44 += rtConstP.IW2153_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S239>/Dot Product' incorporates:
       *  Constant: '<S188>/IW{2,1}(54,:)''
       */
      rtDW.d45 += rtConstP.IW2154_Value[rtDW.k] * rtDW.rtb_netsum_k;
    }

    /* Sum: '<S14>/netsum' incorporates:
     *  DotProduct: '<S190>/Dot Product'
     *  DotProduct: '<S191>/Dot Product'
     *  DotProduct: '<S192>/Dot Product'
     *  DotProduct: '<S193>/Dot Product'
     *  DotProduct: '<S194>/Dot Product'
     *  DotProduct: '<S195>/Dot Product'
     *  DotProduct: '<S196>/Dot Product'
     *  DotProduct: '<S197>/Dot Product'
     *  DotProduct: '<S198>/Dot Product'
     *  DotProduct: '<S199>/Dot Product'
     *  DotProduct: '<S200>/Dot Product'
     *  DotProduct: '<S201>/Dot Product'
     *  DotProduct: '<S202>/Dot Product'
     *  DotProduct: '<S203>/Dot Product'
     *  DotProduct: '<S204>/Dot Product'
     *  DotProduct: '<S205>/Dot Product'
     *  DotProduct: '<S206>/Dot Product'
     *  DotProduct: '<S207>/Dot Product'
     *  DotProduct: '<S208>/Dot Product'
     *  DotProduct: '<S209>/Dot Product'
     *  DotProduct: '<S210>/Dot Product'
     *  DotProduct: '<S211>/Dot Product'
     *  DotProduct: '<S212>/Dot Product'
     *  DotProduct: '<S213>/Dot Product'
     *  DotProduct: '<S214>/Dot Product'
     *  DotProduct: '<S215>/Dot Product'
     *  DotProduct: '<S216>/Dot Product'
     *  DotProduct: '<S217>/Dot Product'
     *  DotProduct: '<S218>/Dot Product'
     *  DotProduct: '<S219>/Dot Product'
     *  DotProduct: '<S220>/Dot Product'
     *  DotProduct: '<S221>/Dot Product'
     *  DotProduct: '<S222>/Dot Product'
     *  DotProduct: '<S223>/Dot Product'
     *  DotProduct: '<S224>/Dot Product'
     *  DotProduct: '<S225>/Dot Product'
     *  DotProduct: '<S226>/Dot Product'
     *  DotProduct: '<S227>/Dot Product'
     *  DotProduct: '<S228>/Dot Product'
     *  DotProduct: '<S229>/Dot Product'
     *  DotProduct: '<S230>/Dot Product'
     *  DotProduct: '<S231>/Dot Product'
     *  DotProduct: '<S232>/Dot Product'
     *  DotProduct: '<S233>/Dot Product'
     *  DotProduct: '<S234>/Dot Product'
     *  DotProduct: '<S235>/Dot Product'
     *  DotProduct: '<S236>/Dot Product'
     *  DotProduct: '<S237>/Dot Product'
     *  DotProduct: '<S238>/Dot Product'
     *  DotProduct: '<S239>/Dot Product'
     *  DotProduct: '<S240>/Dot Product'
     *  DotProduct: '<S241>/Dot Product'
     *  DotProduct: '<S242>/Dot Product'
     *  DotProduct: '<S243>/Dot Product'
     */
    rtDW.dv1[0] = rtDW.denAccum;
    rtDW.dv1[1] = rtDW.A_idx_0;
    rtDW.dv1[2] = rtDW.A_idx_2;
    rtDW.dv1[3] = rtDW.A_idx_1;
    rtDW.dv1[4] = rtDW.A_idx_3;
    rtDW.dv1[5] = rtDW.B_idx_1;
    rtDW.dv1[6] = rtDW.R;
    rtDW.dv1[7] = rtDW.A_tmp;
    rtDW.dv1[8] = rtDW.d0;
    rtDW.dv1[9] = rtDW.d1;
    rtDW.dv1[10] = rtDW.d2;
    rtDW.dv1[11] = rtDW.d3;
    rtDW.dv1[12] = rtDW.d4;
    rtDW.dv1[13] = rtDW.d5;
    rtDW.dv1[14] = rtDW.d6;
    rtDW.dv1[15] = rtDW.d7;
    rtDW.dv1[16] = rtDW.d8;
    rtDW.dv1[17] = rtDW.d9;
    rtDW.dv1[18] = rtDW.d10;
    rtDW.dv1[19] = rtDW.d11;
    rtDW.dv1[20] = rtDW.d12;
    rtDW.dv1[21] = rtDW.d13;
    rtDW.dv1[22] = rtDW.d14;
    rtDW.dv1[23] = rtDW.d15;
    rtDW.dv1[24] = rtDW.d16;
    rtDW.dv1[25] = rtDW.d17;
    rtDW.dv1[26] = rtDW.d18;
    rtDW.dv1[27] = rtDW.d19;
    rtDW.dv1[28] = rtDW.d20;
    rtDW.dv1[29] = rtDW.d21;
    rtDW.dv1[30] = rtDW.d22;
    rtDW.dv1[31] = rtDW.d23;
    rtDW.dv1[32] = rtDW.d24;
    rtDW.dv1[33] = rtDW.d25;
    rtDW.dv1[34] = rtDW.d26;
    rtDW.dv1[35] = rtDW.d27;
    rtDW.dv1[36] = rtDW.d28;
    rtDW.dv1[37] = rtDW.d29;
    rtDW.dv1[38] = rtDW.d30;
    rtDW.dv1[39] = rtDW.d31;
    rtDW.dv1[40] = rtDW.d32;
    rtDW.dv1[41] = rtDW.d33;
    rtDW.dv1[42] = rtDW.d34;
    rtDW.dv1[43] = rtDW.d35;
    rtDW.dv1[44] = rtDW.d36;
    rtDW.dv1[45] = rtDW.d37;
    rtDW.dv1[46] = rtDW.d38;
    rtDW.dv1[47] = rtDW.d39;
    rtDW.dv1[48] = rtDW.d40;
    rtDW.dv1[49] = rtDW.d41;
    rtDW.dv1[50] = rtDW.d42;
    rtDW.dv1[51] = rtDW.d43;
    rtDW.dv1[52] = rtDW.d44;
    rtDW.dv1[53] = rtDW.d45;

    /* DotProduct: '<S247>/Dot Product' */
    rtDW.denAccum = 0.0;

    /* DotProduct: '<S248>/Dot Product' */
    rtDW.A_idx_0 = 0.0;

    /* DotProduct: '<S249>/Dot Product' */
    rtDW.A_idx_2 = 0.0;

    /* DotProduct: '<S250>/Dot Product' */
    rtDW.A_idx_1 = 0.0;

    /* DotProduct: '<S251>/Dot Product' */
    rtDW.A_idx_3 = 0.0;
    for (rtDW.k = 0; rtDW.k < 54; rtDW.k++) {
      /* Sum: '<S189>/Sum1' incorporates:
       *  Constant: '<S14>/b{2}'
       *  Constant: '<S189>/one'
       *  Constant: '<S189>/one1'
       *  Gain: '<S189>/Gain'
       *  Gain: '<S189>/Gain1'
       *  Math: '<S189>/Exp'
       *  Math: '<S189>/Reciprocal'
       *  Sum: '<S14>/netsum'
       *  Sum: '<S189>/Sum'
       *
       * About '<S189>/Exp':
       *  Operator: exp
       *
       * About '<S189>/Reciprocal':
       *  Operator: reciprocal
       */
      rtDW.rtb_netsum_k = 1.0 / (exp((rtDW.dv1[rtDW.k] +
        rtConstP.b2_Value[rtDW.k]) * -2.0) + 1.0) * 2.0 - 1.0;

      /* DotProduct: '<S247>/Dot Product' incorporates:
       *  Constant: '<S245>/IW{3,2}(1,:)''
       */
      rtDW.denAccum += rtConstP.IW321_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S248>/Dot Product' incorporates:
       *  Constant: '<S245>/IW{3,2}(2,:)''
       */
      rtDW.A_idx_0 += rtConstP.IW322_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S249>/Dot Product' incorporates:
       *  Constant: '<S245>/IW{3,2}(3,:)''
       */
      rtDW.A_idx_2 += rtConstP.IW323_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S250>/Dot Product' incorporates:
       *  Constant: '<S245>/IW{3,2}(4,:)''
       */
      rtDW.A_idx_1 += rtConstP.IW324_Value[rtDW.k] * rtDW.rtb_netsum_k;

      /* DotProduct: '<S251>/Dot Product' incorporates:
       *  Constant: '<S245>/IW{3,2}(5,:)''
       */
      rtDW.A_idx_3 += rtConstP.IW325_Value[rtDW.k] * rtDW.rtb_netsum_k;
    }

    /* Sum: '<S15>/netsum' incorporates:
     *  DotProduct: '<S247>/Dot Product'
     *  DotProduct: '<S248>/Dot Product'
     *  DotProduct: '<S249>/Dot Product'
     *  DotProduct: '<S250>/Dot Product'
     *  DotProduct: '<S251>/Dot Product'
     */
    rtDW.dv2[0] = rtDW.denAccum;
    rtDW.dv2[1] = rtDW.A_idx_0;
    rtDW.dv2[2] = rtDW.A_idx_2;
    rtDW.dv2[3] = rtDW.A_idx_1;
    rtDW.dv2[4] = rtDW.A_idx_3;
    for (rtDW.k = 0; rtDW.k < 5; rtDW.k++) {
      /* MATLAB Function: '<S7>/MATLAB Function1' incorporates:
       *  Bias: '<S253>/Add min x'
       *  Bias: '<S253>/Subtract min y'
       *  Constant: '<S15>/b{3}'
       *  Constant: '<S7>/Constant'
       *  Gain: '<S253>/Divide by range y'
       */
      rtDW.A_idx_0 = log10(rtConstP.Constant_Value[rtDW.k]);
      rtDW.decoded[rtDW.k] = rt_powd_snf(10.0, (((rtDW.dv2[rtDW.k] +
        rtConstP.b3_Value[rtDW.k]) + 1.0) * rtConstP.Dividebyrangey_Gain[rtDW.k]
        + rtConstP.Addminx_Bias[rtDW.k]) * (log10(rtConstP.Constant_Value[5 +
        rtDW.k]) - rtDW.A_idx_0) + rtDW.A_idx_0);
    }

    /* End of Sum: '<S15>/netsum' */

    /* MATLAB Function: '<S7>/MATLAB Function1' incorporates:
     *  Constant: '<S7>/Constant'
     */
    rtb_ENC_A_0 = false;
    rtDW.k = 0;
    exitg1 = false;
    while ((!exitg1) && (rtDW.k < 5)) {
      if (rtDW.decoded[rtDW.k] > rtConstP.Constant_Value[5 + rtDW.k]) {
        rtb_ENC_A_0 = true;
        exitg1 = true;
      } else {
        rtDW.k++;
      }
    }

    if (rtb_ENC_A_0) {
      for (rtDW.k = 0; rtDW.k < 5; rtDW.k++) {
        rtDW.A_idx_0 = rtDW.decoded[rtDW.k];
        rtDW.denAccum = rtConstP.Constant_Value[5 + rtDW.k];
        if (rtDW.decoded[rtDW.k] > rtDW.denAccum) {
          rtDW.A_idx_0 = rtDW.denAccum;
        }

        rtDW.decoded[rtDW.k] = rtDW.A_idx_0;
      }
    } else {
      rtb_ENC_A_0 = false;
      rtDW.k = 0;
      exitg1 = false;
      while ((!exitg1) && (rtDW.k < 5)) {
        if (rtDW.decoded[rtDW.k] < rtConstP.Constant_Value[rtDW.k]) {
          rtb_ENC_A_0 = true;
          exitg1 = true;
        } else {
          rtDW.k++;
        }
      }

      if (rtb_ENC_A_0) {
        for (rtDW.k = 0; rtDW.k < 5; rtDW.k++) {
          rtDW.A_idx_0 = rtDW.decoded[rtDW.k];
          if (rtDW.decoded[rtDW.k] < rtConstP.Constant_Value[rtDW.k]) {
            rtDW.A_idx_0 = rtConstP.Constant_Value[rtDW.k];
          }

          rtDW.decoded[rtDW.k] = rtDW.A_idx_0;
        }
      }
    }

    /* MATLAB Function: '<S7>/MATLAB Function' incorporates:
     *  Constant: '<S7>/i_max'
     *  Constant: '<S7>/omega_max'
     *  Constant: '<S7>/v_max'
     */
    rtDW.A_idx_0 = -rtDW.decoded[3] / rtDW.decoded[4];
    rtDW.A_idx_2 = rtDW.decoded[2] / rtDW.decoded[4];
    rtDW.A_idx_1 = -rtDW.decoded[2] / rtDW.decoded[1];
    rtDW.A_idx_3 = -rtDW.decoded[0] / rtDW.decoded[1];
    rtDW.B_idx_1 = 1.0 / rtDW.decoded[1];
    rtDW.R = inv_f(100.0);
    rtDW.dv3[0] = 400.0;
    rtDW.dv3[2] = 0.0;
    rtDW.dv3[1] = 0.0;
    rtDW.dv3[3] = 1.0;
    inv(rtDW.dv3, rtDW.U_m);
    rtDW.denAccum = 1.0 / rtDW.R;
    rtDW.A[0] = rtDW.A_idx_0;
    rtDW.A[1] = rtDW.A_idx_1;
    rtDW.A[4] = rtDW.A_idx_2;
    rtDW.A[5] = rtDW.A_idx_3;
    rtDW.A[8] = -(rtDW.denAccum * 0.0 * 0.0);
    rtDW.A[2] = -(0.5 * rtDW.U_m[0]);
    rtDW.A[10] = -rtDW.A_idx_0;
    rtDW.A_tmp = rtDW.denAccum * rtDW.B_idx_1;
    rtDW.A[9] = -(rtDW.A_tmp * 0.0);
    rtDW.A[3] = -(0.5 * rtDW.U_m[1]);
    rtDW.A[11] = -rtDW.A_idx_2;
    rtDW.A[12] = -(rtDW.denAccum * 0.0 * rtDW.B_idx_1);
    rtDW.A[6] = -(0.5 * rtDW.U_m[2]);
    rtDW.A[14] = -rtDW.A_idx_1;
    rtDW.A[13] = -(rtDW.A_tmp * rtDW.B_idx_1);
    rtDW.A[7] = -(0.5 * rtDW.U_m[3]);
    rtDW.A[15] = -rtDW.A_idx_3;
    schur(rtDW.A, rtDW.U, rtDW.unusedU0);
    rtDW.U_m[0] = rtDW.U[0];
    rtDW.U_m[1] = rtDW.U[1];
    rtDW.U_m[2] = rtDW.U[4];
    rtDW.U_m[3] = rtDW.U[5];
    inv(rtDW.U_m, rtDW.dv3);
    rtDW.denAccum = -(1.0 / rtDW.R);
    for (rtDW.k = 0; rtDW.k < 2; rtDW.k++) {
      rtDW.U_m[rtDW.k] = 0.0;
      rtDW.R = rtDW.U[2 + rtDW.k];
      rtDW.U_m[rtDW.k] += rtDW.R * rtDW.dv3[0];
      rtDW.A_tmp = rtDW.U[rtDW.k + 6];
      rtDW.U_m[rtDW.k] += rtDW.A_tmp * rtDW.dv3[1];
      rtDW.U_m[rtDW.k + 2] = 0.0;
      rtDW.U_m[rtDW.k + 2] += rtDW.R * rtDW.dv3[2];
      rtDW.U_m[rtDW.k + 2] += rtDW.A_tmp * rtDW.dv3[3];
    }

    rtDW.K[0] = 0.0;
    rtDW.K[0] += rtDW.denAccum * 0.0 * rtDW.U_m[0];
    rtDW.R = rtDW.denAccum * rtDW.B_idx_1;
    rtDW.K[0] += rtDW.R * rtDW.U_m[1];
    rtDW.K[1] = 0.0;
    rtDW.K[1] += rtDW.denAccum * 0.0 * rtDW.U_m[2];
    rtDW.K[1] += rtDW.R * rtDW.U_m[3];
    rtDW.U_m[0] = 0.0 * rtDW.K[0] + rtDW.A_idx_0;
    rtDW.U_m[2] = 0.0 * rtDW.K[1] + rtDW.A_idx_2;
    rtDW.U_m[1] = rtDW.B_idx_1 * rtDW.K[0] + rtDW.A_idx_1;
    rtDW.U_m[3] = rtDW.B_idx_1 * rtDW.K[1] + rtDW.A_idx_3;
    inv(rtDW.U_m, rtDW.dv3);
    rtDW.Kref = -inv_f((0.0 * rtDW.dv3[1] + rtDW.dv3[0]) * 0.0 + (0.0 *
      rtDW.dv3[3] + rtDW.dv3[2]) * rtDW.B_idx_1);

    /* End of MATLAB Function: '<S7>/MATLAB Function' */
  }

  rtPrevZCX.ParameterEstimationLQR1_Trig_ZC = rtDW.Delay4_DSTATE[0];

  /* End of Delay: '<Root>/Delay4' */
  /* End of Outputs for SubSystem: '<Root>/Parameter Estimation & LQR 1' */

  /* RateTransition: '<S1>/Rate Transition1' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    rtDW.RateTransition1_n = rtDW.RateTransition1_Buffer0_k;

    /* RateTransition: '<Root>/Rate Transition4' */
    rtDW.RateTransition4 = rtDW.RateTransition1_n;

    /* RateTransition: '<S8>/Rate Transition6' */
    rtDW.RateTransition6 = rtDW.RateTransition6_Buffer0;
  }

  /* End of RateTransition: '<S1>/Rate Transition1' */

  /* DiscreteTransferFcn: '<S254>/Discrete Transfer Fcn' */
  rtDW.denAccum = rtDW.RateTransition6 - rtDW.DiscreteTransferFcn_states;
  rtDW.A_idx_0 = 199999.99999999997 * rtDW.denAccum + -199999.99999999997 *
    rtDW.DiscreteTransferFcn_states;

  /* RateTransition: '<Root>/Rate Transition5' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* Gain: '<Root>/Gain1' */
    rtDW.Gain1[0] = 0.001 * rtDW.RateTransition4;
    rtDW.Gain1[1] = 0.001 * rtDW.A_idx_0;
  }

  /* End of RateTransition: '<Root>/Rate Transition5' */

  /* MATLABSystem: '<S5>/Analog Input' */
  if (rtDW.obj.SampleTime != -1.0) {
    rtDW.obj.SampleTime = -1.0;
  }

  MW_AnalogIn_Start(rtDW.obj.MW_ANALOGIN_HANDLE);
  MW_AnalogInSingle_ReadResult(rtDW.obj.MW_ANALOGIN_HANDLE, &rtDW.A_idx_2, 7);

  /* Outputs for Atomic SubSystem: '<Root>/LQR controller 1' */
  /* Switch: '<Root>/Switch3' incorporates:
   *  Constant: '<S5>/omega_offset'
   *  Delay: '<Root>/Delay5'
   *  Gain: '<S5>/omega_gain'
   *  Gain: '<S5>/to Volts'
   *  MATLABSystem: '<S5>/Analog Input'
   *  Product: '<S3>/Matrix Multiply'
   *  Product: '<S3>/Multiply'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtMatrix MultiplyInport2'
   *  Sum: '<S3>/Add'
   *  Sum: '<S5>/Add'
   */
  rtDW.Delay5_DSTATE = (0.0008056640625 * rtDW.A_idx_2 * 0.5 + 1.0) * rtDW.Kref
    + (rtDW.K[0] * rtDW.A_idx_0 + rtDW.K[1] * rtDW.RateTransition1_n);

  /* End of Outputs for SubSystem: '<Root>/LQR controller 1' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* MATLABSystem: '<S1>/Analog Input' */
    if (rtDW.obj_b.SampleTime != 0.002) {
      rtDW.obj_b.SampleTime = 0.002;
    }

    MW_AnalogIn_Start(rtDW.obj_b.MW_ANALOGIN_HANDLE);
    MW_AnalogInSingle_ReadResult(rtDW.obj_b.MW_ANALOGIN_HANDLE, &rtDW.Ampere, 7);

    /* Sum: '<S1>/Add' incorporates:
     *  Constant: '<S1>/current_offset'
     *  Gain: '<S1>/current_gain'
     *  Gain: '<S1>/to Volts'
     *  MATLABSystem: '<S1>/Analog Input'
     */
    rtDW.Ampere = 0.0008056640625 * rtDW.Ampere * 0.5 + 1.0;

    /* Update for RateTransition: '<Root>/Rate Transition8' */
    rtDW.RateTransition8_Buffer0 = rtDW.Gain1[1];

    /* Update for S-Function (sdspsreg2): '<Root>/Delay Line2' */
    rtDW.DelayLine2_Buff[rtDW.DelayLine2_BUFF_OFFSET] = rtDW.Gain1[0];
    rtDW.DelayLine2_BUFF_OFFSET++;
    while (rtDW.DelayLine2_BUFF_OFFSET >= 50) {
      rtDW.DelayLine2_BUFF_OFFSET -= 50;
    }

    /* End of Update for S-Function (sdspsreg2): '<Root>/Delay Line2' */

    /* Update for S-Function (sdspsreg2): '<Root>/Delay Line3' */
    rtDW.DelayLine3_Buff[rtDW.DelayLine3_BUFF_OFFSET] = rtDW.Gain1[1];
    rtDW.DelayLine3_BUFF_OFFSET++;
    while (rtDW.DelayLine3_BUFF_OFFSET >= 50) {
      rtDW.DelayLine3_BUFF_OFFSET -= 50;
    }

    /* End of Update for S-Function (sdspsreg2): '<Root>/Delay Line3' */
  }

  /* Update for Delay: '<Root>/Delay3' */
  rtDW.bitsForTID0.Delay3_DSTATE = rtb_Counter1;

  /* Update for Delay: '<Root>/Delay4' */
  for (rtDW.k = 0; rtDW.k < 199; rtDW.k++) {
    rtDW.Delay4_DSTATE[rtDW.k] = rtDW.Delay4_DSTATE[rtDW.k + 1];
  }

  rtDW.Delay4_DSTATE[199] = rtb_Counter1;

  /* End of Update for Delay: '<Root>/Delay4' */

  /* Update for RateTransition: '<Root>/Rate Transition1' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    for (rtDW.k = 0; rtDW.k < 50; rtDW.k++) {
      rtDW.RateTransition1_Buffer0[rtDW.k] = rtDW.DelayLine2[rtDW.k];
      rtDW.RateTransition1_Buffer0[rtDW.k + 50] = rtDW.DelayLine3[rtDW.k];
    }

    /* Update for RateTransition: '<S1>/Rate Transition1' */
    rtDW.RateTransition1_Buffer0_k = rtDW.Ampere;

    /* Update for RateTransition: '<S8>/Rate Transition6' */
    rtDW.RateTransition6_Buffer0 = rtDW.rad;
  }

  /* End of Update for RateTransition: '<Root>/Rate Transition1' */

  /* Update for DiscreteTransferFcn: '<S254>/Discrete Transfer Fcn' */
  rtDW.DiscreteTransferFcn_states = rtDW.denAccum;
  rate_scheduler();
}

/* Model initialize function */
void motoraiHIL_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    mbed_DigitalRead *obj;
    uint32_T pinname;
    mbed_DigitalWrite *obj_0;
    mbed_PWMOutput *obj_1;
    mbed_AnalogInput *obj_2;
    MW_AnalogIn_TriggerSource_Type trigger_val;

    /* Start for MATLABSystem: '<S9>/Digital Read' */
    rtDW.obj_h.matlabCodegenIsDeleted = true;
    rtDW.obj_h.isInitialized = 0;
    rtDW.obj_h.matlabCodegenIsDeleted = false;
    rtDW.obj_h.SampleTime = -1.0;
    obj = &rtDW.obj_h;
    rtDW.obj_h.isSetupComplete = false;
    rtDW.obj_h.isInitialized = 1;
    pinname = PC_13;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(pinname, 0);
    rtDW.obj_h.isSetupComplete = true;

    /* Start for MATLABSystem: '<S8>/ENC_A' */
    rtDW.obj_e.matlabCodegenIsDeleted = true;
    rtDW.obj_e.isInitialized = 0;
    rtDW.obj_e.matlabCodegenIsDeleted = false;
    rtDW.obj_e.SampleTime = 0.002;
    obj = &rtDW.obj_e;
    rtDW.obj_e.isSetupComplete = false;
    rtDW.obj_e.isInitialized = 1;
    pinname = PA_0;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(pinname, 0);
    rtDW.obj_e.isSetupComplete = true;

    /* Start for S-Function (discreteNLastSamples): '<S257>/S-Function ' */

    /* S-Function Block: <S257>/S-Function  */
    {
      static real_T dnls_buffer[1 * 2];
      rtDW.SFunction_PWORK.uBuffers = (void *)&dnls_buffer[0];
    }

    {
      int ids;

      /* Assign default sample(s) */
      if (rtDW.SFunction_PWORK.uBuffers != NULL) {
        for (ids = 0; ids < 2; ++ids)
          ((real_T *)rtDW.SFunction_PWORK.uBuffers)[ids] = (real_T)0.0;
      }

      /* Set work values */
      rtDW.SFunction_IWORK.indPs = 0;
    }

    /* Start for MATLABSystem: '<S8>/ENC_B' */
    rtDW.obj_k.matlabCodegenIsDeleted = true;
    rtDW.obj_k.isInitialized = 0;
    rtDW.obj_k.matlabCodegenIsDeleted = false;
    rtDW.obj_k.SampleTime = 0.002;
    obj = &rtDW.obj_k;
    rtDW.obj_k.isSetupComplete = false;
    rtDW.obj_k.isInitialized = 1;
    pinname = PA_1;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(pinname, 0);
    rtDW.obj_k.isSetupComplete = true;

    /* Start for S-Function (discreteNLastSamples): '<S258>/S-Function ' */

    /* S-Function Block: <S258>/S-Function  */
    {
      static real_T dnls_buffer[1 * 2];
      rtDW.SFunction_PWORK_m.uBuffers = (void *)&dnls_buffer[0];
    }

    {
      int ids;

      /* Assign default sample(s) */
      if (rtDW.SFunction_PWORK_m.uBuffers != NULL) {
        for (ids = 0; ids < 2; ++ids)
          ((real_T *)rtDW.SFunction_PWORK_m.uBuffers)[ids] = (real_T)0.0;
      }

      /* Set work values */
      rtDW.SFunction_IWORK_p.indPs = 0;
    }

    /* Start for MATLABSystem: '<S2>/Digital Write' */
    rtDW.obj_bu.matlabCodegenIsDeleted = true;
    rtDW.obj_bu.isInitialized = 0;
    rtDW.obj_bu.matlabCodegenIsDeleted = false;
    obj_0 = &rtDW.obj_bu;
    rtDW.obj_bu.isSetupComplete = false;
    rtDW.obj_bu.isInitialized = 1;
    pinname = PA_5;
    obj_0->MW_DIGITALIO_HANDLE = MW_digitalIO_open(pinname, 1);
    rtDW.obj_bu.isSetupComplete = true;

    /* Start for MATLABSystem: '<S6>/PWM Output' */
    rtDW.obj_ko.matlabCodegenIsDeleted = true;
    rtDW.obj_ko.isInitialized = 0;
    rtDW.obj_ko.matlabCodegenIsDeleted = false;
    obj_1 = &rtDW.obj_ko;
    rtDW.obj_ko.isSetupComplete = false;
    rtDW.obj_ko.isInitialized = 1;
    pinname = PA_3;
    obj_1->MW_PWM_HANDLE = MW_PWM_Open(pinname, 2000.0, 50.0);
    MW_PWM_Start(rtDW.obj_ko.MW_PWM_HANDLE);
    rtDW.obj_ko.isSetupComplete = true;

    /* Start for MATLABSystem: '<S5>/Analog Input' */
    rtDW.obj.matlabCodegenIsDeleted = true;
    rtDW.obj.isInitialized = 0;
    rtDW.obj.matlabCodegenIsDeleted = false;
    rtDW.obj.SampleTime = -1.0;
    obj_2 = &rtDW.obj;
    rtDW.obj.isSetupComplete = false;
    rtDW.obj.isInitialized = 1;
    pinname = PC_0;
    obj_2->MW_ANALOGIN_HANDLE = MW_AnalogInSingle_Open(pinname);
    trigger_val = MW_ANALOGIN_SOFTWARE_TRIGGER;
    MW_AnalogIn_SetTriggerSource(rtDW.obj.MW_ANALOGIN_HANDLE, trigger_val, 0U);
    rtDW.obj.isSetupComplete = true;

    /* Start for MATLABSystem: '<S1>/Analog Input' */
    rtDW.obj_b.matlabCodegenIsDeleted = true;
    rtDW.obj_b.isInitialized = 0;
    rtDW.obj_b.matlabCodegenIsDeleted = false;
    rtDW.obj_b.SampleTime = 0.002;
    obj_2 = &rtDW.obj_b;
    rtDW.obj_b.isSetupComplete = false;
    rtDW.obj_b.isInitialized = 1;
    pinname = PB_0;
    obj_2->MW_ANALOGIN_HANDLE = MW_AnalogInSingle_Open(pinname);
    trigger_val = MW_ANALOGIN_SOFTWARE_TRIGGER;
    MW_AnalogIn_SetTriggerSource(rtDW.obj_b.MW_ANALOGIN_HANDLE, trigger_val, 0U);
    rtDW.obj_b.isSetupComplete = true;
    rtPrevZCX.ParameterEstimationLQR1_Trig_ZC = POS_ZCSIG;

    /* InitializeConditions for S-Function (sdspcount2): '<S8>/Counter' */
    rtDW.Counter_ClkEphState = 5U;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
