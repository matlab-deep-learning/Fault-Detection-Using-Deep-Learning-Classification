//
// File: streamingClassifier.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 08-May-2020 10:27:24
//
#ifndef STREAMINGCLASSIFIER_H
#define STREAMINGCLASSIFIER_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "streamingClassifier_types.h"

// Function Declarations
extern void streamingClassifier(const float audioIn[256], const float M[10],
  const float S[10], float scores[8], float features[10]);
extern void streamingClassifier_init();

#endif

//
// File trailer for streamingClassifier.h
//
// [EOF]
//
