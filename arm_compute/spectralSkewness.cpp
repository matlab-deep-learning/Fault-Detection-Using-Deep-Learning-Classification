//
// File: spectralSkewness.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 08-May-2020 10:27:24
//

// Include Files
#include "spectralSkewness.h"
#include "DeepLearningNetwork.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"
#include "streamingClassifier_rtwutil.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const float x_data[]
//                const int x_size[2]
//                const double f[257]
//                float sk_data[]
//                int sk_size[1]
// Return Type  : void
//
void spectralSkewness(const float x_data[], const int x_size[2], const double f
                      [257], float sk_data[], int sk_size[1])
{
  float b_f;
  int k;
  int y_size_idx_1;
  float y_tmp_data[1];
  float temp_data[257];
  int nx;
  float spread_data[1];
  float y_data[257];
  int spread_size_idx_1;
  float skewness_data[1];
  if (x_size[1] != 0) {
    b_f = x_data[0];
    for (k = 0; k < 256; k++) {
      b_f += x_data[k + 1];
    }

    y_tmp_data[0] = b_f;
  }

  if (static_cast<signed char>(x_size[1]) == 0) {
    y_size_idx_1 = 0;
  } else {
    for (k = 0; k < 257; k++) {
      temp_data[k] = x_data[k] * static_cast<float>(f[k]);
    }

    y_size_idx_1 = 1;
    b_f = temp_data[0];
    for (k = 0; k < 256; k++) {
      b_f += temp_data[k + 1];
    }

    spread_data[0] = b_f;
  }

  nx = y_size_idx_1 - 1;
  for (k = 0; k <= nx; k++) {
    spread_data[0] /= y_tmp_data[0];
  }

  if (y_size_idx_1 != 0) {
    for (k = 0; k < 257; k++) {
      temp_data[k] = static_cast<float>(f[k]) - spread_data[0];
    }
  }

  nx = 257 * y_size_idx_1;
  for (k = 0; k < nx; k++) {
    y_data[k] = temp_data[k] * temp_data[k];
  }

  nx = 257 * y_size_idx_1;
  for (k = 0; k < nx; k++) {
    y_data[k] *= x_data[k];
  }

  if (y_size_idx_1 == 0) {
    spread_size_idx_1 = 0;
  } else {
    spread_size_idx_1 = 1;
    b_f = y_data[0];
    for (k = 0; k < 256; k++) {
      b_f += y_data[k + 1];
    }

    spread_data[0] = b_f;
  }

  nx = spread_size_idx_1 - 1;
  for (k = 0; k <= nx; k++) {
    spread_data[0] /= y_tmp_data[0];
  }

  for (k = 0; k < spread_size_idx_1; k++) {
    spread_data[0] = std::sqrt(spread_data[0]);
  }

  nx = 257 * y_size_idx_1;
  for (k = 0; k < nx; k++) {
    y_data[k] = rt_powf_snf(temp_data[k], 3.0F);
  }

  nx = 257 * y_size_idx_1;
  for (k = 0; k < nx; k++) {
    y_data[k] *= x_data[k];
  }

  if (y_size_idx_1 == 0) {
    y_size_idx_1 = 0;
  } else {
    y_size_idx_1 = 1;
    b_f = y_data[0];
    for (k = 0; k < 256; k++) {
      b_f += y_data[k + 1];
    }

    skewness_data[0] = b_f;
  }

  if (0 <= spread_size_idx_1 - 1) {
    spread_data[0] = rt_powf_snf(spread_data[0], 3.0F);
  }

  nx = y_size_idx_1 - 1;
  for (k = 0; k <= nx; k++) {
    skewness_data[0] /= spread_data[0] * y_tmp_data[0];
  }

  sk_size[0] = y_size_idx_1;
  if (0 <= y_size_idx_1 - 1) {
    sk_data[0] = skewness_data[0];
  }
}

//
// File trailer for spectralSkewness.cpp
//
// [EOF]
//
