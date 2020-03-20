/* Copyright 2016-2020 The MathWorks, Inc. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdexcept>
#include <string>
#include <stdarg.h>
#include <cassert>
#include <vector>
#include "cnn_api.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWTargetNetworkImpl.hpp"
// Get string value from the macro
#define XSTR(x) #x
#define STR(x) XSTR(x)

MWCNNLayer::MWCNNLayer() :
    m_impl( NULL)
{    
}

MWCNNLayer::~MWCNNLayer()
{  
}

void MWCNNLayer::predict() 
{
    if (m_impl)
    {
        m_impl->predict();
    }
}

/**
 * everything instantiated during setup() should be cleaned up here 
 */
void MWCNNLayer::cleanup()
{
    if (m_impl)
    {
        m_impl->cleanup();
        delete m_impl;
        m_impl = 0;
    }
    
    for(int idx = 0; idx < getNumOutputs(); idx++)
    {        
        MWTensor* op = getOutputTensor(idx);
        delete op;
        op = 0;
        m_output[idx] = 0;        
    }
       
    // free up tensor maps
    m_input.clear();
    m_output.clear();
}
void MWCNNLayer::allocate()
{
    if(m_impl)
    {
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_ARMNEON) || defined(MW_TARGET_TYPE_MKLDNN)
        // allocate memory for each output tensor
        for (int i = 0; i < getNumOutputs(); ++i) {
            MWTensor* op = getOutputTensor(i);

            if (op->getopBufIndex() < 0) {
                // for non-buffer-reuse, relegate allocation to target-specific class
                m_impl->allocateOutputData(i);
            } else {

 #if defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)              
                 // perform any target-specific tasks required for allocation (e.g. preparing the mkldnn tensor)
                 m_impl->allocateOutputData(i);
 #else
              
                 /*
                  * For CuDNN buffer reuse, point the output tensor's data pointer to the
                  * appropriate buffer managed by the targetNetworkImpl. The analagous setting
                  * of the output tensor data pointer for ARM and MKLDNN happens in the call to
                  * allocateOutputData in the above branch. It cannot be moved to the target-agnostic
                  * layer class since it requires accessing the arm/mkldnn buffer, which is layer specific.
                  */
                 op->setData(m_impl->getTargetNetworkImpl()->memBuffer[op->getopBufIndex()]);
#endif
            }
        }
#else
        m_impl->allocateOutputData();
#endif

        // allocate buffers for additional memory buffers required by the layerImpl
        m_impl->allocate();
    }
}
void MWCNNLayer::deallocate()
{
    if(m_impl)
    {
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_ARMNEON) || defined(MW_TARGET_TYPE_MKLDNN)
        // deallocate memory for each output tensor
        for (int i = 0; i < getNumOutputs(); ++i) {
            MWTensor* op = getOutputTensor(i);

            float* data = op->getData<float>();

            if (data) {
                if (op->getopBufIndex() < 0) {
                    // for buffer-non-reuse, relegate deallocation to target-specific class
                    m_impl->deallocateOutputData(i);
                }
                
                // avoid dangling pointer
                op->setData((float *)NULL);
            }
        }
#else
        m_impl->deallocateOutputData();
#endif

        // deallocate buffers for additional memory buffers required by the layerImpl
        m_impl->deallocate();
    }
}
void MWCNNLayer::postSetup()
{
    if(m_impl)
    {
        m_impl->postSetup();
    }
}
std::string getFilePath(std:: string fileS)
{
    char* usrDataPath = NULL;
    std::string path;
    
// Get file path from user environment
    usrDataPath = getenv("USER_DL_DATA_PATH");
    
    if(usrDataPath != NULL)
    {
        path = usrDataPath;
    }
    else
    {
        // Get file path from macro
        path = STR(MW_DL_DATA_PATH);
    }
    
    // Find name of file
    size_t fNamePos = fileS.find_last_of("/\\");
    
    if(fNamePos != std::string::npos)
    {
        std::string fileN(fileS.substr(fNamePos));
        fileS = path + fileN;
    }
    else
    {
        fileS = path + fileS;
    }
    
    return fileS;
}
// open filename
// if file is not found, look in current directory
FILE* MWCNNLayer::openBinaryFile(const char* fileName)
{
    FILE* fp = fopen(fileName, "rb");
    if (!fp)
    {
        std::string fileS(fileName);
        std::string codegenFolder;

        /* Code to extract the directory path */
        size_t fNamePos = fileS.find_last_of("/\\");

        if(fNamePos != std::string::npos){
            codegenFolder = fileS.substr(0, fNamePos);
        }
        else{
            /* Default path when there is no directory*/
            codegenFolder = std::string(".");
        }

        size_t pos = 0;
#ifdef MW_DL_DATA_PATH
        fileS = getFilePath(fileS);
#else
#if defined(_WIN32) || defined(_WIN64)
        
        char delim_unix[] = "/";
        char delim_win[] = "\\";
        
        while(((pos = fileS.find(delim_unix)) != std::string::npos) || 
              ((pos = fileS.find(delim_win)) != std::string::npos))
#else
        char delim_unix[] = "/";
        
        while((pos = fileS.find(delim_unix)) != std::string::npos)
#endif
        {
            if (pos == (fileS.size() - 1))
            {
                fileS = "";
                break;
            }
            fileS = fileS.substr(pos+1);
        }
#endif

        if (!fileS.empty())
        {
            fp = fopen(fileS.c_str(), "rb");           
        }
        
        if (!fp)
        {
            std::string errmsg = std::string("Unable to find the ") + 
                    fileS + std::string(" binary file in ") + codegenFolder +
                    std::string(" .");
            throw std::runtime_error(errmsg.c_str());
        }
    }

    return fp;
}

std::runtime_error MWCNNLayer::getFileOpenError(const char* filename)
{
    const std::string message = std::string("Error! Unable to open file ") +
        std::string(filename);
    return std::runtime_error(message);
}

void MWCNNLayer::setName(const std::string& n)
{
    m_name = n;
    return;
}

MWTensor* MWCNNLayer::getInputTensor(int index)
{ 
    std::map<int, MWTensor*>::iterator it = m_input.find(index);
    assert(it != m_input.end());
    return it->second;
}

MWTensor* MWCNNLayer::getOutputTensor(size_t index)
{
    std::map<int, MWTensor*>::iterator it = m_output.find(static_cast<const int>(index));
    assert(it != m_output.end());
    return it->second;
}

void MWCNNLayer::setInputTensor(MWTensor * other, int index)
{
    m_input[index] = other;
}

int MWCNNLayer::getHeight(int index)
{
    return getOutputTensor(index)->getHeight();
}

int MWCNNLayer::getBatchSize()
{
    // return batch size from the output tensor
    return getOutputTensor(0)->getBatchSize();
}

int MWCNNLayer::getWidth(int index)
{
    return getOutputTensor(index)->getWidth();
}

int MWCNNLayer::getNumInputFeatures(int index)
{
    return getInputTensor(index)->getChannels();
}

int MWCNNLayer::getNumOutputFeatures(int index)
{
    return getOutputTensor(index)->getChannels();
}

float* MWCNNLayer::getLayerOutput(int index)
{
   // assumes layer output is float type
   return getOutputTensor(index)->getData<float>();
}

void MWCNNLayer::allocateOutputTensor(int numHeight, int numWidth, int numChannels, int batchSize, int sequenceLength, void* data, int index) 
{
    MWTensor* op = new MWTensor(numHeight, numWidth, numChannels, batchSize, sequenceLength, data, this, index);
    assert(op != NULL);
    std::map<int, MWTensor*>::iterator it = m_output.find(index);
    assert(it == m_output.end());
    m_output[index]  = op;
}

void MWCNNLayer::resizeOutputTensor(int numHeight, int numWidth, int numChannels, int batchSize, int sequenceLength, int index)
{
    std::map<int, MWTensor*>::iterator it = m_output.find(index);
    assert(it != m_output.end());
    it->second->setHeight(numHeight);
    it->second->setWidth(numWidth);
    it->second->setChannels(numChannels);
    it->second->setBatchSize(batchSize);
    it->second->setSequenceLength(sequenceLength);
}

void MWCNNLayer::loadParams(const char* MW_mangled_fileName, const int MW_mangled_num, float* MW_mangled_buffer)
{
    // MW_mangled_buffer is float buffer of size MW_mangled_num

    FILE* MW_mangled_fp = MWCNNLayer::openBinaryFile(MW_mangled_fileName);     
    assert(MW_mangled_fp);
    call_fread(MW_mangled_buffer, sizeof(float), MW_mangled_num, MW_mangled_fp, MW_mangled_fileName);
    fclose(MW_mangled_fp);
}

MWTensor::MWTensor(int height, int width, int channels, int batchsize, int sequencelength, void* data, MWCNNLayer* owner, int srcport) :
    m_height(height),
    m_width(width),
    m_channels(channels),
    m_batchSize(batchsize),
    m_sequenceLength(sequencelength),
    m_data(data),
    m_owner(owner),
    m_srcport(srcport),
    opBufIndex(-1)
{
}

MWTensor::~MWTensor()
{
}


//Creating the ImageInputLayer
//InputSize should be [h w n].
//If normalization is 'zerocenter', withAvg should be true.
//g1429526: currently AverageImage is not accessible.
//Will have to update the codegen to generate avg binary file once the geck is complete.
//And 'zerocenter' is the only supported transformation for this layer.
void MWInputLayer::createInputLayer(MWTargetNetworkImpl* ntwk_impl, MWTensor* m_in, int m_height, int m_width, int m_channels, int m_withAvg, const char* avg_file_name, int outbufIdx)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    setInputTensor(m_in);
    allocateOutputTensor(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    m_impl = new MWInputLayerImpl(this, ntwk_impl, m_height, m_width, m_channels, m_withAvg, avg_file_name);
    
#else
    // populate output tensor
    allocateOutputTensor(m_height,
                         m_width,
                         m_channels,
                         m_in->getBatchSize(),
                         1,
                         NULL);
    
    assert(m_in->getSequenceLength() == 1);

    m_impl = new MWInputLayerImpl(this,
                                  ntwk_impl,
                                  m_in->getBatchSize(),
                                  m_height,
                                  m_width,
                                  m_channels,
                                  m_withAvg,
                                  avg_file_name,
                                  outbufIdx);
    
    assert(getOutputTensor()->getSequenceLength() == 1);

    return;
#endif
}

void MWInputLayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    resizeOutputTensor(getInputTensor(0)->getHeight(),
                       getInputTensor(0)->getWidth(),
                       getInputTensor(0)->getChannels(),
                       getInputTensor(0)->getBatchSize(),
                       getInputTensor(0)->getSequenceLength());

    assert(getOutputTensor()->getSequenceLength() == 1);

    m_impl->propagateSize();
#endif
}

//Create ReLULayer
void MWReLULayer::createReLULayer(MWTargetNetworkImpl* ntwk_impl, MWTensor* m_in, int inPlace, int outbufIdx)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    setInputTensor(m_in);
    allocateOutputTensor(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    m_impl = new MWReLULayerImpl(this, ntwk_impl, inPlace);
    
#else
    setInputTensor(m_in);

    // allocate output, reusing input tensor's data buffer
    int numOutputFeatures = getInputTensor()->getChannels();
    allocateOutputTensor(getInputTensor()->getHeight(), getInputTensor()->getWidth(), numOutputFeatures, getInputTensor()->getBatchSize(), getInputTensor()->getSequenceLength(), NULL);
   
    m_impl = new MWReLULayerImpl(this, ntwk_impl, inPlace, outbufIdx);

    return;
#endif
}

void MWReLULayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    resizeOutputTensor(getInputTensor()->getHeight(),
                       getInputTensor()->getWidth(),
                       getInputTensor()->getChannels(),
                       getInputTensor()->getBatchSize(),
                       getInputTensor()->getSequenceLength());

    m_impl->propagateSize();
#endif
}

//Create CrossChannelNormalizationLayer
//Parameters here are the same naming as NNT.
void MWNormLayer::createNormLayer(MWTargetNetworkImpl* ntwk_impl, MWTensor* m_in, unsigned m_WindowChannelSize, double m_Alpha, double m_Beta, double m_K, int outbufIdx)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    setInputTensor(m_in);
    allocateOutputTensor(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    m_impl = new MWNormLayerImpl(this, ntwk_impl, m_WindowChannelSize, m_Alpha, m_Beta, m_K);
    
#else
    setInputTensor(m_in);
    
    int numOutputFeatures = getInputTensor()->getChannels();
    allocateOutputTensor(getInputTensor()->getHeight(), getInputTensor()->getWidth(), numOutputFeatures, getInputTensor()->getBatchSize(), getInputTensor()->getSequenceLength(), NULL);
    assert(getOutputTensor()->getSequenceLength() == 1);

    m_impl = new MWNormLayerImpl(this, ntwk_impl, m_WindowChannelSize, m_Alpha, m_Beta, m_K, outbufIdx);
#endif
}

void MWNormLayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    assert(getInputTensor()->getSequenceLength() == 1);
    
    resizeOutputTensor(getInputTensor()->getHeight(),
                       getInputTensor()->getWidth(),
                       getInputTensor()->getChannels(),
                       getInputTensor()->getBatchSize(),
                       getInputTensor()->getSequenceLength());

    m_impl->propagateSize();
#endif
}

//Create MaxPooling2DLayer with PoolSize = [ PoolH PoolW ]
//                                Stride = [ StrideH StrideW ]
//                               Padding = [ PaddingH_T PaddingH_B PaddingW_L PaddingW_R ]
void MWMaxPoolingLayer::createMaxPoolingLayer(MWTargetNetworkImpl* ntwk_impl, MWTensor* m_in, int m_PoolH, int m_PoolW, int m_StrideH, int m_StrideW, int m_PaddingH_T,int m_PaddingH_B, int m_PaddingW_L, int m_PaddingW_R, bool m_hasIndices, int numOutputs, ...)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    setInputTensor(m_in);
    allocateOutputTensor(-1, -1, -1, -1, -1, NULL, 0);

    if (m_hasIndices)
    {
        // allocate index tensor
        allocateOutputTensor(-1, -1, -1, -1, -1, NULL, 1);
    }

    strideH = m_StrideH;
    strideW = m_StrideW;
    
    poolH = m_PoolH;
    poolW = m_PoolW;

    isGlobalAveragePooling = (poolH == -1 ) && (poolW == -1);

    paddingH_T = m_PaddingH_T;
    paddingH_B = m_PaddingH_B;
    paddingW_L = m_PaddingW_L;
    paddingW_R = m_PaddingW_R;

    hasIndices = m_hasIndices;

    {
        va_list args;
        va_start(args, numOutputs);
        std::vector<int> bufIndices(numOutputs, -1);
   
        for(int i = 0; i < numOutputs; i++)
        {
            bufIndices[i] = va_arg(args, int);
        }

        for (int i = 0; i < getNumOutputs(); ++i) {
            getOutputTensor(i)->setopBufIndex(bufIndices[i]);
        }

        m_impl = new MWMaxPoolingLayerImpl(this, ntwk_impl, m_PoolH, m_PoolW, m_StrideH, m_StrideW, m_PaddingH_T, m_PaddingH_B, m_PaddingW_L, m_PaddingW_R, m_hasIndices, numOutputs);
    }
#else
    setInputTensor(m_in);

    // Global Max Pooling case
    if ((m_PoolH == -1 )&& (m_PoolW == -1)){
        m_PoolH = getInputTensor()->getHeight();
        m_PoolW = getInputTensor()->getWidth();
    }  

    int outputH = ((getInputTensor()->getHeight()- m_PoolH + m_PaddingH_T + m_PaddingH_B)/m_StrideH) + 1;
    int outputW = ((getInputTensor()->getWidth()- m_PoolW + m_PaddingW_L + m_PaddingW_R)/m_StrideW) + 1;

    int numOutputFeatures = getInputTensor()->getChannels();
    allocateOutputTensor(outputH, outputW, numOutputFeatures, getInputTensor()->getBatchSize(), getInputTensor()->getSequenceLength(), NULL, 0);
    assert(getOutputTensor()->getSequenceLength() == 1);

    if (m_hasIndices)
    {
        // allocate index tensor
        allocateOutputTensor(outputH, outputW, numOutputFeatures, getInputTensor()->getBatchSize(), getInputTensor()->getSequenceLength(), NULL, 1);
        MWTensor *indexOpTensor = getOutputTensor(1);
        assert(indexOpTensor->getSequenceLength() == 1);
    }


    {
        va_list args;
        va_start(args, numOutputs);
        std::vector<int> bufIndices(numOutputs, -1);
   
        for(int i = 0; i < numOutputs; i++)
        {
            bufIndices[i] = va_arg(args, int);
        }

        m_impl = new MWMaxPoolingLayerImpl(this, ntwk_impl, m_PoolH, m_PoolW, m_StrideH, m_StrideW, m_PaddingH_T, m_PaddingH_B, m_PaddingW_L, m_PaddingW_R, m_hasIndices, numOutputs, bufIndices);

    }
#endif
}

void MWMaxPoolingLayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    // Global Average Pooling case
    if (isGlobalAveragePooling)
    {
        poolH = getInputTensor()->getHeight();
        poolW = getInputTensor()->getWidth();
    }
    
    int outputH = ((getInputTensor()->getHeight()- poolH + paddingH_T + paddingH_B)/strideH) + 1;
    int outputW = ((getInputTensor()->getWidth()- poolW + paddingW_L + paddingW_R)/strideW) + 1;

    assert(getInputTensor()->getSequenceLength() == 1);
    
    resizeOutputTensor(outputH,
                       outputW,
                       getInputTensor()->getChannels(),
                       getInputTensor()->getBatchSize(),
                       getInputTensor()->getSequenceLength());

    if (hasIndices)
    {
        // allocate index tensor
        resizeOutputTensor(outputH,
                           outputW,
                           getInputTensor()->getChannels(),
                           getInputTensor()->getBatchSize(),
                           getInputTensor()->getSequenceLength(),
                           1);
    }

    m_impl->propagateSize();
#endif
}

//Create FullyConnectedLayer with corresponding InputSize and OutputSize.
//This implementation uses SGEMV for m_BatchSize = 1 and SGEMM for others.
void MWFCLayer::createFCLayer(MWTargetNetworkImpl* ntwk_impl, MWTensor* m_in, int m_InputSize, int m_OutputSize, const char* m_weights_file, const char* m_bias_file, int outbufIdx)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    setInputTensor(m_in);
    allocateOutputTensor(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    numInputFeatures = m_InputSize;
    numOutputFeatures = m_OutputSize;

    m_impl = new MWFCLayerImpl(this,
                               ntwk_impl,
                               m_InputSize,
                               m_OutputSize,
                               m_weights_file,
                               m_bias_file);
    
#else
    setInputTensor(m_in);
    allocateOutputTensor(1, 1, m_OutputSize, getInputTensor()->getBatchSize(), getInputTensor()->getSequenceLength(), NULL);

    m_impl = new MWFCLayerImpl(this, ntwk_impl, m_InputSize, m_weights_file, m_bias_file, outbufIdx);
    
    return;
#endif
}

void MWFCLayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    resizeOutputTensor(1,
                       1,
                       numOutputFeatures,
                       getInputTensor()->getBatchSize(),
                       getInputTensor()->getSequenceLength());

    m_impl->propagateSize();
#endif
}

//Create SoftmaxLayer
void MWSoftmaxLayer::createSoftmaxLayer(MWTargetNetworkImpl* ntwk_impl, MWTensor* m_in, int outbufIdx)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    setInputTensor(m_in);
    allocateOutputTensor(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    m_impl = new MWSoftmaxLayerImpl(this, ntwk_impl);

#else
    setInputTensor(m_in);
    
    allocateOutputTensor(getInputTensor()->getHeight(), getInputTensor()->getWidth(), getInputTensor()->getChannels(), getInputTensor()->getBatchSize(), getInputTensor()->getSequenceLength(), NULL);

    m_impl = new MWSoftmaxLayerImpl(this, ntwk_impl, outbufIdx);
    
    return;
#endif
}

void MWSoftmaxLayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    resizeOutputTensor(getInputTensor()->getHeight(),
                       getInputTensor()->getWidth(),
                       getInputTensor()->getChannels(),
                       getInputTensor()->getBatchSize(),
                       getInputTensor()->getSequenceLength());

    m_impl->propagateSize();
#endif
}

//Create ClassificationOutputLayer
//We are doing inference only so LossFunction is not needed.
//This layer would do nothing but point the data to previous layer.
void MWOutputLayer::createOutputLayer(MWTargetNetworkImpl* ntwk_impl, MWTensor* m_in, int outbufIdx)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    setInputTensor(m_in);
    allocateOutputTensor(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    m_impl = new MWOutputLayerImpl(this, ntwk_impl);

#else
    setInputTensor(m_in);
    allocateOutputTensor(getInputTensor()->getHeight(),
                         getInputTensor()->getWidth(),
                         getInputTensor()->getChannels(),
                         getInputTensor()->getBatchSize(),
                         getInputTensor()->getSequenceLength(),
                         getInputTensor()->getData<float>());

    m_impl = new MWOutputLayerImpl(this, ntwk_impl, outbufIdx);
    return;
#endif
}

void MWOutputLayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    resizeOutputTensor(getInputTensor()->getHeight(),
                       getInputTensor()->getWidth(),
                       getInputTensor()->getChannels(),
                       getInputTensor()->getBatchSize(),
                       getInputTensor()->getSequenceLength());
    m_impl->propagateSize();
#endif
}

void MWOutputLayer::predict() 
{
    m_impl->predict();
}


//Create pass through
//This layer would do nothing but point the data to previous layer.
void MWPassthroughLayer::createPassthroughLayer(MWTargetNetworkImpl* /* ntwk_impl */, MWTensor* m_in, int /* outbufIdx */)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    setInputTensor(m_in);
    allocateOutputTensor(-1, -1, -1, -1, -1, NULL);

#else
    
    setInputTensor(m_in);

    int numOutputFeatures = getInputTensor()->getChannels();
    allocateOutputTensor(getInputTensor()->getHeight(),
                         getInputTensor()->getWidth(),
                         numOutputFeatures,
                         getInputTensor()->getBatchSize(),
                         getInputTensor()->getSequenceLength(),
                         getInputTensor()->getData<float>());
    
    return;
#endif
}

void MWPassthroughLayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    resizeOutputTensor(getInputTensor(0)->getHeight(),
                       getInputTensor(0)->getWidth(),
                       getInputTensor(0)->getChannels(),
                       getInputTensor(0)->getBatchSize(),
                       getInputTensor(0)->getSequenceLength());
#endif
}

void MWPassthroughLayer::allocate()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    getOutputTensor(0)->setData(getInputTensor(0)->getData<float>());
#endif
}

//Create AvgPooling2DLayer with PoolSize = [ PoolH PoolW ]
//                                Stride = [ StrideH StrideW ]
//                               Padding = [ PaddingH_T PaddingH_T_B PaddingW_L PaddingW_R ]
void MWAvgPoolingLayer::createAvgPoolingLayer(MWTargetNetworkImpl* ntwk_impl, MWTensor* m_in, int m_PoolH, int m_PoolW, int m_StrideH, int m_StrideW, int m_PaddingH_T, int m_PaddingH_B, int m_PaddingW_L, int m_PaddingW_R, int outbufIdx)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    setInputTensor(m_in);
    allocateOutputTensor(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);
    
    strideH = m_StrideH;
    strideW = m_StrideW;
    
    poolH = m_PoolH;
    poolW = m_PoolW;

    isGlobalAveragePooling = (poolH == -1 ) && (poolW == -1);

    paddingH_T = m_PaddingH_T;
    paddingH_B = m_PaddingH_B;
    paddingW_L = m_PaddingW_L;
    paddingW_R = m_PaddingW_R;

    m_impl = new MWAvgPoolingLayerImpl(this, ntwk_impl, m_PoolH, m_PoolW, m_StrideH, m_StrideW, m_PaddingH_T, m_PaddingH_B, m_PaddingW_L, m_PaddingW_R);

#else
    setInputTensor(m_in);

    // Global Average Pooling case
    if ((m_PoolH == -1 )&& (m_PoolW == -1)){
        m_PoolH = getInputTensor()->getHeight();
        m_PoolW = getInputTensor()->getWidth();
    }        
    
    int outputH = ((getInputTensor()->getHeight()- m_PoolH + m_PaddingH_T + m_PaddingH_B)/m_StrideH) + 1;
    int outputW = ((getInputTensor()->getWidth()- m_PoolW + m_PaddingW_L + m_PaddingW_R)/m_StrideW) + 1;

    int numOutputFeatures = getInputTensor()->getChannels();
    allocateOutputTensor(outputH, outputW, numOutputFeatures, getInputTensor()->getBatchSize(), getInputTensor()->getSequenceLength(), NULL);
    assert(getOutputTensor()->getSequenceLength() == 1);
  
    m_impl = new MWAvgPoolingLayerImpl(this, ntwk_impl, m_PoolH, m_PoolW, m_StrideH, m_StrideW, m_PaddingH_T, m_PaddingH_B, m_PaddingW_L, m_PaddingW_R, outbufIdx);
#endif
}

void MWAvgPoolingLayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)

    // Global Average Pooling case
    if (isGlobalAveragePooling)
    {
        poolH = getInputTensor()->getHeight();
        poolW = getInputTensor()->getWidth();
    }
    
    int outputH = ((getInputTensor()->getHeight()- poolH + paddingH_T + paddingH_B)/strideH) + 1;
    int outputW = ((getInputTensor()->getWidth()- poolW + paddingW_L + paddingW_R)/strideW) + 1;
    
    assert(getInputTensor()->getSequenceLength() == 1);
    
    resizeOutputTensor(outputH,
                       outputW,
                       getInputTensor()->getChannels(),
                       getInputTensor()->getBatchSize(),
                       getInputTensor()->getSequenceLength());

    m_impl->propagateSize();
#endif
}

