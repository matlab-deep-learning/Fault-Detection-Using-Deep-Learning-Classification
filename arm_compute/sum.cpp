//
// File: sum.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 20-Mar-2020 02:48:33
//

// Include Files
#include "sum.h"
#include "DeepLearningNetwork.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"

// Function Definitions

//
// Arguments    : const float x_data[]
//                const int x_size[2]
//                float y_data[]
//                int y_size[2]
// Return Type  : void
//
void sum(const float x_data[], const int x_size[2], float y_data[], int y_size[2])
{
  float f;
  if (x_size[1] == 0) {
    y_size[0] = 1;
    y_size[1] = 0;
  } else {
    y_size[0] = 1;
    y_size[1] = 1;
    f = x_data[0];
    for (int k = 0; k < 256; k++) {
      f += x_data[k + 1];
    }

    y_data[0] = f;
  }
}

//
// File trailer for sum.cpp
//
// [EOF]
//
