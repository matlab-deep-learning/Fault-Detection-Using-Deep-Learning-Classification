//
// File: _coder_streamingClassifier_api.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 19-Mar-2021 15:00:36
//

#ifndef _CODER_STREAMINGCLASSIFIER_API_H
#define _CODER_STREAMINGCLASSIFIER_API_H

// Include Files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void streamingClassifier(real32_T audioIn[512], real32_T M[10], real32_T S[10],
                         real32_T scores[8], real32_T features[10]);

void streamingClassifier_api(const mxArray *const prhs[3], int32_T nlhs,
                             const mxArray *plhs[2]);

void streamingClassifier_atexit();

void streamingClassifier_initialize();

void streamingClassifier_terminate();

void streamingClassifier_xil_shutdown();

void streamingClassifier_xil_terminate();

#endif
//
// File trailer for _coder_streamingClassifier_api.h
//
// [EOF]
//
