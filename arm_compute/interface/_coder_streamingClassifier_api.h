/*
 * File: _coder_streamingClassifier_api.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 08-May-2020 10:27:24
 */

#ifndef _CODER_STREAMINGCLASSIFIER_API_H
#define _CODER_STREAMINGCLASSIFIER_API_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void streamingClassifier(real32_T audioIn[256], real32_T M[10], real32_T
  S[10], real32_T scores[8], real32_T features[10]);
extern void streamingClassifier_api(const mxArray * const prhs[3], int32_T nlhs,
  const mxArray *plhs[2]);
extern void streamingClassifier_atexit(void);
extern void streamingClassifier_initialize(void);
extern void streamingClassifier_terminate(void);
extern void streamingClassifier_xil_shutdown(void);
extern void streamingClassifier_xil_terminate(void);

#endif

/*
 * File trailer for _coder_streamingClassifier_api.h
 *
 * [EOF]
 */
