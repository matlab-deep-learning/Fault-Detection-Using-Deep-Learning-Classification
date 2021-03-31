#include "MWSequenceInputLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include <cassert>
#include <cstdio>
 class MWTargetNetworkImpl;
#if MW_SEQIP_TAP
 extern void mw_interm_tap(float* memBuf, int size, int count); extern int tap_count;
#endif
 MWSequenceInputLayerImpl::MWSequenceInputLayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl) : MWCNNLayerImpl(layer, ntwk_impl) { 
ZUTPCvgISoRdtnhGqXzM = true; } 
MWSequenceInputLayerImpl::~MWSequenceInputLayerImpl() { } void 
MWSequenceInputLayerImpl::propagateSize() { } void 
MWSequenceInputLayerImpl::predict() {
#if MW_SEQIP_TAP
 MWTensorBase* opTensorBase = getLayer()->getOutputTensor(0); MWTensor<float>* 
opTensor = static_cast<MWTensor<float>*>(opTensorBase); 
mw_interm_tap(opTensor->getData(), opTensor->getNumElements(), tap_count++);
#endif
 }