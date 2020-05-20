//
// File: spectralRolloffPoint.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 08-May-2020 10:27:24
//

// Include Files
#include "spectralRolloffPoint.h"
#include "DeepLearningNetwork.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"
#include <cstring>

// Function Definitions

//
// Arguments    : const float x_data[]
//                const int x_size[2]
//                const double f[257]
//                double rolloffPoint_data[]
//                int rolloffPoint_size[1]
// Return Type  : void
//
void spectralRolloffPoint(const float x_data[], const int x_size[2], const
  double f[257], double rolloffPoint_data[], int rolloffPoint_size[1])
{
  int c_size_idx_1;
  int loop_ub;
  float c_data[257];
  signed char unnamed_idx_1;
  float d_data[1];
  int idx_size_idx_1;
  short idx_data[1];
  bool x[257];
  short ii_data_idx_0;
  c_size_idx_1 = x_size[1];
  loop_ub = x_size[0] * x_size[1];
  if (0 <= loop_ub - 1) {
    std::memcpy(&c_data[0], &x_data[0], loop_ub * sizeof(float));
  }

  if (x_size[1] != 0) {
    for (loop_ub = 0; loop_ub < 256; loop_ub++) {
      c_data[loop_ub + 1] += c_data[loop_ub];
    }
  }

  for (loop_ub = 0; loop_ub < c_size_idx_1; loop_ub++) {
    d_data[loop_ub] = c_data[257 * loop_ub + 256] * 0.95F;
  }

  unnamed_idx_1 = static_cast<signed char>(x_size[1]);
  idx_size_idx_1 = unnamed_idx_1;
  loop_ub = unnamed_idx_1;
  if (0 <= loop_ub - 1) {
    std::memset(&idx_data[0], 0, loop_ub * sizeof(short));
  }

  if (0 <= c_size_idx_1 - 1) {
    for (loop_ub = 0; loop_ub < 257; loop_ub++) {
      x[loop_ub] = (c_data[loop_ub] >= d_data[0]);
    }
  }

  for (int i = 0; i < c_size_idx_1; i++) {
    bool exitg1;
    loop_ub = 0;
    exitg1 = false;
    while ((!exitg1) && (loop_ub < 257)) {
      if (x[loop_ub]) {
        ii_data_idx_0 = static_cast<short>(loop_ub + 1);
        exitg1 = true;
      } else {
        loop_ub++;
      }
    }

    idx_data[0] = ii_data_idx_0;
  }

  rolloffPoint_size[0] = unnamed_idx_1;
  for (loop_ub = 0; loop_ub < idx_size_idx_1; loop_ub++) {
    rolloffPoint_data[loop_ub] = f[idx_data[loop_ub] - 1];
  }
}

//
// File trailer for spectralRolloffPoint.cpp
//
// [EOF]
//
