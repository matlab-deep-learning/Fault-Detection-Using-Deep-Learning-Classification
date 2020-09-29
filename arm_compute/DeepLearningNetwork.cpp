//
// File: DeepLearningNetwork.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 08-May-2020 10:27:24
//

// Include Files
#include "DeepLearningNetwork.h"
#include "matlabCodegenHandle.h"
#include "predictAndUpdateState.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"
#include "streamingClassifier_rtwutil.h"

// Type Definitions
#include "cnn_api.hpp"
#include "MWLSTMLayer.hpp"
#include "MWSequenceInputLayer.hpp"
#include "MWTargetNetworkImpl.hpp"

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//

//
// Arguments    : int numBufstoAllocate
//                MWCNNLayer *layers[7]
//                int numLayers
// Return Type  : void
//

//
// Arguments    : void
// Return Type  : void
//

//
// Arguments    : void
// Return Type  : void
//

//
// Arguments    : MWTargetNetworkImpl *targetImpl
//                MWTensor *b
//                int InputSize
//                int OutputSize
//                const char * c_a___arm_compute_cnn_TrainedMo
//                const char * d_a___arm_compute_cnn_TrainedMo
//                int c
// Return Type  : void
//

//
// Arguments    : MWTargetNetworkImpl *targetImpl
//                MWTensor *b
//                int FeatureDimension
//                int HiddenSize
//                bool LastMode
//                bool IsBidirectional
//                int NumLayers
//                const char * c_a___arm_compute_cnn_TrainedMo
//                const char * d_a___arm_compute_cnn_TrainedMo
//                const char * e_a___arm_compute_cnn_TrainedMo
//                const char * f_a___arm_compute_cnn_TrainedMo
//                int c
// Return Type  : void
//

//
// Arguments    : MWTargetNetworkImpl *targetImpl
//                MWTensor *b
//                int c
// Return Type  : void
//

//
// Arguments    : MWTargetNetworkImpl *targetImpl
//                MWTensor *b
//                int c
// Return Type  : void
//

//
// Arguments    : MWTargetNetworkImpl *targetImpl
//                MWTensor *m_in
//                int b
// Return Type  : void
//

//
// Arguments    : MWTargetNetworkImpl *targetImpl
//                MWTensor *b
//                int c
// Return Type  : void
//

//
// Arguments    : void
// Return Type  : void
//

//
// Arguments    : void
// Return Type  : void
//

//
// Arguments    : void
// Return Type  : float *
//

//
// Arguments    : int handle
// Return Type  : void
//

//
// Arguments    : MWCNNLayer *layers[7]
//                int layerIdx
//                int portIdx
// Return Type  : float *
//

//
// Arguments    : void
// Return Type  : int *
//

//
// Arguments    : void
// Return Type  : void
//

//
// Arguments    : void
// Return Type  : void
//

//
// Arguments    : void
// Return Type  : void
//

//
// Arguments    : void
// Return Type  : void
//

//
// Arguments    : void
// Return Type  : void
//

//
// Arguments    : int batchSize
// Return Type  : void
//

//
// Arguments    : int channels
// Return Type  : void
//

//
// Arguments    : float *data
// Return Type  : void
//

//
// Arguments    : int height
// Return Type  : void
//

//
// Arguments    : const char * name
// Return Type  : void
//

//
// Arguments    : int sequenceLength
// Return Type  : void
//

//
// Arguments    : int width
// Return Type  : void
//

//
// Arguments    : void
// Return Type  : void
//

//
// Arguments    : void
// Return Type  : void
//
b_TrainedModel_0::b_TrainedModel_0()
{
  this->numLayers = 7;
  this->targetImpl = 0;
  this->layers[0] = new MWSequenceInputLayer;
  this->layers[0]->setName("sequenceinput");
  this->layers[1] = new MWLSTMLayer;
  this->layers[1]->setName("lstm_1");
  this->layers[2] = new MWPassthroughLayer;
  this->layers[2]->setName("dropout");
  this->layers[3] = new MWLSTMLayer;
  this->layers[3]->setName("lstm_2");
  this->layers[4] = new MWFCLayer;
  this->layers[4]->setName("fc");
  this->layers[5] = new MWSoftmaxLayer;
  this->layers[5]->setName("softmax");
  this->layers[6] = new MWOutputLayer;
  this->layers[6]->setName("classoutput");
  this->targetImpl = new MWTargetNetworkImpl;
  this->inputTensor = new MWTensor;
  this->inputTensor->setHeight(1);
  this->inputTensor->setWidth(1);
  this->inputTensor->setChannels(10);
  this->inputTensor->setBatchSize(1);
  this->outputTensor = new MWTensor;
  this->maxSequenceLength = -1;
}

//
// Arguments    : void
// Return Type  : void
//
b_TrainedModel_0::~b_TrainedModel_0()
{
  this->cleanup();
  for (int idx = 0; idx < 7; idx++) {
    delete this->layers[idx];
  }

  if (this->targetImpl) {
    delete this->targetImpl;
  }

  delete this->inputTensor;
  delete this->outputTensor;
}

//
// Arguments    : void
// Return Type  : void
//
void b_TrainedModel_0::allocate()
{
  this->targetImpl->allocate(2, this->layers, this->numLayers);
  for (int idx = 0; idx < 7; idx++) {
    this->layers[idx]->allocate();
  }

  this->inputTensor->setData(this->layers[0]->getLayerOutput(0));
  this->outputTensor->setData(this->layers[6]->getLayerOutput(0));
}

//
// Arguments    : void
// Return Type  : void
//
void b_TrainedModel_0::cleanup()
{
  this->deallocate();
  for (int idx = 0; idx < 7; idx++) {
    this->layers[idx]->cleanup();
  }

  if (this->targetImpl) {
    this->targetImpl->cleanup();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_TrainedModel_0::deallocate()
{
  this->targetImpl->deallocate();
  for (int idx = 0; idx < 7; idx++) {
    this->layers[idx]->deallocate();
  }
}

//
// Arguments    : void
// Return Type  : float *
//
float *b_TrainedModel_0::getInputDataPointer()
{
  return this->inputTensor->getFloatData();
}

//
// Arguments    : int layerIndex
//                int portIndex
// Return Type  : float *
//
float *b_TrainedModel_0::getLayerOutput(int layerIndex, int portIndex)
{
  return this->targetImpl->getLayerOutput(this->layers, layerIndex, portIndex);
}

//
// Arguments    : void
// Return Type  : float *
//
float *b_TrainedModel_0::getOutputDataPointer()
{
  return this->outputTensor->getFloatData();
}

//
// Arguments    : void
// Return Type  : void
//
void b_TrainedModel_0::postsetup()
{
  this->targetImpl->postSetup();
}

//
// Arguments    : void
// Return Type  : void
//
void b_TrainedModel_0::predict()
{
  for (int idx = 0; idx < 7; idx++) {
    this->layers[idx]->predict();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_TrainedModel_0::resetState()
{
  (dynamic_cast<MWLSTMLayer *>(this->layers[1]))->resetState();
  (dynamic_cast<MWLSTMLayer *>(this->layers[3]))->resetState();
}

//
// Arguments    : int seqLength
// Return Type  : void
//
void b_TrainedModel_0::setSize(int seqLength)
{
  if (seqLength != this->inputTensor->getSequenceLength()) {
    this->inputTensor->setSequenceLength(seqLength);
    for (int idx = 0; idx < 7; idx++) {
      this->layers[idx]->propagateSize();
    }

    if (seqLength > this->maxSequenceLength) {
      if (this->maxSequenceLength != -1) {
        this->deallocate();
      }

      this->maxSequenceLength = seqLength;
      this->allocate();
    }

    this->postsetup();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_TrainedModel_0::setup()
{
  this->targetImpl->preSetup();
  (dynamic_cast<MWSequenceInputLayer *>(this->layers[0]))
    ->createSequenceInputLayer(this->targetImpl, this->inputTensor, 0);
  (dynamic_cast<MWLSTMLayer *>(this->layers[1]))->createLSTMLayer
    (this->targetImpl, this->layers[0]->getOutputTensor(0), 10, 100, false,
     false, 1, "./arm_compute/cnn_TrainedModel_lstm_1_w.bin",
     "./arm_compute/cnn_TrainedModel_lstm_1_b.bin",
     "./arm_compute/cnn_TrainedModel_lstm_1_hx.bin",
     "./arm_compute/cnn_TrainedModel_lstm_1_cx.bin", 1);
  (dynamic_cast<MWPassthroughLayer *>(this->layers[2]))->createPassthroughLayer
    (this->targetImpl, this->layers[1]->getOutputTensor(0), 1);
  (dynamic_cast<MWLSTMLayer *>(this->layers[3]))->createLSTMLayer
    (this->targetImpl, this->layers[2]->getOutputTensor(0), 100, 100, true,
     false, 1, "./arm_compute/cnn_TrainedModel_lstm_2_w.bin",
     "./arm_compute/cnn_TrainedModel_lstm_2_b.bin",
     "./arm_compute/cnn_TrainedModel_lstm_2_hx.bin",
     "./arm_compute/cnn_TrainedModel_lstm_2_cx.bin", 0);
  (dynamic_cast<MWFCLayer *>(this->layers[4]))->createFCLayer(this->targetImpl,
    this->layers[3]->getOutputTensor(0), 100, 8,
    "./arm_compute/cnn_TrainedModel_fc_w.bin",
    "./arm_compute/cnn_TrainedModel_fc_b.bin", 1);
  (dynamic_cast<MWSoftmaxLayer *>(this->layers[5]))->createSoftmaxLayer
    (this->targetImpl, this->layers[4]->getOutputTensor(0), 0);
  (dynamic_cast<MWOutputLayer *>(this->layers[6]))->createOutputLayer
    (this->targetImpl, this->layers[5]->getOutputTensor(0), 0);
}

//
// Arguments    : void
// Return Type  : void
//
void b_TrainedModel_0::updateState()
{
  (dynamic_cast<MWLSTMLayer *>(this->layers[1]))->updateState();
  (dynamic_cast<MWLSTMLayer *>(this->layers[3]))->updateState();
}

//
// Arguments    : b_TrainedModel_0 *obj
// Return Type  : void
//
void DeepLearningNetwork_setup(b_TrainedModel_0 *obj)
{
  obj->setup();
  obj->batchSize = 1;
}

//
// File trailer for DeepLearningNetwork.cpp
//
// [EOF]
//
