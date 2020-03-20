//
// File: spectralEntropy.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 20-Mar-2020 02:48:33
//

// Include Files
#include "spectralEntropy.h"
#include "DeepLearningNetwork.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const float x_data[]
//                const int x_size[2]
//                float entropy_data[]
//                int entropy_size[1]
// Return Type  : void
//
void spectralEntropy(const float x_data[], const int x_size[2], float
                     entropy_data[], int entropy_size[1])
{
  int e_size_idx_1;
  float t;
  int k;
  int nx;
  float e_data[1];
  float X_data[257];
  float tmp_data[257];
  int eint;
  if (x_size[1] == 0) {
    e_size_idx_1 = 0;
  } else {
    e_size_idx_1 = 1;
    t = x_data[0];
    for (k = 0; k < 256; k++) {
      t += x_data[k + 1];
    }

    e_data[0] = t;
  }

  if (0 <= e_size_idx_1 - 1) {
    for (nx = 0; nx < 257; nx++) {
      X_data[nx] = e_data[0];
    }
  }

  nx = x_size[0] * x_size[1];
  for (k = 0; k < nx; k++) {
    X_data[k] = x_data[k] / X_data[k];
  }

  nx = 257 * x_size[1];
  for (k = 0; k < nx; k++) {
    if (X_data[k] == 0.0F) {
      tmp_data[k] = rtMinusInfF;
    } else if (X_data[k] < 0.0F) {
      tmp_data[k] = rtNaNF;
    } else {
      bool b;
      bool b1;
      b = !rtIsInfF(X_data[k]);
      b1 = !rtIsNaNF(X_data[k]);
      if (b && b1) {
        float inte;
        t = std::frexp(X_data[k], &eint);
        inte = static_cast<float>(eint);
        if (t == 0.5F) {
          tmp_data[k] = inte - 1.0F;
        } else if ((inte == 1.0F) && (t < 0.75F)) {
          tmp_data[k] = std::log(2.0F * t) / 0.693147182F;
        } else {
          tmp_data[k] = std::log(t) / 0.693147182F + inte;
        }
      } else {
        tmp_data[k] = X_data[k];
      }
    }
  }

  nx = 257 * x_size[1];
  for (k = 0; k < nx; k++) {
    X_data[k] *= tmp_data[k];
  }

  if (x_size[1] == 0) {
    e_size_idx_1 = 0;
  } else {
    e_size_idx_1 = 1;
    if (rtIsNaNF(X_data[0])) {
      e_data[0] = 0.0F;
    } else {
      e_data[0] = X_data[0];
    }

    for (k = 0; k < 256; k++) {
      t = X_data[k + 1];
      if (!rtIsNaNF(t)) {
        e_data[0] += t;
      }
    }
  }

  nx = e_size_idx_1 - 1;
  for (k = 0; k <= nx; k++) {
    e_data[0] = -e_data[0] / 8.00562477F;
  }

  entropy_size[0] = e_size_idx_1;
  if (0 <= e_size_idx_1 - 1) {
    entropy_data[0] = e_data[0];
  }
}

//
// File trailer for spectralEntropy.cpp
//
// [EOF]
//
