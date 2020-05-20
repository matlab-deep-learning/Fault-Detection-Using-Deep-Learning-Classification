/* Copyright 2018 The MathWorks, Inc. */

#ifndef _MW_LSTM_LAYER_
#define _MW_LSTM_LAYER_

#include "cnn_api.hpp"

/**
 * Codegen class for LSTM layer
 */
class MWTargetNetworkImpl;

class MWLSTMLayer: public MWCNNLayer
{
  public:
    
    MWLSTMLayer(){}
    ~MWLSTMLayer(){}
    void createLSTMLayer(MWTargetNetworkImpl*,
                         MWTensor*,
                         int,
                         int,
                         bool,
                         bool, 
                         int, 
                         const char*,
                         const char*,
                         const char*,
                         const char*,
                         int);
    void propagateSize();
    void resetState();
    void updateState();
   
  public:
    int hiddenSize;
    bool lastMode;
    bool isBidirectional;
    int numFeatures;
    int numLayers;
    
};

#endif
