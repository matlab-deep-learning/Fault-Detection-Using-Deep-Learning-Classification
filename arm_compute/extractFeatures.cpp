//
// File: extractFeatures.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 19-Mar-2021 15:00:36
//

// Include Files
#include "extractFeatures.h"
#include "rt_nonfinite.h"
#include "streamingClassifier_data.h"
#include "streamingClassifier_types.h"

// Function Definitions
//
// extractFeatures Extract multiple features from streaming audio
//    featureVector = extractFeatures(audioIn) returns audio features
//    extracted from audioIn.
//
//    Parameters of the audioFeatureExtractor used to generated this
//    function must be honored when calling this function.
//     - Sample rate of the input should be 16000 Hz.
//     - Frame length of the input should be 512 samples.
//     - Successive frames of the input should be overlapped by
//       0 samples before calling extractFeatures.
//
//
//       % EXAMPLE 1: Extract features
//         source = dsp.ColoredNoise();
//         inputBuffer = dsp.AsyncBuffer;
//         for ii = 1:10
//             audioIn = source();
//             write(inputBuffer,audioIn);
//             while inputBuffer.NumUnreadSamples > 512
//                 x = read(inputBuffer,512,0);
//                 featureVector = extractFeatures(x);
//                 % ... do something with featureVector ...
//             end
//          end
//
//
//       % EXAMPLE 2: Generate code
//         targetDataType = "single";
//         codegen extractFeatures -args {ones(512,1,targetDataType)}
//         source = dsp.ColoredNoise('OutputDataType',targetDataType);
//         inputBuffer = dsp.AsyncBuffer;
//         for ii = 1:10
//             audioIn = source();
//             write(inputBuffer,audioIn);
//             while inputBuffer.NumUnreadSamples > 512
//                 x = read(inputBuffer,512,0);
//                 featureVector = extractFeatures_mex(x);
//                 % ... do something with featureVector ...
//             end
//          end
//
//    See also audioFeatureExtractor, dsp.AsyncBuffer, codegen.
//
// Arguments    : void
// Return Type  : void
//
void extractFeatures_init()
{
  config.linearSpectrum.NormalizationFactor = 2.61639143E-5F;
  for (int i{0}; i < 257; i++) {
    config.OneSidedSpectrumBins[i] = static_cast<unsigned short>(i + 1U);
    config.linearSpectrum.FrequencyBins[i] =
        static_cast<unsigned short>(i + 1U);
    config.SpectralDescriptorInput.FrequencyVector[i] =
        31.25F * static_cast<float>(i);
  }
}

//
// File trailer for extractFeatures.cpp
//
// [EOF]
//
