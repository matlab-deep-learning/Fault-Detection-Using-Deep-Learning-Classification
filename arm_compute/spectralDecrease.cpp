//
// File: spectralDecrease.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 08-May-2020 10:27:24
//

// Include Files
#include "spectralDecrease.h"
#include "DeepLearningNetwork.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"

// Function Definitions

//
// Arguments    : const float x_data[]
//                const int x_size[2]
//                float decrease_data[]
//                int decrease_size[1]
// Return Type  : void
//
void spectralDecrease(const float x_data[], const int x_size[2], float
                      decrease_data[], int decrease_size[1])
{
  signed char csz_idx_1;
  int k;
  int d_size_idx_1;
  float c_data[256];
  float b_c_data[256];
  float f;
  int npages;
  float d_data[1];
  float y_data[1];
  csz_idx_1 = static_cast<signed char>(x_size[1] == 1);
  if (csz_idx_1 != 0) {
    for (k = 0; k < 256; k++) {
      c_data[k] = x_data[k + 1] - x_data[0];
    }
  }

  if (csz_idx_1 == 0) {
    d_size_idx_1 = 0;
  } else {
    for (k = 0; k < 256; k++) {
      b_c_data[k] = c_data[k] / (static_cast<float>(k) + 1.0F);
    }

    d_size_idx_1 = 1;
    f = b_c_data[0];
    for (k = 0; k < 255; k++) {
      f += b_c_data[k + 1];
    }

    d_data[0] = f;
  }

  if (x_size[1] != 0) {
    npages = x_size[1] - 1;
    for (int xi = 0; xi <= npages; xi++) {
      f = x_data[1];
      for (k = 0; k < 255; k++) {
        f += x_data[((k + 1) % 256 + 257 * ((k + 1) / 256)) + 1];
      }

      y_data[0] = f;
    }
  }

  npages = d_size_idx_1 - 1;
  for (k = 0; k <= npages; k++) {
    d_data[0] /= y_data[0];
  }

  decrease_size[0] = d_size_idx_1;
  if (0 <= d_size_idx_1 - 1) {
    decrease_data[0] = d_data[0];
  }
}

//
// File trailer for spectralDecrease.cpp
//
// [EOF]
//
