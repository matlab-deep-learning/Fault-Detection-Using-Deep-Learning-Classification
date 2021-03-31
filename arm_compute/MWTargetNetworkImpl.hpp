/* Copyright 2017 The MathWorks, Inc. */
#ifndef CNN_TARGET_NTWK_IMPL
#define CNN_TARGET_NTWK_IMPL

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <memory>

class MWCNNLayer;
class MWTensorBase;

#define MW_TARGET_TYPE_ARMNEON 1

#define ALLOCATE_MEMORY_BUFFER(){\
        uint8_t *memPtr ;\
        memPtr = (uint8_t*)calloc(maxBufSize,sizeof(float));\
        memBuffer.push_back(memPtr);\
}
#define FREE_MEMORY_BUFFER(){\
        uint8_t *memPtr = memBuffer[i];\
        free(memPtr);\
}

#define FREE_BUFFER_MEMORY(mem_Ptr) \
    {                               \
        if (mem_Ptr) {              \
            free(mem_Ptr);          \
            mem_Ptr = nullptr;         \
        }                           \
    }
#define GET_BUFFER(mem_ptr) mem_ptr
#define CREATE_BUFFER(size) (float*)malloc(size * sizeof(float))
#define CREATE_BUFFER_INT8(size) (signed char*)malloc(size * sizeof(signed  char))

class MWTargetNetworkImpl {
  public:
    MWTargetNetworkImpl() {
    }
    ~MWTargetNetworkImpl() {
    }
    void allocate(int, MWCNNLayer* layers[], int numLayers, int maxCustomLayerBufSize);
    void deallocate();
    void preSetup(){}
    void postSetup(){}

    void setWorkSpaceSize(size_t); // Set the workspace size of this layer and previous layers
    size_t* getWorkSpaceSize();    // Get the workspace size of this layer and previous layers
    float* getWorkSpace();         // Get the workspace buffer in GPU memory
    void cleanup();
    void createWorkSpace(float**); // Create the workspace needed for this layer
    float* getLayerOutput(MWCNNLayer *layers[], int layerIndex, int portIndex);
    float* getLayerActivation(MWTensorBase*);
    size_t maxBufSize;
    int numBufs=0;
    std::vector<uint8_t *> memBuffer;

    float* getPermuteBuffer(int index);    // Get the buffer for custom layers' data layout permutation
    void allocatePermuteBuffers(int, int); // allocate buffer for custom layers' data layout permutation

  private:
    std::vector<float*> nDsbARncmIrIaLubvLVZ;

};
#endif
