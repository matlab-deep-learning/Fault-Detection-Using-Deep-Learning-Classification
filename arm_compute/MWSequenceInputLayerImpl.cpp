#include "MWSequenceInputLayerImpl.hpp"
#include "MWSequenceInputLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "cnn_api.hpp"
#include <cassert>
#include <stdio.h>
#if MW_SEQIP_TAP
 extern void mw_interm_tap(arm_compute::Tensor& armTensor, int size, int 
count); extern int tap_count;
#endif
 MWSequenceInputLayerImpl::MWSequenceInputLayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl) : MWCNNLayerImpl(layer, ntwk_impl) { 
setarmTensor(std::make_shared<arm_compute::Tensor>()); isPaddingEnabled = 
false; } MWSequenceInputLayerImpl::~MWSequenceInputLayerImpl() { } void 
MWSequenceInputLayerImpl::propagateSize() { MWTensor* opTensor = 
getLayer()->getOutputTensor(0); 
getarmTensor()->allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)opTensor->getChannels() , (long 
unsigned int)(opTensor->getBatchSize() * opTensor->getSequenceLength())), 1, 
arm_compute::DataType::F32)); } void 
MWSequenceInputLayerImpl::allocateOutputData(int i) { 
MWCNNLayerImpl::allocateOutputData(i); if 
(getarmTensor(i)->info()->has_padding()) { MWTensor* opTensor = 
getLayer()->getOutputTensor(i); int m_actualOutputSize = 
opTensor->getNumElements(); isPaddingEnabled = true; m_inputData = 
(float*)malloc(m_actualOutputSize * sizeof(float)); 
opTensor->setData(m_inputData); } } void MWSequenceInputLayerImpl::predict() { 
if (isPaddingEnabled) { MWACLUtils::fillBufferToTensor(m_inputData, 
*getarmTensor()); }
#if MW_SEQIP_TAP
 MWTensor* opTensor = getLayer()->getOutputTensor(0); 
mw_interm_tap(*getarmTensor(), opTensor->getNumElements(), tap_count++);
#endif
 } void MWSequenceInputLayerImpl::deallocateOutputData(int i) { if 
(isPaddingEnabled) { free(m_inputData); m_inputData = NULL; isPaddingEnabled = 
false; } MWCNNLayerImpl::deallocateOutputData(i); }