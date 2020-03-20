//
// File: STFTSysObj.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 20-Mar-2020 02:48:33
//

// Include Files
#include "STFTSysObj.h"
#include "AsyncBuffercg.h"
#include "DeepLearningNetwork.h"
#include "FFTImplementationCallback.h"
#include "ProcessConstructorArguments.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"
#include <cstring>

// Function Definitions

//
// Arguments    : void
// Return Type  : dsp_private_STFTSysObj *
//
dsp_private_STFTSysObj *dsp_private_STFTSysObj::init()
{
  dsp_private_STFTSysObj *obj;
  obj = this;
  obj->isInitialized = 0;
  ProcessConstructorArguments::b_do((obj));
  obj->pNumChans = -1;
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : const float u[256]
//                creal32_T Y_data[]
//                int Y_size[2]
// Return Type  : void
//
void dsp_private_STFTSysObj::stepImpl(const float u[256], creal32_T Y_data[],
  int Y_size[2])
{
  float y_data[1024];
  int y_size[1];
  float y[512];
  creal32_T b_y[512];
  this->pBuff.write(u);
  if (this->pBuff.get_NumUnreadSamples() >= 512) {
    this->pBuff.read(y_data, y_size);
    for (int i = 0; i < 512; i++) {
      y[i] = y_data[i] * this->pWindow[i];
    }

    FFTImplementationCallback::doHalfLengthRadix2((y), (b_y));
    Y_size[0] = 512;
    Y_size[1] = 1;
    std::memcpy(&Y_data[0], &b_y[0], 512U * sizeof(creal32_T));
  } else {
    Y_size[0] = 512;
    Y_size[1] = 0;
  }
}

//
// File trailer for STFTSysObj.cpp
//
// [EOF]
//
