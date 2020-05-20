//
// File: streamingClassifier_terminate.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 08-May-2020 10:27:24
//

// Include Files
#include "streamingClassifier_terminate.h"
#include "DeepLearningNetwork.h"
#include "extractFeatures.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"
#include "streamingClassifier_data.h"

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void streamingClassifier_terminate()
{
  extractFeatures_free();
  isInitialized_streamingClassifier = false;
}

//
// File trailer for streamingClassifier_terminate.cpp
//
// [EOF]
//
