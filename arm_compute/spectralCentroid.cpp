//
// File: spectralCentroid.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 20-Mar-2020 02:48:33
//

// Include Files
#include "spectralCentroid.h"
#include "DeepLearningNetwork.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"

// Function Definitions

//
// Arguments    : const float x_data[]
//                const int x_size[2]
//                const double f[257]
//                float c_data[]
//                int c_size[1]
// Return Type  : void
//
void spectralCentroid(const float x_data[], const int x_size[2], const double f
                      [257], float c_data[], int c_size[1])
{
  int k;
  int centroid_size_idx_1;
  float b_c_data[257];
  float b_f;
  float centroid_data[1];
  float y_data[1];
  if (static_cast<signed char>(x_size[1]) == 0) {
    centroid_size_idx_1 = 0;
  } else {
    for (k = 0; k < 257; k++) {
      b_c_data[k] = x_data[k] * static_cast<float>(f[k]);
    }

    centroid_size_idx_1 = 1;
    b_f = b_c_data[0];
    for (k = 0; k < 256; k++) {
      b_f += b_c_data[k + 1];
    }

    centroid_data[0] = b_f;
  }

  if (x_size[1] != 0) {
    b_f = x_data[0];
    for (k = 0; k < 256; k++) {
      b_f += x_data[k + 1];
    }

    y_data[0] = b_f;
  }

  k = centroid_size_idx_1 - 1;
  for (int i = 0; i <= k; i++) {
    centroid_data[0] /= y_data[0];
  }

  c_size[0] = centroid_size_idx_1;
  if (0 <= centroid_size_idx_1 - 1) {
    c_data[0] = centroid_data[0];
  }
}

//
// File trailer for spectralCentroid.cpp
//
// [EOF]
//
