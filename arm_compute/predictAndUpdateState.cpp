//
// File: predictAndUpdateState.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 20-Mar-2020 02:48:33
//

// Include Files
#include "predictAndUpdateState.h"
#include "DeepLearningNetwork.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"
#include "streamingClassifier_rtwutil.h"
#include <cstring>

// Function Definitions

//
// Arguments    : void
// Return Type  : int *
//

//
// Arguments    : b_TrainedModel_0 *obj
//                const float indata[10]
//                float out[8]
// Return Type  : void
//
void c_DeepLearningNetwork_predictAn(b_TrainedModel_0 *obj, const float indata
  [10], float out[8])
{
  obj->setSize(1);
  memcpy(obj->getInputDataPointer(), indata, obj->layers[0]->getOutputTensor(0
         )->getNumElements() * sizeof(float));
  obj->predict();
  memcpy(out, obj->getLayerOutput(6, 0), obj->layers[6]->getOutputTensor(0)
         ->getNumElements() * sizeof(float));
  obj->updateState();
}

//
// File trailer for predictAndUpdateState.cpp
//
// [EOF]
//
