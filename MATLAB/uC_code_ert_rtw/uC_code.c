/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uC_code.c
 *
 * Code generated for Simulink model 'uC_code'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sat Jan 26 11:55:46 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. RAM efficiency
 *    2. Execution efficiency
 * Validation result: Not run
 */

#include "uC_code.h"
#include <math.h>
#include <stdlib.h>
#define NumBitsPerChar                 8U

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

#define MAX_BUFFER_SIZE                32768
#ifndef ssGetFixedStepSize
#define ssGetFixedStepSize(S)          (S).stepSize
#endif                                 /* ssGetFixedStepSize */

/* Continuous states */
X rtX;

/* Block signals and states (default storage) */
DW rtDW;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern uint32_T MWDSP_EPH_R_B(boolean_T evt, uint32_T *sta);

/* private model entry point functions */
extern void uC_code_derivatives(void);

/* Forward declaration for local functions */
static void SystemCore_release_f2l(const mbed_DigitalRead *obj);
static void SystemCore_delete_f2l(const mbed_DigitalRead *obj);
static void matlabCodegenHandle_matlabC_f2l(mbed_DigitalRead *obj);
static void SystemCore_release(const mbed_AnalogInput *obj);
static void SystemCore_delete(const mbed_AnalogInput *obj);
static void matlabCodegenHandle_matlabCodeg(mbed_AnalogInput *obj);
static void SystemCore_release_f2(const mbed_PWMOutput *obj);
static void SystemCore_delete_f2(const mbed_PWMOutput *obj);
static void matlabCodegenHandle_matlabCo_f2(mbed_PWMOutput *obj);
extern real_T rtGetInf(void);
extern real32_T rtGetInfF(void);
extern real_T rtGetMinusInf(void);
extern real32_T rtGetMinusInfF(void);
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
extern real_T rtGetNaN(void);
extern real32_T rtGetNaNF(void);

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
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  uC_code_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  uC_code_step();
  uC_code_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  uC_code_step();
  uC_code_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

uint32_T MWDSP_EPH_R_B(boolean_T evt, uint32_T *sta)
{
  uint32_T retVal;
  int32_T curState;
  int32_T newState;
  int32_T newStateR;
  int32_T lastzcevent;
  uint32_T previousState;

  /* S-Function (sdspcount2): '<S5>/Counter' */
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

  /* End of S-Function (sdspcount2): '<S5>/Counter' */
  return retVal;
}

static void SystemCore_release_f2l(const mbed_DigitalRead *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_digitalIO_close(obj->MW_DIGITALIO_HANDLE);
  }
}

static void SystemCore_delete_f2l(const mbed_DigitalRead *obj)
{
  SystemCore_release_f2l(obj);
}

static void matlabCodegenHandle_matlabC_f2l(mbed_DigitalRead *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    SystemCore_delete_f2l(obj);
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

static void SystemCore_release_f2(const mbed_PWMOutput *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_PWM_Stop(obj->MW_PWM_HANDLE);
    MW_PWM_Close(obj->MW_PWM_HANDLE);
  }
}

static void SystemCore_delete_f2(const mbed_PWMOutput *obj)
{
  SystemCore_release_f2(obj);
}

static void matlabCodegenHandle_matlabCo_f2(mbed_PWMOutput *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    SystemCore_delete_f2(obj);
  }
}

/* Model step function */
void uC_code_step(void)
{
  if (rtmIsMajorTimeStep(rtM)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&rtM->solverInfo,((rtM->Timing.clockTick0+1)*
      rtM->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rtM)) {
    rtM->Timing.t[0] = rtsiGetT(&rtM->solverInfo);
  }

  {
    real_T *lastU;
    real_T lastTime;
    boolean_T rtb_ENC_B_0;
    real_T rtb_rads_j;
    if (rtmIsMajorTimeStep(rtM)) {
      /* MATLABSystem: '<S5>/ENC_B' */
      if (rtDW.obj_jb.SampleTime != -1.0) {
        rtDW.obj_jb.SampleTime = -1.0;
      }

      rtb_ENC_B_0 = MW_digitalIO_read(rtDW.obj_jb.MW_DIGITALIO_HANDLE);

      /* DataTypeConversion: '<S6>/Data Type Conversion1' incorporates:
       *  MATLABSystem: '<S5>/ENC_B'
       */
      rtDW.DataTypeConversion1 = rtb_ENC_B_0;

      /* MATLABSystem: '<S5>/ENC_A' */
      if (rtDW.obj_n.SampleTime != -1.0) {
        rtDW.obj_n.SampleTime = -1.0;
      }

      rtb_ENC_B_0 = MW_digitalIO_read(rtDW.obj_n.MW_DIGITALIO_HANDLE);

      /* DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
       *  MATLABSystem: '<S5>/ENC_A'
       */
      rtDW.DataTypeConversion = rtb_ENC_B_0;

      /* S-Function (discreteNLastSamples): '<S8>/S-Function ' */
      /* S-Function block: <S8>/S-Function  */
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

      /* S-Function (discreteNLastSamples): '<S9>/S-Function ' */
      /* S-Function block: <S9>/S-Function  */
      {
        int nSamples = 2 ;
        int io = 0;
        int iv;
        int ind_Ps = rtDW.SFunction_IWORK_d.indPs;

        /* Input present value(s) */
        ((real_T *)rtDW.SFunction_PWORK_f.uBuffers)[ind_Ps] =
          rtDW.DataTypeConversion1;

        /* Output past value(s) */
        /* Output from present sample index to 0 */
        for (iv = ind_Ps; iv >= 0; --iv)
          (&rtDW.SFunction_f[0])[io++] = ((real_T *)
            rtDW.SFunction_PWORK_f.uBuffers)[iv];

        /* Output from end of buffer to present sample index excl. */
        for (iv = nSamples-1; iv > ind_Ps; --iv)
          (&rtDW.SFunction_f[0])[io++] = ((real_T *)
            rtDW.SFunction_PWORK_f.uBuffers)[iv];

        /* Update ring buffer index */
        if (++(rtDW.SFunction_IWORK_d.indPs) == nSamples)
          rtDW.SFunction_IWORK_d.indPs = 0;
      }

      /* S-Function (sdspcount2): '<S5>/Counter' incorporates:
       *  DataTypeConversion: '<S6>/Data Type Conversion2'
       *  DataTypeConversion: '<S6>/Data Type Conversion3'
       *  Logic: '<S7>/XOR'
       *  Logic: '<S7>/XOR1'
       *  Logic: '<S7>/XOR2'
       */
      if (MWDSP_EPH_R_B((boolean_T)((boolean_T)((rtDW.SFunction[1] != 0.0) ^
             (rtDW.SFunction[0] != 0.0)) ^ (boolean_T)((rtDW.SFunction_f[0] !=
              0.0) ^ (rtDW.SFunction_f[1] != 0.0))), &rtDW.Counter_ClkEphState)
          != 0U) {
        if (rtDW.Counter_Count < 255) {
          rtDW.Counter_Count++;
        } else {
          rtDW.Counter_Count = 0U;
        }
      }

      /* Gain: '<S5>/Gain' incorporates:
       *  S-Function (sdspcount2): '<S5>/Counter'
       */
      rtDW.rad = 0.0062831853071795866 * (real_T)rtDW.Counter_Count;
    }

    /* Derivative: '<S5>/Derivative' */
    rtb_rads_j = rtM->Timing.t[0];
    if ((rtDW.TimeStampA >= rtb_rads_j) && (rtDW.TimeStampB >= rtb_rads_j)) {
      rtb_rads_j = 0.0;
    } else {
      lastTime = rtDW.TimeStampA;
      lastU = &rtDW.LastUAtTimeA;
      if (rtDW.TimeStampA < rtDW.TimeStampB) {
        if (rtDW.TimeStampB < rtb_rads_j) {
          lastTime = rtDW.TimeStampB;
          lastU = &rtDW.LastUAtTimeB;
        }
      } else {
        if (rtDW.TimeStampA >= rtb_rads_j) {
          lastTime = rtDW.TimeStampB;
          lastU = &rtDW.LastUAtTimeB;
        }
      }

      rtb_rads_j = (rtDW.rad - *lastU) / (rtb_rads_j - lastTime);
    }

    /* End of Derivative: '<S5>/Derivative' */

    /* MATLABSystem: '<S1>/Analog Input' */
    if (rtDW.obj_j.SampleTime != -1.0) {
      rtDW.obj_j.SampleTime = -1.0;
    }

    MW_AnalogIn_Start(rtDW.obj_j.MW_ANALOGIN_HANDLE);
    MW_AnalogInSingle_ReadResult(rtDW.obj_j.MW_ANALOGIN_HANDLE, &lastTime, 7);

    /* MATLABSystem: '<S4>/PWM Output' incorporates:
     *  Constant: '<S1>/current_offset'
     *  Constant: '<S4>/Actuation voltage'
     *  Constant: '<S4>/to %'
     *  Gain: '<S1>/current_gain'
     *  Gain: '<S1>/to Volts'
     *  Gain: '<S2>/Gain'
     *  Integrator: '<S2>/Integrator'
     *  MATLABSystem: '<S1>/Analog Input'
     *  Product: '<S4>/Divide'
     *  Product: '<S4>/Divide1'
     *  SignalConversion: '<S2>/TmpSignal ConversionAtGainInport1'
     *  Sum: '<S1>/Add'
     */
    MW_PWM_SetDutyCycle(rtDW.obj_ni.MW_PWM_HANDLE, ((-0.17248970967292074 *
      rtb_rads_j + -0.09172320288306765 * (0.5 * (0.0008056640625 * lastTime) +
      1.0)) + 3.5355339059326467 * rtX.Integrator_CSTATE) / 12.0 * 100.0);

    /* MATLABSystem: '<S3>/Analog Input' */
    if (rtDW.obj.SampleTime != -1.0) {
      rtDW.obj.SampleTime = -1.0;
    }

    MW_AnalogIn_Start(rtDW.obj.MW_ANALOGIN_HANDLE);
    MW_AnalogInSingle_ReadResult(rtDW.obj.MW_ANALOGIN_HANDLE, &lastTime, 7);

    /* Sum: '<S2>/Add1' incorporates:
     *  Constant: '<S3>/omega_offset'
     *  Gain: '<S3>/omega_gain'
     *  Gain: '<S3>/to Volts'
     *  MATLABSystem: '<S3>/Analog Input'
     *  Sum: '<S3>/Add'
     */
    rtDW.Add1 = (0.0008056640625 * lastTime * 0.5 + 1.0) - rtb_rads_j;
  }

  if (rtmIsMajorTimeStep(rtM)) {
    real_T *lastU;

    /* Update for Derivative: '<S5>/Derivative' */
    if (rtDW.TimeStampA == (rtInf)) {
      rtDW.TimeStampA = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeA;
    } else if (rtDW.TimeStampB == (rtInf)) {
      rtDW.TimeStampB = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeB;
    } else if (rtDW.TimeStampA < rtDW.TimeStampB) {
      rtDW.TimeStampA = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeA;
    } else {
      rtDW.TimeStampB = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeB;
    }

    *lastU = rtDW.rad;

    /* End of Update for Derivative: '<S5>/Derivative' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(rtM)) {
    rt_ertODEUpdateContinuousStates(&rtM->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++rtM->Timing.clockTick0;
    rtM->Timing.t[0] = rtsiGetSolverStopTime(&rtM->solverInfo);

    {
      /* Update absolute timer for sample time: [5.0E-5s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 5.0E-5, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      rtM->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void uC_code_derivatives(void)
{
  XDot *_rtXdot;
  _rtXdot = ((XDot *) rtM->derivs);

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE = rtDW.Add1;
}

/* Model initialize function */
void uC_code_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rtM->solverInfo, &rtM->Timing.simTimeStep);
    rtsiSetTPtr(&rtM->solverInfo, &rtmGetTPtr(rtM));
    rtsiSetStepSizePtr(&rtM->solverInfo, &rtM->Timing.stepSize0);
    rtsiSetdXPtr(&rtM->solverInfo, &rtM->derivs);
    rtsiSetContStatesPtr(&rtM->solverInfo, (real_T **) &rtM->contStates);
    rtsiSetNumContStatesPtr(&rtM->solverInfo, &rtM->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&rtM->solverInfo,
      &rtM->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&rtM->solverInfo,
      &rtM->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&rtM->solverInfo,
      &rtM->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&rtM->solverInfo, (&rtmGetErrorStatus(rtM)));
    rtsiSetRTModelPtr(&rtM->solverInfo, rtM);
  }

  rtsiSetSimTimeStep(&rtM->solverInfo, MAJOR_TIME_STEP);
  rtM->intgData.y = rtM->odeY;
  rtM->intgData.f[0] = rtM->odeF[0];
  rtM->intgData.f[1] = rtM->odeF[1];
  rtM->intgData.f[2] = rtM->odeF[2];
  rtM->contStates = ((X *) &rtX);
  rtsiSetSolverData(&rtM->solverInfo, (void *)&rtM->intgData);
  rtsiSetSolverName(&rtM->solverInfo,"ode3");
  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);
  rtM->Timing.stepSize0 = 5.0E-5;

  {
    mbed_DigitalRead *obj;
    uint32_T pinname;
    mbed_AnalogInput *obj_0;
    MW_AnalogIn_TriggerSource_Type trigger_val;
    mbed_PWMOutput *obj_1;

    /* Start for MATLABSystem: '<S5>/ENC_B' */
    rtDW.obj_jb.matlabCodegenIsDeleted = true;
    rtDW.obj_jb.isInitialized = 0;
    rtDW.obj_jb.matlabCodegenIsDeleted = false;
    rtDW.obj_jb.SampleTime = -1.0;
    obj = &rtDW.obj_jb;
    rtDW.obj_jb.isSetupComplete = false;
    rtDW.obj_jb.isInitialized = 1;
    pinname = 6;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(pinname, 0);
    rtDW.obj_jb.isSetupComplete = true;

    /* Start for MATLABSystem: '<S5>/ENC_A' */
    rtDW.obj_n.matlabCodegenIsDeleted = true;
    rtDW.obj_n.isInitialized = 0;
    rtDW.obj_n.matlabCodegenIsDeleted = false;
    rtDW.obj_n.SampleTime = -1.0;
    obj = &rtDW.obj_n;
    rtDW.obj_n.isSetupComplete = false;
    rtDW.obj_n.isInitialized = 1;
    pinname = 5;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(pinname, 0);
    rtDW.obj_n.isSetupComplete = true;

    /* Start for S-Function (discreteNLastSamples): '<S8>/S-Function ' */

    /* S-Function Block: <S8>/S-Function  */
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

    /* Start for S-Function (discreteNLastSamples): '<S9>/S-Function ' */

    /* S-Function Block: <S9>/S-Function  */
    {
      static real_T dnls_buffer[1 * 2];
      rtDW.SFunction_PWORK_f.uBuffers = (void *)&dnls_buffer[0];
    }

    {
      int ids;

      /* Assign default sample(s) */
      if (rtDW.SFunction_PWORK_f.uBuffers != NULL) {
        for (ids = 0; ids < 2; ++ids)
          ((real_T *)rtDW.SFunction_PWORK_f.uBuffers)[ids] = (real_T)0.0;
      }

      /* Set work values */
      rtDW.SFunction_IWORK_d.indPs = 0;
    }

    /* Start for MATLABSystem: '<S1>/Analog Input' */
    rtDW.obj_j.matlabCodegenIsDeleted = true;
    rtDW.obj_j.isInitialized = 0;
    rtDW.obj_j.matlabCodegenIsDeleted = false;
    rtDW.obj_j.SampleTime = -1.0;
    obj_0 = &rtDW.obj_j;
    rtDW.obj_j.isSetupComplete = false;
    rtDW.obj_j.isInitialized = 1;
    pinname = 10;
    obj_0->MW_ANALOGIN_HANDLE = MW_AnalogInSingle_Open(pinname);
    trigger_val = MW_ANALOGIN_SOFTWARE_TRIGGER;
    MW_AnalogIn_SetTriggerSource(rtDW.obj_j.MW_ANALOGIN_HANDLE, trigger_val, 0U);
    rtDW.obj_j.isSetupComplete = true;

    /* Start for MATLABSystem: '<S4>/PWM Output' */
    rtDW.obj_ni.matlabCodegenIsDeleted = true;
    rtDW.obj_ni.isInitialized = 0;
    rtDW.obj_ni.matlabCodegenIsDeleted = false;
    obj_1 = &rtDW.obj_ni;
    rtDW.obj_ni.isSetupComplete = false;
    rtDW.obj_ni.isInitialized = 1;
    pinname = 7;
    obj_1->MW_PWM_HANDLE = MW_PWM_Open(pinname, 2000.0, 50.0);
    MW_PWM_Start(rtDW.obj_ni.MW_PWM_HANDLE);
    rtDW.obj_ni.isSetupComplete = true;

    /* Start for MATLABSystem: '<S3>/Analog Input' */
    rtDW.obj.matlabCodegenIsDeleted = true;
    rtDW.obj.isInitialized = 0;
    rtDW.obj.matlabCodegenIsDeleted = false;
    rtDW.obj.SampleTime = -1.0;
    obj_0 = &rtDW.obj;
    rtDW.obj.isSetupComplete = false;
    rtDW.obj.isInitialized = 1;
    pinname = 11;
    obj_0->MW_ANALOGIN_HANDLE = MW_AnalogInSingle_Open(pinname);
    trigger_val = MW_ANALOGIN_SOFTWARE_TRIGGER;
    MW_AnalogIn_SetTriggerSource(rtDW.obj.MW_ANALOGIN_HANDLE, trigger_val, 0U);
    rtDW.obj.isSetupComplete = true;

    /* InitializeConditions for S-Function (sdspcount2): '<S5>/Counter' */
    rtDW.Counter_ClkEphState = 5U;

    /* InitializeConditions for Derivative: '<S5>/Derivative' */
    rtDW.TimeStampA = (rtInf);
    rtDW.TimeStampB = (rtInf);

    /* InitializeConditions for Integrator: '<S2>/Integrator' */
    rtX.Integrator_CSTATE = 0.0;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
