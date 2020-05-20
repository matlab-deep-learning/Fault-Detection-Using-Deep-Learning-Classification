#include "MWLSTMLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWLSTMLayerImpl.hpp"

void MWLSTMLayer::createLSTMLayer(MWTargetNetworkImpl* ntwk_impl,
                                  MWTensor* m_in,
                                  int m_num_features,
                                  int m_hidden_units,
                                  bool m_last_mode,
                                  bool m_is_bidirectional, 
                                  int m_num_layers, 
                                  const char* m_weights_file,
                                  const char* m_bias_file,
                                  const char* m_initial_hidden_state_file,
                                  const char* m_initial_cell_state_file,
                                  int outbufIdx)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    setInputTensor(m_in);
    allocateOutputTensor(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);
    
    hiddenSize = m_hidden_units;
    lastMode = m_last_mode;
    isBidirectional = m_is_bidirectional;
    numFeatures = m_num_features;
    numLayers = m_num_layers;

    m_impl = new MWLSTMLayerImpl(this,
                                 ntwk_impl,
                                 m_num_features,
                                 m_hidden_units,
                                 m_last_mode,
                                 m_weights_file,
                                 m_bias_file,
                                 m_initial_hidden_state_file,
                                 m_initial_cell_state_file);
    
#else
    setInputTensor(m_in);

    // allocate output tensor
    // height = 1, width = 1, channels = numHiddenUnits, batchSize = batchSize, seqLength = seqLength
    hiddenSize = m_hidden_units;
    lastMode = m_last_mode;
    isBidirectional = m_is_bidirectional;
    numFeatures = m_num_features;

    int outSequenceLength = m_last_mode ? 1 : getInputTensor()->getSequenceLength();
    allocateOutputTensor(1,
                         1,
                         isBidirectional ? 2*hiddenSize : hiddenSize,
                         getInputTensor()->getBatchSize(),
                         outSequenceLength,
                         NULL);

    // will need to lift this assumption for image sequences
    assert(getOutputTensor()->getHeight() == 1 && getOutputTensor()->getWidth() == 1);

    m_impl = new MWLSTMLayerImpl(this,
                                 ntwk_impl,
                                 m_last_mode,
                                 m_num_layers,
                                 m_weights_file,
                                 m_bias_file,
                                 m_initial_hidden_state_file,
                                 m_initial_cell_state_file,
                                 outbufIdx);
#endif
}

void MWLSTMLayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    // allocate output tensor
    // height = 1, width = 1, channels = numHiddenUnits, batchSize = batchSize, seqLength = seqLength
    int outSequenceLength = lastMode ? 1 : getInputTensor()->getSequenceLength();
    resizeOutputTensor(1,
                       1,
                       isBidirectional ? 2*hiddenSize : hiddenSize,
                       getInputTensor()->getBatchSize(),
                       outSequenceLength);

    // will need to lift this assumption for image sequences
    assert(getOutputTensor()->getHeight() == 1 && getOutputTensor()->getWidth() == 1);

    m_impl->propagateSize();
#endif
}

void MWLSTMLayer::resetState() {
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    static_cast<MWLSTMLayerImpl*>(m_impl)->resetState();
#endif
}

void MWLSTMLayer::updateState() {
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    static_cast<MWLSTMLayerImpl*>(m_impl)->updateState();
#endif
}
