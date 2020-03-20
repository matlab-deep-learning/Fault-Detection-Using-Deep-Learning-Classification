/* Copyright 2019 The MathWorks, Inc. */

#ifndef _MW_ARMNEON_SEQINPUT_LAYER_IMPL_
#define _MW_ARMNEON_SEQINPUT_LAYER_IMPL_

#include "MWCNNLayerImpl.hpp"

/**
 * Codegen class for Sequence Input layer implementation
 */
class MWSequenceInputLayerImpl : public MWCNNLayerImpl {
  public:
    MWSequenceInputLayerImpl(MWCNNLayer*, MWTargetNetworkImpl*);
    ~MWSequenceInputLayerImpl();
    void predict();
    void allocateOutputData(int);
    void deallocateOutputData(int);

  private:
    bool isPaddingEnabled;
    float* m_inputData;

  private:
    void propagateSize();
};

#endif
