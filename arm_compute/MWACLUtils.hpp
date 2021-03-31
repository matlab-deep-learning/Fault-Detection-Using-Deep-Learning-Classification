/* Copyright 2019-2020 The MathWorks, Inc. */
// Include MWACLUtils.hpp file to use Arm Compute Library(ACL) related utility functions.

#ifndef _ACL_UTILS_
#define _ACL_UTILS_

#include <arm_neon.h>

class MWTensorBase;

/* ARM Compute Library related header files */
#include "arm_compute/runtime/NEON/NEFunctions.h"
#include "arm_compute/core/Types.h"
#include "arm_compute/runtime/SubTensor.h"
#include "arm_compute/core/SubTensorInfo.h"
#include "arm_compute/runtime/Memory.h"


class MWACLUtils {

  public:
	template <typename T>
    static void fillBufferToTensor(T*, arm_compute::ITensor&);
	template <typename T>
    static void fillTensorToBuffer(T*, arm_compute::ITensor&);

    static void fillRNNOutputTensor(arm_compute::ITensor&, arm_compute::ITensor&, int);
    static void fillRNNInputTensor(arm_compute::ITensor&, arm_compute::ITensor&, int);
    static void fillValueToTensor(float, arm_compute::ITensor&);
    static void fillRNNOutputArmTensor(const float*,
                                        arm_compute::ITensor&,
                                        int&,
                                        bool,
                                        int,
                                        bool isBiRNN=false,
                                        bool isBackwardRNN=false);

	template <typename T>
    static void allocateAndFillTensor(arm_compute::Tensor&, T*, int, bool& isPadded);


    static arm_compute::Tensor* getLayerOpArmTensor(MWTensorBase*);
    static std::shared_ptr<arm_compute::Tensor> getLayerOpArmTensorsharedPtr(MWTensorBase*);
    static void doPermutation(const float* inputBuf,
                              float* outputBuf,
                              const int ipDims[],
                              const int strides[]);
};


/* Use allocateAndFillTensor(..) utility to fill ARM Tensor using input buffer
 * where ARM Tensor is not allocated. Here this utility will decide whether 
 * to allocate new memory for ARM Tensor (or) simply assign the input buffer pointer
 * to the ARM Tensor.
 * if tensor is padded, allocate memory for tensor and fill tensor with data in buffer
 * if no padding is done for tensor, use the buffer as memory for tensor using import_memory
 */
template <typename T>	
#if defined(USE_19_05_LIBRARY) || defined(USE_20_02_1_LIBRARY)
void MWACLUtils::allocateAndFillTensor(arm_compute::Tensor& armTensor, T* buffer, int /*size*/, bool& isPadded) {
#else
void MWACLUtils::allocateAndFillTensor(arm_compute::Tensor& armTensor, T* buffer, int size, bool& isPadded) {
#endif

    if(armTensor.info()->has_padding()){

        armTensor.allocator()->allocate();
        MWACLUtils::fillBufferToTensor<T>(buffer, armTensor);
        isPadded = true;
    }else{
        #if defined(USE_19_05_LIBRARY) || defined(USE_20_02_1_LIBRARY)
            armTensor.allocator()->import_memory(buffer);
        #else
            armTensor.allocator()->import_memory(buffer, size * sizeof(T));
        #endif
        isPadded = false;
    }
}

// Use fillBufferToTensor(..) utility to copy the data to the padded tensor.
// Here inputTensor must be allocated before calling this method.
template <typename T>
void MWACLUtils::fillBufferToTensor(T* input_data, arm_compute::ITensor& inputTensor) {

    arm_compute::Window inputWindow;
    inputWindow.use_tensor_dimensions(inputTensor.info()->tensor_shape());
    arm_compute::Iterator inputIterator(&inputTensor, inputWindow);
    int counter = 0;
    /* The execute_window_loop function takes an execution window, a lambda function
     * and an iterator. It will iterate through every element of the execution window
     * and for each element it will update the iterators accordingly and call the lambda function
     */
    arm_compute::execute_window_loop(
        inputWindow,
        [&](const arm_compute::Coordinates& ) {
            *reinterpret_cast<T*>(inputIterator.ptr()) = input_data[counter];
            counter++;
        },
        inputIterator);
}


// Use fillTensorToBuffer(..) utility to copy the data from the padded tensor.
// Here output_data must be allocated previously.
template <typename T>
void MWACLUtils::fillTensorToBuffer(T* output_data, arm_compute::ITensor& outputTensor) {


    arm_compute::Window outputWindow;
    outputWindow.use_tensor_dimensions(outputTensor.info()->tensor_shape());
    arm_compute::Iterator outputIterator(&outputTensor, outputWindow);
    int counter = 0;
    arm_compute::execute_window_loop(
        outputWindow,
        [&](const arm_compute::Coordinates& ) {
            output_data[counter] = *reinterpret_cast<T*>(outputIterator.ptr());
            counter++;
        },
        outputIterator);
}
#endif
