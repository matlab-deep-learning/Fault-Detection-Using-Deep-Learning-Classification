#include "MWTargetNetworkImpl.hpp"
#include "cnn_api.hpp"
#include "MWCNNLayerImpl.hpp"
 void MWTargetNetworkImpl::allocate(int numBufsToAlloc, MWCNNLayer* 
layers[],int numLayers) { numBufs = numBufsToAlloc; maxBufSize = -1; for(int i 
= 0; i < numLayers; i++) { if ( (layers[i]->getImpl() != NULL) && 
(dynamic_cast<MWOutputLayer*>(layers[i]) == NULL) ) { maxBufSize = 
std::max((int)maxBufSize, 
(int)((layers[i]->getImpl()->getarmTensor()->info()->total_size()) / 4)); } } 
for(int i = 0; i < numBufs; i++) { ALLOCATE_MEMORY_BUFFER(); } } float* 
MWTargetNetworkImpl::getLayerOutput(MWCNNLayer* layers[], int layerIndex, int 
portIndex) { MWTensor* opTensor = 
layers[layerIndex]->getOutputTensor(portIndex); float* opData = 
getLayerActivation(opTensor); return opData; } float* 
MWTargetNetworkImpl::getLayerActivation(MWTensor* opTensor){ MWCNNLayerImpl* 
layerImpl = opTensor->getOwner()->getImpl(); if(layerImpl == NULL){  return 
getLayerActivation(opTensor->getOwner()->getInputTensor()); } else{ if 
(dynamic_cast<MWOutputLayerImpl*>(layerImpl)) { return 
layerImpl->getData<float>(); } else { arm_compute::Tensor* currLayerArmTensor = 
layerImpl->getarmTensor(); int layerOutputSize = opTensor->getNumElements(); 
float* m_data = (float*)malloc(sizeof(float) * layerOutputSize); 
MWACLUtils::fillTensorToBuffer(m_data, *currLayerArmTensor); 
memcpy(opTensor->getData<float>(), m_data, layerOutputSize * sizeof(float)); 
free(m_data); return opTensor->getData<float>(); } } } void 
MWTargetNetworkImpl::createWorkSpace(float** zzWugmJRYlNEuAzHMpeQ) { } void 
MWTargetNetworkImpl::setWorkSpaceSize(size_t wss) { } size_t* 
MWTargetNetworkImpl::getWorkSpaceSize() { return NULL; } float* 
MWTargetNetworkImpl::getWorkSpace() { return NULL; } void 
MWTargetNetworkImpl::deallocate() { for(int i = 0; i < memBuffer.size(); i++) { 
if(memBuffer[i] != nullptr) { FREE_MEMORY_BUFFER(); } } memBuffer.clear(); } 
void MWTargetNetworkImpl::cleanup() { }