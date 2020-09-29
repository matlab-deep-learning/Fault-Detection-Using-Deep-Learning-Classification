/* Copyright 2017 The MathWorks, Inc. */
#ifndef CNN_TARGET_NTWK_IMPL
#define CNN_TARGET_NTWK_IMPL

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <memory>
#include "cnn_api.hpp"
#define MW_TARGET_TYPE_ARMNEON 1

#if defined(USE_18_05_LIBRARY) || defined(USE_18_08_LIBRARY)
#include "arm_compute/runtime/MemoryRegion.h"
#define ALLOCATE_MEMORY_BUFFER(){\
        arm_compute::IMemoryRegion *memPtr = new arm_compute::MemoryRegion((size_t) maxBufSize* sizeof(float)) ;\
        memBuffer.push_back(memPtr);\
}
#define FREE_MEMORY_BUFFER(){\
        delete(memBuffer[i]);\
}
#else
#define ALLOCATE_MEMORY_BUFFER(){\
        uint8_t *memPtr ;\
        memPtr = (uint8_t*)calloc(maxBufSize,sizeof(float));\
        memBuffer.push_back(memPtr);\
}
#define FREE_MEMORY_BUFFER(){\
        uint8_t *memPtr = memBuffer[i];\
        free(memPtr);\
}
#endif

class MWTargetNetworkImpl {
  public:
    MWTargetNetworkImpl() {
    }
    ~MWTargetNetworkImpl() {
    }
    void allocate(int, MWCNNLayer* layers[], int numLayers);
    void deallocate();
    void preSetup(){}
    void postSetup(){}

    void setWorkSpaceSize(size_t); // Set the workspace size of this layer and previous layers
    size_t* getWorkSpaceSize();    // Get the workspace size of this layer and previous layers
    float* getWorkSpace();         // Get the workspace buffer in GPU memory
    void cleanup();
    void createWorkSpace(float**); // Create the workspace needed for this layer
    float* getLayerOutput(MWCNNLayer *layers[], int layerIndex, int portIndex);
    float* getLayerActivation(MWTensor*);
    size_t maxBufSize;
    int numBufs=0;
    #if defined(USE_18_05_LIBRARY) | defined(USE_18_08_LIBRARY)
    std::vector<arm_compute::IMemoryRegion *> memBuffer;
    #else
    std::vector<uint8_t *> memBuffer;
    #endif
};
#endif