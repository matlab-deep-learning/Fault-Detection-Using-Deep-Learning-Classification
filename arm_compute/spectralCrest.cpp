//
// File: spectralCrest.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 20-Mar-2020 02:48:33
//

// Include Files
#include "spectralCrest.h"
#include "DeepLearningNetwork.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"
#include <cstring>

// Function Definitions

//
// Arguments    : const float x_data[]
//                const int x_size[2]
//                float crest_data[]
//                int crest_size[1]
// Return Type  : void
//
void spectralCrest(const float x_data[], const int x_size[2], float crest_data[],
                   int crest_size[1])
{
  int p_size_idx_1;
  float a;
  int i;
  float p_data[1];
  float y_data[1];
  p_size_idx_1 = x_size[1];
  if (x_size[1] >= 1) {
    a = x_data[0];
    for (i = 0; i < 256; i++) {
      float b;
      b = x_data[i + 1];
      if ((!rtIsNaNF(b)) && (rtIsNaNF(a) || (a < b))) {
        a = b;
      }
    }

    p_data[0] = a;
  }

  if (x_size[1] != 0) {
    a = x_data[0];
    for (i = 0; i < 256; i++) {
      a += x_data[i + 1];
    }

    y_data[0] = a;
  }

  i = x_size[1] - 1;
  for (int b_i = 0; b_i <= i; b_i++) {
    p_data[b_i] /= y_data[b_i] / 257.0F;
  }

  crest_size[0] = x_size[1];
  if (0 <= p_size_idx_1 - 1) {
    std::memcpy(&crest_data[0], &p_data[0], p_size_idx_1 * sizeof(float));
  }
}

//
// File trailer for spectralCrest.cpp
//
// [EOF]
//
