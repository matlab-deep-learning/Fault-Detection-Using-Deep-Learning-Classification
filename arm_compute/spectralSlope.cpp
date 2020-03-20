//
// File: spectralSlope.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 20-Mar-2020 02:48:33
//

// Include Files
#include "spectralSlope.h"
#include "DeepLearningNetwork.h"
#include "bsxfun.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"
#include "sum.h"
#include <cstring>

// Function Definitions

//
// Arguments    : const float x_data[]
//                const int x_size[2]
//                const double f[257]
//                float slope_data[]
//                int slope_size[1]
// Return Type  : void
//
void spectralSlope(const float x_data[], const int x_size[2], const double f[257],
                   float slope_data[], int slope_size[1])
{
  double y;
  int k;
  double x[257];
  double f_minus_mu_f[257];
  float s_data[1];
  int s_size[2];
  int b_s_size[2];
  int i;
  float b_s_data[1];
  float tmp_data[257];
  float b_tmp_data[257];
  y = f[0];
  for (k = 0; k < 256; k++) {
    y += f[k + 1];
  }

  for (k = 0; k < 257; k++) {
    double d;
    d = f[k] - y / 257.0;
    f_minus_mu_f[k] = d;
    x[k] = d * d;
  }

  y = x[0];
  for (k = 0; k < 256; k++) {
    y += x[k + 1];
  }

  sum(x_data, x_size, s_data, s_size);
  b_s_size[0] = 1;
  b_s_size[1] = s_size[1];
  k = s_size[0] * s_size[1];
  for (i = 0; i < k; i++) {
    b_s_data[i] = s_data[i] / 257.0F;
  }

  b_bsxfun(x_data, x_size, b_s_data, b_s_size, tmp_data, s_size);
  bsxfun(tmp_data, s_size, f_minus_mu_f, b_tmp_data, b_s_size);
  sum(b_tmp_data, b_s_size, s_data, s_size);
  k = s_size[0] * s_size[1] - 1;
  for (i = 0; i <= k; i++) {
    s_data[i] /= static_cast<float>(y);
  }

  slope_size[0] = s_size[1];
  k = s_size[1];
  if (0 <= k - 1) {
    std::memcpy(&slope_data[0], &s_data[0], k * sizeof(float));
  }
}

//
// File trailer for spectralSlope.cpp
//
// [EOF]
//
