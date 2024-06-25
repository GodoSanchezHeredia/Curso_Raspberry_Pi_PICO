/*
 * File: untitled1.c
 *
 * Code generated for Simulink model 'untitled1'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Wed Jun 19 12:41:05 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "untitled1.h"
#include "rtwtypes.h"
#include "untitled1_types.h"
#include "untitled1_private.h"

/* Block states (default storage) */
DW_untitled1_T untitled1_DW;

/* Real-time model */
static RT_MODEL_untitled1_T untitled1_M_;
RT_MODEL_untitled1_T *const untitled1_M = &untitled1_M_;

/* Model step function */
void untitled1_step(void)
{
  real_T acc1;
  real_T rtb_Filter1;
  real_T zCurr;
  int32_T k;
  int32_T n;

  /* MATLABSystem: '<Root>/Analog Input' */
  if (untitled1_DW.obj.SampleTime != untitled1_P.AnalogInput_SampleTime) {
    untitled1_DW.obj.SampleTime = untitled1_P.AnalogInput_SampleTime;
  }

  MW_AnalogIn_Start(untitled1_DW.obj.MW_ANALOGIN_HANDLE);

  /* DiscreteFir: '<Root>/Filter1' incorporates:
   *  MATLABSystem: '<Root>/Analog Input'
   */
  MW_AnalogInSingle_ReadResult(untitled1_DW.obj.MW_ANALOGIN_HANDLE, &rtb_Filter1,
    7);
  for (k = 0; k < 1; k++) {
    acc1 = 0.0;

    /* load input sample */
    for (n = 0; n < 50; n++) {
      /* shift state */
      zCurr = rtb_Filter1;
      rtb_Filter1 = untitled1_DW.Filter1_states[n];
      untitled1_DW.Filter1_states[n] = zCurr;

      /* compute one tap */
      acc1 += untitled1_P.Filter1_Coefficients[n] * zCurr;
    }

    /* compute last tap */
    /* store output sample */
    rtb_Filter1 = untitled1_P.Filter1_Coefficients[n] * rtb_Filter1 + acc1;
  }

  /* End of DiscreteFir: '<Root>/Filter1' */

  /* MATLABSystem: '<Root>/Analog Output' */
  MW_AnalogOut_Write(untitled1_DW.obj_g.MW_ANALOGOUT_HANDLE, (real32_T)
                     rtb_Filter1);

  {                                    /* Sample time: [0.01s, 0.0s] */
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  untitled1_M->Timing.taskTime0 =
    ((time_T)(++untitled1_M->Timing.clockTick0)) * untitled1_M->Timing.stepSize0;
}

/* Model initialize function */
void untitled1_initialize(void)
{
  /* Registration code */
  rtmSetTFinal(untitled1_M, -1);
  untitled1_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  untitled1_M->Sizes.checksums[0] = (3952341556U);
  untitled1_M->Sizes.checksums[1] = (3872809052U);
  untitled1_M->Sizes.checksums[2] = (2554917779U);
  untitled1_M->Sizes.checksums[3] = (2468923831U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[3];
    untitled1_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(untitled1_M->extModeInfo,
      &untitled1_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(untitled1_M->extModeInfo, untitled1_M->Sizes.checksums);
    rteiSetTPtr(untitled1_M->extModeInfo, rtmGetTPtr(untitled1_M));
  }

  {
    MW_AnalogIn_TriggerSource_Type trigger_val;
    uint32_T pinname;
    mbed_AnalogInput_untitled1_T *obj;
    mbed_AnalogOutput_untitled1_T *obj_0;
    int32_T i;

    /* InitializeConditions for DiscreteFir: '<Root>/Filter1' */
    for (i = 0; i < 50; i++) {
      untitled1_DW.Filter1_states[i] = untitled1_P.Filter1_InitialStates;
    }

    /* End of InitializeConditions for DiscreteFir: '<Root>/Filter1' */

    /* Start for MATLABSystem: '<Root>/Analog Input' */
    untitled1_DW.obj.matlabCodegenIsDeleted = false;
    untitled1_DW.obj.SampleTime = untitled1_P.AnalogInput_SampleTime;
    obj = &untitled1_DW.obj;
    untitled1_DW.obj.isInitialized = 1;
    pinname = A0;
    obj->MW_ANALOGIN_HANDLE = MW_AnalogInSingle_Open(pinname);
    trigger_val = MW_ANALOGIN_SOFTWARE_TRIGGER;
    MW_AnalogIn_SetTriggerSource(untitled1_DW.obj.MW_ANALOGIN_HANDLE,
      trigger_val, 0U);
    untitled1_DW.obj.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Analog Output' */
    untitled1_DW.obj_g.matlabCodegenIsDeleted = false;
    obj_0 = &untitled1_DW.obj_g;
    untitled1_DW.obj_g.isInitialized = 1;
    pinname = PA_5;
    untitled1_DW.obj_g.MW_ANALOGOUT_HANDLE = NULL;
    obj_0->MW_ANALOGOUT_HANDLE = MW_AnalogOut_Open(pinname);
    untitled1_DW.obj_g.isSetupComplete = true;
  }
}

/* Model terminate function */
void untitled1_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Analog Input' */
  if (!untitled1_DW.obj.matlabCodegenIsDeleted) {
    untitled1_DW.obj.matlabCodegenIsDeleted = true;
    if ((untitled1_DW.obj.isInitialized == 1) &&
        untitled1_DW.obj.isSetupComplete) {
      MW_AnalogIn_Stop(untitled1_DW.obj.MW_ANALOGIN_HANDLE);
      MW_AnalogIn_Close(untitled1_DW.obj.MW_ANALOGIN_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Analog Input' */

  /* Terminate for MATLABSystem: '<Root>/Analog Output' */
  if (!untitled1_DW.obj_g.matlabCodegenIsDeleted) {
    untitled1_DW.obj_g.matlabCodegenIsDeleted = true;
    if ((untitled1_DW.obj_g.isInitialized == 1) &&
        untitled1_DW.obj_g.isSetupComplete) {
      MW_AnalogOut_Close(untitled1_DW.obj_g.MW_ANALOGOUT_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Analog Output' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
