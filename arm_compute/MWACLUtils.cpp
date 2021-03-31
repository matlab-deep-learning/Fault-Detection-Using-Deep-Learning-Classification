#include "MWACLUtils.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include <arm_neon.h>
#include <cassert>
#include <memory>
 void MWACLUtils::fillRNNOutputTensor(arm_compute::ITensor& inputTensor, 
arm_compute::ITensor& outputTensor, int outputIteratorVal = 0) { 
assert(inputTensor.info()->num_dimensions() <= 2 && 
outputTensor.info()->num_dimensions() <= 2);  auto ip_w = 
inputTensor.info()->dimension(0); auto ip_h = inputTensor.info()->dimension(1); 
auto op_w = outputTensor.info()->dimension(0); auto op_h = 
outputTensor.info()->dimension(1); assert(ip_w == op_w); assert(op_h >= ip_h);  
float* ipArmTensorBuffer = (float*)(inputTensor.buffer() + 
inputTensor.info()->offset_first_element_in_bytes()); float* opArmTensorBuffer 
= (float*)(outputTensor.buffer() + 
outputTensor.info()->offset_first_element_in_bytes()); auto ipStridesInBytes = 
inputTensor.info()->strides_in_bytes(); int numElmntsPerRowInInputTensor = 
ipStridesInBytes.y() / 4; auto opStridesInBytes = 
outputTensor.info()->strides_in_bytes(); int numElmntsPerRowInOutputTensor = 
opStridesInBytes.y() / 4; int numElmntsCopiedInPrevTimeSteps = 
outputIteratorVal * ip_h * numElmntsPerRowInOutputTensor; size_t ipRowAxis = 0, 
opRowAxis = 0; while (ipRowAxis < ip_h) { int ipRowOffset = ipRowAxis * 
numElmntsPerRowInInputTensor; int opRowOffset = opRowAxis * 
numElmntsPerRowInOutputTensor; memcpy(opArmTensorBuffer + opRowOffset + 
numElmntsCopiedInPrevTimeSteps, ipArmTensorBuffer + ipRowOffset, ip_w * 
sizeof(float)); ipRowAxis++; opRowAxis++; } } void 
MWACLUtils::fillRNNInputTensor(arm_compute::ITensor& inputTensor, 
arm_compute::ITensor& outputTensor, int inputIteratorVal = 0) { 
assert(inputTensor.info()->num_dimensions() <= 2 && 
outputTensor.info()->num_dimensions() <= 2);  auto ip_w = 
inputTensor.info()->dimension(0); auto op_w = 
outputTensor.info()->dimension(0); auto op_h = 
outputTensor.info()->dimension(1); assert(ip_w == op_w);  float* 
ipArmTensorBuffer = (float*)(inputTensor.buffer() + 
inputTensor.info()->offset_first_element_in_bytes()); float* opArmTensorBuffer 
= (float*)(outputTensor.buffer() + 
outputTensor.info()->offset_first_element_in_bytes()); auto ipStridesInBytes = 
inputTensor.info()->strides_in_bytes(); int numElmntsPerRowInInputTensor = 
ipStridesInBytes.y() / 4; auto opStridesInBytes = 
outputTensor.info()->strides_in_bytes(); int numElmntsPerRowInOutputTensor = 
opStridesInBytes.y() / 4; int numElmntsCopiedInPrevTimeSteps = inputIteratorVal 
* op_h * numElmntsPerRowInInputTensor; size_t opRowAxis = 0, ipRowAxis = 0; 
while (opRowAxis < op_h) { int opRowOffset = opRowAxis * 
numElmntsPerRowInOutputTensor; int ipRowOffset = ipRowAxis * 
numElmntsPerRowInInputTensor; memcpy(opArmTensorBuffer + opRowOffset, 
ipArmTensorBuffer + ipRowOffset + numElmntsCopiedInPrevTimeSteps, op_w * 
sizeof(float)); opRowAxis++; } } void MWACLUtils::fillValueToTensor(float 
value, arm_compute::ITensor& inputTensor) { arm_compute::Window inputWindow; 
inputWindow.use_tensor_dimensions(inputTensor.info()->tensor_shape()); 
arm_compute::Iterator inputIterator(&inputTensor, inputWindow); 
arm_compute::execute_window_loop( inputWindow, [&](const 
arm_compute::Coordinates& ) { *reinterpret_cast<float*>(inputIterator.ptr()) = 
value; }, inputIterator); } void MWACLUtils::fillRNNOutputArmTensor(const 
float* opBufferAtSingleTimeStep, arm_compute::ITensor& layerOpArmTensor, int& 
batchSize, bool isLastMode, int outputIteratorVal, bool isBiRNN, bool isBwdRNN) 
{ assert(layerOpArmTensor.info()->num_dimensions() <= 2);  int 
opBufSizePerBatch = layerOpArmTensor.info()->dimension(0); int 
opBufSizePerBatchInSigleDir = opBufSizePerBatch; if (isBiRNN) { 
opBufSizePerBatchInSigleDir = opBufSizePerBatchInSigleDir / 2; } float* 
opArmTensorBuffer = (float*)(layerOpArmTensor.buffer() + 
layerOpArmTensor.info()->offset_first_element_in_bytes()); auto 
opStridesInBytes = layerOpArmTensor.info()->strides_in_bytes(); int 
numElmntsPerRowInOpArmTensor = opStridesInBytes.y() / 4; int 
numElmntsCopiedInPrevTimeSteps; if (isLastMode) { 
numElmntsCopiedInPrevTimeSteps = 0; } else { numElmntsCopiedInPrevTimeSteps = 
outputIteratorVal * batchSize * numElmntsPerRowInOpArmTensor; } if (isBwdRNN) { 
numElmntsCopiedInPrevTimeSteps = numElmntsCopiedInPrevTimeSteps + 
opBufSizePerBatchInSigleDir; } float* currentTimeStepOpArmTensorBuf = 
opArmTensorBuffer + numElmntsCopiedInPrevTimeSteps; int ipRowAxis = 0, 
opRowAxis = 0; while (ipRowAxis < batchSize) { int ipRowOffset = ipRowAxis * 
opBufSizePerBatch; int opRowOffset = opRowAxis * numElmntsPerRowInOpArmTensor; 
memcpy(currentTimeStepOpArmTensorBuf + opRowOffset, opBufferAtSingleTimeStep + 
ipRowOffset, opBufSizePerBatchInSigleDir * sizeof(float)); ipRowAxis++; 
opRowAxis++; } }
#if MW_LAYERS_TAP
 int tap_count = 0; void mw_interm_tap(float* memBuf, int size, int count) { 
FILE* fp; int i; char str[500];
#define TXT_FILE 1
#if TXT_FILE
 sprintf(str, "taps/mw_interm_tap_%d.txt", count); fp = fopen(str, "w"); for (i 
= 0; i < size; i++) { fprintf(fp, "%f\n", memBuf[i]); }
#else
 sprintf(str, "taps/mw_interm_tap_%d.bin", count); fp = fopen(str, "wb"); 
fwrite(inp, 4, size, fp);
#endif
 fclose(fp); } void mw_interm_tap(arm_compute::Tensor& armTensor, int size, int 
count) { float* memBuf = (float*)calloc(size, sizeof(float)); 
MWACLUtils::fillTensorToBuffer(memBuf, armTensor); mw_interm_tap(memBuf, size, 
count); free(memBuf); } void mw_interm_tap(signed char* memBuf, int size, int 
count) { FILE* fp; int i; char str[500];
#define TXT_FILE 1
#if TXT_FILE
 sprintf(str, "taps/mw_interm_tap_%d.txt", count); fp = fopen(str, "w"); for (i 
= 0; i < size; i++) { fprintf(fp, "%d\n", memBuf[i]); }
#else
 sprintf(str, "taps/mw_interm_tap_%d.bin", count); fp = fopen(str, "wb"); 
fwrite(inp, 1, size, fp);
#endif
 fclose(fp); } void mw_interm_tap_INT8(arm_compute::Tensor& armTensor, int 
size, int count) { signed char* memBuf = (signed char*)calloc(size, 
sizeof(signed char*)); MWACLUtils::fillTensorToBuffer(memBuf, armTensor); 
mw_interm_tap(memBuf, size, count); free(memBuf); }
#endif
 arm_compute::Tensor* MWACLUtils::getLayerOpArmTensor(MWTensorBase* aTensor) { 
auto owningLayer = aTensor->getOwner(); if (owningLayer == nullptr) { return 
nullptr; } auto owningLayerImpl = owningLayer->getImpl(); int layerOpPortIndex 
= aTensor->getSourcePortIndex(); if (owningLayerImpl == nullptr) { if 
(owningLayer->isCustomLayer()) { return nullptr; }else{ int inIndex = 
owningLayer->getInPlaceIndex(layerOpPortIndex); bool isInplaceLayer = 
(inIndex!=-1); bool isSingleIpLayer = (owningLayer->getNumInputs() == 1); 
assert(isSingleIpLayer || isInplaceLayer); if(isSingleIpLayer){ return 
MWACLUtils::getLayerOpArmTensor(owningLayer->getInputTensor(0)); } else{ 
assert(isInplaceLayer); return 
MWACLUtils::getLayerOpArmTensor(owningLayer->getInputTensor(inIndex)); } } } 
else { auto layerOpArmTensor = 
owningLayerImpl->getCurrentLayerOpArmTensor(layerOpPortIndex); if 
(layerOpArmTensor) { return layerOpArmTensor; } else { return nullptr; } } } 
std::shared_ptr<arm_compute::Tensor> MWACLUtils::getLayerOpArmTensorsharedPtr( 
MWTensorBase* aTensor) { auto owningLayer = aTensor->getOwner(); if 
(owningLayer == nullptr) { return nullptr; } auto owningLayerImpl = 
owningLayer->getImpl(); int layerOpPortIndex = aTensor->getSourcePortIndex(); 
if (owningLayerImpl == nullptr) { if (owningLayer->isCustomLayer()) { return 
nullptr; }else{ int inIndex = owningLayer->getInPlaceIndex(layerOpPortIndex); 
bool isInplaceLayer = (inIndex!=-1); bool isSingleIpLayer = 
(owningLayer->getNumInputs() == 1); assert(isSingleIpLayer || isInplaceLayer); 
if(isSingleIpLayer){ return 
MWACLUtils::getLayerOpArmTensorsharedPtr(owningLayer->getInputTensor(0)); } 
else { assert(isInplaceLayer); return 
MWACLUtils::getLayerOpArmTensorsharedPtr(owningLayer->getInputTensor(inIndex)); 
} } } else { auto layerOpArmTensorSharePtr = 
owningLayerImpl->getCurrentLayerOpArmTensorSharedPtr(layerOpPortIndex); if 
(layerOpArmTensorSharePtr) { return layerOpArmTensorSharePtr; } else { return 
nullptr; } } } void MWACLUtils::doPermutation(const float* inputBuf, float* 
outputBuf, const int ipDims[], const int strides[]) { int ipDim_0 = ipDims[0];  
int ipDim_1 = ipDims[1]; int ipDim_2 = ipDims[2]; int ipDim_3 = ipDims[3]; int 
ipDim_4 = ipDims[4];  int ipStride_4 = 1;  int ipStride_3 = ipDim_4; int 
ipStride_2 = ipDim_3 * ipStride_3; int ipStride_1 = ipDim_2 * ipStride_2; int 
ipStride_0 = ipDim_1 * ipStride_1;  int opStride_0 = strides[0];  int 
opStride_1 = strides[1]; int opStride_2 = strides[2]; int opStride_3 = 
strides[3]; int opStride_4 = strides[4]; 
#pragma omp parallel for collapse(5)
 for (int p = 0; p < ipDim_0; p++) { for (int q = 0; q < ipDim_1; q++) { for 
(int r = 0; r < ipDim_2; r++) { for (int s = 0; s < ipDim_3; s++) { for (int t 
= 0; t < ipDim_4; t++) { int ipBufIdx = (p * ipStride_0) + (q * ipStride_1) + 
(r * ipStride_2) + (s * ipStride_3) + (t * ipStride_4); int opBufIdx = (p * 
opStride_0) + (q * opStride_1) + (r * opStride_2) + (s * opStride_3) + (t * 
opStride_4); outputBuf[opBufIdx] = inputBuf[ipBufIdx]; } } } } } }