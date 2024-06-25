/*
 * File: untitled.c
 *
 * Code generated for Simulink model 'untitled'.
 *
 * Model version                  : 1.1
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Wed Jun 19 12:48:17 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "untitled.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "untitled_private.h"

/* Block signals (default storage) */
B_untitled_T untitled_B;

/* Block states (default storage) */
DW_untitled_T untitled_DW;

/* Real-time model */
static RT_MODEL_untitled_T untitled_M_;
RT_MODEL_untitled_T *const untitled_M = &untitled_M_;

/* Model step function */
void untitled_step(void)
{
  real_T Add2_tmp;

  /* SignalGenerator: '<Root>/Signal Generator' incorporates:
   *  SignalGenerator: '<Root>/Signal Generator1'
   *  SignalGenerator: '<Root>/Signal Generator2'
   */
  Add2_tmp = 6.2831853071795862 * untitled_M->Timing.t[0];

  /* Sum: '<Root>/Add2' incorporates:
   *  Constant: '<Root>/Constant'
   *  SignalGenerator: '<Root>/Signal Generator'
   *  SignalGenerator: '<Root>/Signal Generator1'
   *  SignalGenerator: '<Root>/Signal Generator2'
   *  Sum: '<Root>/Add'
   *  Sum: '<Root>/Add1'
   */
  untitled_B.Add2 = ((sin(Add2_tmp * untitled_P.SignalGenerator_Frequency) *
                      untitled_P.SignalGenerator_Amplitude +
                      untitled_P.Constant_Value) + sin(Add2_tmp *
    untitled_P.SignalGenerator1_Frequency) *
                     untitled_P.SignalGenerator1_Amplitude) + sin(Add2_tmp *
    untitled_P.SignalGenerator2_Frequency) *
    untitled_P.SignalGenerator2_Amplitude;

  /* DataTypeConversion: '<Root>/Data Type Conversion' */
  Add2_tmp = floor(untitled_B.Add2);
  if (rtIsNaN(Add2_tmp) || rtIsInf(Add2_tmp)) {
    Add2_tmp = 0.0;
  } else {
    Add2_tmp = fmod(Add2_tmp, 65536.0);
  }

  /* MATLABSystem: '<Root>/Analog Output' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   */
  MW_DACWrite(1, (uint32_T)(Add2_tmp < 0.0 ? (int32_T)(uint16_T)-(int16_T)
    (uint16_T)-Add2_tmp : (int32_T)(uint16_T)Add2_tmp));

  {                                    /* Sample time: [0.0s, 0.0s] */
    extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
    extmodeSimulationTime_T currentTime = (extmodeSimulationTime_T)
      untitled_M->Timing.t[0];

    /* Trigger External Mode event */
    errorCode = extmodeEvent(0,currentTime);
    if (errorCode != EXTMODE_SUCCESS) {
      /* Code to handle External Mode event errors
         may be added here */
    }
  }

  {                            /* Sample time: [0.0041666666666666666s, 0.0s] */
    extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
    extmodeSimulationTime_T currentTime = (extmodeSimulationTime_T)
      ((untitled_M->Timing.clockTick1) * 0.0041666666666666666);

    /* Trigger External Mode event */
    errorCode = extmodeEvent(1,currentTime);
    if (errorCode != EXTMODE_SUCCESS) {
      /* Code to handle External Mode event errors
         may be added here */
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  untitled_M->Timing.t[0] =
    ((time_T)(++untitled_M->Timing.clockTick0)) * untitled_M->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.0041666666666666666s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.0041666666666666666, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    untitled_M->Timing.clockTick1++;
  }
}

/* Model initialize function */
void untitled_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&untitled_M->solverInfo,
                          &untitled_M->Timing.simTimeStep);
    rtsiSetTPtr(&untitled_M->solverInfo, &rtmGetTPtr(untitled_M));
    rtsiSetStepSizePtr(&untitled_M->solverInfo, &untitled_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&untitled_M->solverInfo, (&rtmGetErrorStatus
      (untitled_M)));
    rtsiSetRTModelPtr(&untitled_M->solverInfo, untitled_M);
  }

  rtsiSetSimTimeStep(&untitled_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&untitled_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(untitled_M, &untitled_M->Timing.tArray[0]);
  rtmSetTFinal(untitled_M, -1);
  untitled_M->Timing.stepSize0 = 0.0041666666666666666;

  /* External mode info */
  untitled_M->Sizes.checksums[0] = (1441200815U);
  untitled_M->Sizes.checksums[1] = (2222823564U);
  untitled_M->Sizes.checksums[2] = (3292768901U);
  untitled_M->Sizes.checksums[3] = (3265086956U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    untitled_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(untitled_M->extModeInfo,
      &untitled_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(untitled_M->extModeInfo, untitled_M->Sizes.checksums);
    rteiSetTPtr(untitled_M->extModeInfo, rtmGetTPtr(untitled_M));
  }
}

/* Model terminate function */
void untitled_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
