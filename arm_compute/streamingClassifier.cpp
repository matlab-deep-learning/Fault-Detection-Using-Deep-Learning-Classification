//
// File: streamingClassifier.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 20-Mar-2020 02:48:33
//

// Include Files
#include "streamingClassifier.h"
#include "DeepLearningNetwork.h"
#include "extractFeatures.h"
#include "matlabCodegenHandle.h"
#include "predictAndUpdateState.h"
#include "rt_nonfinite.h"
#include "streamingClassifier_data.h"
#include "streamingClassifier_initialize.h"

// Variable Definitions
static b_TrainedModel_0 airCompNet;
static bool airCompNet_not_empty;

// Function Definitions

//
// This is a streaming classifier function
// Arguments    : const float audioIn[256]
//                const float M[10]
//                const float S[10]
//                float scores[8]
//                float features[10]
// Return Type  : void
//
void streamingClassifier(const float audioIn[256], const float M[10], const
  float S[10], float scores[8], float features[10])
{
  float features_data[10];
  int features_size[2];
  float b_features[10];
  if (!isInitialized_streamingClassifier) {
    streamingClassifier_initialize();
  }

  //    Copyright 2020 The MathWorks, Inc.
  if (!airCompNet_not_empty) {
    DeepLearningNetwork_setup(&airCompNet);
    airCompNet_not_empty = true;
  }

  //  Extract features using function
  extractFeatures(audioIn, features_data, features_size);

  //  Normalize
  //  Classify
  for (int i = 0; i < 10; i++) {
    float features_tmp;
    features_tmp = (features_data[i] - M[i]) / S[i];
    features[i] = features_tmp;
    b_features[i] = features_tmp;
  }

  c_DeepLearningNetwork_predictAn(&airCompNet, b_features, scores);
}

//
// This is a streaming classifier function
// Arguments    : void
// Return Type  : void
//
void streamingClassifier_init()
{
  airCompNet_not_empty = false;
}

//
// File trailer for streamingClassifier.cpp
//
// [EOF]
//
