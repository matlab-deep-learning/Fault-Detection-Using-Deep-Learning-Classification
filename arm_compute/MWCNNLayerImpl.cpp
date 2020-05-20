#include "MWCNNLayerImpl.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "cnn_api.hpp"
#include <cassert>
#include <cstring>
#include <stdio.h>
#if MW_LAYERS_TAP
 extern void mw_interm_tap(arm_compute::Tensor& armTensor, int size, int 
count); extern int tap_count;
#endif
 MWCNNLayerImpl::MWCNNLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl) : cnEykmOGhLuyKuadExWe(layer) , fylVqSnTjNbHDtlPhzaj(ntwk_impl) { } void 
MWCNNLayerImpl::allocateOutputData(int i) { MWTensor* opTensor = 
getLayer()->getOutputTensor(i); if (opTensor->getopBufIndex() < 0) { 
getarmTensor(i)->allocator()->allocate(); } else {
#if defined(USE_18_11_LIBRARY) || defined(USE_19_02_LIBRARY)
 
getarmTensor(i)->allocator()->import_memory(fylVqSnTjNbHDtlPhzaj->memBuffer[opTensor->getopBufIndex()],fylVqSnTjNbHDtlPhzaj->maxBufSize 
*sizeof(float));
#elif defined(USE_19_05_LIBRARY)
 getarmTensor(i)->allocator()->import_memory(fylVqSnTjNbHDtlPhzaj->memBuffer[opTensor->getopBufIndex()]);
#else
 getarmTensor(i)->allocator()->import_memory(arm_compute::Memory(fylVqSnTjNbHDtlPhzaj->memBuffer[opTensor->getopBufIndex()]));
#endif
 } opTensor->setData((float*)getarmTensor(i)->buffer()); } void 
MWCNNLayerImpl::deallocateOutputData(int i) { if 
(cnEykmOGhLuyKuadExWe->getOutputTensor()->getopBufIndex() < 0) { 
getarmTensor(i)->allocator()->free(); } } std::string 
MWCNNLayerImpl::getLinuxPath(const char* fileName) { std::string 
fileS(fileName); std::string key ("\\"); std::size_t found = 0; while(found != 
std::string::npos){ found = fileS.rfind(key); if (found!=std::string::npos) 
fileS.replace (found,key.length(),"/"); } return fileS; } arm_compute::Tensor* 
MWCNNLayerImpl::getprevLayerarmTensor(MWTensor* ipTensor) { int index = 
ipTensor->getSourcePortIndex(); if (ipTensor->getOwner()->getImpl() == NULL) { 
return 
ipTensor->getOwner()->getInputTensor()->getOwner()->getImpl()->getarmTensor(index); 
} else { if (ipTensor->getOwner()->getImpl()->getarmTensor() == nullptr) { 
return 
ipTensor->getOwner()->getInputTensor()->getOwner()->getImpl()->getarmTensor( 
index); } else { return ipTensor->getOwner()->getImpl()->getarmTensor(index); } 
} } std::shared_ptr<arm_compute::Tensor> 
MWCNNLayerImpl::getARMTensorsharedPtr(MWTensor* ipTensor) { int index = 
ipTensor->getSourcePortIndex(); if (ipTensor->getOwner()->getImpl() == NULL) { 
return 
ipTensor->getOwner()->getInputTensor()->getOwner()->getImpl()->armTensor[index]; 
} else { if (ipTensor->getOwner()->getImpl()->getarmTensor() == nullptr) { 
return 
ipTensor->getOwner()->getInputTensor()->getOwner()->getImpl()->armTensor[index]; 
} else { return ipTensor->getOwner()->getImpl()->armTensor[index]; } } } 
arm_compute::Tensor* MWCNNLayerImpl::getarmTensor(int index) { if 
(armTensor.size() >= 1) { return armTensor[index].get(); } else { return 
nullptr; } } void 
MWCNNLayerImpl::setarmTensor(std::shared_ptr<arm_compute::Tensor> tensor, int 
index) { armTensor[index] = tensor; } 
MWInputLayerImpl::MWInputLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl, int TfsmDFpPPOscKZifVzSQ, int wJyXsrUCMgxdIKVIJSyx, int QhTesEEIHwhNmHSeYbRR, int 
zRhMJbzYfMHEzDwdpDGW, const char* avg_file_name) : MWCNNLayerImpl(layer, 
ntwk_impl) , bYBVtTnVUuGDUlaTmmHp(zRhMJbzYfMHEzDwdpDGW) { 
setarmTensor(std::make_shared<arm_compute::Tensor>()); if( bYBVtTnVUuGDUlaTmmHp 
) { loadAvg(avg_file_name, TfsmDFpPPOscKZifVzSQ * wJyXsrUCMgxdIKVIJSyx, QhTesEEIHwhNmHSeYbRR); } } 
MWInputLayerImpl::~MWInputLayerImpl() { } void 
MWInputLayerImpl::propagateSize(){ MWInputLayer* inpLayer = 
static_cast<MWInputLayer*>(getLayer()); MWTensor* ipTensor = 
inpLayer->getInputTensor(0); getarmTensor()->allocator()->init( 
arm_compute::TensorInfo(arm_compute::TensorShape((long unsigned 
int)ipTensor->getWidth(), (long unsigned int)ipTensor->getHeight(), (long 
unsigned int)ipTensor->getChannels(), (long unsigned 
int)ipTensor->getBatchSize()), 1, arm_compute::DataType::F32)); } void 
MWInputLayerImpl::loadAvg(const char* THfVbcZJtANcLKxEriuV, int channelSize, int 
numChannels) { std::string fileString = getLinuxPath(THfVbcZJtANcLKxEriuV); 
FILE* TbrNrGxaFFHrzKUcfHNZ = MWCNNLayer::openBinaryFile(fileString.c_str()); if 
(TbrNrGxaFFHrzKUcfHNZ == NULL) { 
std::cerr<<"Unable to open Input Average file"<<std::endl; } int gNROjwaqhxDPvBWUCUcQ 
= channelSize * numChannels; JLDBTuxkNCsKfaFIEVHB = new std::vector<float>; 
JLDBTuxkNCsKfaFIEVHB->reserve(gNROjwaqhxDPvBWUCUcQ); if(bYBVtTnVUuGDUlaTmmHp==1){ 
call_fread(JLDBTuxkNCsKfaFIEVHB->data(), sizeof(float), gNROjwaqhxDPvBWUCUcQ, TbrNrGxaFFHrzKUcfHNZ, 
THfVbcZJtANcLKxEriuV); } else{ int channelOffset=0; std::vector<float> 
ONvcEjLBnVNUdjMKOAwF(numChannels); call_fread(ONvcEjLBnVNUdjMKOAwF.data(), 
sizeof(float), numChannels, TbrNrGxaFFHrzKUcfHNZ, THfVbcZJtANcLKxEriuV); for(int 
i=0;i<numChannels;i++){ std::fill_n(JLDBTuxkNCsKfaFIEVHB->begin()+channelOffset, 
channelSize, ONvcEjLBnVNUdjMKOAwF[i]); channelOffset = channelOffset+channelSize; 
} } fclose(TbrNrGxaFFHrzKUcfHNZ); return; } void 
MWInputLayerImpl::allocateOutputData(int i) { 
MWCNNLayerImpl::allocateOutputData(i); MWTensor* ipTensor = 
getLayer()->getInputTensor(0); MWTensor* opTensor = 
getLayer()->getOutputTensor(0); m_inputImage = 
(float*)malloc(ipTensor->getBatchSize() * ipTensor->getChannels() * 
ipTensor->getHeight() * ipTensor->getWidth() * sizeof(float)); if 
((getarmTensor(i)->info()->total_size() / 4) == (opTensor->getBatchSize() * 
opTensor->getChannels() * opTensor->getHeight() * opTensor->getWidth())) { 
opTensor->setData((float*)getarmTensor(i)->buffer()); } else { 
opTensor->setData(m_inputImage); } opTensor->setData(getData<float>()); } void 
MWInputLayerImpl::predict() { float* inp = m_inputImage; int i, btch; 
MWInputLayer* inpLayer = static_cast<MWInputLayer*>(getLayer()); MWTensor* 
opTensor = inpLayer->getOutputTensor(0); float* out = m_inputImage; if 
((getarmTensor()->info()->total_size() / 4) == (opTensor->getBatchSize() * 
opTensor->getChannels() * opTensor->getHeight() * opTensor->getWidth())) { inp 
= (float*)getarmTensor()->buffer(); out = (float*)getarmTensor()->buffer(); } 
else { inp = m_inputImage; out = m_inputImage; } if (bYBVtTnVUuGDUlaTmmHp) { 
for (btch = 0; btch < opTensor->getBatchSize(); btch++) {
#pragma omp parallel for
 for (i = 0; i < opTensor->getChannels() * opTensor->getHeight() * 
opTensor->getWidth(); i++) { out[i] = inp[i] - (*JLDBTuxkNCsKfaFIEVHB)[i]; } inp += 
opTensor->getChannels() * opTensor->getHeight() * opTensor->getWidth(); out += 
opTensor->getChannels() * opTensor->getHeight() * opTensor->getWidth(); } } if 
((getarmTensor()->info()->total_size() / 4) != (opTensor->getBatchSize() * 
opTensor->getChannels() * opTensor->getHeight() * opTensor->getWidth())) { 
MWACLUtils::fillBufferToTensor(m_inputImage, *getarmTensor()); }
#if MW_INPUT_TAP
 mw_interm_tap(*getarmTensor(), opTensor->getNumElements(), tap_count++);
#endif
 return; } void MWInputLayerImpl::cleanup() { if (bYBVtTnVUuGDUlaTmmHp) { if 
(JLDBTuxkNCsKfaFIEVHB) { delete JLDBTuxkNCsKfaFIEVHB; } } return; } void 
MWInputLayerImpl::deallocate() { free(m_inputImage); m_inputImage = NULL; 
return; } MWReLULayerImpl::MWReLULayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl, int inPlace) : MWCNNLayerImpl(layer, ntwk_impl) 
, MW_Mangled_inPlace(inPlace) { if(MW_Mangled_inPlace){ MWTensor* ipTensor = 
getLayer()->getInputTensor(); setarmTensor(getARMTensorsharedPtr(ipTensor)); 
}else{ setarmTensor(std::make_shared<arm_compute::Tensor>()); } } 
MWReLULayerImpl::~MWReLULayerImpl() { } void MWReLULayerImpl::propagateSize() { 
MWReLULayer* reluLayer = static_cast<MWReLULayer*>(getLayer()); MWTensor* 
ipTensor = reluLayer->getInputTensor(); MWTensor* opTensor = 
reluLayer->getOutputTensor(); m_actLayer = 
std::unique_ptr<arm_compute::NEActivationLayer>(new 
arm_compute::NEActivationLayer); arm_compute::Tensor* prevLayerarmTensor = 
getprevLayerarmTensor(ipTensor); if(!MW_Mangled_inPlace){ bool 
doesPrevLayerHas2DArmTensor = prevLayerarmTensor->info()->num_dimensions() <= 2 
&& ipTensor->getHeight() == 1 && ipTensor->getWidth()==1; if 
(doesPrevLayerHas2DArmTensor) { 
getarmTensor()->allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)opTensor->getChannels(), (long 
unsigned int)(opTensor->getSequenceLength()*opTensor->getBatchSize())), 1, 
arm_compute::DataType::F32)); } else { getarmTensor()->allocator()->init( 
arm_compute::TensorInfo(arm_compute::TensorShape((long unsigned 
int)ipTensor->getWidth(), (long unsigned int)ipTensor->getHeight(), (long 
unsigned int)opTensor->getChannels(), (long unsigned 
int)(opTensor->getSequenceLength()*opTensor->getBatchSize())), 1, 
arm_compute::DataType::F32)); } } m_actLayer->configure(prevLayerarmTensor, 
getarmTensor(), 
arm_compute::ActivationLayerInfo(arm_compute::ActivationLayerInfo::ActivationFunction::RELU)); 
return; } void MWReLULayerImpl::allocateOutputData(int i){ assert(i==0); 
MWTensor* opTensor = getLayer()->getOutputTensor(i); if(MW_Mangled_inPlace){ 
MWTensor* ipTensor = getLayer()->getInputTensor(); 
opTensor->setData((float*)getprevLayerarmTensor(ipTensor)->buffer()); }else{ 
getarmTensor(i)->allocator()->allocate(); 
opTensor->setData((float*)getarmTensor(i)->buffer()); } } void 
MWReLULayerImpl::deallocateOutputData(int i){ if(!MW_Mangled_inPlace) 
getarmTensor(i)->allocator()->free(); } void MWReLULayerImpl::predict() { 
MWReLULayer* reluLayer = static_cast<MWReLULayer*>(getLayer()); MWTensor* 
opTensor = reluLayer->getOutputTensor(); m_actLayer->run();
#if MW_RELU_TAP
 mw_interm_tap(*getarmTensor(), opTensor->getNumElements(), tap_count++);
#endif
 return; } MWNormLayerImpl::MWNormLayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl, unsigned JABfZsGuaCAmcRcqOYEO,  double 
AuqaQHxmPQSyYRemQvyX,  double BHuHNDGoRwGRouCxeMbw,  double CDJtexcMbXMWAmnNZsNf) : 
MWCNNLayerImpl(layer, ntwk_impl) , AuqaQHxmPQSyYRemQvyX(AuqaQHxmPQSyYRemQvyX) , 
BHuHNDGoRwGRouCxeMbw(BHuHNDGoRwGRouCxeMbw) , CDJtexcMbXMWAmnNZsNf(CDJtexcMbXMWAmnNZsNf) , 
JABfZsGuaCAmcRcqOYEO(JABfZsGuaCAmcRcqOYEO) { 
setarmTensor(std::make_shared<arm_compute::Tensor>()); } 
MWNormLayerImpl::~MWNormLayerImpl() { } void MWNormLayerImpl::propagateSize() { 
MWNormLayer* normLayer = static_cast<MWNormLayer*>(getLayer()); MWTensor* 
ipTensor = normLayer->getInputTensor(); m_normLayer = 
std::unique_ptr<arm_compute::NENormalizationLayer>(new 
arm_compute::NENormalizationLayer); arm_compute::Tensor* prevLayerarmTensor = 
getprevLayerarmTensor(ipTensor); m_isIpArmTensorReshaped = 
prevLayerarmTensor->info()->num_dimensions() <= 2 && ipTensor->getHeight() == 1 
&& ipTensor->getWidth()==1; if(m_isIpArmTensorReshaped){  m_layerInputArmTensor 
= std::make_shared<arm_compute::Tensor>(); 
m_layerInputArmTensor->allocator()->init( 
arm_compute::TensorInfo(arm_compute::TensorShape((long unsigned 
int)ipTensor->getWidth(), (long unsigned int)ipTensor->getHeight(), (long 
unsigned int)ipTensor->getChannels(), (long unsigned 
int)ipTensor->getBatchSize()), 1, arm_compute::DataType::F32)); m_reshapeKernel 
= std::unique_ptr<arm_compute::NEReshapeLayer>(new 
arm_compute::NEReshapeLayer); m_reshapeKernel->configure(prevLayerarmTensor, 
m_layerInputArmTensor.get()); } else{  m_layerInputArmTensor = 
getARMTensorsharedPtr(ipTensor); } getarmTensor()->allocator()->init( 
arm_compute::TensorInfo(arm_compute::TensorShape((long unsigned 
int)ipTensor->getWidth(), (long unsigned int)ipTensor->getHeight(), (long 
unsigned int)ipTensor->getChannels(), (long unsigned 
int)ipTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
m_normLayer->configure(m_layerInputArmTensor.get(), getarmTensor(), 
arm_compute::NormalizationLayerInfo(arm_compute::NormType::CROSS_MAP, 
JABfZsGuaCAmcRcqOYEO, AuqaQHxmPQSyYRemQvyX, BHuHNDGoRwGRouCxeMbw, 
CDJtexcMbXMWAmnNZsNf)); return; } void MWNormLayerImpl::allocate(){ 
if(m_isIpArmTensorReshaped){ m_layerInputArmTensor->allocator()->allocate(); } 
return; } void MWNormLayerImpl::predict() { MWNormLayer* normLayer = 
static_cast<MWNormLayer*>(getLayer()); MWTensor* opTensor = 
normLayer->getOutputTensor(); if(m_isIpArmTensorReshaped){ 
m_reshapeKernel->run(); } m_normLayer->run();
#if MW_NORM_TAP
 mw_interm_tap(*getarmTensor(), opTensor->getNumElements(), tap_count++);
#endif
 return; } MWMaxPoolingLayerImpl::MWMaxPoolingLayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl, int GZGFVDrXwFLJleoTDywO,  int GbdgxISzcqHOpzQEBrvP,  
int IIiwAtyrOtLzLWAUlTey,  int IpFhwalnAlrMvcuyQpQD, int FeVcBgtQmTLtmnNcJGMY, int 
FLuSVNoPhAFKtLUchSvv,  int GFggoMvRWucDMqzlWzCl, int GLovsOhUpzOJhKgXUAJY, 
bool JsZenQeBPMhwsyEhVHiD, int hKyfKjPACkOBDvLdESxH) : MWCNNLayerImpl(layer, 
ntwk_impl) , GZGFVDrXwFLJleoTDywO(GZGFVDrXwFLJleoTDywO) , 
GbdgxISzcqHOpzQEBrvP(GbdgxISzcqHOpzQEBrvP) , 
FeVcBgtQmTLtmnNcJGMY(FeVcBgtQmTLtmnNcJGMY) , 
FLuSVNoPhAFKtLUchSvv(FLuSVNoPhAFKtLUchSvv) , 
GFggoMvRWucDMqzlWzCl(GFggoMvRWucDMqzlWzCl) , 
GLovsOhUpzOJhKgXUAJY(GLovsOhUpzOJhKgXUAJY) , 
IIiwAtyrOtLzLWAUlTey(IIiwAtyrOtLzLWAUlTey) , 
IpFhwalnAlrMvcuyQpQD(IpFhwalnAlrMvcuyQpQD){ assert(hKyfKjPACkOBDvLdESxH == 1); 
assert(!JsZenQeBPMhwsyEhVHiD); 
setarmTensor(std::make_shared<arm_compute::Tensor>()); } 
MWMaxPoolingLayerImpl::~MWMaxPoolingLayerImpl() { } float* 
MWMaxPoolingLayerImpl::getIndexData() { assert(false); } void 
MWMaxPoolingLayerImpl::propagateSize() { MWMaxPoolingLayer* maxPoolLayer = 
static_cast<MWMaxPoolingLayer*>(getLayer()); MWTensor* ipTensor = 
maxPoolLayer->getInputTensor(); MWTensor* opTensor = 
maxPoolLayer->getOutputTensor(); m_maxPoolLayer = 
std::unique_ptr<arm_compute::NEPoolingLayer>(new arm_compute::NEPoolingLayer); 
arm_compute::Tensor* prevLayerarmTensor = getprevLayerarmTensor(ipTensor); if 
((GZGFVDrXwFLJleoTDywO == -1) && (GbdgxISzcqHOpzQEBrvP == -1)) { GZGFVDrXwFLJleoTDywO = 
ipTensor->getHeight(); GbdgxISzcqHOpzQEBrvP = ipTensor->getWidth(); } 
getarmTensor()->allocator()->init(arm_compute::TensorInfo(arm_compute::TensorShape((long 
unsigned int)opTensor->getWidth(), (long unsigned int)opTensor->getHeight(), 
(long unsigned int)opTensor->getChannels(), (long unsigned 
int)opTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
m_maxPoolLayer->configure( prevLayerarmTensor, getarmTensor(), 
arm_compute::PoolingLayerInfo( arm_compute::PoolingType::MAX, GZGFVDrXwFLJleoTDywO, 
arm_compute::PadStrideInfo(IpFhwalnAlrMvcuyQpQD, IIiwAtyrOtLzLWAUlTey, 
GFggoMvRWucDMqzlWzCl, GLovsOhUpzOJhKgXUAJY, FeVcBgtQmTLtmnNcJGMY, 
FLuSVNoPhAFKtLUchSvv, arm_compute::DimensionRoundingType::FLOOR))); return; } 
void MWMaxPoolingLayerImpl::predict() { MWMaxPoolingLayer* maxPoolLayer = 
static_cast<MWMaxPoolingLayer*>(getLayer()); MWTensor* opTensor = 
maxPoolLayer->getOutputTensor(); m_maxPoolLayer->run();
#if MW_POOL_TAP
 mw_interm_tap(*getarmTensor(), opTensor->getNumElements(), tap_count++);
#endif
 return; } MWFCLayerImpl::MWFCLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl, int m_NumInputFeatures, int m_NumOutputFeatures, const char* 
m_weights_file,  const char* m_bias_file) : MWCNNLayerImpl(layer, ntwk_impl) { 
MWTensor* opTensor = getLayer()->getOutputTensor(); 
setarmTensor(std::make_shared<arm_compute::Tensor>()); int gNROjwaqhxDPvBWUCUcQ = 
m_NumInputFeatures * m_NumOutputFeatures;  wJyXsrUCMgxdIKVIJSyx = 
CREATE_BUFFER(gNROjwaqhxDPvBWUCUcQ); OiVqrkNdXioJhALWMMvm = 
CREATE_BUFFER(m_NumOutputFeatures); m_fcLayerWgtTensor.allocator()->init( 
arm_compute::TensorInfo(arm_compute::TensorShape((long unsigned 
int)(m_NumInputFeatures), (long unsigned int)(m_NumOutputFeatures)), 1, 
arm_compute::DataType::F32)); m_fcLayerBiasTensor.allocator()->init( 
arm_compute::TensorInfo(arm_compute::TensorShape((long unsigned 
int)(m_NumOutputFeatures)), 1, arm_compute::DataType::F32)); 
loadWeights(m_weights_file, gNROjwaqhxDPvBWUCUcQ); loadBias(m_bias_file, 
m_NumOutputFeatures); } MWFCLayerImpl::~MWFCLayerImpl() { } void 
MWFCLayerImpl::propagateSize(){ MWFCLayer* fcLayer = 
static_cast<MWFCLayer*>(getLayer()); MWTensor* ipTensor = 
fcLayer->getInputTensor(); MWTensor* opTensor = fcLayer->getOutputTensor(); 
m_fcLayer = std::unique_ptr<arm_compute::NEFullyConnectedLayer>(new 
arm_compute::NEFullyConnectedLayer); arm_compute::Tensor* prevLayerarmTensor = 
getprevLayerarmTensor(ipTensor); 
getarmTensor()->allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)(opTensor->getWidth()* 
opTensor->getHeight()*opTensor->getChannels()), (long unsigned 
int)(opTensor->getBatchSize()* opTensor->getSequenceLength())), 1, 
arm_compute::DataType::F32)); m_fcLayer->configure(prevLayerarmTensor, 
&m_fcLayerWgtTensor, &m_fcLayerBiasTensor, getarmTensor()); prepareWeights(); 
return; } void MWFCLayerImpl::allocate(){ MWFCLayer* fcLayer = 
static_cast<MWFCLayer*>(getLayer()); MWTensor* ipTensor = 
fcLayer->getInputTensor(); MWTensor* opTensor = fcLayer->getOutputTensor(); int 
CufLFODQDXTAPyRqYodN = ipTensor->getChannels(); int 
DRzwhbNPpftRRIXXfHzd = opTensor->getChannels(); 
MWACLUtils::allocateAndFillTensor(m_fcLayerWgtTensor, wJyXsrUCMgxdIKVIJSyx, 
CufLFODQDXTAPyRqYodN * DRzwhbNPpftRRIXXfHzd, isWgtsPadded); 
MWACLUtils::allocateAndFillTensor(m_fcLayerBiasTensor, OiVqrkNdXioJhALWMMvm, 
DRzwhbNPpftRRIXXfHzd, isBiasPadded); return; } void 
MWFCLayerImpl::loadWeights(const char* THfVbcZJtANcLKxEriuV, int gNROjwaqhxDPvBWUCUcQ) 
{ float* wMySyzzledUmSLTWhuYH = GET_BUFFER(wJyXsrUCMgxdIKVIJSyx); std::string fileString = 
getLinuxPath(THfVbcZJtANcLKxEriuV); FILE* TbrNrGxaFFHrzKUcfHNZ = 
MWCNNLayer::openBinaryFile(fileString.c_str()); call_fread(wMySyzzledUmSLTWhuYH, 
sizeof(float), gNROjwaqhxDPvBWUCUcQ, TbrNrGxaFFHrzKUcfHNZ, THfVbcZJtANcLKxEriuV); 
fclose(TbrNrGxaFFHrzKUcfHNZ); } void MWFCLayerImpl::prepareWeights(){ float* 
wvufwFZlsnpjbxmTBVYE = GET_BUFFER(wJyXsrUCMgxdIKVIJSyx); MWFCLayer* fcLayer = 
static_cast<MWFCLayer*>(getLayer()); MWTensor* ipTensor = 
fcLayer->getInputTensor(); MWTensor* opTensor = fcLayer->getOutputTensor(); int 
CufLFODQDXTAPyRqYodN = ipTensor->getChannels() * ipTensor->getWidth() * 
ipTensor->getHeight(); int DRzwhbNPpftRRIXXfHzd = 
opTensor->getChannels(); int gNROjwaqhxDPvBWUCUcQ = CufLFODQDXTAPyRqYodN * 
DRzwhbNPpftRRIXXfHzd;  if (ipTensor->getHeight() != 1 && 
ipTensor->getWidth() != 1) { float* wMySyzzledUmSLTWhuYH = 
(float*)malloc(sizeof(float) * ipTensor->getHeight() * ipTensor->getWidth()); 
for (int k = 0; k < gNROjwaqhxDPvBWUCUcQ / ipTensor->getHeight() / 
ipTensor->getWidth(); k++) { for (int i = 0; i < ipTensor->getHeight() * 
ipTensor->getWidth(); i++) wMySyzzledUmSLTWhuYH[i] = wvufwFZlsnpjbxmTBVYE[k * 
ipTensor->getHeight() * ipTensor->getWidth() + i]; for (int j = 0; j < 
ipTensor->getHeight(); j++) for (int i = 0; i < ipTensor->getWidth(); i++) 
wvufwFZlsnpjbxmTBVYE[k * ipTensor->getHeight() * ipTensor->getWidth() + j * 
ipTensor->getWidth() + i] = wMySyzzledUmSLTWhuYH[j + i * ipTensor->getHeight()]; } 
free(wMySyzzledUmSLTWhuYH); } return; } void MWFCLayerImpl::loadBias(const char* 
THfVbcZJtANcLKxEriuV, int DRzwhbNPpftRRIXXfHzd) { float* OzygUJRIZYnGLzSjgahB = 
GET_BUFFER(OiVqrkNdXioJhALWMMvm); std::string fileString = 
getLinuxPath(THfVbcZJtANcLKxEriuV); FILE* TbrNrGxaFFHrzKUcfHNZ = 
MWCNNLayer::openBinaryFile(fileString.c_str()); call_fread(OzygUJRIZYnGLzSjgahB, 
sizeof(float), DRzwhbNPpftRRIXXfHzd, TbrNrGxaFFHrzKUcfHNZ, 
THfVbcZJtANcLKxEriuV); fclose(TbrNrGxaFFHrzKUcfHNZ); return; } void 
MWFCLayerImpl::predict() { m_fcLayer->run();
#if MW_FC_TAP
 MWFCLayer* fcLayer = static_cast<MWFCLayer*>(getLayer()); MWTensor* opTensor = 
fcLayer->getOutputTensor(); mw_interm_tap(*getarmTensor(), 
opTensor->getNumElements(), tap_count++);
#endif
 return; } void MWFCLayerImpl::deallocate() { if (isWgtsPadded){ 
m_fcLayerWgtTensor.allocator()->free(); isWgtsPadded = false; } if 
(isBiasPadded){ m_fcLayerBiasTensor.allocator()->free(); isWgtsPadded = false; 
} return; } void MWFCLayerImpl::cleanup() { FREE_BUFFER_MEMORY(wJyXsrUCMgxdIKVIJSyx); 
FREE_BUFFER_MEMORY(OiVqrkNdXioJhALWMMvm); return; } 
MWSoftmaxLayerImpl::MWSoftmaxLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl) : MWCNNLayerImpl(layer, ntwk_impl) , m_doesChannelwiseSoftmax(false) 
{ setarmTensor(std::make_shared<arm_compute::Tensor>()); } 
MWSoftmaxLayerImpl::~MWSoftmaxLayerImpl() { } void 
MWSoftmaxLayerImpl::propagateSize() { MWSoftmaxLayer* sfmxLayer = 
static_cast<MWSoftmaxLayer*>(getLayer()); MWTensor* ipTensor = 
sfmxLayer->getInputTensor(); MWTensor* opTensor = sfmxLayer->getOutputTensor(); 
m_softmaxLayer = std::unique_ptr<arm_compute::NESoftmaxLayer>(new 
arm_compute::NESoftmaxLayer); arm_compute::Tensor* prevLayerarmTensor = 
getprevLayerarmTensor(ipTensor); bool doesPrevLayerHas2DArmTensor = 
prevLayerarmTensor->info()->num_dimensions() <= 2 && ipTensor->getHeight() == 1 
&& ipTensor->getWidth()==1; if (doesPrevLayerHas2DArmTensor) { 
getarmTensor()->allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)opTensor->getChannels(),  (long 
unsigned int)(opTensor->getBatchSize()*opTensor->getSequenceLength())), 1, 
arm_compute::DataType::F32)); } else { m_doesChannelwiseSoftmax = true; 
getarmTensor()->allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)opTensor->getWidth(), (long 
unsigned int)opTensor->getHeight(), (long unsigned int)opTensor->getChannels(), 
(long unsigned int)(opTensor->getBatchSize()*opTensor->getSequenceLength())), 
1, arm_compute::DataType::F32)); } if (!m_doesChannelwiseSoftmax) { 
m_softmaxLayer->configure(prevLayerarmTensor, getarmTensor()); } else { 
permuteToNHWC = std::unique_ptr<arm_compute::NEPermute>(new 
arm_compute::NEPermute); permuteToNCHW = 
std::unique_ptr<arm_compute::NEPermute>(new arm_compute::NEPermute); 
arm_compute::PermutationVector nhwcPermuteDims(2, 0, 1), nchwPermuteDims(1, 2, 
0); inputNHWCArmTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)ipTensor->getChannels(), (long 
unsigned int)ipTensor->getWidth(), (long unsigned int)ipTensor->getHeight(), 
1), 1, arm_compute::DataType::F32)); 
permuteToNHWC->configure(prevLayerarmTensor, &inputNHWCArmTensor, 
nhwcPermuteDims); 
tmpSfmaxNHWCArmTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)ipTensor->getChannels(), (long 
unsigned int)ipTensor->getWidth(), (long unsigned int)ipTensor->getHeight(), 
1), 1, arm_compute::DataType::F32)); 
m_softmaxLayer->configure(&inputNHWCArmTensor, &tmpSfmaxNHWCArmTensor); 
permuteToNCHW->configure(&tmpSfmaxNHWCArmTensor, getarmTensor(), 
nchwPermuteDims); } return; } void MWSoftmaxLayerImpl::allocate() { if 
(m_doesChannelwiseSoftmax) { inputNHWCArmTensor.allocator()->allocate(); 
tmpSfmaxNHWCArmTensor.allocator()->allocate(); } return; } void 
MWSoftmaxLayerImpl::predict() { MWSoftmaxLayer* sfmxLayer = 
static_cast<MWSoftmaxLayer*>(getLayer()); MWTensor* opTensor = 
sfmxLayer->getOutputTensor(); if (!m_doesChannelwiseSoftmax) { 
m_softmaxLayer->run(); } else {  permuteToNHWC->run(); m_softmaxLayer->run(); 
permuteToNCHW->run(); }
#if MW_SFMX_TAP
 mw_interm_tap(*getarmTensor(), opTensor->getNumElements(), tap_count++);
#endif
 return; } void MWSoftmaxLayerImpl::deallocate() { if 
(m_doesChannelwiseSoftmax) { inputNHWCArmTensor.allocator()->free(); 
tmpSfmaxNHWCArmTensor.allocator()->free(); } return; } 
MWAvgPoolingLayerImpl::MWAvgPoolingLayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl, int GZGFVDrXwFLJleoTDywO,  int GbdgxISzcqHOpzQEBrvP,  
int IIiwAtyrOtLzLWAUlTey,  int IpFhwalnAlrMvcuyQpQD,  int FwLnexHgxHRquTKmNpoa,  int 
EvebzoroiuKkIxwjkGnD, int FpguQZSermqZCMRiUfML, int FshVHIJMRAhtQirYPlZd) : 
MWCNNLayerImpl(layer, ntwk_impl) , GZGFVDrXwFLJleoTDywO(GZGFVDrXwFLJleoTDywO) , 
GbdgxISzcqHOpzQEBrvP(GbdgxISzcqHOpzQEBrvP) , IIiwAtyrOtLzLWAUlTey(IIiwAtyrOtLzLWAUlTey) , 
IpFhwalnAlrMvcuyQpQD(IpFhwalnAlrMvcuyQpQD) , 
FeVcBgtQmTLtmnNcJGMY(FwLnexHgxHRquTKmNpoa) , 
FLuSVNoPhAFKtLUchSvv(EvebzoroiuKkIxwjkGnD) , 
GFggoMvRWucDMqzlWzCl(FpguQZSermqZCMRiUfML) , 
GLovsOhUpzOJhKgXUAJY(FshVHIJMRAhtQirYPlZd) { 
setarmTensor(std::make_shared<arm_compute::Tensor>()); } 
MWAvgPoolingLayerImpl::~MWAvgPoolingLayerImpl() { } void 
MWAvgPoolingLayerImpl::propagateSize() { MWAvgPoolingLayer* avgpoolLayer = 
static_cast<MWAvgPoolingLayer*>(getLayer()); MWTensor* opTensor = 
avgpoolLayer->getOutputTensor(); MWTensor* ipTensor = 
avgpoolLayer->getInputTensor(); m_avgPoolLayer = 
std::unique_ptr<arm_compute::NEPoolingLayer>(new arm_compute::NEPoolingLayer); 
if ((GZGFVDrXwFLJleoTDywO == -1) && (GbdgxISzcqHOpzQEBrvP == -1)) { GZGFVDrXwFLJleoTDywO = 
ipTensor->getHeight(); GbdgxISzcqHOpzQEBrvP = ipTensor->getWidth(); } 
arm_compute::Tensor* prevLayerarmTensor = getprevLayerarmTensor(ipTensor); 
getarmTensor()->allocator()->init(arm_compute::TensorInfo(arm_compute::TensorShape((long 
unsigned int)opTensor->getWidth(), (long unsigned int)opTensor->getHeight(), 
(long unsigned int)opTensor->getChannels(), (long unsigned 
int)opTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
m_avgPoolLayer->configure( prevLayerarmTensor, getarmTensor(), 
arm_compute::PoolingLayerInfo( arm_compute::PoolingType::AVG, GZGFVDrXwFLJleoTDywO, 
arm_compute::PadStrideInfo(IpFhwalnAlrMvcuyQpQD, IIiwAtyrOtLzLWAUlTey, 
GFggoMvRWucDMqzlWzCl, GLovsOhUpzOJhKgXUAJY, FeVcBgtQmTLtmnNcJGMY, 
FLuSVNoPhAFKtLUchSvv, arm_compute::DimensionRoundingType::FLOOR))); return ; } 
void MWAvgPoolingLayerImpl::predict() { m_avgPoolLayer->run();
#if MW_AVG_POOL_TAP
 MWAvgPoolingLayer* avgpoolLayer = static_cast<MWAvgPoolingLayer*>(getLayer()); 
MWTensor* opTensor = avgpoolLayer->getOutputTensor(); 
mw_interm_tap(*getarmTensor(), opTensor->getNumElements(), tap_count++);
#endif
 return; } MWOutputLayerImpl::MWOutputLayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl) : MWCNNLayerImpl(layer, ntwk_impl) { } 
MWOutputLayerImpl::~MWOutputLayerImpl() { } void 
MWOutputLayerImpl::propagateSize() { MWOutputLayer* opLayer = 
static_cast<MWOutputLayer*>(getLayer()); MWTensor* ipTensor = 
opLayer->getInputTensor(0); MWTensor* opTensor = opLayer->getOutputTensor(0); 
m_outputArmTensor = getprevLayerarmTensor(ipTensor); } void 
MWOutputLayerImpl::allocateOutputData(int i) { assert(i == 0); MWOutputLayer* 
opLayer = static_cast<MWOutputLayer*>(getLayer()); MWTensor* opTensor = 
opLayer->getOutputTensor(0); m_outputData = 
(float*)malloc(opTensor->getNumElements() * sizeof(float)); 
opTensor->setData(m_outputData); if ((m_outputArmTensor->info()->total_size() / 
4) == opTensor->getNumElements()) { 
opTensor->setData((float*)m_outputArmTensor->buffer()); } 
opTensor->setData(getData<float>()); } void MWOutputLayerImpl::predict() { 
MWOutputLayer* opLayer = static_cast<MWOutputLayer*>(getLayer()); MWTensor* 
opTensor = opLayer->getOutputTensor(0); if 
((m_outputArmTensor->info()->total_size() / 4) != opTensor->getNumElements()) { 
MWACLUtils::fillTensorToBuffer(opTensor->getData<float>(), *m_outputArmTensor); 
} return; } void MWOutputLayerImpl::deallocateOutputData(int i) { 
if(m_outputData){ free(m_outputData); m_outputData = NULL; } return; }