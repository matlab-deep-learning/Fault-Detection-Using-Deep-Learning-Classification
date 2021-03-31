//
// File: _coder_streamingClassifier_mex.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 19-Mar-2021 15:00:36
//

#ifndef _CODER_STREAMINGCLASSIFIER_MEX_H
#define _CODER_STREAMINGCLASSIFIER_MEX_H

// Include Files
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

// Function Declarations
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS();

void unsafe_streamingClassifier_mexFunction(int32_T nlhs, mxArray *plhs[2],
                                            int32_T nrhs,
                                            const mxArray *prhs[3]);

#endif
//
// File trailer for _coder_streamingClassifier_mex.h
//
// [EOF]
//
