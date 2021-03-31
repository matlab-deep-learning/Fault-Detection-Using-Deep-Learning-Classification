//
// File: predictAndUpdateState.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 19-Mar-2021 15:00:36
//

// Include Files
#include "predictAndUpdateState.h"
#include "DeepLearningNetwork.h"
#include "rt_nonfinite.h"
#include "streamingClassifier_internal_types.h"
#include <cstring>

// Function Definitions
//
// Arguments    : TrainedModel0_0 *obj
//                const float indata[10]
//                float out[8]
// Return Type  : void
//
namespace coder {
void DeepLearningNetwork_predictAndUpdateState(TrainedModel0_0 *obj,
                                               const float indata[10],
                                               float out[8])
{
  obj->setSize(1);
  memcpy(obj->getInputDataPointer(0), indata, obj->getLayerOutputSize(0, 0));
  obj->predict();
  memcpy(out, obj->getLayerOutput(5, 0), obj->getLayerOutputSize(5, 0));
  obj->updateState();
}

} // namespace coder

//
// File trailer for predictAndUpdateState.cpp
//
// [EOF]
//
