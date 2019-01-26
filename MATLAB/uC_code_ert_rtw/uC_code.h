/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uC_code.h
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

#ifndef RTW_HEADER_uC_code_h_
#define RTW_HEADER_uC_code_h_
#include "rtwtypes.h"
#include <stddef.h>
#ifndef uC_code_COMMON_INCLUDES_
# define uC_code_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "MW_AnalogIn.h"
#include "MW_MbedPinInterface.h"
#include "MW_PWM.h"
#include "MW_digitalIO.h"
#endif                                 /* uC_code_COMMON_INCLUDES_ */

#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#define uC_code_M                      (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Custom Type definition for MATLABSystem: '<S5>/ENC_B' */
#include "MW_SVD.h"
#ifndef typedef_mbed_AnalogInput
#define typedef_mbed_AnalogInput

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  MW_Handle_Type MW_ANALOGIN_HANDLE;
  real_T SampleTime;
} mbed_AnalogInput;

#endif                                 /*typedef_mbed_AnalogInput*/

#ifndef typedef_mbed_PWMOutput
#define typedef_mbed_PWMOutput

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  MW_Handle_Type MW_PWM_HANDLE;
} mbed_PWMOutput;

#endif                                 /*typedef_mbed_PWMOutput*/

#ifndef typedef_mbed_DigitalRead
#define typedef_mbed_DigitalRead

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  MW_Handle_Type MW_DIGITALIO_HANDLE;
  real_T SampleTime;
} mbed_DigitalRead;

#endif                                 /*typedef_mbed_DigitalRead*/

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  mbed_AnalogInput obj;                /* '<S3>/Analog Input' */
  mbed_AnalogInput obj_j;              /* '<S1>/Analog Input' */
  mbed_DigitalRead obj_jb;             /* '<S5>/ENC_B' */
  mbed_DigitalRead obj_n;              /* '<S5>/ENC_A' */
  mbed_PWMOutput obj_ni;               /* '<S4>/PWM Output' */
  real_T SFunction[2];                 /* '<S9>/S-Function ' */
  real_T SFunction_f[2];               /* '<S10>/S-Function ' */
  real_T DataTypeConversion1;          /* '<S7>/Data Type Conversion1' */
  real_T DataTypeConversion;           /* '<S7>/Data Type Conversion' */
  real_T DiscreteTransferFcn_states;   /* '<S6>/Discrete Transfer Fcn' */
  real_T Integrator_DSTATE;            /* '<S2>/Integrator' */
  struct {
    int_T indPs;
    int_T bufSz;
  } SFunction_IWORK;                   /* '<S9>/S-Function ' */

  struct {
    int_T indPs;
    int_T bufSz;
  } SFunction_IWORK_d;                 /* '<S10>/S-Function ' */

  uint32_T Counter_ClkEphState;        /* '<S5>/Counter' */
  struct {
    void *uBuffers;
  } SFunction_PWORK;                   /* '<S9>/S-Function ' */

  struct {
    void *uBuffers;
  } SFunction_PWORK_f;                 /* '<S10>/S-Function ' */

  uint8_T Counter_Count;               /* '<S5>/Counter' */
} DW;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint16_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* Model entry point functions */
extern void uC_code_initialize(void);
extern void uC_code_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S7>/XOR' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uC_code'
 * '<S1>'   : 'uC_code/Current from Sensor'
 * '<S2>'   : 'uC_code/LQR control'
 * '<S3>'   : 'uC_code/Omega ref from Sensor'
 * '<S4>'   : 'uC_code/PWM to motor'
 * '<S5>'   : 'uC_code/Speed from ENCODER'
 * '<S6>'   : 'uC_code/Speed from ENCODER/Derivative'
 * '<S7>'   : 'uC_code/Speed from ENCODER/Quadrature Decoder'
 * '<S8>'   : 'uC_code/Speed from ENCODER/Quadrature Decoder/4 wires XOR'
 * '<S9>'   : 'uC_code/Speed from ENCODER/Quadrature Decoder/Discrete Shift Register'
 * '<S10>'  : 'uC_code/Speed from ENCODER/Quadrature Decoder/Discrete Shift Register1'
 */
#endif                                 /* RTW_HEADER_uC_code_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
