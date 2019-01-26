/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uC_code.c
 *
 * Code generated for Simulink model 'uC_code'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sat Jan 26 17:42:54 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. MISRA C:2012 guidelines
 *    2. RAM efficiency
 *    3. Execution efficiency
 * Validation result: Not run
 */

#include "uC_code.h"
#include <math.h>
#include <stdlib.h>
#include "MWDSP_EPH_R_B.h"
#define MAX_BUFFER_SIZE                32768
#ifndef ssGetFixedStepSize
#define ssGetFixedStepSize(S)          (S).stepSize
#endif                                 /* ssGetFixedStepSize */

/* Block signals and states (default storage) */
DW rtDW;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

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
static void rate_scheduler(void);

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
  if ((rtM->Timing.TaskCounters.TID[1]) > 19999) {/* Sample time: [1.0s, 0.0s] */
    rtM->Timing.TaskCounters.TID[1] = 0;
  }
}

static void SystemCore_release_f2l(const mbed_DigitalRead *obj)
{
  if ((obj->isInitialized == 1) && (obj->isSetupComplete)) {
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
  if ((obj->isInitialized == 1) && (obj->isSetupComplete)) {
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
  if ((obj->isInitialized == 1) && (obj->isSetupComplete)) {
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
  real_T numAccum;
  real_T denAccum;
  boolean_T rtb_ENC_B_0;
  real_T rtb_word_h_0;

  /* MATLABSystem: '<S5>/ENC_B' */
  if (rtDW.obj_jb.SampleTime != -1.0) {
    rtDW.obj_jb.SampleTime = -1.0;
  }

  rtb_ENC_B_0 = MW_digitalIO_read(rtDW.obj_jb.MW_DIGITALIO_HANDLE);

  /* DataTypeConversion: '<S7>/Data Type Conversion1' incorporates:
   *  MATLABSystem: '<S5>/ENC_B'
   */
  rtDW.DataTypeConversion1 = rtb_ENC_B_0 ? 1.0 : 0.0;

  /* MATLABSystem: '<S5>/ENC_A' */
  if (rtDW.obj_n.SampleTime != -1.0) {
    rtDW.obj_n.SampleTime = -1.0;
  }

  rtb_ENC_B_0 = MW_digitalIO_read(rtDW.obj_n.MW_DIGITALIO_HANDLE);

  /* DataTypeConversion: '<S7>/Data Type Conversion' incorporates:
   *  MATLABSystem: '<S5>/ENC_A'
   */
  rtDW.DataTypeConversion = rtb_ENC_B_0 ? 1.0 : 0.0;

  /* S-Function (discreteNLastSamples): '<S9>/S-Function ' */
  /* S-Function block: <S9>/S-Function  */
  {
    int nSamples = 2 ;
    int io = 0;
    int iv;
    int ind_Ps = rtDW.SFunction_IWORK.indPs;

    /* Input present value(s) */
    ((real_T *)rtDW.SFunction_PWORK.uBuffers)[ind_Ps] = rtDW.DataTypeConversion;

    /* Output past value(s) */
    /* Output from present sample index to 0 */
    for (iv = ind_Ps; iv >= 0; --iv)
      (&rtDW.SFunction[0])[io++] = ((real_T *)rtDW.SFunction_PWORK.uBuffers)[iv];

    /* Output from end of buffer to present sample index excl. */
    for (iv = nSamples-1; iv > ind_Ps; --iv)
      (&rtDW.SFunction[0])[io++] = ((real_T *)rtDW.SFunction_PWORK.uBuffers)[iv];

    /* Update ring buffer index */
    if (++(rtDW.SFunction_IWORK.indPs) == nSamples)
      rtDW.SFunction_IWORK.indPs = 0;
  }

  /* S-Function (discreteNLastSamples): '<S10>/S-Function ' */
  /* S-Function block: <S10>/S-Function  */
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
      (&rtDW.SFunction_f[0])[io++] = ((real_T *)rtDW.SFunction_PWORK_f.uBuffers)
        [iv];

    /* Output from end of buffer to present sample index excl. */
    for (iv = nSamples-1; iv > ind_Ps; --iv)
      (&rtDW.SFunction_f[0])[io++] = ((real_T *)rtDW.SFunction_PWORK_f.uBuffers)
        [iv];

    /* Update ring buffer index */
    if (++(rtDW.SFunction_IWORK_d.indPs) == nSamples)
      rtDW.SFunction_IWORK_d.indPs = 0;
  }

  /* S-Function (sdspcount2): '<S5>/Counter' incorporates:
   *  DataTypeConversion: '<S7>/Data Type Conversion2'
   *  DataTypeConversion: '<S7>/Data Type Conversion3'
   *  Logic: '<S8>/XOR'
   *  Logic: '<S8>/XOR1'
   *  Logic: '<S8>/XOR2'
   */
  if (MWDSP_EPH_R_B(((rtDW.SFunction[1] != 0.0) != (rtDW.SFunction[0] != 0.0))
                    != ((rtDW.SFunction_f[0] != 0.0) != (rtDW.SFunction_f[1] !=
         0.0)), &rtDW.Counter_ClkEphState) != 0U) {
    if (((int32_T)rtDW.Counter_Count) < 255) {
      rtDW.Counter_Count = (uint8_T)(((uint32_T)rtDW.Counter_Count) + 1U);
    } else {
      rtDW.Counter_Count = 0U;
    }
  }

  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* DiscreteTransferFcn: '<S6>/Discrete Transfer Fcn' incorporates:
     *  Gain: '<S5>/Gain'
     *  S-Function (sdspcount2): '<S5>/Counter'
     */
    denAccum = (0.0062831853071795866 * ((real_T)rtDW.Counter_Count)) -
      rtDW.DiscreteTransferFcn_states;
    numAccum = (2.0 * denAccum) + (-2.0 * rtDW.DiscreteTransferFcn_states);

    /* MATLABSystem: '<S1>/Analog Input' */
    if (rtDW.obj_j.SampleTime != -1.0) {
      rtDW.obj_j.SampleTime = -1.0;
    }

    MW_AnalogIn_Start(rtDW.obj_j.MW_ANALOGIN_HANDLE);
    MW_AnalogInSingle_ReadResult(rtDW.obj_j.MW_ANALOGIN_HANDLE, &rtb_word_h_0, 7);

    /* MATLABSystem: '<S4>/PWM Output' incorporates:
     *  Constant: '<S1>/current_offset'
     *  Constant: '<S4>/Actuation voltage'
     *  Constant: '<S4>/to percentage'
     *  DiscreteIntegrator: '<S2>/Integrator'
     *  DiscreteTransferFcn: '<S6>/Discrete Transfer Fcn'
     *  Gain: '<S1>/current_gain'
     *  Gain: '<S1>/to Volts'
     *  Gain: '<S2>/Gain'
     *  MATLABSystem: '<S1>/Analog Input'
     *  Product: '<S4>/Divide'
     *  Product: '<S4>/Divide1'
     *  Sum: '<S1>/Add'
     */
    MW_PWM_SetDutyCycle(rtDW.obj_ni.MW_PWM_HANDLE, ((((-0.17248970967292074 *
      numAccum) + (-0.09172320288306765 * ((0.5 * (0.0008056640625 *
      rtb_word_h_0)) + 1.0))) + (3.5355339059326467 * rtDW.Integrator_DSTATE)) /
      12.0) * 100.0);

    /* MATLABSystem: '<S3>/Analog Input' */
    if (rtDW.obj.SampleTime != -1.0) {
      rtDW.obj.SampleTime = -1.0;
    }

    MW_AnalogIn_Start(rtDW.obj.MW_ANALOGIN_HANDLE);
    MW_AnalogInSingle_ReadResult(rtDW.obj.MW_ANALOGIN_HANDLE, &rtb_word_h_0, 7);

    /* Update for DiscreteTransferFcn: '<S6>/Discrete Transfer Fcn' */
    rtDW.DiscreteTransferFcn_states = denAccum;

    /* Update for DiscreteIntegrator: '<S2>/Integrator' incorporates:
     *  Constant: '<S3>/omega_offset'
     *  DiscreteTransferFcn: '<S6>/Discrete Transfer Fcn'
     *  Gain: '<S3>/omega_gain'
     *  Gain: '<S3>/to Volts'
     *  MATLABSystem: '<S3>/Analog Input'
     *  Sum: '<S2>/Add1'
     *  Sum: '<S3>/Add'
     */
    rtDW.Integrator_DSTATE += (((0.0008056640625 * rtb_word_h_0) * 0.5) + 1.0) -
      numAccum;
  }

  rate_scheduler();
}

/* Model initialize function */
void uC_code_initialize(void)
{
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
    pinname = PA_1;
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
    pinname = PA_0;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(pinname, 0);
    rtDW.obj_n.isSetupComplete = true;

    /* Start for S-Function (discreteNLastSamples): '<S9>/S-Function ' */

    /* S-Function Block: <S9>/S-Function  */
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

    /* Start for S-Function (discreteNLastSamples): '<S10>/S-Function ' */

    /* S-Function Block: <S10>/S-Function  */
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
    pinname = PB_0;
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
    pinname = PA_3;
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
    pinname = PC_0;
    obj_0->MW_ANALOGIN_HANDLE = MW_AnalogInSingle_Open(pinname);
    trigger_val = MW_ANALOGIN_SOFTWARE_TRIGGER;
    MW_AnalogIn_SetTriggerSource(rtDW.obj.MW_ANALOGIN_HANDLE, trigger_val, 0U);
    rtDW.obj.isSetupComplete = true;

    /* InitializeConditions for S-Function (sdspcount2): '<S5>/Counter' */
    rtDW.Counter_ClkEphState = 5U;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
