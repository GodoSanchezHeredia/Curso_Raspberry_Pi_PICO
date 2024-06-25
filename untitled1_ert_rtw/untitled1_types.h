/*
 * File: untitled1_types.h
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

#ifndef RTW_HEADER_untitled1_types_h_
#define RTW_HEADER_untitled1_types_h_
#include "rtwtypes.h"
#include "MW_SVD.h"

/* Custom Type definition for MATLABSystem: '<Root>/Analog Input' */
#include "MW_SVD.h"
#ifndef struct_tag_p5Oj7yF0nd6COoUgI0GAlG
#define struct_tag_p5Oj7yF0nd6COoUgI0GAlG

struct tag_p5Oj7yF0nd6COoUgI0GAlG
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  MW_Handle_Type MW_ANALOGIN_HANDLE;
  real_T SampleTime;
};

#endif                                 /* struct_tag_p5Oj7yF0nd6COoUgI0GAlG */

#ifndef typedef_mbed_AnalogInput_untitled1_T
#define typedef_mbed_AnalogInput_untitled1_T

typedef struct tag_p5Oj7yF0nd6COoUgI0GAlG mbed_AnalogInput_untitled1_T;

#endif                                /* typedef_mbed_AnalogInput_untitled1_T */

#ifndef struct_tag_LqyuMmJIWYfQ3MCRdlPEPB
#define struct_tag_LqyuMmJIWYfQ3MCRdlPEPB

struct tag_LqyuMmJIWYfQ3MCRdlPEPB
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  MW_Handle_Type MW_ANALOGOUT_HANDLE;
};

#endif                                 /* struct_tag_LqyuMmJIWYfQ3MCRdlPEPB */

#ifndef typedef_mbed_AnalogOutput_untitled1_T
#define typedef_mbed_AnalogOutput_untitled1_T

typedef struct tag_LqyuMmJIWYfQ3MCRdlPEPB mbed_AnalogOutput_untitled1_T;

#endif                               /* typedef_mbed_AnalogOutput_untitled1_T */

/* Parameters (default storage) */
typedef struct P_untitled1_T_ P_untitled1_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_untitled1_T RT_MODEL_untitled1_T;

#endif                                 /* RTW_HEADER_untitled1_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
