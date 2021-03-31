//
// File: bsxfun.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 08-May-2020 10:27:24
//

// Include Files
#include "bsxfun.h"
#include "DeepLearningNetwork.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"

// Function Definitions

//
// Arguments    : const float a_data[]
//                const int a_size[2]
//                const float b_data[]
//                const int b_size[2]
//                float c_data[]
//                int c_size[2]
// Return Type  : void
//
void b_bsxfun(const float a_data[], const int a_size[2], const float b_data[],
              const int b_size[2], float c_data[], int c_size[2])
{
  int b_b_size;
  c_size[0] = 257;
  if (b_size[1] == 1) {
    c_size[1] = static_cast<signed char>(a_size[1]);
    b_b_size = static_cast<signed char>(a_size[1]);
  } else {
    c_size[1] = 0;
    b_b_size = 0;
  }

  if (b_b_size != 0) {
    for (b_b_size = 0; b_b_size < 257; b_b_size++) {
      c_data[b_b_size] = a_data[b_b_size] - b_data[0];
    }
  }
}

//
// Arguments    : const float a_data[]
//                const int a_size[2]
//                const double b[257]
//                float c_data[]
//                int c_size[2]
// Return Type  : void
//
void bsxfun(const float a_data[], const int a_size[2], const double b[257],
            float c_data[], int c_size[2])
{
  c_size[0] = 257;
  c_size[1] = static_cast<signed char>(a_size[1]);
  if (static_cast<signed char>(a_size[1]) != 0) {
    for (int k = 0; k < 257; k++) {
      c_data[k] = a_data[k] * static_cast<float>(b[k]);
    }
  }
}

//
// File trailer for bsxfun.cpp
//
// [EOF]
//
