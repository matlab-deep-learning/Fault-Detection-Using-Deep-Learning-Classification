//
// File: extractFeatures.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 20-Mar-2020 02:48:33
//
#ifndef EXTRACTFEATURES_H
#define EXTRACTFEATURES_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "streamingClassifier_types.h"

// Function Declarations
extern void extractFeatures(const float audioIn[256], float features_data[], int
  features_size[2]);
extern void extractFeatures_free();
extern void extractFeatures_init();

#endif

//
// File trailer for extractFeatures.h
//
// [EOF]
//
