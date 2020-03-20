//
// File: SystemProp.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 20-Mar-2020 02:48:33
//

// Include Files
#include "SystemProp.h"
#include "DeepLearningNetwork.h"
#include "SystemCore.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"

// Function Definitions

//
// Arguments    : dsp_private_STFTSysObj *obj
// Return Type  : void
//
void SystemProp::matlabCodegenNotifyAnyProp(dsp_private_STFTSysObj *obj)
{
  if (obj->isLockedAndNotReleased()) {
    obj->TunablePropsChanged = true;
  }
}

//
// File trailer for SystemProp.cpp
//
// [EOF]
//
