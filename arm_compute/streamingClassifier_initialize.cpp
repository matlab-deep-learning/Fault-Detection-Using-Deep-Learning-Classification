//
// File: streamingClassifier_initialize.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 19-Mar-2021 15:00:36
//

// Include Files
#include "streamingClassifier_initialize.h"
#include "extractFeatures.h"
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
  streamingClassifier_init();
  extractFeatures_init();
  isInitialized_streamingClassifier = true;
}

//
// File trailer for streamingClassifier_initialize.cpp
//
// [EOF]
//
