/* Copyright 2016-2020 The MathWorks, Inc. */
#ifndef CNN_API_HPP
#define CNN_API_HPP

#include <string>
#include <stdexcept>
#include <map>
#include <cassert>

template <typename T>
void call_fread(T* m_buffer, size_t m_size, size_t m_num, FILE* m_fp, char const* const m_fileName) {
    if (fread(m_buffer, m_size, m_num, m_fp) != m_num) {
        throw std::runtime_error("Unexpected number of bytes read from " + std::string(m_fileName));
    }
}

class MWTensor;
class MWTargetNetworkImpl;
class MWCNNLayerImpl;

class MWCNNLayer {
  protected:
    std::string m_name;                // Name of the layer
    std::map<int, MWTensor*> m_input;  // inputs
    std::map<int, MWTensor*> m_output; // outputs

    MWCNNLayerImpl* m_impl; // layer impl

  public:
    MWCNNLayer();
    virtual ~MWCNNLayer();
    virtual void predict();
    virtual void cleanup();
    virtual void propagateSize() = 0;
    virtual void allocate();
    void deallocate();
    void postSetup();

    MWCNNLayerImpl* getImpl() {
        return m_impl;
    }
    size_t getNumOutputs() {
        return m_output.size();
    }
    size_t getNumInputs() {
        return m_input.size();
    }
    MWTensor* getInputTensor(int index = 0);
    float* getLayerOutput(int index);
    MWTensor* getOutputTensor(size_t index = 0);
    void setName(const std::string&); // Set the name for this layer
    std::string getName() const {
        return m_name;
    }; // Get the name for this layer

    static bool isDebuggingEnabled() {return m_enableDebugging; };

  protected:
    int getBatchSize();                      // Get the batch size
    int getHeight(int index = 0);            // Get the height of output y
    int getWidth(int index = 0);             // Get the width of output y
    int getNumInputFeatures(int index = 0);  // Get the number of channels of the input
    int getNumOutputFeatures(int index = 0); // Get the number of channels of the output

    void setInputTensor(MWTensor* other, int index = 0); // shallow copy tensor from other
    void allocateOutputTensor(int numHeight,
                              int numWidth,
                              int numChannels,
                              int batchsize,
                              int sequencelength,
                              void* data,
                              int index = 0); // allocate output tensor
    
    void resizeOutputTensor(int numHeight,
                            int numWidth,
                            int numChannels,
                            int batchsize,
                            int sequencelength,
                            int index = 0); // resize output tensor

    void loadParams(const char* MW_mangled_fileName,
                    const int MW_mangled_num,
                    float* MW_mangled_buffer); // load non-scalar numeric parameters for custom layers

  public:
    static FILE* openBinaryFile(const char* filename);
    static std::runtime_error getFileOpenError(const char* filename);

  private:

#if DEBUG

    const static bool m_enableDebugging = true;

#else

    const static bool m_enableDebugging = false;

#endif
    
};

class MWTensor {
  public:
    MWTensor()
        : m_height(-1)
        , m_width(-1)
        , m_channels(-1)
        , m_batchSize(-1)
        , m_sequenceLength(-1)
        , m_data(NULL)
        , m_owner(NULL)
        , m_srcport(-1)
        , opBufIndex(-1){};
    MWTensor(int height,
             int width,
             int channels,
             int batchsize,
             int sequencelength,
             void* data,
             MWCNNLayer* owner,
             int srcport);
    ~MWTensor();

    int getHeight() const {
        return m_height;
    }
    int getWidth() const {
        return m_width;
    }
    int getChannels() const {
        return m_channels;
    }
    int getBatchSize() const {
        return m_batchSize;
    }
    int getSequenceLength() const {
        return m_sequenceLength;
    }
    int getNumElements() const {
        return getHeight() * getWidth() * getChannels() * getBatchSize() * getSequenceLength();
    }
    void setHeight(int height) {
        m_height = height;
    }
    void setWidth(int width) {
        m_width = width;
    }
    void setChannels(int channels) {
        m_channels = channels;
    }
    void setBatchSize(int batchSize) {
        m_batchSize = batchSize;
    }
    void setSequenceLength(int sequenceLength) {
        m_sequenceLength = sequenceLength;
    }
    template <typename T>
    T* getData() const;
    float* getFloatData() {
        return this->getData<float>();
    }
    MWCNNLayer* getOwner() const {
        return m_owner;
    }
    int getSourcePortIndex() const {
        return m_srcport;
    }
    template <typename T>
    void setData(T* data);
    void setopBufIndex(int bufIndex) {
        opBufIndex = bufIndex;
    }
    int getopBufIndex() {
        return opBufIndex;
    };

    void getShape(int tensorShape[5]) const {
        tensorShape[0] = m_height;
        tensorShape[1] = m_width;
        tensorShape[2] = m_channels;
        tensorShape[3] = m_batchSize;
        tensorShape[4] = m_sequenceLength;
    }

  private:
    int m_height;
    int m_width;
    int m_channels;
    int m_batchSize;
    int m_sequenceLength;
    void* m_data;
    MWCNNLayer* m_owner;
    int m_srcport;
    int opBufIndex;
};

template <typename T>
T* MWTensor::getData() const {
    T* data = static_cast<T*>(m_data);

    // We do not allocate memory for the intermediate layers when the target is "tensorrt"
    // so "m_data" member in the MWTensor for all the intermediate layers (except input and output
    // layers) will have null pointers, consequently when getData() is called from "getBuffer"
    // method of "MWTargetNetworkImpl" class will cause assert error, hence commenting out the below
    // line.

    // assert(data);
    return data;
}

template <typename T>
void MWTensor::setData(T* data) {
    m_data = (void*)data;
}


// ImageInputLayer
class MWInputLayer : public MWCNNLayer {
  public:
    MWInputLayer() {
    }
    ~MWInputLayer() {
    }

    void createInputLayer(MWTargetNetworkImpl* ntwk_impl,
                          MWTensor* m_in,
                          int,
                          int,
                          int,
                          int,
                          const char* avg_file_name,
                          int);
    void propagateSize();
};

// ReLULayer
class MWReLULayer : public MWCNNLayer {
  public:
    MWReLULayer() {
    }
    ~MWReLULayer() {
    }

    void createReLULayer(MWTargetNetworkImpl*, MWTensor*, int, int);
    void propagateSize();
};

// CrossChannelNormalizationLayer
class MWNormLayer : public MWCNNLayer {
  public:
    MWNormLayer() {
    }
    ~MWNormLayer() {
    }

    void createNormLayer(MWTargetNetworkImpl*, MWTensor*, unsigned, double, double, double, int);
    void propagateSize();
};

// AvgPooling2DLayer
class MWAvgPoolingLayer : public MWCNNLayer {
  public:
    MWAvgPoolingLayer() : isGlobalAveragePooling(false)
    {
    }
    ~MWAvgPoolingLayer() {
    }
    void createAvgPoolingLayer(MWTargetNetworkImpl*, MWTensor*, int, int, int, int, int, int, int, int, int);
    void propagateSize();

    int strideH;
    int strideW;
    
    int poolH;
    int poolW;

    int paddingH_T;
    int paddingH_B;
    int paddingW_L;
    int paddingW_R;

    bool isGlobalAveragePooling;
};

// MaxPooling2DLayer
class MWMaxPoolingLayer : public MWCNNLayer {
  public:
    MWMaxPoolingLayer() : isGlobalAveragePooling(false)
    {
    }
    ~MWMaxPoolingLayer() {
    }
    // Create MaxPooling2DLayer with PoolSize = [ PoolH PoolW ]
    //                                Stride = [ StrideH StrideW ]
    //                               Padding = [ PaddingH_T PaddingH_B PaddingW_L PaddingW_R ]
    void createMaxPoolingLayer(MWTargetNetworkImpl*,
                               MWTensor*,
                               int,
                               int,
                               int,
                               int,
                               int,
                               int,
                               int,
                               int,
                               bool,
                               int,
                               ...);
    void propagateSize();

  private:
    int strideH;
    int strideW;
    
    int poolH;
    int poolW;

    int paddingH_T;
    int paddingH_B;
    int paddingW_L;
    int paddingW_R;

    bool isGlobalAveragePooling;

    bool hasIndices;
};

// FullyConnectedLayer
class MWFCLayer : public MWCNNLayer {
  public:
    MWFCLayer() {
    }
    ~MWFCLayer() {
    }

    void createFCLayer(MWTargetNetworkImpl*, MWTensor*, int, int, const char*, const char*, int);
    void propagateSize();

  private:
    int numInputFeatures;
    int numOutputFeatures;
};

// SoftmaxLayer
class MWSoftmaxLayer : public MWCNNLayer {
  public:
    MWSoftmaxLayer() {
    }
    ~MWSoftmaxLayer() {
    }

    void createSoftmaxLayer(MWTargetNetworkImpl*, MWTensor*, int);
    void propagateSize();
};

// ClassificationOutputLayer
class MWOutputLayer : public MWCNNLayer {
  public:
    MWOutputLayer() {
    }
    ~MWOutputLayer() {
    }

    void createOutputLayer(MWTargetNetworkImpl*, MWTensor*, int);
    void predict();
    void propagateSize();
};

// pass through
class MWPassthroughLayer : public MWCNNLayer {
  public:
    MWPassthroughLayer() {
    }
    ~MWPassthroughLayer() {
    }

    void createPassthroughLayer(MWTargetNetworkImpl*, MWTensor*, int);
    void propagateSize();
    void allocate();
};

// Onnx FlattenLayer
class MWRowMajorFlattenLayer : public MWCNNLayer {
  public:
    MWRowMajorFlattenLayer() {
    }
    ~MWRowMajorFlattenLayer() {
    }

    void createRowMajorFlattenLayer(MWTargetNetworkImpl*, MWTensor*, int);
    void propagateSize();
    void allocate();
};

// FlattenLayer
class MWFlattenLayer : public MWCNNLayer {
  public:
    MWFlattenLayer() {
    }
    ~MWFlattenLayer() {
    }

    void createFlattenLayer(MWTargetNetworkImpl*, MWTensor*, int);
    void propagateSize();
};

#endif
