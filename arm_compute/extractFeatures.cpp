//
// File: extractFeatures.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 08-May-2020 10:27:24
//

// Include Files
#include "extractFeatures.h"
#include "DeepLearningNetwork.h"
#include "STFTCG.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "spectralCentroid.h"
#include "spectralCrest.h"
#include "spectralDecrease.h"
#include "spectralEntropy.h"
#include "spectralFlatness.h"
#include "spectralKurtosis.h"
#include "spectralRolloffPoint.h"
#include "spectralSkewness.h"
#include "spectralSlope.h"
#include "spectralSpread.h"
#include "streamingClassifier.h"
#include <cstring>

// Variable Definitions
static dsp_private_STFTCG stf;
static bool stf_not_empty;
static double F[257];

// Function Definitions

//
// Arguments    : const float audioIn[256]
//                float features_data[]
//                int features_size[2]
// Return Type  : void
//
void extractFeatures(const float audioIn[256], float features_data[], int
                     features_size[2])
{
  creal32_T Xcomp_data[512];
  int Xcomp_size[2];
  int loop_ub;
  int X_size[2];
  int i;
  int tmp_size_idx_1;
  float X_data[257];
  float tmp_data[1];
  float S4_data[1];
  int S4_size[1];
  double S8_data[1];
  int S8_size[1];
  int tmp_size[1];
  float b_tmp_data[1];
  int b_tmp_size[1];
  float c_tmp_data[1];
  int c_tmp_size[1];
  float d_tmp_data[1];
  int d_tmp_size[1];
  float e_tmp_data[1];
  int e_tmp_size[1];
  float f_tmp_data[1];
  int f_tmp_size[1];
  float g_tmp_data[1];
  int g_tmp_size[1];
  float h_tmp_data[1];
  int h_tmp_size[1];

  //    Copyright 2020 The MathWorks, Inc.
  if (!stf_not_empty) {
    //  Setup a short time fourier transform object
    stf.init();
    stf_not_empty = true;
  }

  stf.parenReference(audioIn, Xcomp_data, Xcomp_size);

  //  Get power spectrum
  //  Normalize by window power
  loop_ub = Xcomp_size[1];
  X_size[0] = 257;
  X_size[1] = Xcomp_size[1];
  for (i = 0; i < loop_ub; i++) {
    for (tmp_size_idx_1 = 0; tmp_size_idx_1 < 257; tmp_size_idx_1++) {
      int X_data_tmp;
      X_data_tmp = tmp_size_idx_1 + 512 * i;
      X_data[tmp_size_idx_1 + 257 * i] = (Xcomp_data[X_data_tmp].re *
        Xcomp_data[X_data_tmp].re - Xcomp_data[X_data_tmp].im *
        -Xcomp_data[X_data_tmp].im) * 2.61639052E-5F;
    }
  }

  loop_ub = Xcomp_size[1] - 1;
  tmp_size_idx_1 = Xcomp_size[1];
  for (i = 0; i <= loop_ub; i++) {
    tmp_data[i] = 0.5F * X_data[257 * i];
  }

  for (i = 0; i < tmp_size_idx_1; i++) {
    X_data[257 * i] = tmp_data[i];
  }

  loop_ub = Xcomp_size[1] - 1;
  tmp_size_idx_1 = Xcomp_size[1];
  for (i = 0; i <= loop_ub; i++) {
    tmp_data[i] = 0.5F * X_data[257 * i + 256];
  }

  for (i = 0; i < tmp_size_idx_1; i++) {
    X_data[257 * i + 256] = tmp_data[i];
  }

  spectralEntropy(X_data, X_size, S4_data, S4_size);

  //      S6 = spectralFlux(X,F);
  spectralRolloffPoint(X_data, X_size, F, S8_data, S8_size);
  spectralCentroid(X_data, X_size, F, tmp_data, tmp_size);
  spectralCrest(X_data, X_size, b_tmp_data, b_tmp_size);
  spectralDecrease(X_data, X_size, c_tmp_data, c_tmp_size);
  spectralFlatness(X_data, X_size, d_tmp_data, d_tmp_size);
  spectralKurtosis(X_data, X_size, F, e_tmp_data, e_tmp_size);
  spectralSkewness(X_data, X_size, F, f_tmp_data, f_tmp_size);
  spectralSlope(X_data, X_size, F, g_tmp_data, g_tmp_size);
  spectralSpread(X_data, X_size, F, h_tmp_data, h_tmp_size);
  features_size[0] = tmp_size[0];
  features_size[1] = 10;
  loop_ub = tmp_size[0];
  if (0 <= loop_ub - 1) {
    std::memcpy(&features_data[0], &tmp_data[0], loop_ub * sizeof(float));
  }

  loop_ub = b_tmp_size[0];
  for (i = 0; i < loop_ub; i++) {
    features_data[i + features_size[0]] = b_tmp_data[i];
  }

  loop_ub = c_tmp_size[0];
  for (i = 0; i < loop_ub; i++) {
    features_data[i + features_size[0] * 2] = c_tmp_data[i];
  }

  loop_ub = S4_size[0];
  for (i = 0; i < loop_ub; i++) {
    features_data[i + features_size[0] * 3] = S4_data[i];
  }

  loop_ub = d_tmp_size[0];
  for (i = 0; i < loop_ub; i++) {
    features_data[i + features_size[0] * 4] = d_tmp_data[i];
  }

  loop_ub = e_tmp_size[0];
  for (i = 0; i < loop_ub; i++) {
    features_data[i + features_size[0] * 5] = e_tmp_data[i];
  }

  loop_ub = S8_size[0];
  for (i = 0; i < loop_ub; i++) {
    features_data[i + features_size[0] * 6] = static_cast<float>(S8_data[i]);
  }

  loop_ub = f_tmp_size[0];
  for (i = 0; i < loop_ub; i++) {
    features_data[i + features_size[0] * 7] = f_tmp_data[i];
  }

  loop_ub = g_tmp_size[0];
  for (i = 0; i < loop_ub; i++) {
    features_data[i + features_size[0] * 8] = g_tmp_data[i];
  }

  loop_ub = h_tmp_size[0];
  for (i = 0; i < loop_ub; i++) {
    features_data[i + features_size[0] * 9] = h_tmp_data[i];
  }
}

//
// Arguments    : void
// Return Type  : void
//
void extractFeatures_free()
{
  stf.matlabCodegenDestructor();
  stf.pObj.matlabCodegenDestructor();
  stf.pObj.pBuff.matlabCodegenDestructor();
  stf.pObj.pBuff.pBuffer.matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
void extractFeatures_init()
{
  stf_not_empty = false;
  stf.pObj.pBuff.pBuffer.matlabCodegenIsDeleted = true;
  stf.pObj.pBuff.matlabCodegenIsDeleted = true;
  stf.pObj.matlabCodegenIsDeleted = true;
  stf.matlabCodegenIsDeleted = true;
  for (int i = 0; i < 257; i++) {
    F[i] = 31.25 * static_cast<double>(i);
  }
}

//
// File trailer for extractFeatures.cpp
//
// [EOF]
//
