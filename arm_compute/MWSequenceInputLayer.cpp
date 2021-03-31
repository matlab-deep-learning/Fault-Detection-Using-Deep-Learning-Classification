/* Copyright 2018-2020 The MathWorks, Inc. */

#include "MWSequenceInputLayerImpl.hpp"
#include "MWSequenceInputLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWCNNLayer.hpp"

#include <cassert>
#include <cstdio>

void MWSequenceInputLayer::createSequenceInputLayer(MWTargetNetworkImpl* ntwk_impl, MWTensorBase* m_in, bool m_isImageInput, int outbufIdx)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    setInputTensor(m_in);
    allocateOutputTensor<float>(-1, -1, -1, -1, -1, NULL);

	isImageInput = m_isImageInput;
    getOutputTensor(0)->setopBufIndex(outbufIdx);

    m_impl = new MWSequenceInputLayerImpl(this, ntwk_impl);
    
#else
    // populate output tensor
    allocateOutputTensor<float>(m_in->getHeight(),
                                m_in->getWidth(),
                                m_in->getChannels(),
                                m_in->getBatchSize(),
                                m_in->getSequenceLength(),
                                NULL);
    
    m_impl = new MWSequenceInputLayerImpl(this, ntwk_impl, m_in->getChannels(), m_in->getBatchSize(), outbufIdx);
    
    return;
#endif
}

void MWSequenceInputLayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    resizeOutputTensor(getInputTensor(0)->getHeight(),
                       getInputTensor(0)->getWidth(),
                       getInputTensor(0)->getChannels(),
                       getInputTensor(0)->getBatchSize(),
                       getInputTensor(0)->getSequenceLength());

    m_impl->propagateSize();
#endif
}
