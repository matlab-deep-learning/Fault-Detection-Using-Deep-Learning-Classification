/* Copyright 2017-2020 The MathWorks, Inc. */
#ifndef CNN_API_IMPL
#define CNN_API_IMPL

#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWACLUtils.hpp"

#include <map>
#include <vector>
#include <omp.h>

class MWTargetNetworkImpl;


/* ARM Compute Library related header files */
#include "arm_compute/runtime/NEON/NEFunctions.h"
#include "arm_compute/core/Types.h"
#include "arm_compute/runtime/SubTensor.h"
#include "arm_compute/core/SubTensorInfo.h"
#include "arm_compute/runtime/Memory.h"

#define MW_LAYERS_TAP 0

#if MW_LAYERS_TAP
extern int tap_count;
extern void mw_interm_tap(arm_compute::Tensor& armTensor, int size, int count);
extern void mw_interm_tap(float* memBuf, int size, int count);

extern void mw_interm_tap_INT8(arm_compute::Tensor& armTensor, int size, int count);
extern void mw_interm_tap(signed char* memBuf, int size, int count);

#define MW_INPUT_TAP 1
#define MW_AFFINE_TAP 1
#define MW_CONV_TAP 1
#define MW_RELU_TAP 1
#define MW_NORM_TAP 1
#define MW_BNORM_TAP 1
#define MW_ADDITION_TAP 1
#define MW_POOL_TAP 1
#define MW_AVG_POOL_TAP 1
#define MW_FC_TAP 1
#define MW_SFMX_TAP 1
#define MW_CONCATENATE_TAP 1
#define MW_YOLOEXTRACT_TAP 1
#define MW_REORG_TAP 1
#define MW_SIGMOID_TAP 1
#define MW_EXP_TAP 1
#define MW_YOLOSOFTMAX_TAP 1
#define MW_TRANSPOSEDCONV_TAP 1
#define MW_FLATTEN_TAP 1
#define MW_ZEROPAD_TAP 1
#define MW_SPLIT_TAP 1
#define MW_AFFINE_TAP 1
#define MW_CROP2D_TAP 1
#define MW_SEQIP_TAP 1
#define MW_RNN_TAP 1
#define MW_SCALE_TAP 1
#define MW_SSDMERGE_TAP 1
#define MW_ELU_TAP 1
#define MW_WORDEMBED_TAP 1
#define MW_BFPSCALE_TAP 1
#define MW_BFPRESCALE_TAP 1

#else
#define MW_INPUT_TAP 0
#define MW_AFFINE_TAP 0
#define MW_CONV_TAP 0
#define MW_RELU_TAP 0
#define MW_AVG_POOL_TAP 0
#define MW_NORM_TAP 0
#define MW_BNORM_TAP 0
#define MW_ADDITION_TAP 0
#define MW_POOL_TAP 0
#define MW_FC_TAP 0
#define MW_SFMX_TAP 0
#define MW_CONCATENATE_TAP 0
#define MW_YOLOEXTRACT_TAP 0
#define MW_REORG_TAP 0
#define MW_SIGMOID_TAP 0
#define MW_EXP_TAP 0
#define MW_YOLOSOFTMAX_TAP 0
#define MW_TRANSPOSEDCONV_TAP 0
#define MW_FLATTEN_TAP 0
#define MW_ZEROPAD_TAP 0
#define MW_SPLIT_TAP 0
#define MW_AFFINE_TAP 0
#define MW_CROP2D_TAP 0
#define MW_SEQIP_TAP 0
#define MW_RNN_TAP 0
#define MW_SCALE_TAP 0
#define MW_SSDMERGE_TAP 0
#define MW_ELU_TAP 0
#define MW_WORDEMBED_TAP 0
#define MW_BFPSCALE_TAP 0
#define MW_BFPRESCALE_TAP 0
#endif

class MWCNNLayerImpl {
  public:
    MWCNNLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* ntwk_impl);
    virtual ~MWCNNLayerImpl() {
    }
    virtual void predict() {
    }
    virtual void cleanup() {
    }
    virtual void propagateSize() = 0;
    virtual void allocate() {
    }
    virtual void deallocate() {
    }

    template <class T>
    void allocateOutputData(int);

    template <class T>
    void allocateACLLayerOpData(int);

    template <class T>
    void allocateHandCodedLayerOpData(int);

    template <class T>
    void deallocateOutputData(int);

    void allocateInputData(int);

    template <class T>
    void allocateInputDataImpl(int);

    void deallocateInputData(int);

    template <class T>
    void deallocateInputDataImpl(int);

    template <class T>
    void setUnpaddedIpData(MWTensorBase*, T*);

    void* getUnpaddedIpData(MWTensorBase*);

    virtual void postSetup() {
    }

    MWCNNLayer* getLayer() {
        return bLhHPDtQpqOAnMiVledO;
    }

    void setCurrentLayerOpArmTensor(std::shared_ptr<arm_compute::Tensor>, int index = 0);
    arm_compute::Tensor* getCurrentLayerOpArmTensor(int index = 0);
    std::shared_ptr<arm_compute::Tensor> getCurrentLayerOpArmTensorSharedPtr(int index = 0);

    void setCurrentLayerIpArmTensor(std::shared_ptr<arm_compute::Tensor>, int index = 0);
    arm_compute::Tensor* getCurrentLayerIpArmTensor(int index = 0);
    std::shared_ptr<arm_compute::Tensor> getCurrentLayerIpArmTensorSharedPtr(int index = 0);

    bool isHandCodedLayer() const {
        return ZUTPCvgISoRdtnhGqXzM;
    }

    void setupIpArmTensors();
    void configureIpArmTensors();
    void prepareIpArmTensorsForPredict();
  protected:
    // map of output arm tensors of current layer
    std::map<int, std::shared_ptr<arm_compute::Tensor>> jHaoHEqZgMiwRsdCogKz;

    std::map<MWTensorBase*, void*> YFrWUSnoOKzYyZzANuxg;

    // map of input arm tensors of current layer
    std::map<int, std::shared_ptr<arm_compute::Tensor>> VFKMunbyHoAmpHUSkuUn;

    bool ZUTPCvgISoRdtnhGqXzM{false}; // To differentiate between hand coded and ACL layers.

    MWCNNLayer* bLhHPDtQpqOAnMiVledO;
    MWTargetNetworkImpl* dAGMlbhOYuZqhuDGCqih;
    std::string getLinuxPath(const char*);
};



#endif
