/* Copyright 2017-2019 The MathWorks, Inc. */
#ifndef CNN_API_IMPL
#define CNN_API_IMPL

#include <map>
#include <vector>
#include <omp.h>

#include "cnn_api.hpp"
#include "MWACLUtils.hpp"

class MWTargetNetworkImpl;

/* ARM Compute Library related header files */
#include "arm_compute/runtime/NEON/NEFunctions.h"
#include "arm_compute/core/Types.h"
#include "arm_compute/runtime/SubTensor.h"
#include "arm_compute/core/SubTensorInfo.h"
#include "arm_compute/runtime/Memory.h"

#define MW_LAYERS_TAP 0

#if MW_LAYERS_TAP
#define MW_INPUT_TAP 1
#define MW_CONV_TAP 1
#define MW_RELU_TAP 1
#define MW_NORM_TAP 1
#define MW_BNORM_TAP 1
#define MW_ADDITION_TAP 1
#define MW_POOL_TAP 1
#define MW_AVG_POOL_TAP 1
#define MW_FC_TAP 1
#define MW_SFMX_TAP 1
#define MW_DCONCATENATE_TAP 1
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
#define MW_LSTM_TAP 1
#define MW_SCALE_TAP 1
#define MW_CONCATENATE_TAP 1
#define MW_SSDMERGE_TAP 1
#define MW_ELU_TAP 1
#define MW_WORDEMBED_TAP 1
#else
#define MW_INPUT_TAP 0
#define MW_CONV_TAP 0
#define MW_RELU_TAP 0
#define MW_AVG_POOL_TAP 0
#define MW_NORM_TAP 0
#define MW_BNORM_TAP 0
#define MW_ADDITION_TAP 0
#define MW_POOL_TAP 0
#define MW_FC_TAP 0
#define MW_SFMX_TAP 0
#define MW_DCONCATENATE_TAP 0
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
#define MW_LSTM_TAP 0
#define MW_SCALE_TAP 0
#define MW_CONCATENATE_TAP 0
#define MW_SSDMERGE_TAP 0
#define MW_ELU_TAP 0
#define MW_WORDEMBED_TAP 0
#endif

#if defined(USE_18_05_LIBRARY) || defined(USE_18_08_LIBRARY)
#define FREE_BUFFER_MEMORY(mem_ptr){\
    if(mem_ptr){\
     delete(mem_ptr);\
    }\
}
#define GET_BUFFER(mem_ptr) (float*)((mem_ptr)->buffer())
#define CREATE_BUFFER(size) new arm_compute::MemoryRegion((size_t) size* sizeof(float))
#else
#define FREE_BUFFER_MEMORY(mem_Ptr){\
    if(mem_Ptr){\
        free(mem_Ptr);\
        mem_Ptr = NULL;\
    }\
}
#define GET_BUFFER(mem_ptr) mem_ptr
#define CREATE_BUFFER(size) (float*)malloc(size * sizeof(float))
#endif

class MWCNNLayerImpl {
  public:
    MWCNNLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* ntwk_impl);
    virtual ~MWCNNLayerImpl() {
    }
    virtual void predict() {
    }
    virtual void cleanup(){}
    virtual void propagateSize()= 0;
    virtual void allocate(){}
    virtual void deallocate(){}
    
    virtual void allocateOutputData(int);
    virtual void deallocateOutputData(int);
    
    virtual void postSetup() {
    }
    
    template <typename T>
    T*  getData(int index = 0);

    MWCNNLayer* getLayer() {
        return cnEykmOGhLuyKuadExWe;
    }
    arm_compute::Tensor* getprevLayerarmTensor(MWTensor*);
    std::shared_ptr<arm_compute::Tensor> getARMTensorsharedPtr(MWTensor*);
    arm_compute::Tensor* getarmTensor(int index = 0);
    void setarmTensor(std::shared_ptr<arm_compute::Tensor>, int index = 0);

  protected:
    std::map<int, std::shared_ptr<arm_compute::Tensor>> armTensor; // map of outputs of current layer

    MWCNNLayer* cnEykmOGhLuyKuadExWe;
    MWTargetNetworkImpl* fylVqSnTjNbHDtlPhzaj;
    std::string getLinuxPath(const char* );
};

template <typename T>
T* MWCNNLayerImpl::getData(int index)
{
    T* data = getLayer()->getOutputTensor(index)->getData<T>();
    assert(data);
    return data;
}

class MWInputLayerImpl : public MWCNNLayerImpl {

  private:
    int bYBVtTnVUuGDUlaTmmHp;
    std::vector<float> *JLDBTuxkNCsKfaFIEVHB;
    float* m_inputImage;

    void loadAvg(const char*, int, int);
    void allocateOutputData(int);
    void predict();
    void propagateSize();
    void deallocate();
    void cleanup();

  public:
    MWInputLayerImpl(MWCNNLayer* layer,
                     MWTargetNetworkImpl* ntwk_impl,
                     int,
                     int,
                     int,
                     int,
                     const char* avg_file_name);
    ~MWInputLayerImpl();
};

// ReLULayer
class MWReLULayerImpl : public MWCNNLayerImpl {
  private:
    std::unique_ptr<arm_compute::NEActivationLayer> m_actLayer;
    int MW_Mangled_inPlace;

    void predict();
    void propagateSize();
    void allocateOutputData(int);
    void deallocateOutputData(int);

  public:
    MWReLULayerImpl(MWCNNLayer* , MWTargetNetworkImpl*, int);
    ~MWReLULayerImpl();
};


// CrossChannelNormalizationLayer
class MWNormLayerImpl : public MWCNNLayerImpl {
  private:
    std::unique_ptr<arm_compute::NENormalizationLayer> m_normLayer;
    std::unique_ptr<arm_compute::NEReshapeLayer> m_reshapeKernel;
    std::shared_ptr<arm_compute::Tensor> m_layerInputArmTensor=nullptr;

    unsigned JABfZsGuaCAmcRcqOYEO;
    double AuqaQHxmPQSyYRemQvyX;
    double BHuHNDGoRwGRouCxeMbw;
    double CDJtexcMbXMWAmnNZsNf;
    bool m_isIpArmTensorReshaped{false};

    void propagateSize();
    void predict();
    void allocate();

  public:
    MWNormLayerImpl(MWCNNLayer*, MWTargetNetworkImpl*, unsigned, double, double, double);
    ~MWNormLayerImpl();
};

// maxpoolingLayer
class MWMaxPoolingLayerImpl : public MWCNNLayerImpl {
  private:
    std::unique_ptr<arm_compute::NEPoolingLayer> m_maxPoolLayer;
    int GZGFVDrXwFLJleoTDywO;
    int GbdgxISzcqHOpzQEBrvP;
    int IIiwAtyrOtLzLWAUlTey;
    int IpFhwalnAlrMvcuyQpQD;
    int FeVcBgtQmTLtmnNcJGMY;
    int FLuSVNoPhAFKtLUchSvv;
    int GFggoMvRWucDMqzlWzCl;
    int GLovsOhUpzOJhKgXUAJY;

    void propagateSize();
    void predict();

  public:
    MWMaxPoolingLayerImpl(MWCNNLayer *, MWTargetNetworkImpl*, int, int, int, int, int, int, int, int, bool, int);
    ~MWMaxPoolingLayerImpl();
    float* getIndexData();
};

// FullyConnectedLayer
class MWFCLayerImpl : public MWCNNLayerImpl {
  private:
    std::unique_ptr<arm_compute::NEFullyConnectedLayer> m_fcLayer;
    arm_compute::Tensor m_fcLayerWgtTensor;
    arm_compute::Tensor m_fcLayerBiasTensor;
    bool isWgtsPadded = false;
    bool isBiasPadded = false;
    #if defined(USE_18_05_LIBRARY) | defined(USE_18_08_LIBRARY)
    arm_compute::MemoryRegion* wJyXsrUCMgxdIKVIJSyx;
    arm_compute::MemoryRegion* OiVqrkNdXioJhALWMMvm;
    #else
    float* wJyXsrUCMgxdIKVIJSyx;
    float* OiVqrkNdXioJhALWMMvm;
    #endif

    void loadWeights(const char*, int);
    void loadBias(const char*, int);
    void prepareWeights();
    void propagateSize();
    void predict();
    void cleanup();
    void allocate();
    void deallocate();

  public:
    MWFCLayerImpl(MWCNNLayer*, MWTargetNetworkImpl*, int, int, const char*, const char*);
    ~MWFCLayerImpl();
};

// SoftmaxLayer
class MWSoftmaxLayerImpl : public MWCNNLayerImpl {
  private:
    std::unique_ptr<arm_compute::NESoftmaxLayer> m_softmaxLayer;
    arm_compute::Tensor inputNHWCArmTensor, tmpSfmaxNHWCArmTensor;
    std::unique_ptr<arm_compute::NEPermute> permuteToNHWC;
    std::unique_ptr<arm_compute::NEPermute> permuteToNCHW;
    bool m_doesChannelwiseSoftmax;    

    void propagateSize();
    void predict();
    void allocate();
    void deallocate();


  public:
    MWSoftmaxLayerImpl(MWCNNLayer* , MWTargetNetworkImpl*);
    ~MWSoftmaxLayerImpl();
};

// AvgPoolingLayer
class MWAvgPoolingLayerImpl : public MWCNNLayerImpl {
  private:
    std::unique_ptr<arm_compute::NEPoolingLayer> m_avgPoolLayer;
    int GZGFVDrXwFLJleoTDywO;
    int GbdgxISzcqHOpzQEBrvP;
    int IIiwAtyrOtLzLWAUlTey;
    int IpFhwalnAlrMvcuyQpQD;
    int FeVcBgtQmTLtmnNcJGMY;
    int FLuSVNoPhAFKtLUchSvv;
    int GFggoMvRWucDMqzlWzCl;
    int GLovsOhUpzOJhKgXUAJY;

    void propagateSize();
    void predict();

  public:
    MWAvgPoolingLayerImpl(MWCNNLayer*, MWTargetNetworkImpl*, int, int, int, int, int, int, int, int);
    ~MWAvgPoolingLayerImpl();
};

class MWOutputLayerImpl : public MWCNNLayerImpl {
  private:
    float* m_outputData;
    arm_compute::Tensor* m_outputArmTensor;

    void propagateSize();
    void allocateOutputData(int);
    void predict();
    void deallocateOutputData(int);

  public:
    MWOutputLayerImpl(MWCNNLayer*, MWTargetNetworkImpl*);
    ~MWOutputLayerImpl();
};

#endif
