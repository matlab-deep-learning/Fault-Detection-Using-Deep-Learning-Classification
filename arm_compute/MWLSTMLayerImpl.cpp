#include <cassert>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "MWLSTMLayerImpl.hpp"
#include "MWLSTMLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "cnn_api.hpp"
#if MW_LSTM_TAP
 extern void mw_interm_tap(arm_compute::Tensor& armTensor, int size, int 
count); extern int tap_count;
#endif
#if USE_LSTM_ACL_API
 MWLSTMLayerImpl::MWLSTMLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl, int jHaoHEqZgMiwRsdCogKz, int UpnEytIWGokwbTFkBcSx, bool 
cwCXkgHfZmFQRzNVUlCO, const char* m_weights_file, const char* m_bias_file, const 
char* m_initial_hidden_state_file, const char* m_cell_state_file) : 
MWCNNLayerImpl(layer, ntwk_impl) , 
iFWfUCwhmxBsOTMvFHgz(jHaoHEqZgMiwRsdCogKz) , 
iMyHYqdPsEjdhQptHQNt(UpnEytIWGokwbTFkBcSx) , 
cCXqPFPPcoHzYMDpnUxQ(cwCXkgHfZmFQRzNVUlCO) , m_initialCellStateData(NULL) , 
m_initialHiddenStateData(NULL) { for (int i = 0; i < 3; i++){ 
RQSttSyDKXCHDWSijmNk[i]=NULL; UWAGLbDcvybdWBtshhsr[i]=NULL; 
} setarmTensor(std::make_shared<arm_compute::Tensor>()); 
createWeightAndBiasArmTensors();  m_lstmParams.set_cifg_params( 
&YeIFysyIXePEVfpcANol[0]  , &qBTcAwVGZERyCjGYByPe[0]  , 
nullptr  , &PfisSEEWDaQFynnzlcin[0]  ); long int weightFileSize = 4 * 
iMyHYqdPsEjdhQptHQNt * (iMyHYqdPsEjdhQptHQNt + 
iFWfUCwhmxBsOTMvFHgz); loadWeights(m_weights_file, weightFileSize); long int 
biasFileSize = 8 * iMyHYqdPsEjdhQptHQNt; loadBias(m_bias_file, 
biasFileSize); loadInitialHiddenState(m_initial_hidden_state_file); 
loadInitialCellState(m_cell_state_file); } void 
MWLSTMLayerImpl::propagateSize(){ m_lstmLayer = 
std::unique_ptr<arm_compute::NELSTMLayer>(new arm_compute::NELSTMLayer); 
MWTensor* opTensor = getLayer()->getOutputTensor(0); MWTensor* ipTensor = 
getLayer()->getInputTensor(0); tnTPxeDjBsqLAPkJcPJX = 
ipTensor->getSequenceLength(); if(opTensor->getBatchSize()==1){ 
m_usePingPongStrategy = true; } createInputArmTensors();  
createOutputArmTensors();  auto m_prevLayerArmTensor = 
getprevLayerarmTensor(ipTensor); auto activationFunctionInfo = 
arm_compute::ActivationLayerInfo(arm_compute::ActivationLayerInfo( 
arm_compute::ActivationLayerInfo::ActivationFunction::TANH, 1.0f, 1.0f)); 
m_lstmLayer->configure( &m_tmpInputArmTensor  , 
&YeIFysyIXePEVfpcANol[1]  , &YeIFysyIXePEVfpcANol[2]  , 
&YeIFysyIXePEVfpcANol[3]  , &qBTcAwVGZERyCjGYByPe[1]  , 
&qBTcAwVGZERyCjGYByPe[2]  , &qBTcAwVGZERyCjGYByPe[3]  , 
&PfisSEEWDaQFynnzlcin[1]  , &PfisSEEWDaQFynnzlcin[2]  , 
&PfisSEEWDaQFynnzlcin[3]  , &m_hxTempArmTensor  , &m_cxTempArmTensor  , 
&m_scratchBufArmTensor  , &m_hyTempArmTensor  , &m_cyTempArmTensor  , 
(cCXqPFPPcoHzYMDpnUxQ) ? getarmTensor() : &m_hyTempArmTensor  , m_lstmParams , 
activationFunctionInfo, 0.0f, 0.0f ); } void MWLSTMLayerImpl::allocate() { 
MWLSTMLayer* lstmLayer = static_cast<MWLSTMLayer*>(getLayer()); MWTensor* 
ipTensor = lstmLayer->getInputTensor(0); MWTensor* opTensor = 
lstmLayer->getOutputTensor(0); m_tmpInputArmTensor.allocator()->allocate(); 
if(!m_areCHStateArmTensorsAllocated){ allocateCellHiddenIOARMTensors(); 
m_areCHStateArmTensorsAllocated = true; } 
m_scratchBufArmTensor.allocator()->allocate(); allocateWeights(); 
allocateBias(); } void MWLSTMLayerImpl::allocateCellHiddenIOARMTensors() { auto 
cellIOStateBufSizeVector = { m_cxTempArmTensor.info()->total_size()/4 , 
m_cyTempArmTensor.info()->total_size()/4 }; auto hiddenIOStateBufSizeVector = 
{m_hxTempArmTensor.info()->total_size()/4, 
m_hyTempArmTensor.info()->total_size()/4}; m_maxCellIOStateBufSize = 
*std::max_element(cellIOStateBufSizeVector.begin(), 
cellIOStateBufSizeVector.end()); m_maxhiddenIOStateBufSize = 
*std::max_element(hiddenIOStateBufSizeVector.begin(), 
hiddenIOStateBufSizeVector.end()); RQSttSyDKXCHDWSijmNk[0] = 
(float*)calloc(m_maxCellIOStateBufSize, sizeof(float)); 
RQSttSyDKXCHDWSijmNk[1] = (float*)calloc(m_maxCellIOStateBufSize, 
sizeof(float)); RQSttSyDKXCHDWSijmNk[2] = 
(float*)calloc(m_maxCellIOStateBufSize, sizeof(float)); 
UWAGLbDcvybdWBtshhsr[0] = (float*)calloc(m_maxhiddenIOStateBufSize, 
sizeof(float)); UWAGLbDcvybdWBtshhsr[1] = 
(float*)calloc(m_maxhiddenIOStateBufSize, sizeof(float)); 
UWAGLbDcvybdWBtshhsr[2] = (float*)calloc(m_maxhiddenIOStateBufSize, 
sizeof(float)); 
m_cxArmTensor.allocator()->import_memory((uint8_t*)m_initialCellStateData 
MAX_CELL_IO_STATEBUF_SIZE); 
m_hxArmTensor.allocator()->import_memory((uint8_t*)m_initialHiddenStateData 
MAX_HIDDEN_IO_STATE_BUF_SIZE); if(!m_usePingPongStrategy){ 
m_cyArmTensor.allocator()->import_memory((uint8_t*)RQSttSyDKXCHDWSijmNk[0] 
MAX_CELL_IO_STATEBUF_SIZE); 
m_hyArmTensor.allocator()->import_memory((uint8_t*)UWAGLbDcvybdWBtshhsr[0] 
MAX_HIDDEN_IO_STATE_BUF_SIZE); 
m_cxTempArmTensor.allocator()->import_memory((uint8_t*)RQSttSyDKXCHDWSijmNk[1] 
MAX_CELL_IO_STATEBUF_SIZE); 
m_hxTempArmTensor.allocator()->import_memory((uint8_t*)UWAGLbDcvybdWBtshhsr[1] 
MAX_HIDDEN_IO_STATE_BUF_SIZE); 
m_cyTempArmTensor.allocator()->import_memory((uint8_t*)RQSttSyDKXCHDWSijmNk[2] 
MAX_CELL_IO_STATEBUF_SIZE); 
m_hyTempArmTensor.allocator()->import_memory((uint8_t*)UWAGLbDcvybdWBtshhsr[2] 
MAX_HIDDEN_IO_STATE_BUF_SIZE); } } void MWLSTMLayerImpl::predict() { 
MWLSTMLayer* lstmLayer = static_cast<MWLSTMLayer*>(getLayer()); MWTensor* 
ipTensor = lstmLayer->getInputTensor(0); MWTensor* opTensor = 
lstmLayer->getOutputTensor(0); assert(tnTPxeDjBsqLAPkJcPJX != 0); 
assert(getprevLayerarmTensor(ipTensor)->info()->num_dimensions() <=2 ); 
resetInternalTmpStates(); 
MWACLUtils::fillLSTMInputTensor(*getprevLayerarmTensor(ipTensor), 
m_tmpInputArmTensor, 0); m_lstmLayer->run(); if(!cCXqPFPPcoHzYMDpnUxQ){ 
MWACLUtils::fillLSTMOutputTensor(m_hyTempArmTensor, *getarmTensor(), 0); } if 
(tnTPxeDjBsqLAPkJcPJX > 1) { if (cCXqPFPPcoHzYMDpnUxQ) { for (int m_seqLength = 
1; m_seqLength < tnTPxeDjBsqLAPkJcPJX; m_seqLength++) { 
MWACLUtils::fillLSTMInputTensor(*getprevLayerarmTensor(ipTensor), 
m_tmpInputArmTensor, m_seqLength); updateInternalTmpStates(); 
m_lstmLayer->run(); } } else { for (int m_seqLength = 1; m_seqLength < 
tnTPxeDjBsqLAPkJcPJX; m_seqLength++) { 
MWACLUtils::fillLSTMInputTensor(*getprevLayerarmTensor(ipTensor), 
m_tmpInputArmTensor, m_seqLength); updateInternalTmpStates(); 
m_lstmLayer->run(); MWACLUtils::fillLSTMOutputTensor(m_hyTempArmTensor, 
*getarmTensor(), m_seqLength); }  }  } if(m_usePingPongStrategy){ float* 
m_cyTempArmTensorDataPointer = (float*)m_cyTempArmTensor.buffer(); float* 
m_hyTempArmTensorDataPointer = (float*)m_hyTempArmTensor.buffer(); 
m_cyArmTensor.allocator()->import_memory((uint8_t*)m_cyTempArmTensorDataPointer 
MAX_CELL_IO_STATEBUF_SIZE); 
m_hyArmTensor.allocator()->import_memory((uint8_t*)m_hyTempArmTensorDataPointer 
MAX_HIDDEN_IO_STATE_BUF_SIZE); } else{ 
m_cyArmTensor.copy_from(m_cyTempArmTensor); 
m_hyArmTensor.copy_from(m_hyTempArmTensor); }
#if MW_LSTM_TAP
 mw_interm_tap(*getarmTensor(), opTensor->getNumElements(), tap_count++);
#endif
 } void MWLSTMLayerImpl::cleanup() { if (m_initialHiddenStateData) { 
free(m_initialHiddenStateData); m_initialHiddenStateData = NULL; } if 
(m_initialCellStateData) { free(m_initialCellStateData); m_initialCellStateData 
= NULL; } FREE_BUFFER_MEMORY(yPBlKhIGljihkXaXbYpB); 
FREE_BUFFER_MEMORY(PtRNGuserCxHAQfyEjFc); for(int i=0;i<3;i++){ 
if(RQSttSyDKXCHDWSijmNk[i]){ free(RQSttSyDKXCHDWSijmNk[i]); 
RQSttSyDKXCHDWSijmNk[i] = NULL; } 
if(UWAGLbDcvybdWBtshhsr[i]){ 
free(UWAGLbDcvybdWBtshhsr[i]); UWAGLbDcvybdWBtshhsr[i] = 
NULL; } } return; } void MWLSTMLayerImpl::deallocate() { for (int i = 0; i < 4; 
i++) { if(isIpWgtsPadded[i]){ 
YeIFysyIXePEVfpcANol[i].allocator()->free(); isIpWgtsPadded[i] = 
false; } if(isRecWgtsPadded[i]){ 
qBTcAwVGZERyCjGYByPe[i].allocator()->free(); isRecWgtsPadded[i] = 
false; } if(isBiasPadded[i]){ PfisSEEWDaQFynnzlcin[i].allocator()->free(); 
isBiasPadded[i] = false; } } m_scratchBufArmTensor.allocator()->free(); } void 
MWLSTMLayerImpl::createWeightAndBiasArmTensors() { for (int i = 0; i < 4; i++) 
{ YeIFysyIXePEVfpcANol[i].allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)iFWfUCwhmxBsOTMvFHgz, (long 
unsigned int)iMyHYqdPsEjdhQptHQNt), 1, arm_compute::DataType::F32)); 
qBTcAwVGZERyCjGYByPe[i].allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)(iMyHYqdPsEjdhQptHQNt), 
(long unsigned int)iMyHYqdPsEjdhQptHQNt), 1, 
arm_compute::DataType::F32)); 
PfisSEEWDaQFynnzlcin[i].allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)iMyHYqdPsEjdhQptHQNt), 1, 
arm_compute::DataType::F32)); } } void MWLSTMLayerImpl::createInputArmTensors() 
{ MWTensor* opTensor = getLayer()->getOutputTensor(0); 
m_tmpInputArmTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)(iFWfUCwhmxBsOTMvFHgz), (long 
unsigned int)opTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
m_hxArmTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)(iMyHYqdPsEjdhQptHQNt), 
(long unsigned int)opTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
m_cxArmTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)(iMyHYqdPsEjdhQptHQNt), 
(long unsigned int)opTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
m_hxTempArmTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)(iMyHYqdPsEjdhQptHQNt), 
(long unsigned int)opTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
m_cxTempArmTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)(iMyHYqdPsEjdhQptHQNt), 
(long unsigned int)opTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
} void MWLSTMLayerImpl::createOutputArmTensors() { MWTensor* opTensor = 
getLayer()->getOutputTensor(0); 
getarmTensor()->allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape( (long unsigned int)iMyHYqdPsEjdhQptHQNt, (long 
unsigned int)(opTensor->getSequenceLength() * opTensor->getBatchSize())), 1, 
arm_compute::DataType::F32)); 
m_hyArmTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)(iMyHYqdPsEjdhQptHQNt), 
(long unsigned int)opTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
m_cyArmTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)(iMyHYqdPsEjdhQptHQNt), 
(long unsigned int)opTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
m_hyTempArmTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)(iMyHYqdPsEjdhQptHQNt), 
(long unsigned int)opTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
m_cyTempArmTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)(iMyHYqdPsEjdhQptHQNt), 
(long unsigned int)opTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
m_scratchBufArmTensor.allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape((long unsigned int)(iMyHYqdPsEjdhQptHQNt * 3), 
(long unsigned int)opTensor->getBatchSize()), 1, arm_compute::DataType::F32)); 
} void MWLSTMLayerImpl::loadWeights(const char* THfVbcZJtANcLKxEriuV, long int 
weightFileSize) { std::string fileString = getLinuxPath(THfVbcZJtANcLKxEriuV); 
FILE* TbrNrGxaFFHrzKUcfHNZ = MWCNNLayer::openBinaryFile(fileString.c_str()); if 
(TbrNrGxaFFHrzKUcfHNZ == nullptr) { std::cerr << "Unable to open the weights file" << 
std::endl; } yPBlKhIGljihkXaXbYpB = (float*)calloc(weightFileSize, 
sizeof(float)); call_fread(yPBlKhIGljihkXaXbYpB, sizeof(float), 
weightFileSize, TbrNrGxaFFHrzKUcfHNZ, THfVbcZJtANcLKxEriuV); fclose(TbrNrGxaFFHrzKUcfHNZ); } 
void MWLSTMLayerImpl::loadBias(const char* THfVbcZJtANcLKxEriuV, long int 
biasFileSize) { std::string fileString = getLinuxPath(THfVbcZJtANcLKxEriuV); 
FILE* TbrNrGxaFFHrzKUcfHNZ = MWCNNLayer::openBinaryFile(fileString.c_str()); if 
(TbrNrGxaFFHrzKUcfHNZ == nullptr) { std::cerr << "Unable to open the bias file" << 
std::endl; } PtRNGuserCxHAQfyEjFc = (float*)calloc(biasFileSize, 
sizeof(float)); call_fread(PtRNGuserCxHAQfyEjFc, sizeof(float), biasFileSize, 
TbrNrGxaFFHrzKUcfHNZ, THfVbcZJtANcLKxEriuV); fclose(TbrNrGxaFFHrzKUcfHNZ); } void 
MWLSTMLayerImpl::allocateWeights(){ long int inputWeightSize = 
iMyHYqdPsEjdhQptHQNt * iFWfUCwhmxBsOTMvFHgz; long int 
inputWeightEndOffset = 4 * inputWeightSize; long int recurrentWeightSize = 
iMyHYqdPsEjdhQptHQNt * iMyHYqdPsEjdhQptHQNt; long int 
recurrentWeightEndOffset = inputWeightEndOffset + 4 * recurrentWeightSize; for 
(int i = 0; i < 4; i++) { isIpWgtsPadded[i] = false; 
MWACLUtils::allocateAndFillTensor(YeIFysyIXePEVfpcANol[i], 
yPBlKhIGljihkXaXbYpB + i * inputWeightSize, inputWeightSize, 
isIpWgtsPadded[i]); isRecWgtsPadded[i] = false; 
MWACLUtils::allocateAndFillTensor(qBTcAwVGZERyCjGYByPe[i], 
yPBlKhIGljihkXaXbYpB + inputWeightEndOffset + i * recurrentWeightSize, 
recurrentWeightSize, isRecWgtsPadded[i]); } } void 
MWLSTMLayerImpl::allocateBias(){ long int biasSize = 
iMyHYqdPsEjdhQptHQNt; for (int i = 0; i < 4; i++) { isBiasPadded[i] = 
false; MWACLUtils::allocateAndFillTensor(PfisSEEWDaQFynnzlcin[i], 
PtRNGuserCxHAQfyEjFc + i * biasSize, biasSize, isBiasPadded[i]); } } void 
MWLSTMLayerImpl::loadInitialHiddenState(const char* THfVbcZJtANcLKxEriuV) { 
std::string fileString = getLinuxPath(THfVbcZJtANcLKxEriuV); FILE* TbrNrGxaFFHrzKUcfHNZ 
= MWCNNLayer::openBinaryFile(fileString.c_str()); if (TbrNrGxaFFHrzKUcfHNZ == nullptr) 
{ std::cerr << "Unable to open initial hidden state file" << std::endl; } 
m_initialHiddenStateData = (float*)calloc(iMyHYqdPsEjdhQptHQNt, 
sizeof(float)); call_fread(m_initialHiddenStateData, sizeof(float), 
iMyHYqdPsEjdhQptHQNt, TbrNrGxaFFHrzKUcfHNZ, THfVbcZJtANcLKxEriuV); 
fclose(TbrNrGxaFFHrzKUcfHNZ); } void MWLSTMLayerImpl::loadInitialCellState(const char* 
THfVbcZJtANcLKxEriuV) { std::string fileString = 
getLinuxPath(THfVbcZJtANcLKxEriuV); FILE* TbrNrGxaFFHrzKUcfHNZ = 
MWCNNLayer::openBinaryFile(fileString.c_str()); if (TbrNrGxaFFHrzKUcfHNZ == nullptr) { 
std::cerr << "Unable to open initial cell state file" << std::endl; } 
m_initialCellStateData = (float*)calloc(iMyHYqdPsEjdhQptHQNt, 
sizeof(float)); call_fread(m_initialCellStateData, sizeof(float), 
iMyHYqdPsEjdhQptHQNt, TbrNrGxaFFHrzKUcfHNZ, THfVbcZJtANcLKxEriuV); 
fclose(TbrNrGxaFFHrzKUcfHNZ); } inline void MWLSTMLayerImpl::resetInternalTmpStates(){ 
MWTensor* opTensor = getLayer()->getOutputTensor(0); if(m_usePingPongStrategy){ 
m_hxTempArmTensor.allocator()->import_memory((uint8_t*)m_hxArmTensor.buffer() 
MAX_HIDDEN_IO_STATE_BUF_SIZE); 
m_cxTempArmTensor.allocator()->import_memory((uint8_t*)m_cxArmTensor.buffer() 
MAX_CELL_IO_STATEBUF_SIZE); for(int i=0; i<3 ;i++){ 
if(RQSttSyDKXCHDWSijmNk[i]!= (float*)m_cxTempArmTensor.buffer()){ 
m_cyTempArmTensor.allocator()->import_memory((uint8_t*)RQSttSyDKXCHDWSijmNk[i] 
MAX_CELL_IO_STATEBUF_SIZE); assert(UWAGLbDcvybdWBtshhsr[i]!= 
(float*)m_hxTempArmTensor.buffer()); 
m_hyTempArmTensor.allocator()->import_memory((uint8_t*)UWAGLbDcvybdWBtshhsr[i] 
MAX_HIDDEN_IO_STATE_BUF_SIZE); break; } } } else{ 
m_cxTempArmTensor.copy_from(m_cxArmTensor); 
m_hxTempArmTensor.copy_from(m_hxArmTensor); } } inline void 
MWLSTMLayerImpl::updateInternalTmpStates(){ MWTensor* opTensor = 
getLayer()->getOutputTensor(0); if(m_usePingPongStrategy){ float* 
m_cxTempArmTensorDataPointer = (float*)m_cxTempArmTensor.buffer(); float* 
m_cyTempArmTensorDataPointer = (float*)m_cyTempArmTensor.buffer(); float* 
m_cxArmTensorDataPointer = (float*)m_cxArmTensor.buffer(); float* 
m_hxTempArmTensorDataPointer = (float*)m_hxTempArmTensor.buffer(); float* 
m_hyTempArmTensorDataPointer = (float*)m_hyTempArmTensor.buffer(); float* 
m_hxArmTensorDataPointer = (float*)m_hxArmTensor.buffer(); 
m_cxTempArmTensor.allocator()->import_memory((uint8_t*)m_cyTempArmTensorDataPointer 
MAX_CELL_IO_STATEBUF_SIZE); 
m_hxTempArmTensor.allocator()->import_memory((uint8_t*)m_hyTempArmTensorDataPointer 
MAX_HIDDEN_IO_STATE_BUF_SIZE); if(m_cxTempArmTensorDataPointer == 
m_cxArmTensorDataPointer){ assert(m_hxTempArmTensorDataPointer == 
m_hxArmTensorDataPointer); for(int i=0; i<3 ;i++){ 
if(RQSttSyDKXCHDWSijmNk[i]!= (float*)m_cxTempArmTensor.buffer() && 
RQSttSyDKXCHDWSijmNk[i] != m_cxArmTensorDataPointer){ 
m_cyTempArmTensor.allocator()->import_memory((uint8_t*)RQSttSyDKXCHDWSijmNk[i] 
MAX_CELL_IO_STATEBUF_SIZE); assert(UWAGLbDcvybdWBtshhsr[i]!= 
(float*)m_hxTempArmTensor.buffer() && UWAGLbDcvybdWBtshhsr[i]!= 
m_hxArmTensorDataPointer); 
m_hyTempArmTensor.allocator()->import_memory((uint8_t*)UWAGLbDcvybdWBtshhsr[i] 
MAX_HIDDEN_IO_STATE_BUF_SIZE); break; } } } else{ 
m_cyTempArmTensor.allocator()->import_memory((uint8_t*)m_cxTempArmTensorDataPointer 
MAX_CELL_IO_STATEBUF_SIZE); 
m_hyTempArmTensor.allocator()->import_memory((uint8_t*)m_hxTempArmTensorDataPointer 
MAX_HIDDEN_IO_STATE_BUF_SIZE); } } else{  
m_hxTempArmTensor.copy_from(m_hyTempArmTensor); 
m_cxTempArmTensor.copy_from(m_cyTempArmTensor); } } void 
MWLSTMLayerImpl::updateState(){ if(m_usePingPongStrategy){ 
m_cxArmTensor.allocator()->import_memory((uint8_t*)m_cyArmTensor.buffer() 
MAX_CELL_IO_STATEBUF_SIZE); 
m_hxArmTensor.allocator()->import_memory((uint8_t*)m_hyArmTensor.buffer() 
MAX_HIDDEN_IO_STATE_BUF_SIZE); } else{ m_cxArmTensor.copy_from(m_cyArmTensor); 
m_hxArmTensor.copy_from(m_hyArmTensor); } } void MWLSTMLayerImpl::resetState(){ 
if(m_usePingPongStrategy){ 
m_cxArmTensor.allocator()->import_memory((uint8_t*)m_initialCellStateData 
MAX_CELL_IO_STATEBUF_SIZE); 
m_hxArmTensor.allocator()->import_memory((uint8_t*)m_initialHiddenStateData 
MAX_HIDDEN_IO_STATE_BUF_SIZE); } else{ if(m_cxArmTensor.buffer()){ 
assert(m_hxArmTensor.buffer() != nullptr); 
MWACLUtils::fillBufferToTensor(m_initialCellStateData, m_cxArmTensor); 
MWACLUtils::fillBufferToTensor(m_initialHiddenStateData, m_hxArmTensor); } } }
#else
 MWLSTMLayerImpl::MWLSTMLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl, int jHaoHEqZgMiwRsdCogKz, int UpnEytIWGokwbTFkBcSx, bool 
cwCXkgHfZmFQRzNVUlCO, const char* m_weights_file, const char* m_bias_file, const 
char* m_initial_hidden_state_file, const char* m_cell_state_file) : 
MWCNNLayerImpl(layer, ntwk_impl) , 
iFWfUCwhmxBsOTMvFHgz(jHaoHEqZgMiwRsdCogKz) , 
iMyHYqdPsEjdhQptHQNt(UpnEytIWGokwbTFkBcSx) , 
cCXqPFPPcoHzYMDpnUxQ(cwCXkgHfZmFQRzNVUlCO) , RAtlBpdedvgxUsgDTsch(NULL) , 
URgvgDXnZskIYGdtimcU(NULL) { for (int i = 0; i < 3; i++) { 
RQSttSyDKXCHDWSijmNk[i] = NULL; UWAGLbDcvybdWBtshhsr[i] = 
NULL; } MWLSTMLayer* lstmLayer = static_cast<MWLSTMLayer*>(getLayer()); bool 
aFDPITUhkPdupMfPOBnd = lstmLayer->isBidirectional; tqZLvfMHdgZzbchUyDzd = 
iMyHYqdPsEjdhQptHQNt; if(aFDPITUhkPdupMfPOBnd){ 
tqZLvfMHdgZzbchUyDzd *= 2; } loadWeights(m_weights_file); 
loadBias(m_bias_file); loadInitialHiddenState(m_initial_hidden_state_file); 
loadInitialCellState(m_cell_state_file); 
setarmTensor(std::make_shared<arm_compute::Tensor>()); } void 
MWLSTMLayerImpl::propagateSize() { MWTensor* ipTensor = 
getLayer()->getInputTensor(0); MWTensor* opTensor = 
getLayer()->getOutputTensor(0); tnTPxeDjBsqLAPkJcPJX = 
ipTensor->getSequenceLength(); 
getarmTensor()->allocator()->init(arm_compute::TensorInfo( 
arm_compute::TensorShape( (long unsigned int)opTensor->getChannels(), (long 
unsigned int)(opTensor->getSequenceLength() * opTensor->getBatchSize())), 1, 
arm_compute::DataType::F32)); } void MWLSTMLayerImpl::allocate() { MWLSTMLayer* 
lstmLayer = static_cast<MWLSTMLayer*>(getLayer()); MWTensor* ipTensor = 
lstmLayer->getInputTensor(0); fSbUUBgjKRbNXrHrlOLo = 
(float*)calloc(ipTensor->getNumElements(), sizeof(float)); if 
(!m_areCHStateArmTensorsAllocated) { allocateCellHiddenIOARMTensors(); 
m_areCHStateArmTensorsAllocated = true; } } void 
MWLSTMLayerImpl::allocateCellHiddenIOARMTensors() { MWLSTMLayer* lstmLayer = 
static_cast<MWLSTMLayer*>(getLayer()); MWTensor* opTensor = 
lstmLayer->getOutputTensor(0); RQSttSyDKXCHDWSijmNk[0] = 
(float*)calloc(tqZLvfMHdgZzbchUyDzd, sizeof(float)); 
RQSttSyDKXCHDWSijmNk[1] = (float*)calloc(tqZLvfMHdgZzbchUyDzd, 
sizeof(float)); RQSttSyDKXCHDWSijmNk[2] = 
(float*)calloc(tqZLvfMHdgZzbchUyDzd, sizeof(float)); 
UWAGLbDcvybdWBtshhsr[0] = (float*)calloc(tqZLvfMHdgZzbchUyDzd, 
sizeof(float)); UWAGLbDcvybdWBtshhsr[1] = 
(float*)calloc(tqZLvfMHdgZzbchUyDzd, sizeof(float)); 
UWAGLbDcvybdWBtshhsr[2] = (float*)calloc(tqZLvfMHdgZzbchUyDzd, 
sizeof(float)); assert(URgvgDXnZskIYGdtimcU); assert(RAtlBpdedvgxUsgDTsch); 
UzOdnHgHuNHtprVxxxXl = URgvgDXnZskIYGdtimcU; RVrPByQXdKmunRZHKWJD = RAtlBpdedvgxUsgDTsch; } 
void MWLSTMLayerImpl::runSingleTimeStepPredict(float* inputBuffer, float* 
ipWeights_buffer, float* recWeights_buffer, float* bias_buffer, float* 
hxTempBuffer, float* hyTempBuffer, float* cxTempBuffer, float* cyTempBuffer) { 
int singleGateOpSize = iMyHYqdPsEjdhQptHQNt; int totalGatesOpSize = 4 * 
singleGateOpSize; float* allGatesLinearOpData = (float*)calloc(sizeof(float), totalGatesOpSize);
#pragma omp parallel for
 for (int k = 0; k < totalGatesOpSize; k++) { float fi = 0.0f; for (int j = 0; 
j < iFWfUCwhmxBsOTMvFHgz; j++) { fi += inputBuffer[j] * ipWeights_buffer[j + 
iFWfUCwhmxBsOTMvFHgz * k]; } float fr = 0.0f; for (int i = 0; i < 
singleGateOpSize; i++) { fr += hxTempBuffer[i] * recWeights_buffer[i + 
iMyHYqdPsEjdhQptHQNt * k]; } allGatesLinearOpData[k] = fi + fr + 
bias_buffer[k]; }
#pragma omp parallel for
 for (int k = 0; k < singleGateOpSize ; k++) { allGatesLinearOpData[k] = 
expf(-allGatesLinearOpData[k]); allGatesLinearOpData[k] = 1.0F / 
(allGatesLinearOpData[k] + 1.0F); allGatesLinearOpData[k + singleGateOpSize * 
1] = expf(-allGatesLinearOpData[k + singleGateOpSize * 1]); 
allGatesLinearOpData[k + singleGateOpSize * 1] = 1.0F / (allGatesLinearOpData[k 
+ singleGateOpSize * 1] + 1.0F); allGatesLinearOpData[k + singleGateOpSize * 2] 
= tanhf(allGatesLinearOpData[singleGateOpSize * 2 + k]); allGatesLinearOpData[k 
+ singleGateOpSize * 3] = expf(-allGatesLinearOpData[k + singleGateOpSize * 
3]); allGatesLinearOpData[k + singleGateOpSize * 3] = 1.0F / 
(allGatesLinearOpData[k + singleGateOpSize * 3] + 1.0F); }
#pragma omp parallel for
 for (int k = 0; k < iMyHYqdPsEjdhQptHQNt; k++) { cyTempBuffer[k] = 
allGatesLinearOpData[k] * allGatesLinearOpData[k + singleGateOpSize * 2] + 
allGatesLinearOpData[k + singleGateOpSize] * cxTempBuffer[k]; hyTempBuffer[k] = 
tanhf(cyTempBuffer[k]) * allGatesLinearOpData[k + singleGateOpSize * 3]; } 
free(allGatesLinearOpData); } void MWLSTMLayerImpl::predict() { MWLSTMLayer* 
lstmLayer = static_cast<MWLSTMLayer*>(getLayer()); MWTensor* ipTensor = 
lstmLayer->getInputTensor(0); MWTensor* opTensor = 
lstmLayer->getOutputTensor(0); int batchSize = opTensor->getBatchSize(); bool 
aFDPITUhkPdupMfPOBnd = lstmLayer->isBidirectional; float* 
XYbzSmRQGatVJtGmDZSo; float* pzUAoBDvaKAtdsmkQuct; float* 
QhTWatiCfcWYsHdkcyhZ; assert(tnTPxeDjBsqLAPkJcPJX != 0); 
MWACLUtils::fillTensorToBuffer(fSbUUBgjKRbNXrHrlOLo, 
*getprevLayerarmTensor(ipTensor)); resetInternalTmpStates(); 
runSingleTimeStepPredict(fSbUUBgjKRbNXrHrlOLo, ZKjSVYDDjACizBkGbqBq, 
qEXwbWWsnOADJeTXfRVa, PtRNGuserCxHAQfyEjFc, UzaGmBLFEwmwaFXebUma, 
WOJynDmqVUPWjAGVIuMQ, RgjhbaFFVMpznMgMQMrE, SUjIWYfjMcdzSZaCSVRT); 
if(aFDPITUhkPdupMfPOBnd){ XYbzSmRQGatVJtGmDZSo = 
ZKjSVYDDjACizBkGbqBq + 
(iFWfUCwhmxBsOTMvFHgz*iMyHYqdPsEjdhQptHQNt*4); 
pzUAoBDvaKAtdsmkQuct = qEXwbWWsnOADJeTXfRVa + 
(iMyHYqdPsEjdhQptHQNt*iMyHYqdPsEjdhQptHQNt*4); 
QhTWatiCfcWYsHdkcyhZ = PtRNGuserCxHAQfyEjFc+ 
((4*iMyHYqdPsEjdhQptHQNt) * 2); 
runSingleTimeStepPredict(fSbUUBgjKRbNXrHrlOLo + (tnTPxeDjBsqLAPkJcPJX-1) * 
iFWfUCwhmxBsOTMvFHgz, XYbzSmRQGatVJtGmDZSo, 
pzUAoBDvaKAtdsmkQuct, QhTWatiCfcWYsHdkcyhZ, 
UzaGmBLFEwmwaFXebUma+iMyHYqdPsEjdhQptHQNt, 
WOJynDmqVUPWjAGVIuMQ+iMyHYqdPsEjdhQptHQNt, 
RgjhbaFFVMpznMgMQMrE+iMyHYqdPsEjdhQptHQNt, 
SUjIWYfjMcdzSZaCSVRT+iMyHYqdPsEjdhQptHQNt); } if (tnTPxeDjBsqLAPkJcPJX > 1) 
{ if (cCXqPFPPcoHzYMDpnUxQ) { for (int m_seqLengthIdx = 1; m_seqLengthIdx < 
tnTPxeDjBsqLAPkJcPJX; m_seqLengthIdx++) { updateInternalTmpStates(); 
runSingleTimeStepPredict(fSbUUBgjKRbNXrHrlOLo + m_seqLengthIdx * 
iFWfUCwhmxBsOTMvFHgz, ZKjSVYDDjACizBkGbqBq, 
qEXwbWWsnOADJeTXfRVa, PtRNGuserCxHAQfyEjFc, UzaGmBLFEwmwaFXebUma, 
WOJynDmqVUPWjAGVIuMQ, RgjhbaFFVMpznMgMQMrE, SUjIWYfjMcdzSZaCSVRT); 
if(aFDPITUhkPdupMfPOBnd){ 
runSingleTimeStepPredict(fSbUUBgjKRbNXrHrlOLo + 
(tnTPxeDjBsqLAPkJcPJX-m_seqLengthIdx-1) * iFWfUCwhmxBsOTMvFHgz, 
XYbzSmRQGatVJtGmDZSo, pzUAoBDvaKAtdsmkQuct, 
QhTWatiCfcWYsHdkcyhZ, UzaGmBLFEwmwaFXebUma+iMyHYqdPsEjdhQptHQNt, 
WOJynDmqVUPWjAGVIuMQ+iMyHYqdPsEjdhQptHQNt, 
RgjhbaFFVMpznMgMQMrE+iMyHYqdPsEjdhQptHQNt, 
SUjIWYfjMcdzSZaCSVRT+iMyHYqdPsEjdhQptHQNt); } } } else { for (int 
m_seqLengthIdx = 1; m_seqLengthIdx < tnTPxeDjBsqLAPkJcPJX; m_seqLengthIdx++) { 
MWACLUtils::fillLSTMOutputArmTensor(WOJynDmqVUPWjAGVIuMQ, *getarmTensor(), 
batchSize, cCXqPFPPcoHzYMDpnUxQ,  m_seqLengthIdx-1, 
aFDPITUhkPdupMfPOBnd); if(aFDPITUhkPdupMfPOBnd){ 
MWACLUtils::fillLSTMOutputArmTensor(WOJynDmqVUPWjAGVIuMQ + 
iMyHYqdPsEjdhQptHQNt, *getarmTensor(), batchSize, cCXqPFPPcoHzYMDpnUxQ, 
tnTPxeDjBsqLAPkJcPJX-m_seqLengthIdx, aFDPITUhkPdupMfPOBnd, true); } 
updateInternalTmpStates(); runSingleTimeStepPredict(fSbUUBgjKRbNXrHrlOLo + 
m_seqLengthIdx * iFWfUCwhmxBsOTMvFHgz, ZKjSVYDDjACizBkGbqBq, 
qEXwbWWsnOADJeTXfRVa, PtRNGuserCxHAQfyEjFc, UzaGmBLFEwmwaFXebUma, 
WOJynDmqVUPWjAGVIuMQ, RgjhbaFFVMpznMgMQMrE, SUjIWYfjMcdzSZaCSVRT); 
if(aFDPITUhkPdupMfPOBnd){ 
runSingleTimeStepPredict(fSbUUBgjKRbNXrHrlOLo + 
(tnTPxeDjBsqLAPkJcPJX-m_seqLengthIdx-1) * iFWfUCwhmxBsOTMvFHgz, 
XYbzSmRQGatVJtGmDZSo, pzUAoBDvaKAtdsmkQuct, 
QhTWatiCfcWYsHdkcyhZ, UzaGmBLFEwmwaFXebUma+iMyHYqdPsEjdhQptHQNt, 
WOJynDmqVUPWjAGVIuMQ+iMyHYqdPsEjdhQptHQNt, 
RgjhbaFFVMpznMgMQMrE+iMyHYqdPsEjdhQptHQNt, 
SUjIWYfjMcdzSZaCSVRT+iMyHYqdPsEjdhQptHQNt); } }  }  } 
MWACLUtils::fillLSTMOutputArmTensor(WOJynDmqVUPWjAGVIuMQ, *getarmTensor(), 
batchSize, cCXqPFPPcoHzYMDpnUxQ,  tnTPxeDjBsqLAPkJcPJX-1, 
aFDPITUhkPdupMfPOBnd); if(aFDPITUhkPdupMfPOBnd){ 
MWACLUtils::fillLSTMOutputArmTensor(WOJynDmqVUPWjAGVIuMQ+ 
iMyHYqdPsEjdhQptHQNt, *getarmTensor(), batchSize, cCXqPFPPcoHzYMDpnUxQ, 
0, aFDPITUhkPdupMfPOBnd, true); } VFKMunbyHoAmpHUSkuUn = WOJynDmqVUPWjAGVIuMQ; 
SIBpKtDURUWQaaenbwrC = SUjIWYfjMcdzSZaCSVRT;
#if MW_LSTM_TAP
 mw_interm_tap(*getarmTensor(), opTensor->getNumElements(), tap_count++);
#endif
 } void MWLSTMLayerImpl::cleanup() { if (URgvgDXnZskIYGdtimcU) { 
free(URgvgDXnZskIYGdtimcU); URgvgDXnZskIYGdtimcU = NULL; } if 
(RAtlBpdedvgxUsgDTsch) { free(RAtlBpdedvgxUsgDTsch); RAtlBpdedvgxUsgDTsch = 
NULL; } if (yPBlKhIGljihkXaXbYpB) { free(yPBlKhIGljihkXaXbYpB); 
yPBlKhIGljihkXaXbYpB = NULL; } if (ZKjSVYDDjACizBkGbqBq) { 
free(ZKjSVYDDjACizBkGbqBq); ZKjSVYDDjACizBkGbqBq = NULL; } if 
(qEXwbWWsnOADJeTXfRVa) { free(qEXwbWWsnOADJeTXfRVa); 
qEXwbWWsnOADJeTXfRVa = NULL; } if (PtRNGuserCxHAQfyEjFc) { 
free(PtRNGuserCxHAQfyEjFc); PtRNGuserCxHAQfyEjFc = NULL; } for (int i = 0; 
i < 3; i++) { if (RQSttSyDKXCHDWSijmNk[i]) { 
free(RQSttSyDKXCHDWSijmNk[i]); RQSttSyDKXCHDWSijmNk[i] = 
NULL; } if (UWAGLbDcvybdWBtshhsr[i]) { 
free(UWAGLbDcvybdWBtshhsr[i]); UWAGLbDcvybdWBtshhsr[i] = 
NULL; } } return; } void MWLSTMLayerImpl::deallocate() { if 
(fSbUUBgjKRbNXrHrlOLo) { free(fSbUUBgjKRbNXrHrlOLo); 
fSbUUBgjKRbNXrHrlOLo = NULL; } } void MWLSTMLayerImpl::loadWeights(const 
char* THfVbcZJtANcLKxEriuV) { MWLSTMLayer* lstmLayer = 
static_cast<MWLSTMLayer*>(getLayer()); bool aFDPITUhkPdupMfPOBnd = 
lstmLayer->isBidirectional; std::string fileString = 
getLinuxPath(THfVbcZJtANcLKxEriuV); FILE* TbrNrGxaFFHrzKUcfHNZ = 
MWCNNLayer::openBinaryFile(fileString.c_str()); if (TbrNrGxaFFHrzKUcfHNZ == nullptr) { 
std::cerr << "Unable to open the weights file" << std::endl; } long int 
input_singleDirection_weight_size = 4 * iMyHYqdPsEjdhQptHQNt * 
iFWfUCwhmxBsOTMvFHgz; long int recurrent_singleDirection_weight_size = 4 * 
iMyHYqdPsEjdhQptHQNt * iMyHYqdPsEjdhQptHQNt; long int 
input_weight_size = input_singleDirection_weight_size; long int 
recurrent_weight_size = recurrent_singleDirection_weight_size; long int 
weightFileSize = input_singleDirection_weight_size + 
recurrent_singleDirection_weight_size; if(aFDPITUhkPdupMfPOBnd){ 
weightFileSize*=2; input_weight_size *= 2; recurrent_weight_size *= 2; } 
yPBlKhIGljihkXaXbYpB = (float*)calloc(weightFileSize, sizeof(float)); 
ZKjSVYDDjACizBkGbqBq = (float*)calloc(input_weight_size, sizeof(float)); 
qEXwbWWsnOADJeTXfRVa = (float*)calloc(recurrent_weight_size, 
sizeof(float)); call_fread(yPBlKhIGljihkXaXbYpB, sizeof(float), 
weightFileSize, TbrNrGxaFFHrzKUcfHNZ, THfVbcZJtANcLKxEriuV); 
memcpy(ZKjSVYDDjACizBkGbqBq, yPBlKhIGljihkXaXbYpB, sizeof(float) * 
input_singleDirection_weight_size); memcpy(qEXwbWWsnOADJeTXfRVa, 
yPBlKhIGljihkXaXbYpB + input_singleDirection_weight_size, sizeof(float) * 
recurrent_singleDirection_weight_size); if(aFDPITUhkPdupMfPOBnd){ 
memcpy(ZKjSVYDDjACizBkGbqBq + input_singleDirection_weight_size, 
yPBlKhIGljihkXaXbYpB + input_singleDirection_weight_size + 
recurrent_singleDirection_weight_size, sizeof(float) * 
input_singleDirection_weight_size); memcpy(qEXwbWWsnOADJeTXfRVa + 
recurrent_singleDirection_weight_size, yPBlKhIGljihkXaXbYpB + 
input_weight_size + recurrent_singleDirection_weight_size, sizeof(float) * 
recurrent_singleDirection_weight_size); } fclose(TbrNrGxaFFHrzKUcfHNZ); } void 
MWLSTMLayerImpl::loadBias(const char* THfVbcZJtANcLKxEriuV) { MWLSTMLayer* 
lstmLayer = static_cast<MWLSTMLayer*>(getLayer()); bool 
aFDPITUhkPdupMfPOBnd = lstmLayer->isBidirectional; std::string fileString 
= getLinuxPath(THfVbcZJtANcLKxEriuV); FILE* TbrNrGxaFFHrzKUcfHNZ = 
MWCNNLayer::openBinaryFile(fileString.c_str()); if (TbrNrGxaFFHrzKUcfHNZ == nullptr) { 
std::cerr << "Unable to open the bias file" << std::endl; } long int 
biasFileSize = 8 * iMyHYqdPsEjdhQptHQNt; if(aFDPITUhkPdupMfPOBnd){ 
biasFileSize*=2; } PtRNGuserCxHAQfyEjFc = (float*)calloc(biasFileSize, 
sizeof(float)); call_fread(PtRNGuserCxHAQfyEjFc, sizeof(float), biasFileSize, 
TbrNrGxaFFHrzKUcfHNZ, THfVbcZJtANcLKxEriuV); fclose(TbrNrGxaFFHrzKUcfHNZ); } void 
MWLSTMLayerImpl::loadInitialHiddenState(const char* THfVbcZJtANcLKxEriuV) { 
std::string fileString = getLinuxPath(THfVbcZJtANcLKxEriuV); FILE* TbrNrGxaFFHrzKUcfHNZ 
= MWCNNLayer::openBinaryFile(fileString.c_str()); if (TbrNrGxaFFHrzKUcfHNZ == nullptr) 
{ std::cerr << "Unable to open initial hidden state file" << std::endl; } 
URgvgDXnZskIYGdtimcU = (float*)calloc(tqZLvfMHdgZzbchUyDzd, sizeof(float)); 
call_fread(URgvgDXnZskIYGdtimcU, sizeof(float), tqZLvfMHdgZzbchUyDzd, 
TbrNrGxaFFHrzKUcfHNZ, THfVbcZJtANcLKxEriuV); fclose(TbrNrGxaFFHrzKUcfHNZ); } void 
MWLSTMLayerImpl::loadInitialCellState(const char* THfVbcZJtANcLKxEriuV) { 
std::string fileString = getLinuxPath(THfVbcZJtANcLKxEriuV); FILE* TbrNrGxaFFHrzKUcfHNZ 
= MWCNNLayer::openBinaryFile(fileString.c_str()); if (TbrNrGxaFFHrzKUcfHNZ == nullptr) 
{ std::cerr << "Unable to open initial cell state file" << std::endl; } 
RAtlBpdedvgxUsgDTsch = (float*)calloc(tqZLvfMHdgZzbchUyDzd, sizeof(float)); 
call_fread(RAtlBpdedvgxUsgDTsch, sizeof(float), tqZLvfMHdgZzbchUyDzd, 
TbrNrGxaFFHrzKUcfHNZ, THfVbcZJtANcLKxEriuV); fclose(TbrNrGxaFFHrzKUcfHNZ); } inline void 
MWLSTMLayerImpl::resetInternalTmpStates() { MWTensor* opTensor = 
getLayer()->getOutputTensor(0); UzaGmBLFEwmwaFXebUma = UzOdnHgHuNHtprVxxxXl; 
RgjhbaFFVMpznMgMQMrE = RVrPByQXdKmunRZHKWJD; for (int i = 0; i < 3; i++) { if 
(RQSttSyDKXCHDWSijmNk[i] != RgjhbaFFVMpznMgMQMrE) { SUjIWYfjMcdzSZaCSVRT = 
RQSttSyDKXCHDWSijmNk[i]; assert(UWAGLbDcvybdWBtshhsr[i] != 
UzaGmBLFEwmwaFXebUma); WOJynDmqVUPWjAGVIuMQ = UWAGLbDcvybdWBtshhsr[i]; 
break; } } } inline void MWLSTMLayerImpl::updateInternalTmpStates() { MWTensor* 
opTensor = getLayer()->getOutputTensor(0); float* m_cxTempArmTensorDataPointer 
= RgjhbaFFVMpznMgMQMrE; float* m_hxTempArmTensorDataPointer = UzaGmBLFEwmwaFXebUma; 
RgjhbaFFVMpznMgMQMrE = SUjIWYfjMcdzSZaCSVRT; UzaGmBLFEwmwaFXebUma = WOJynDmqVUPWjAGVIuMQ; 
if (m_cxTempArmTensorDataPointer == RVrPByQXdKmunRZHKWJD) {  
assert(m_hxTempArmTensorDataPointer == UzOdnHgHuNHtprVxxxXl); for (int i = 0; i < 3; 
i++) { if (RQSttSyDKXCHDWSijmNk[i] != RgjhbaFFVMpznMgMQMrE && 
RQSttSyDKXCHDWSijmNk[i] != RVrPByQXdKmunRZHKWJD) { SUjIWYfjMcdzSZaCSVRT = 
RQSttSyDKXCHDWSijmNk[i]; assert(UWAGLbDcvybdWBtshhsr[i] != 
UzaGmBLFEwmwaFXebUma && UWAGLbDcvybdWBtshhsr[i] != UzOdnHgHuNHtprVxxxXl); 
WOJynDmqVUPWjAGVIuMQ = UWAGLbDcvybdWBtshhsr[i]; break; } } } else { 
SUjIWYfjMcdzSZaCSVRT = RgjhbaFFVMpznMgMQMrE; WOJynDmqVUPWjAGVIuMQ = UzaGmBLFEwmwaFXebUma; } 
} void MWLSTMLayerImpl::updateState() { MWLSTMLayer* lstmLayer = 
static_cast<MWLSTMLayer*>(getLayer()); bool aFDPITUhkPdupMfPOBnd = 
lstmLayer->isBidirectional; if(aFDPITUhkPdupMfPOBnd){ 
memcpy(VFKMunbyHoAmpHUSkuUn+iMyHYqdPsEjdhQptHQNt, 
URgvgDXnZskIYGdtimcU+iMyHYqdPsEjdhQptHQNt, 
sizeof(float)*iMyHYqdPsEjdhQptHQNt); 
memcpy(SIBpKtDURUWQaaenbwrC+iMyHYqdPsEjdhQptHQNt, 
RAtlBpdedvgxUsgDTsch+iMyHYqdPsEjdhQptHQNt, 
sizeof(float)*iMyHYqdPsEjdhQptHQNt); } UzOdnHgHuNHtprVxxxXl = VFKMunbyHoAmpHUSkuUn; 
RVrPByQXdKmunRZHKWJD = SIBpKtDURUWQaaenbwrC; } void MWLSTMLayerImpl::resetState() { 
UzOdnHgHuNHtprVxxxXl = URgvgDXnZskIYGdtimcU; RVrPByQXdKmunRZHKWJD = RAtlBpdedvgxUsgDTsch; }
#endif