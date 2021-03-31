/* Copyright 2018 The MathWorks, Inc. */

#ifndef _MW_SEQUENCEINPUT_LAYER_
#define _MW_SEQUENCEINPUT_LAYER_

#include "MWCNNLayer.hpp"

class MWTargetNetworkImpl;
class MWTensorBase;

/**
 * Codegen class for SequenceInput layer
 */
class MWSequenceInputLayer: public MWCNNLayer
{   
  public:
    MWSequenceInputLayer() {}
    virtual ~MWSequenceInputLayer() {}

    void createSequenceInputLayer(MWTargetNetworkImpl* ntwk_impl,
                                  MWTensorBase* m_in,
								  bool,
                                  int);
    void propagateSize();
	bool isImageInput;
 
};

#endif
