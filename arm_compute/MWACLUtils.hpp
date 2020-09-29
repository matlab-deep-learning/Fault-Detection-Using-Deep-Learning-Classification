/* Copyright 2019 The MathWorks, Inc. */
// Include MWACLUtils.hpp file to use Arm Compute Library(ACL) related utility functions.

#ifndef _ACL_UTILS_
#define _ACL_UTILS_

/* ARM Compute Library related header files */
#include "arm_compute/runtime/NEON/NEFunctions.h"
#include "arm_compute/core/Types.h"
#include "arm_compute/runtime/SubTensor.h"
#include "arm_compute/core/SubTensorInfo.h"
#include "arm_compute/runtime/Memory.h"

#if defined(USE_18_05_LIBRARY) | defined(USE_18_08_LIBRARY)
#include "arm_compute/runtime/MemoryRegion.h"
#endif

class MWACLUtils {

  public:
    static void fillBufferToTensor(float*, arm_compute::ITensor&);
    static void fillTensorToBuffer(float*, arm_compute::ITensor&);
    static void fillLSTMOutputTensor(arm_compute::ITensor&, arm_compute::ITensor&, int);
    static void fillLSTMInputTensor(arm_compute::ITensor&, arm_compute::ITensor&, int);
    static void fillValueToTensor(float, arm_compute::ITensor&);
    static void fillLSTMOutputArmTensor(const float*, arm_compute::ITensor&, int&, bool, int, bool isBiLSTM=false, bool isBackwardLSTM=false);

#if defined(USE_18_05_LIBRARY) | defined(USE_18_08_LIBRARY)
    static void allocateAndFillTensor(arm_compute::Tensor& armTensor, arm_compute::MemoryRegion* memoryPtr, int size, bool& isPadded);
#else
    static void allocateAndFillTensor(arm_compute::Tensor&, float*, int, bool& isPadded);
#endif
};

#endif