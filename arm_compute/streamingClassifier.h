//
// File: streamingClassifier.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 19-Mar-2021 15:00:36
//

#ifndef STREAMINGCLASSIFIER_H
#define STREAMINGCLASSIFIER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void streamingClassifier(const float audioIn[512], const float M[10],
                                const float S[10], float scores[8],
                                float features[10]);

void streamingClassifier_init();

#endif
//
// File trailer for streamingClassifier.h
//
// [EOF]
//
