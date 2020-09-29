//
// File: STFTCG.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 08-May-2020 10:27:24
//

// Include Files
#include "STFTCG.h"
#include "DeepLearningNetwork.h"
#include "STFTSysObj.h"
#include "SystemCore.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"

// Function Definitions

//
// Arguments    : const float u[256]
//                creal32_T y_data[]
//                int y_size[2]
// Return Type  : void
//
void dsp_private_STFTCG::step(const float u[256], creal32_T y_data[], int
  y_size[2])
{
  this->pObj.step(u, y_data, y_size);
}

//
// Arguments    : void
// Return Type  : dsp_private_STFTCG *
//
dsp_private_STFTCG *dsp_private_STFTCG::init()
{
  dsp_private_STFTCG *obj;
  obj = this;
  obj->pObj.init();
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : const float u[256]
//                creal32_T Y_data[]
//                int Y_size[2]
// Return Type  : void
//
void dsp_private_STFTCG::parenReference(const float u[256], creal32_T Y_data[],
  int Y_size[2])
{
  this->step(u, Y_data, Y_size);
}

//
// File trailer for STFTCG.cpp
//
// [EOF]
//
