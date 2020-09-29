/* Copyright 2018 The MathWorks, Inc. */

#include "MWSequenceInputLayerImpl.hpp"
#include "MWSequenceInputLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "cnn_api.hpp"

#include <cassert>
#include <stdio.h>

void MWSequenceInputLayer::createSequenceInputLayer(MWTargetNetworkImpl* ntwk_impl, MWTensor* m_in, int outbufIdx)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    setInputTensor(m_in);
    allocateOutputTensor(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    m_impl = new MWSequenceInputLayerImpl(this, ntwk_impl);
    
#else
    // populate output tensor
    // height = 1, width = 1, channels = numFeatures, batchSize = batchSize, seqLength = seqLength
    allocateOutputTensor(1, 1, m_in->getChannels(), m_in->getBatchSize(), m_in->getSequenceLength(), NULL);
    
    m_impl = new MWSequenceInputLayerImpl(this, ntwk_impl, m_in->getChannels(), m_in->getBatchSize(), outbufIdx);
    
    return;
#endif
}

void MWSequenceInputLayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    resizeOutputTensor(1,
                       1,
                       getInputTensor(0)->getChannels(),
                       getInputTensor(0)->getBatchSize(),
                       getInputTensor(0)->getSequenceLength());

    m_impl->propagateSize();
#endif
}
