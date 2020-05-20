//
// File: streamingClassifier_initialize.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 08-May-2020 10:27:24
//

// Include Files
#include "streamingClassifier_initialize.h"
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
void streamingClassifier_initialize()
{
  rt_InitInfAndNaN();
  streamingClassifier_init();
  extractFeatures_init();
  isInitialized_streamingClassifier = true;
}

//
// File trailer for streamingClassifier_initialize.cpp
//
// [EOF]
//
