#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWACLUtils.hpp"
#include <arm_neon.h>
#include <memory>
#include <cassert>
#include <cstring>
#include <cstdio>
#if MW_LAYERS_TAP
 extern void mw_interm_tap(arm_compute::Tensor& armTensor, int size, int 
count); extern void mw_interm_tap(float* memBuf, int size, int count); extern 
int tap_count;
#endif
 MWCNNLayerImpl::MWCNNLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl) : bLhHPDtQpqOAnMiVledO(layer) , dAGMlbhOYuZqhuDGCqih(ntwk_impl) { } 
template <class T> void MWCNNLayerImpl::allocateOutputData(int outIdx) { if 
(this->isHandCodedLayer()) { allocateHandCodedLayerOpData<T>(outIdx); } else { 
allocateACLLayerOpData<T>(outIdx); } } template <class T> void 
MWCNNLayerImpl::allocateACLLayerOpData(int outIdx){ MWTensorBase* opTensorBase 
= getLayer()->getOutputTensor(outIdx); MWTensor<T>* opTensor = 
static_cast<MWTensor<T>*>(opTensorBase); int outBufIndex = 
opTensor->getopBufIndex(); int inIdx = getLayer()->getInPlaceIndex(outIdx); 
if(inIdx == -1){ if (outBufIndex < 0) {  
getCurrentLayerOpArmTensor(outIdx)->allocator()->allocate(); } else {
#if defined(USE_18_11_LIBRARY) || defined(USE_19_02_LIBRARY)
 getCurrentLayerOpArmTensor(outIdx)->allocator()->import_memory( 
dAGMlbhOYuZqhuDGCqih->memBuffer[outBufIndex],dAGMlbhOYuZqhuDGCqih->maxBufSize *sizeof(T));
#elif defined(USE_19_05_LIBRARY) || defined(USE_20_02_1_LIBRARY)
 getCurrentLayerOpArmTensor(outIdx)->allocator()->import_memory( dAGMlbhOYuZqhuDGCqih->memBuffer[outBufIndex]);
#endif
 } } else{  auto ipArmTensor = getCurrentLayerIpArmTensor(inIdx); auto 
opArmTensor = getCurrentLayerOpArmTensor(outIdx); if(ipArmTensor != 
opArmTensor){ T* ipArmTensorData = (T*)ipArmTensor->buffer();
#if defined(USE_18_11_LIBRARY) || defined(USE_19_02_LIBRARY)
 getCurrentLayerOpArmTensor(outIdx)->allocator()->import_memory( 
ipArmTensorData, dAGMlbhOYuZqhuDGCqih->maxBufSize *sizeof(T));
#elif defined(USE_19_05_LIBRARY) || defined(USE_20_02_1_LIBRARY)
 getCurrentLayerOpArmTensor(outIdx)->allocator()->import_memory( ipArmTensorData);
#endif
 } } opTensor->setData((T*)getCurrentLayerOpArmTensor(outIdx)->buffer()); } 
template <class T> void MWCNNLayerImpl::allocateHandCodedLayerOpData(int 
outIdx) { MWTensorBase* opTensorBase = getLayer()->getOutputTensor(outIdx); 
MWTensor<T>* opTensor = static_cast<MWTensor<T>*>(opTensorBase); int 
outBufIndex = opTensor->getopBufIndex(); bool bufferReuse = outBufIndex >= 0; 
int inIdx = getLayer()->getInPlaceIndex(outIdx); bool inPlace = inIdx != -1; if 
(!bufferReuse) {  if (inPlace) {  MWTensorBase* ipTensorBase = 
getLayer()->getInputTensor(inIdx); T* ipData = 
(T*)getUnpaddedIpData(ipTensorBase); opTensor->setData(ipData); } else {  int 
eqUIJyhXTwRqtPfXapcx = opTensorBase->getNumElements(); 
opTensor->setData((T*)calloc(eqUIJyhXTwRqtPfXapcx, sizeof(T))); } } else { 
assert(!inPlace); auto opBuffer = 
GET_BUFFER(dAGMlbhOYuZqhuDGCqih->memBuffer[outBufIndex]); 
opTensor->setData((T*)opBuffer); } } template void 
MWCNNLayerImpl::allocateOutputData<float>(int); template void 
MWCNNLayerImpl::allocateOutputData<signed char>(int); template <class T> void 
MWCNNLayerImpl::deallocateOutputData(int outIdx) { MWTensorBase* opTensorBase = 
getLayer()->getOutputTensor(outIdx); MWTensor<T>* opTensor = 
static_cast<MWTensor<T>*>(opTensorBase); int inPlaceIdx = 
getLayer()->getInPlaceIndex(outIdx); int opBufIdx = opTensor->getopBufIndex(); 
if (opBufIdx < 0 && inPlaceIdx == -1) { if (this->isHandCodedLayer()) { T* 
opDataBuf = opTensor->getData(); if (opDataBuf) { free(opDataBuf); } } 
opTensor->setData((T*)NULL);  } } template void 
MWCNNLayerImpl::deallocateOutputData<float>(int); template void 
MWCNNLayerImpl::deallocateOutputData<signed char>(int); void 
MWCNNLayerImpl::allocateInputData(int inIdx) { MWTensorBase* ipTensor = 
getLayer()->getInputTensor(inIdx); if (ipTensor->isFloat()) { 
allocateInputDataImpl<float>(inIdx); } else { assert(ipTensor->isInt8()); 
allocateInputDataImpl<signed char>(inIdx); } } template <class T> void 
MWCNNLayerImpl::allocateInputDataImpl(int inIdx) { MWTensorBase* ipTensorBase = 
getLayer()->getInputTensor(inIdx); MWTensor<T>* ipTensor = 
static_cast<MWTensor<T>*>(ipTensorBase); auto prevLayerOpArmTensor = 
MWACLUtils::getLayerOpArmTensor(ipTensorBase); if (this->isHandCodedLayer()) {  
if (prevLayerOpArmTensor != nullptr) { if 
(prevLayerOpArmTensor->info()->has_padding()) { 
setUnpaddedIpData<T>(ipTensorBase, (T*)calloc(ipTensor->getNumElements(), 
sizeof(T))); } else { setUnpaddedIpData<T>(ipTensorBase, 
(T*)prevLayerOpArmTensor->buffer()); } } else { 
setUnpaddedIpData<T>(ipTensorBase, (T*)ipTensor->getData()); } } else {  if 
(prevLayerOpArmTensor == nullptr) { if 
(getCurrentLayerIpArmTensor(inIdx)->info()->has_padding()) { 
getCurrentLayerIpArmTensor(inIdx)->allocator()->allocate(); } else{ T* ipData = (T*)ipTensor->getData();
#if defined(USE_19_05_LIBRARY) || defined(USE_20_02_1_LIBRARY)
 getCurrentLayerIpArmTensor(inIdx)->allocator()->import_memory(ipData);
#else
 getCurrentLayerIpArmTensor(inIdx)->allocator()->import_memory( ipData, ipTensorBase->getNumElements());
#endif
 } } } } template void MWCNNLayerImpl::allocateInputDataImpl<float>(int); 
template void MWCNNLayerImpl::allocateInputDataImpl<signed char>(int); void 
MWCNNLayerImpl::deallocateInputData(int inIdx) { MWTensorBase* ipTensorBase = 
getLayer()->getInputTensor(inIdx); if (ipTensorBase->isFloat()) { 
deallocateInputDataImpl<float>(inIdx); } else { assert(ipTensorBase->isInt8()); 
deallocateInputDataImpl<signed char>(inIdx); } } template <class T> void 
MWCNNLayerImpl::deallocateInputDataImpl(int inIdx) { MWTensorBase* ipTensorBase 
= getLayer()->getInputTensor(inIdx); MWTensor<T>* ipTensor = 
static_cast<MWTensor<T>*>(ipTensorBase); auto prevLayerOpArmTensor = 
MWACLUtils::getLayerOpArmTensor(ipTensor); if (this->isHandCodedLayer()) {  if 
(prevLayerOpArmTensor != nullptr && 
prevLayerOpArmTensor->info()->has_padding()) { T* ipDataBuf = 
(T*)getUnpaddedIpData(ipTensorBase); if (ipDataBuf) { free(ipDataBuf); 
setUnpaddedIpData<T>(ipTensorBase, (T*)NULL); } } } } template void 
MWCNNLayerImpl::deallocateInputDataImpl<float>(int); template void 
MWCNNLayerImpl::deallocateInputDataImpl<signed char>(int); template <class T> 
void MWCNNLayerImpl::setUnpaddedIpData(MWTensorBase* aTensor, T* bufPtr) { 
YFrWUSnoOKzYyZzANuxg[aTensor] = (T*)bufPtr; } void* 
MWCNNLayerImpl::getUnpaddedIpData(MWTensorBase* aTensor) { if 
(YFrWUSnoOKzYyZzANuxg.size() >= 1) { return 
YFrWUSnoOKzYyZzANuxg[aTensor]; } else { return NULL; } } void 
MWCNNLayerImpl::setupIpArmTensors() { int numInputs = 
static_cast<int>(getLayer()->getNumInputs()); for (int inIdx = 0; inIdx < 
numInputs; inIdx++) { MWTensorBase* ipTensor = 
getLayer()->getInputTensor(inIdx); auto prevLayerOpArmTensorSharedPtr = 
MWACLUtils::getLayerOpArmTensorsharedPtr(ipTensor); if 
(prevLayerOpArmTensorSharedPtr) { 
setCurrentLayerIpArmTensor(prevLayerOpArmTensorSharedPtr, inIdx); } else { 
setCurrentLayerIpArmTensor(std::make_shared<arm_compute::Tensor>(), inIdx); } } 
} void MWCNNLayerImpl::prepareIpArmTensorsForPredict() { int numInputs = 
getLayer()->getNumInputs(); for (int inIdx = 0; inIdx < numInputs; inIdx++) { 
MWTensorBase* ipTensorBase = getLayer()->getInputTensor(inIdx); 
if(ipTensorBase->isFloat()) { MWTensor<float>* ipTensor = 
static_cast<MWTensor<float>*>(ipTensorBase); auto prevLayerOpArmTensor = 
MWACLUtils::getLayerOpArmTensor(ipTensor); auto currLayerIpArmTensor = 
getCurrentLayerIpArmTensor(inIdx); float* ipData = ipTensor->getData(); 
if(prevLayerOpArmTensor==nullptr){ 
if(currLayerIpArmTensor->info()->has_padding()){ 
MWACLUtils::fillBufferToTensor<float>(ipData, *currLayerIpArmTensor); } } } 
else { MWTensor<signed char>* ipTensor = static_cast<MWTensor<signed 
char>*>(ipTensorBase); auto prevLayerOpArmTensor = 
MWACLUtils::getLayerOpArmTensor(ipTensor); auto currLayerIpArmTensor = 
getCurrentLayerIpArmTensor(inIdx); signed char* ipData = ipTensor->getData(); 
if(prevLayerOpArmTensor==nullptr){ 
if(currLayerIpArmTensor->info()->has_padding()){ 
MWACLUtils::fillBufferToTensor<signed char>(ipData, *currLayerIpArmTensor); } } 
} } } void MWCNNLayerImpl::configureIpArmTensors(){ int numInputs = 
getLayer()->getNumInputs(); for(int inIdx=0; inIdx<numInputs ; inIdx++) { 
MWTensorBase* ipTensor = getLayer()->getInputTensor(inIdx); 
if(ipTensor->isFloat()) { auto prevLayerOpArmTensor = 
MWACLUtils::getLayerOpArmTensor(ipTensor); if(prevLayerOpArmTensor == nullptr){ 
getCurrentLayerIpArmTensor(inIdx)->allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)ipTensor->getWidth(), (long 
unsigned int)ipTensor->getHeight(), (long unsigned int)ipTensor->getChannels(), 
(long unsigned int)ipTensor->getBatchSize() * (long unsigned 
int)ipTensor->getSequenceLength()), 1, arm_compute::DataType::F32)); } }
#if defined(USE_20_02_1_LIBRARY)
 else { auto prevLayerOpArmTensor = MWACLUtils::getLayerOpArmTensor(ipTensor); 
if(prevLayerOpArmTensor == nullptr){ arm_compute::QuantizationInfo 
inputQuantInfo =  
arm_compute::QuantizationInfo((1.0f/pow(2.0,-ipTensor->getScalingExponent())), 
0); 
getCurrentLayerIpArmTensor(inIdx)->allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)ipTensor->getWidth(), (long 
unsigned int)ipTensor->getHeight(), (long unsigned int)ipTensor->getChannels(), 
(long unsigned int)ipTensor->getBatchSize() * (long unsigned 
int)ipTensor->getSequenceLength()), 1, 
arm_compute::DataType::QASYMM8_SIGNED,inputQuantInfo)); } }
#endif 
 } } std::string MWCNNLayerImpl::getLinuxPath(const char* fileName) { 
std::string fileS(fileName); std::string key("\\"); std::size_t found = 0; 
while (found != std::string::npos) { found = fileS.rfind(key); if (found != 
std::string::npos) { fileS.replace(found, key.length(), "/"); } } return fileS; 
} void 
MWCNNLayerImpl::setCurrentLayerOpArmTensor(std::shared_ptr<arm_compute::Tensor> 
tensor, int index) { jHaoHEqZgMiwRsdCogKz[index] = tensor; } 
arm_compute::Tensor* MWCNNLayerImpl::getCurrentLayerOpArmTensor(int index) { if 
(jHaoHEqZgMiwRsdCogKz.size() >= 1) { return 
jHaoHEqZgMiwRsdCogKz[index].get(); } else { return nullptr; } } 
std::shared_ptr<arm_compute::Tensor> 
MWCNNLayerImpl::getCurrentLayerOpArmTensorSharedPtr( int index) { if 
(jHaoHEqZgMiwRsdCogKz.size() >= 1) { return 
jHaoHEqZgMiwRsdCogKz[index]; } else { return nullptr; } } void 
MWCNNLayerImpl::setCurrentLayerIpArmTensor(std::shared_ptr<arm_compute::Tensor> 
tensor, int index) { VFKMunbyHoAmpHUSkuUn[index] = tensor; } 
arm_compute::Tensor* MWCNNLayerImpl::getCurrentLayerIpArmTensor(int index) { if 
(VFKMunbyHoAmpHUSkuUn.size() >= 1) { return 
VFKMunbyHoAmpHUSkuUn[index].get(); } else { return nullptr; } } 
std::shared_ptr<arm_compute::Tensor> 
MWCNNLayerImpl::getCurrentLayerIpArmTensorSharedPtr( int index) { if 
(VFKMunbyHoAmpHUSkuUn.size() >= 1) { return 
VFKMunbyHoAmpHUSkuUn[index]; } else { return nullptr; } }