/* Copyright 2019 The MathWorks, Inc. */

#ifndef _MW_ARMNEON_SEQINPUT_LAYER_IMPL_
#define _MW_ARMNEON_SEQINPUT_LAYER_IMPL_

#include "MWCNNLayerImpl.hpp"

class MWCNNLayer;
class MWTargetNetworkImpl;

/**
 * Codegen class for Sequence Input layer implementation
 */
class MWSequenceInputLayerImpl : public MWCNNLayerImpl {
  public:
    MWSequenceInputLayerImpl(MWCNNLayer*, MWTargetNetworkImpl*);
    ~MWSequenceInputLayerImpl();
    void predict();

  private:
    void propagateSize();
};

#endif
