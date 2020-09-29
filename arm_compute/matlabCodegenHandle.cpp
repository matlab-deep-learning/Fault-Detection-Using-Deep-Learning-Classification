//
// File: matlabCodegenHandle.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 08-May-2020 10:27:24
//

// Include Files
#include "matlabCodegenHandle.h"
#include "DeepLearningNetwork.h"
#include "SystemCore.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
dsp_private_STFTCG::~dsp_private_STFTCG()
{
  this->matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
dsp_private_STFTSysObj::~dsp_private_STFTSysObj()
{
  this->matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
dsp_private_AsyncBuffercg::~dsp_private_AsyncBuffercg()
{
  this->matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
dsp_private_AsyncBuffercgHelper::~dsp_private_AsyncBuffercgHelper()
{
  this->matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_STFTCG::matlabCodegenDestructor()
{
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_STFTSysObj::matlabCodegenDestructor()
{
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
    this->release();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_AsyncBuffercg::matlabCodegenDestructor()
{
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_AsyncBuffercgHelper::matlabCodegenDestructor()
{
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
    this->release();
  }
}

//
// File trailer for matlabCodegenHandle.cpp
//
// [EOF]
//
