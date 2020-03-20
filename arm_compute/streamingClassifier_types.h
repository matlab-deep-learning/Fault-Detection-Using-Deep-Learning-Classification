//
// File: streamingClassifier_types.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 20-Mar-2020 02:48:33
//
#ifndef STREAMINGCLASSIFIER_TYPES_H
#define STREAMINGCLASSIFIER_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
#include "cnn_api.hpp"
#include "MWTargetNetworkImpl.hpp"

// Type Definitions
class FFTImplementationCallback
{
 public:
  static void doHalfLengthRadix2(const float x[512], creal32_T y[512]);
};

struct cell_wrap_4
{
  unsigned int f1[8];
};

class dsp_private_AsyncBuffercgHelper
{
 public:
  dsp_private_AsyncBuffercgHelper *init();
  void reset();
  int step(const float varargin_1[256]);
  void setupAndReset();
  void b_setup();
  int write(const float in[256]);
  int get_NumUnreadSamples() const;
  void read(float out_data[], int out_size[1], int *underrun);
  static void ReadSamplesFromBuffer(const dsp_private_AsyncBuffercgHelper *obj,
    float out_data[], int out_size[1], int *underrun, int *c);
  void matlabCodegenDestructor();
  void release();
  void releaseWrapper();
  ~dsp_private_AsyncBuffercgHelper();
  bool matlabCodegenIsDeleted;
  float Cache[513];
  int ReadPointer;
  int WritePointer;
  bool c_AsyncBuffercgHelper_isInitial;
 protected:
  int isInitialized;
  int CumulativeOverrun;
  int CumulativeUnderrun;
 private:
  bool isSetupComplete;
  cell_wrap_4 inputVarSize[1];
  int NumChannels;
};

class dsp_private_AsyncBuffercg
{
 public:
  dsp_private_AsyncBuffercg *init();
  void reset();
  void write(const float in[256]);
  int get_NumUnreadSamples() const;
  void read(float out_data[], int out_size[1]);
  void matlabCodegenDestructor();
  void release();
  ~dsp_private_AsyncBuffercg();
  bool matlabCodegenIsDeleted;
  dsp_private_AsyncBuffercgHelper pBuffer;
};

class dsp_private_STFTSysObj
{
 public:
  dsp_private_STFTSysObj *init();
  bool isLockedAndNotReleased() const;
  void step(const float varargin_1[256], creal32_T varargout_1_data[], int
            varargout_1_size[2]);
  void setupAndReset();
  void b_setup();
  void checkTunableProps();
  void matlabCodegenDestructor();
  void release();
  void releaseWrapper();
  ~dsp_private_STFTSysObj();
 protected:
  void stepImpl(const float u[256], creal32_T Y_data[], int Y_size[2]);
 public:
  bool matlabCodegenIsDeleted;
  bool TunablePropsChanged;
  double Window[512];
  dsp_private_AsyncBuffercg pBuff;
 private:
  int isInitialized;
  bool isSetupComplete;
  cell_wrap_4 inputVarSize[1];
  float pWindow[512];
  int pNumChans;
};

class ProcessConstructorArguments
{
 public:
  static void b_do(dsp_private_STFTSysObj *obj);
};

class SystemProp
{
 public:
  static void matlabCodegenNotifyAnyProp(dsp_private_STFTSysObj *obj);
};

class b_TrainedModel_0
{
 public:
  void allocate();
  void postsetup();
  b_TrainedModel_0();
  void deallocate();
  void setSize(int seqLength);
  void resetState();
  void updateState();
  void setup();
  void predict();
  void cleanup();
  float *getLayerOutput(int layerIndex, int portIndex);
  float *getInputDataPointer();
  float *getOutputDataPointer();
  ~b_TrainedModel_0();
  int maxSequenceLength;
  int batchSize;
  int numLayers;
  MWTensor *inputTensor;
  MWTensor *outputTensor;
  MWCNNLayer *layers[7];
  float *inputData;
  float *outputData;
 private:
  MWTargetNetworkImpl *targetImpl;
};

class dsp_private_STFTCG
{
 public:
  dsp_private_STFTCG *init();
  void parenReference(const float u[256], creal32_T Y_data[], int Y_size[2]);
  void step(const float u[256], creal32_T y_data[], int y_size[2]);
  void matlabCodegenDestructor();
  ~dsp_private_STFTCG();
  bool matlabCodegenIsDeleted;
  dsp_private_STFTSysObj pObj;
};

#endif

//
// File trailer for streamingClassifier_types.h
//
// [EOF]
//
