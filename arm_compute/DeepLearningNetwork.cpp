//
// File: DeepLearningNetwork.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 19-Mar-2021 15:00:36
//

// Include Files
#include "DeepLearningNetwork.h"
#include "rt_nonfinite.h"
#include "streamingClassifier_internal_types.h"
#include "MWCNNLayer.hpp"
#include "MWFCLayer.hpp"
#include "MWOutputLayer.hpp"
#include "MWRNNLayer.hpp"
#include "MWSequenceInputLayer.hpp"
#include "MWSoftmaxLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWTensor.hpp"
#include "MWTensorBase.hpp"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void TrainedModel0_0::allocate()
{
  this->targetImpl->allocate(2, this->layers, this->numLayers,
                             this->maxSequenceLength * 0);
  for (int idx{0}; idx < 6; idx++) {
    this->layers[idx]->allocate();
  }
  (static_cast<MWTensor<float> *>(this->inputTensors[0]))
      ->setData(this->layers[0]->getLayerOutput(0));
}

//
// Arguments    : void
// Return Type  : void
//
void TrainedModel0_0::cleanup()
{
  this->deallocate();
  for (int idx{0}; idx < 6; idx++) {
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
void TrainedModel0_0::deallocate()
{
  this->targetImpl->deallocate();
  for (int idx{0}; idx < 6; idx++) {
    this->layers[idx]->deallocate();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void TrainedModel0_0::postsetup()
{
  this->targetImpl->postSetup();
}

//
// Arguments    : void
// Return Type  : void
//
void TrainedModel0_0::resetState()
{
  (dynamic_cast<MWRNNLayer *>(this->layers[1]))->resetState();
  (dynamic_cast<MWRNNLayer *>(this->layers[2]))->resetState();
}

//
// Arguments    : void
// Return Type  : void
//
void TrainedModel0_0::setup()
{
  if (this->isInitialized) {
    this->resetState();
  } else {
    this->isInitialized = true;
    this->targetImpl->preSetup();
    (static_cast<MWSequenceInputLayer *>(this->layers[0]))
        ->createSequenceInputLayer(this->targetImpl, this->inputTensors[0],
                                   false, 0);
    (static_cast<MWRNNLayer *>(this->layers[1]))
        ->createRNNLayer(this->targetImpl, this->layers[0]->getOutputTensor(0),
                         10, 100, false, false, 0, 0, 0, "tanh", "sigmoid", 1,
                         "./arm_compute/cnn_TrainedModel0_0_lstm_1_w.bin",
                         "./arm_compute/cnn_TrainedModel0_0_lstm_1_b.bin",
                         "./arm_compute/cnn_TrainedModel0_0_lstm_1_hx.bin",
                         "./arm_compute/cnn_TrainedModel0_0_lstm_1_cx.bin", 1);
    (static_cast<MWRNNLayer *>(this->layers[2]))
        ->createRNNLayer(this->targetImpl, this->layers[1]->getOutputTensor(0),
                         100, 100, true, false, 0, 0, 0, "tanh", "sigmoid", 1,
                         "./arm_compute/cnn_TrainedModel0_0_lstm_2_w.bin",
                         "./arm_compute/cnn_TrainedModel0_0_lstm_2_b.bin",
                         "./arm_compute/cnn_TrainedModel0_0_lstm_2_hx.bin",
                         "./arm_compute/cnn_TrainedModel0_0_lstm_2_cx.bin", 0);
    (static_cast<MWFCLayer *>(this->layers[3]))
        ->createFCLayer(this->targetImpl, this->layers[2]->getOutputTensor(0),
                        100, 8, "./arm_compute/cnn_TrainedModel0_0_fc_w.bin",
                        "./arm_compute/cnn_TrainedModel0_0_fc_b.bin", 1);
    (static_cast<MWSoftmaxLayer *>(this->layers[4]))
        ->createSoftmaxLayer(this->targetImpl,
                             this->layers[3]->getOutputTensor(0), 0);
    (static_cast<MWOutputLayer *>(this->layers[5]))
        ->createOutputLayer(this->targetImpl,
                            this->layers[4]->getOutputTensor(0), -1);
    this->outputTensors[0] = this->layers[5]->getOutputTensor(0);
  }
}

//
// Arguments    : void
// Return Type  : ::TrainedModel0_0
//
TrainedModel0_0::TrainedModel0_0()
{
  this->numLayers = 6;
  this->isInitialized = false;
  this->targetImpl = 0;
  this->layers[0] = new MWSequenceInputLayer;
  this->layers[0]->setName("sequenceinput");
  this->layers[1] = new MWRNNLayer;
  this->layers[1]->setName("lstm_1");
  this->layers[2] = new MWRNNLayer;
  this->layers[2]->setName("lstm_2");
  this->layers[3] = new MWFCLayer;
  this->layers[3]->setName("fc");
  this->layers[4] = new MWSoftmaxLayer;
  this->layers[4]->setName("softmax");
  this->layers[5] = new MWOutputLayer;
  this->layers[5]->setName("classoutput");
  this->layers[5]->setInPlaceIndex(0, 0);
  this->targetImpl = new MWTargetNetworkImpl;
  this->inputTensors[0] = new MWTensor<float>;
  this->inputTensors[0]->setHeight(1);
  this->inputTensors[0]->setWidth(1);
  this->inputTensors[0]->setChannels(10);
  this->inputTensors[0]->setBatchSize(1);
  this->maxSequenceLength = -1;
}

//
// Arguments    : void
// Return Type  : void
//
TrainedModel0_0::~TrainedModel0_0()
{
  this->cleanup();
  for (int idx{0}; idx < 6; idx++) {
    delete this->layers[idx];
  }
  if (this->targetImpl) {
    delete this->targetImpl;
  }
  delete this->inputTensors[0];
}

//
// Arguments    : void
// Return Type  : int
//
int TrainedModel0_0::getBatchSize()
{
  return this->inputTensors[0]->getBatchSize();
}

//
// Arguments    : int b_index
// Return Type  : float *
//
float *TrainedModel0_0::getInputDataPointer(int b_index)
{
  return (static_cast<MWTensor<float> *>(this->inputTensors[b_index]))
      ->getData();
}

//
// Arguments    : void
// Return Type  : float *
//
float *TrainedModel0_0::getInputDataPointer()
{
  return (static_cast<MWTensor<float> *>(this->inputTensors[0]))->getData();
}

//
// Arguments    : int layerIndex
//                int portIndex
// Return Type  : float *
//
float *TrainedModel0_0::getLayerOutput(int layerIndex, int portIndex)
{
  return this->targetImpl->getLayerOutput(this->layers, layerIndex, portIndex);
}

//
// Arguments    : int layerIndex
//                int portIndex
// Return Type  : int
//
int TrainedModel0_0::getLayerOutputSize(int layerIndex, int portIndex)
{
  return this->layers[layerIndex]
             ->getOutputTensor(portIndex)
             ->getNumElements() *
         sizeof(float);
}

//
// Arguments    : int b_index
// Return Type  : float *
//
float *TrainedModel0_0::getOutputDataPointer(int b_index)
{
  return (static_cast<MWTensor<float> *>(this->outputTensors[b_index]))
      ->getData();
}

//
// Arguments    : void
// Return Type  : float *
//
float *TrainedModel0_0::getOutputDataPointer()
{
  return (static_cast<MWTensor<float> *>(this->outputTensors[0]))->getData();
}

//
// Arguments    : void
// Return Type  : void
//
void TrainedModel0_0::predict()
{
  for (int idx{0}; idx < 6; idx++) {
    this->layers[idx]->predict();
  }
}

//
// Arguments    : int seqLength
// Return Type  : void
//
void TrainedModel0_0::setSize(int seqLength)
{
  if (seqLength != this->inputTensors[0]->getSequenceLength()) {
    this->inputTensors[0]->setSequenceLength(seqLength);
    for (int idx{0}; idx < 6; idx++) {
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
void TrainedModel0_0::updateState()
{
  (dynamic_cast<MWRNNLayer *>(this->layers[1]))->updateState();
  (dynamic_cast<MWRNNLayer *>(this->layers[2]))->updateState();
}

//
// Arguments    : TrainedModel0_0 *obj
// Return Type  : void
//
namespace coder {
void DeepLearningNetwork_setup(TrainedModel0_0 *obj)
{
  obj->setup();
}

} // namespace coder

//
// File trailer for DeepLearningNetwork.cpp
//
// [EOF]
//
