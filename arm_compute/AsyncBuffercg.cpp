//
// File: AsyncBuffercg.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 08-May-2020 10:27:24
//

// Include Files
#include "AsyncBuffercg.h"
#include "AsyncBuffercgHelper.h"
#include "DeepLearningNetwork.h"
#include "SystemCore.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"

// Function Definitions

//
// Arguments    : void
// Return Type  : int
//
int dsp_private_AsyncBuffercg::get_NumUnreadSamples() const
{
  return this->pBuffer.get_NumUnreadSamples();
}

//
// Arguments    : void
// Return Type  : dsp_private_AsyncBuffercg *
//
dsp_private_AsyncBuffercg *dsp_private_AsyncBuffercg::init()
{
  dsp_private_AsyncBuffercg *obj;
  obj = this;
  obj->pBuffer.init();
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : float out_data[]
//                int out_size[1]
// Return Type  : void
//
void dsp_private_AsyncBuffercg::read(float out_data[], int out_size[1])
{
  int underrun;
  this->pBuffer.read(out_data, out_size, (&underrun));
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_AsyncBuffercg::release()
{
  this->pBuffer.release();
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_AsyncBuffercg::reset()
{
  this->pBuffer.reset();
}

//
// Arguments    : const float in[256]
// Return Type  : void
//
void dsp_private_AsyncBuffercg::write(const float in[256])
{
  this->pBuffer.step(in);
}

//
// File trailer for AsyncBuffercg.cpp
//
// [EOF]
//
