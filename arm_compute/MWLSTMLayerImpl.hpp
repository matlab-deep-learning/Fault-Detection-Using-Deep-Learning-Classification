/* Copyright 2019 The MathWorks, Inc. */

#ifndef _MW_ARMNEON_LSTM_LAYER_IMPL_
#define _MW_ARMNEON_LSTM_LAYER_IMPL_

#include "MWCNNLayerImpl.hpp"

/**
 * Codegen class for LSTM layer implementation
 */
#if defined(USE_19_02_LIBRARY)
#define MAX_CELL_IO_STATEBUF_SIZE , m_maxCellIOStateBufSize
#define MAX_HIDDEN_IO_STATE_BUF_SIZE , m_maxhiddenIOStateBufSize
#else
#define MAX_CELL_IO_STATEBUF_SIZE 
#define MAX_HIDDEN_IO_STATE_BUF_SIZE 
#endif

#define USE_LSTM_ACL_API 0
#if USE_LSTM_ACL_API
class MWLSTMLayerImpl : public MWCNNLayerImpl {
  public:
    MWLSTMLayerImpl(MWCNNLayer* layer,
                    MWTargetNetworkImpl* ntwk_impl,
                    int jHaoHEqZgMiwRsdCogKz,
                    int UpnEytIWGokwbTFkBcSx,
                    bool m_last_mode,
                    const char* yeRJnYjpvmkKjBpyWlaV,
                    const char* QMNXyOvXaZDsCpiIJPsn,
                    const char* XCnEVUzxqcNgsuUbRonz,
                    const char* WprSrhAStKGxyXeoxETy);

    ~MWLSTMLayerImpl() {
    }

    void predict();
    void cleanup();
    void allocate();
    void deallocate();
    void resetState();
    void updateState();

  private:
    // Below private members are initialized in impl constructor.
    float* yPBlKhIGljihkXaXbYpB;
    float* PtRNGuserCxHAQfyEjFc;

    int iFWfUCwhmxBsOTMvFHgz;
    int iMyHYqdPsEjdhQptHQNt;
    bool cCXqPFPPcoHzYMDpnUxQ;
    int tnTPxeDjBsqLAPkJcPJX;

    /* Maintain m_initialCellStateData, m_initialHiddenStateData data pointers
     * in this class, because after every predict run, we should reset the initial
     * hx, cx states at the end of predict call.
     */
    float* m_initialCellStateData;
    float* m_initialHiddenStateData;

	// Buffer pointers for the cx, hx, cy and hy respectively.
	float* RQSttSyDKXCHDWSijmNk[3];
	float* UWAGLbDcvybdWBtshhsr[3];
	
	int m_maxCellIOStateBufSize;
	int m_maxhiddenIOStateBufSize;
    
    // This flag used to decide whether we should use ping-pong strategy or not for updating states.
    bool m_usePingPongStrategy{false}; 

    // This flag used to create Cell/Hidden state data buffers at only once.
    // And assign these buffers to Cell/Hidden state Arm tensors.
    bool m_areCHStateArmTensorsAllocated{false};

  private:
    void propagateSize();

    void createInputArmTensors();
    void createWeightAndBiasArmTensors();
    void createOutputArmTensors();
    void allocateWeights();
    void allocateBias();

    void loadWeights(const char*, long int);
    void loadBias(const char*, long int);
    void loadInitialHiddenState(const char*);
    void loadInitialCellState(const char*);

    void updateInternalTmpStates();
    void resetInternalTmpStates();
    void allocateCellHiddenIOARMTensors();

  private:
    // input/rec weights data, bias data for Input, Forget, Cell, Output gates in order.
    arm_compute::Tensor YeIFysyIXePEVfpcANol[4];
    arm_compute::Tensor qBTcAwVGZERyCjGYByPe[4];
    arm_compute::Tensor PfisSEEWDaQFynnzlcin[4];
    bool isIpWgtsPadded[4];
    bool isRecWgtsPadded[4];
    bool isBiasPadded[4];

    // hx, hy arm tensors holds the hidden state input/output of the entire
    // sequence. Same applicable for the cx, cy.
    arm_compute::Tensor m_hxArmTensor; // output_state_in
    arm_compute::Tensor m_cxArmTensor; // cell_state_in

    arm_compute::Tensor m_hyArmTensor; // output_state_out
    arm_compute::Tensor m_cyArmTensor; // cell_state_out

    /* hx temp, hy temp arm tensors holds the hidden state input/output for
     * single time step. Same applicable for the cx temp, cy temp.
     * Use m_hyTempArmTensor in place of the output arm tensor. Because both gives the same output.
     */
    arm_compute::Tensor m_hxTempArmTensor; // API output_state_in
    arm_compute::Tensor m_cxTempArmTensor; // API cell_state_in

    arm_compute::Tensor m_hyTempArmTensor; // API output_state_out
    arm_compute::Tensor m_cyTempArmTensor; // API cell_state_out

    arm_compute::Tensor m_scratchBufArmTensor; // Output data of inputGate, cell state, forget gate

    arm_compute::Tensor m_tmpInputArmTensor;
    std::unique_ptr<arm_compute::NELSTMLayer> m_lstmLayer;

    arm_compute::LSTMParams<arm_compute::ITensor> m_lstmParams;
};
#else
class MWLSTMLayerImpl : public MWCNNLayerImpl {
  public:
    MWLSTMLayerImpl(MWCNNLayer* layer,
                    MWTargetNetworkImpl* ntwk_impl,
                    int jHaoHEqZgMiwRsdCogKz,
                    int UpnEytIWGokwbTFkBcSx,
                    bool m_last_mode,
                    const char* yeRJnYjpvmkKjBpyWlaV,
                    const char* QMNXyOvXaZDsCpiIJPsn,
                    const char* XCnEVUzxqcNgsuUbRonz,
                    const char* WprSrhAStKGxyXeoxETy);

    ~MWLSTMLayerImpl() {
    }

    void predict();
    void cleanup();
    void allocate();
    void deallocate();
    void resetState();
    void updateState();

  private:
    // Below private members are initialized in impl constructor.
    float* yPBlKhIGljihkXaXbYpB;
    float* ZKjSVYDDjACizBkGbqBq;
    float* qEXwbWWsnOADJeTXfRVa;

    float* PtRNGuserCxHAQfyEjFc;

    int iFWfUCwhmxBsOTMvFHgz;
    int iMyHYqdPsEjdhQptHQNt;
    bool cCXqPFPPcoHzYMDpnUxQ;
    int tnTPxeDjBsqLAPkJcPJX;

    // Buffer to hold the LSTM layer input ARM Tensor data.
    float* fSbUUBgjKRbNXrHrlOLo;

    // buffers to hold batch-expanded initial states
    float* URgvgDXnZskIYGdtimcU;
    float* RAtlBpdedvgxUsgDTsch;

    // State Buffers - Used to switch between the input and output states.
    float* RQSttSyDKXCHDWSijmNk[3];
    float* UWAGLbDcvybdWBtshhsr[3];

    // This flag used to create Cell/Hidden state data buffers at only once.
    // And assign these buffers to Cell/Hidden state Arm tensors.
    bool m_areCHStateArmTensorsAllocated{false};

    // Size of cell & hidden states.
    // If LSTM variant is bi-directional then state size will be iMyHYqdPsEjdhQptHQNt*2.
    // Otherwise state size will be iMyHYqdPsEjdhQptHQNt.
    int tqZLvfMHdgZzbchUyDzd;

  private:
    void propagateSize();
    
    void loadWeights(const char*);
    void loadBias(const char*);
    void loadInitialHiddenState(const char*);
    void loadInitialCellState(const char*);

    void updateInternalTmpStates();
    void resetInternalTmpStates();
    void allocateCellHiddenIOARMTensors();

    void runSingleTimeStepPredict(float*, float*, float*, float*, float*, float*, float*, float*);


  private:
    // hx, hxTemp, hy, hyTemp are the buffer pointers that are used to
    // switch between the buffers.
    float* UzOdnHgHuNHtprVxxxXl;
    float* RVrPByQXdKmunRZHKWJD;
    float* VFKMunbyHoAmpHUSkuUn;
    float* SIBpKtDURUWQaaenbwrC;

    float* UzaGmBLFEwmwaFXebUma;
    float* RgjhbaFFVMpznMgMQMrE;
    float* WOJynDmqVUPWjAGVIuMQ;
    float* SUjIWYfjMcdzSZaCSVRT;
};

#endif
#endif