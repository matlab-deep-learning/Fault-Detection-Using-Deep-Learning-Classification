//
// File: spectralFlatness.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 20-Mar-2020 02:48:33
//

// Include Files
#include "spectralFlatness.h"
#include "DeepLearningNetwork.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const float x_data[]
//                const int x_size[2]
//                float flatness_data[]
//                int flatness_size[1]
// Return Type  : void
//
void spectralFlatness(const float x_data[], const int x_size[2], float
                      flatness_data[], int flatness_size[1])
{
  int nx;
  int k;
  float b_x_data[257];
  int g_size_idx_1;
  float f;
  float g_data[1];
  float y_data[1];
  nx = x_size[0] * x_size[1];
  for (k = 0; k < nx; k++) {
    b_x_data[k] = x_data[k] + 1.1920929E-7F;
  }

  nx = 257 * x_size[1];
  for (k = 0; k < nx; k++) {
    b_x_data[k] = std::log(b_x_data[k]);
  }

  if (x_size[1] == 0) {
    g_size_idx_1 = 0;
  } else {
    g_size_idx_1 = 1;
    f = b_x_data[0];
    for (k = 0; k < 256; k++) {
      f += b_x_data[k + 1];
    }

    g_data[0] = f;
  }

  nx = g_size_idx_1 - 1;
  for (k = 0; k <= nx; k++) {
    g_data[0] /= 257.0F;
  }

  for (k = 0; k < g_size_idx_1; k++) {
    g_data[0] = std::exp(g_data[0]);
  }

  if (x_size[1] != 0) {
    f = x_data[0];
    for (k = 0; k < 256; k++) {
      f += x_data[k + 1];
    }

    y_data[0] = f;
  }

  nx = g_size_idx_1 - 1;
  for (k = 0; k <= nx; k++) {
    g_data[0] /= y_data[0] / 257.0F;
  }

  flatness_size[0] = g_size_idx_1;
  if (0 <= g_size_idx_1 - 1) {
    flatness_data[0] = g_data[0];
  }
}

//
// File trailer for spectralFlatness.cpp
//
// [EOF]
//
