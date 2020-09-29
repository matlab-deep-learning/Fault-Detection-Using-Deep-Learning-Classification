//
// File: SystemCore.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 08-May-2020 10:27:24
//

// Include Files
#include "SystemCore.h"
#include "AsyncBuffercg.h"
#include "AsyncBuffercgHelper.h"
#include "DeepLearningNetwork.h"
#include "STFTSysObj.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"
#include <cstring>

// Variable Definitions
static const short iv[8] = { 256, 1, 1, 1, 1, 1, 1, 1 };

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_AsyncBuffercgHelper::b_setup()
{
  this->isSetupComplete = false;
  this->isInitialized = 1;
  this->NumChannels = 1;
  this->c_AsyncBuffercgHelper_isInitial = true;
  std::memset(&this->Cache[0], 0, 513U * sizeof(float));
  this->isSetupComplete = true;
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_STFTSysObj::b_setup()
{
  int i;
  cell_wrap_4 varSizes[1];
  float win[512];
  this->isSetupComplete = false;
  this->isInitialized = 1;
  for (i = 0; i < 8; i++) {
    varSizes[0].f1[i] = static_cast<unsigned int>(iv[i]);
  }

  this->inputVarSize[0] = varSizes[0];
  this->pBuff.init();
  this->pNumChans = 1;
  for (i = 0; i < 512; i++) {
    win[i] = static_cast<float>(this->Window[i]);
  }

  for (i = 0; i < 512; i++) {
    this->pWindow[i] = win[i];
  }

  this->isSetupComplete = true;
  this->TunablePropsChanged = false;
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_STFTSysObj::checkTunableProps()
{
  if (this->TunablePropsChanged) {
    this->TunablePropsChanged = false;
    for (int k = 0; k < 512; k++) {
      this->pWindow[k] = static_cast<float>(this->Window[k]);
    }
  }
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_STFTSysObj::releaseWrapper()
{
  if (this->isSetupComplete) {
    this->pNumChans = -1;
    this->pBuff.release();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_AsyncBuffercgHelper::releaseWrapper()
{
  if (this->isSetupComplete) {
    this->ReadPointer = 1;
    this->WritePointer = 2;
    this->CumulativeOverrun = 0;
    this->CumulativeUnderrun = 0;
    this->c_AsyncBuffercgHelper_isInitial = false;
    this->NumChannels = -1;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_AsyncBuffercgHelper::setupAndReset()
{
  this->b_setup();
  this->ReadPointer = 1;
  this->WritePointer = 2;
  this->CumulativeOverrun = 0;
  this->CumulativeUnderrun = 0;
  std::memset(&this->Cache[0], 0, 513U * sizeof(float));
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_STFTSysObj::setupAndReset()
{
  this->b_setup();
  this->pBuff.reset();
}

//
// Arguments    : void
// Return Type  : bool
//
bool dsp_private_STFTSysObj::isLockedAndNotReleased() const
{
  return this->isInitialized == 1;
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_STFTSysObj::release()
{
  if (this->isInitialized == 1) {
    this->isInitialized = 2;
    this->releaseWrapper();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_AsyncBuffercgHelper::release()
{
  if (this->isInitialized == 1) {
    this->isInitialized = 2;
    this->releaseWrapper();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void dsp_private_AsyncBuffercgHelper::reset()
{
  if (this->isInitialized == 1) {
    this->ReadPointer = 1;
    this->WritePointer = 2;
    this->CumulativeOverrun = 0;
    this->CumulativeUnderrun = 0;
    std::memset(&this->Cache[0], 0, 513U * sizeof(float));
  }
}

//
// Arguments    : const float varargin_1[256]
//                creal32_T varargout_1_data[]
//                int varargout_1_size[2]
// Return Type  : void
//
void dsp_private_STFTSysObj::step(const float varargin_1[256], creal32_T
  varargout_1_data[], int varargout_1_size[2])
{
  int k;
  bool exitg1;
  if (this->isInitialized != 1) {
    this->setupAndReset();
  }

  this->checkTunableProps();
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (this->inputVarSize[0].f1[k] != static_cast<unsigned int>(iv[k])) {
      for (k = 0; k < 8; k++) {
        this->inputVarSize[0].f1[k] = static_cast<unsigned int>(iv[k]);
      }

      exitg1 = true;
    } else {
      k++;
    }
  }

  this->stepImpl(varargin_1, varargout_1_data, varargout_1_size);
}

//
// Arguments    : const float varargin_1[256]
// Return Type  : int
//
int dsp_private_AsyncBuffercgHelper::step(const float varargin_1[256])
{
  if (this->isInitialized != 1) {
    this->setupAndReset();
  }

  return this->write(varargin_1);
}

//
// File trailer for SystemCore.cpp
//
// [EOF]
//
