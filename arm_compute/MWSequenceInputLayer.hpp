/* Copyright 2018 The MathWorks, Inc. */

#ifndef _MW_SEQUENCEINPUT_LAYER_
#define _MW_SEQUENCEINPUT_LAYER_

#include "cnn_api.hpp"

/**
 * Codegen class for SequenceInput layer
 */
class MWTargetNetworkImpl;

class MWSequenceInputLayer: public MWCNNLayer
{   
  public:
    MWSequenceInputLayer() {}
    virtual ~MWSequenceInputLayer() {}

    void createSequenceInputLayer(MWTargetNetworkImpl* ntwk_impl,
                                  MWTensor* m_in,
                                  int);
    void propagateSize();
 
};

#endif
