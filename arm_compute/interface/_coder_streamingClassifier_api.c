/*
 * File: _coder_streamingClassifier_api.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 08-May-2020 10:27:24
 */

/* Include Files */
#include "_coder_streamingClassifier_api.h"
#include "_coder_streamingClassifier_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131594U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "streamingClassifier",               /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static real32_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[256];
static const mxArray *b_emlrt_marshallOut(const real32_T u[10]);
static real32_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *M,
  const char_T *identifier))[10];
static real32_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[10];
static real32_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[256];
static real32_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *audioIn,
  const char_T *identifier))[256];
static const mxArray *emlrt_marshallOut(const real32_T u[8]);
static real32_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[10];

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real32_T (*)[256]
 */
static real32_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[256]
{
  real32_T (*y)[256];
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const real32_T u[10]
 * Return Type  : const mxArray *
 */
  static const mxArray *b_emlrt_marshallOut(const real32_T u[10])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[1] = { 0 };

  static const int32_T iv1[1] = { 10 };

  y = NULL;
  m = emlrtCreateNumericArray(1, &iv[0], mxSINGLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, *(int32_T (*)[1])&iv1[0], 1);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *M
 *                const char_T *identifier
 * Return Type  : real32_T (*)[10]
 */
static real32_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *M,
  const char_T *identifier))[10]
{
  real32_T (*y)[10];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(M), &thisId);
  emlrtDestroyArray(&M);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real32_T (*)[10]
 */
  static real32_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[10]
{
  real32_T (*y)[10];
  y = f_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real32_T (*)[256]
 */
static real32_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[256]
{
  real32_T (*ret)[256];
  static const int32_T dims[1] = { 256 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "single", false, 1U, dims);
  ret = (real32_T (*)[256])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *audioIn
 *                const char_T *identifier
 * Return Type  : real32_T (*)[256]
 */
  static real32_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *audioIn, const char_T *identifier))[256]
{
  real32_T (*y)[256];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(audioIn), &thisId);
  emlrtDestroyArray(&audioIn);
  return y;
}

/*
 * Arguments    : const real32_T u[8]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real32_T u[8])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 0, 0 };

  static const int32_T iv1[2] = { 1, 8 };

  y = NULL;
  m = emlrtCreateNumericArray(2, &iv[0], mxSINGLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, *(int32_T (*)[2])&iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real32_T (*)[10]
 */
static real32_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[10]
{
  real32_T (*ret)[10];
  static const int32_T dims[2] = { 1, 10 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "single", false, 2U, dims);
  ret = (real32_T (*)[10])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const mxArray * const prhs[3]
 *                int32_T nlhs
 *                const mxArray *plhs[2]
 * Return Type  : void
 */
  void streamingClassifier_api(const mxArray * const prhs[3], int32_T nlhs,
  const mxArray *plhs[2])
{
  real32_T (*scores)[8];
  real32_T (*features)[10];
  real32_T (*audioIn)[256];
  real32_T (*M)[10];
  real32_T (*S)[10];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  scores = (real32_T (*)[8])mxMalloc(sizeof(real32_T [8]));
  features = (real32_T (*)[10])mxMalloc(sizeof(real32_T [10]));

  /* Marshall function inputs */
  audioIn = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "audioIn");
  M = c_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "M");
  S = c_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "S");

  /* Invoke the target function */
  streamingClassifier(*audioIn, *M, *S, *scores, *features);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*scores);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(*features);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void streamingClassifier_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  streamingClassifier_xil_terminate();
  streamingClassifier_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void streamingClassifier_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void streamingClassifier_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_streamingClassifier_api.c
 *
 * [EOF]
 */
