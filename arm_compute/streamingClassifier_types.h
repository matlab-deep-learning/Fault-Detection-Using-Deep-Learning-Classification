//
// File: streamingClassifier_types.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 19-Mar-2021 15:00:36
//

#ifndef STREAMINGCLASSIFIER_TYPES_H
#define STREAMINGCLASSIFIER_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
struct struct_T {
  float FrequencyVector[257];
};

struct b_struct_T {
  unsigned short FrequencyBins[257];
  float NormalizationFactor;
};

struct c_struct_T {
  unsigned short OneSidedSpectrumBins[257];
  b_struct_T linearSpectrum;
  struct_T SpectralDescriptorInput;
};

#endif
//
// File trailer for streamingClassifier_types.h
//
// [EOF]
//
