//
// File: spectralSpread.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 20-Mar-2020 02:48:33
//

// Include Files
#include "spectralSpread.h"
#include "DeepLearningNetwork.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const float x_data[]
//                const int x_size[2]
//                const double f[257]
//                float s_data[]
//                int s_size[1]
// Return Type  : void
//
void spectralSpread(const float x_data[], const int x_size[2], const double f
                    [257], float s_data[], int s_size[1])
{
  float b_f;
  int k;
  int spread_size_idx_1;
  float y_tmp_data[1];
  float c_data[257];
  int nx;
  float spread_data[1];
  float y_data[257];
  if (x_size[1] != 0) {
    b_f = x_data[0];
    for (k = 0; k < 256; k++) {
      b_f += x_data[k + 1];
    }

    y_tmp_data[0] = b_f;
  }

  if (static_cast<signed char>(x_size[1]) == 0) {
    spread_size_idx_1 = 0;
  } else {
    for (k = 0; k < 257; k++) {
      c_data[k] = x_data[k] * static_cast<float>(f[k]);
    }

    spread_size_idx_1 = 1;
    b_f = c_data[0];
    for (k = 0; k < 256; k++) {
      b_f += c_data[k + 1];
    }

    spread_data[0] = b_f;
  }

  nx = spread_size_idx_1 - 1;
  for (k = 0; k <= nx; k++) {
    spread_data[0] /= y_tmp_data[0];
  }

  if (spread_size_idx_1 != 0) {
    for (k = 0; k < 257; k++) {
      c_data[k] = static_cast<float>(f[k]) - spread_data[0];
    }
  }

  nx = 257 * spread_size_idx_1;
  for (k = 0; k < nx; k++) {
    y_data[k] = c_data[k] * c_data[k];
  }

  nx = 257 * spread_size_idx_1;
  for (k = 0; k < nx; k++) {
    y_data[k] *= x_data[k];
  }

  if (spread_size_idx_1 == 0) {
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

  s_size[0] = spread_size_idx_1;
  if (0 <= spread_size_idx_1 - 1) {
    s_data[0] = spread_data[0];
  }
}

//
// File trailer for spectralSpread.cpp
//
// [EOF]
//
