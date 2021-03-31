//
// File: streamingClassifier.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 19-Mar-2021 15:00:36
//

// Include Files
#include "streamingClassifier.h"
#include "DeepLearningNetwork.h"
#include "FFTImplementationCallback.h"
#include "predictAndUpdateState.h"
#include "rt_nonfinite.h"
#include "streamingClassifier_data.h"
#include "streamingClassifier_initialize.h"
#include "streamingClassifier_internal_types.h"
#include "streamingClassifier_types.h"
#include <algorithm>
#include <cmath>

// Variable Definitions
static bool airCompNet_not_empty;

// Function Declarations
static float rt_powf_snf(float u0, float u1);

// Function Definitions
//
// Arguments    : float u0
//                float u1
// Return Type  : float
//
static float rt_powf_snf(float u0, float u1)
{
  float y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaNF;
  } else {
    float f;
    float f1;
    f = std::abs(u0);
    f1 = std::abs(u1);
    if (std::isinf(u1)) {
      if (f == 1.0F) {
        y = 1.0F;
      } else if (f > 1.0F) {
        if (u1 > 0.0F) {
          y = rtInfF;
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = rtInfF;
      }
    } else if (f1 == 0.0F) {
      y = 1.0F;
    } else if (f1 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0F) && (u1 > std::floor(u1))) {
      y = rtNaNF;
    } else {
      y = std::pow(u0, u1);
    }
  }
  return y;
}

//
// This is a streaming classifier function
//
// Arguments    : const float audioIn[512]
//                const float M[10]
//                const float S[10]
//                float scores[8]
//                float features[10]
// Return Type  : void
//
void streamingClassifier(const float audioIn[512], const float M[10],
                         const float S[10], float scores[8], float features[10])
{
  static TrainedModel0_0 airCompNet;
  static const float fv[512]{
      0.08F,         0.080034636F,  0.0801385418F, 0.0803117F,    0.0805540904F,
      0.0808656663F, 0.0812463909F, 0.0816962F,    0.082215026F,  0.0828027949F,
      0.0834594145F, 0.0841847882F, 0.084978804F,  0.0858413503F, 0.0867722854F,
      0.0877714753F, 0.088838771F,  0.0899740085F, 0.0911770165F, 0.0924476236F,
      0.0937856212F, 0.0951908231F, 0.0966630131F, 0.0982019603F, 0.0998074487F,
      0.101479225F,  0.103217036F,  0.105020627F,  0.106889732F,  0.108824052F,
      0.110823311F,  0.112887204F,  0.115015417F,  0.117207631F,  0.119463511F,
      0.121782728F,  0.124164924F,  0.126609743F,  0.129116818F,  0.131685778F,
      0.134316221F,  0.137007758F,  0.139759988F,  0.142572492F,  0.14544484F,
      0.148376614F,  0.151367366F,  0.154416636F,  0.157523975F,  0.160688922F,
      0.163910985F,  0.167189687F,  0.170524538F,  0.173915029F,  0.177360639F,
      0.180860877F,  0.184415191F,  0.188023061F,  0.191683933F,  0.195397258F,
      0.199162483F,  0.202979028F,  0.206846341F,  0.210763827F,  0.214730874F,
      0.21874693F,   0.222811356F,  0.22692354F,   0.231082886F,  0.235288739F,
      0.239540488F,  0.243837491F,  0.248179093F,  0.252564639F,  0.256993473F,
      0.261464924F,  0.265978307F,  0.270533F,     0.275128245F,  0.279763371F,
      0.284437686F,  0.289150506F,  0.293901086F,  0.29868874F,   0.303512752F,
      0.308372349F,  0.313266844F,  0.318195462F,  0.323157489F,  0.32815218F,
      0.333178788F,  0.338236541F,  0.343324661F,  0.348442405F,  0.353589F,
      0.358763665F,  0.363965631F,  0.36919409F,   0.37444827F,   0.379727393F,
      0.385030657F,  0.390357256F,  0.395706385F,  0.401077271F,  0.406469047F,
      0.41188094F,   0.417312145F,  0.422761798F,  0.428229123F,  0.433713257F,
      0.439213425F,  0.444728762F,  0.450258464F,  0.455801666F,  0.461357534F,
      0.466925263F,  0.472504F,     0.478092879F,  0.483691096F,  0.489297777F,
      0.494912118F,  0.500533223F,  0.506160319F,  0.511792481F,  0.517428875F,
      0.523068666F,  0.528711F,     0.534355104F,  0.54F,         0.545644879F,
      0.551288962F,  0.556931317F,  0.562571108F,  0.568207562F,  0.573839724F,
      0.57946676F,   0.585087895F,  0.590702236F,  0.596308887F,  0.601907134F,
      0.607496F,     0.61307472F,   0.618642449F,  0.624198377F,  0.629741549F,
      0.635271251F,  0.640786588F,  0.646286726F,  0.65177089F,   0.657238185F,
      0.662687898F,  0.668119073F,  0.673530936F,  0.678922713F,  0.684293628F,
      0.689642727F,  0.694969356F,  0.70027262F,   0.705551744F,  0.710805893F,
      0.716034353F,  0.721236348F,  0.726411F,     0.731557608F,  0.736675322F,
      0.741763473F,  0.746821225F,  0.751847804F,  0.756842494F,  0.761804521F,
      0.76673317F,   0.771627665F,  0.776487291F,  0.781311274F,  0.786098897F,
      0.790849507F,  0.795562327F,  0.800236642F,  0.804871798F,  0.809467F,
      0.814021707F,  0.818535089F,  0.823006511F,  0.827435374F,  0.831820905F,
      0.836162508F,  0.840459526F,  0.844711244F,  0.848917127F,  0.853076458F,
      0.857188642F,  0.861253083F,  0.865269125F,  0.869236171F,  0.873153687F,
      0.877020955F,  0.8808375F,    0.884602726F,  0.888316095F,  0.891976953F,
      0.895584822F,  0.899139106F,  0.902639329F,  0.906084955F,  0.909475446F,
      0.912810326F,  0.916089F,     0.919311106F,  0.922476F,     0.925583363F,
      0.928632617F,  0.931623399F,  0.934555173F,  0.937427521F,  0.94024F,
      0.94299227F,   0.945683777F,  0.94831425F,   0.95088315F,   0.953390241F,
      0.955835104F,  0.958217263F,  0.96053648F,   0.962792397F,  0.964984596F,
      0.96711278F,   0.96917671F,   0.971175969F,  0.973110259F,  0.974979341F,
      0.976783F,     0.978520751F,  0.980192542F,  0.981798053F,  0.983337F,
      0.98480916F,   0.986214399F,  0.987552404F,  0.988823F,     0.990026F,
      0.991161227F,  0.992228508F,  0.99322772F,   0.994158626F,  0.995021224F,
      0.995815217F,  0.996540606F,  0.997197211F,  0.997785F,     0.998303831F,
      0.998753607F,  0.999134302F,  0.999445915F,  0.999688268F,  0.999861479F,
      0.99996537F,   1.0F,          0.99996537F,   0.999861479F,  0.999688268F,
      0.999445915F,  0.999134302F,  0.998753607F,  0.998303831F,  0.997785F,
      0.997197211F,  0.996540606F,  0.995815217F,  0.995021224F,  0.994158626F,
      0.99322772F,   0.992228508F,  0.991161227F,  0.990026F,     0.988823F,
      0.987552404F,  0.986214399F,  0.98480916F,   0.983337F,     0.981798053F,
      0.980192542F,  0.978520751F,  0.976783F,     0.974979341F,  0.973110259F,
      0.971175969F,  0.96917671F,   0.96711278F,   0.964984596F,  0.962792397F,
      0.96053648F,   0.958217263F,  0.955835104F,  0.953390241F,  0.95088315F,
      0.94831425F,   0.945683777F,  0.94299227F,   0.94024F,      0.937427521F,
      0.934555173F,  0.931623399F,  0.928632617F,  0.925583363F,  0.922476F,
      0.919311106F,  0.916089F,     0.912810326F,  0.909475446F,  0.906084955F,
      0.902639329F,  0.899139106F,  0.895584822F,  0.891976953F,  0.888316095F,
      0.884602726F,  0.8808375F,    0.877020955F,  0.873153687F,  0.869236171F,
      0.865269125F,  0.861253083F,  0.857188642F,  0.853076458F,  0.848917127F,
      0.844711244F,  0.840459526F,  0.836162508F,  0.831820905F,  0.827435374F,
      0.823006511F,  0.818535089F,  0.814021707F,  0.809467F,     0.804871798F,
      0.800236642F,  0.795562327F,  0.790849507F,  0.786098897F,  0.781311274F,
      0.776487291F,  0.771627665F,  0.76673317F,   0.761804521F,  0.756842494F,
      0.751847804F,  0.746821225F,  0.741763473F,  0.736675322F,  0.731557608F,
      0.726411F,     0.721236348F,  0.716034353F,  0.710805893F,  0.705551744F,
      0.70027262F,   0.694969356F,  0.689642727F,  0.684293628F,  0.678922713F,
      0.673530936F,  0.668119073F,  0.662687898F,  0.657238185F,  0.65177089F,
      0.646286726F,  0.640786588F,  0.635271251F,  0.629741549F,  0.624198377F,
      0.618642449F,  0.61307472F,   0.607496F,     0.601907134F,  0.596308887F,
      0.590702236F,  0.585087895F,  0.57946676F,   0.573839724F,  0.568207562F,
      0.562571108F,  0.556931317F,  0.551288962F,  0.545644879F,  0.54F,
      0.534355104F,  0.528711F,     0.523068666F,  0.517428875F,  0.511792481F,
      0.506160319F,  0.500533223F,  0.494912118F,  0.489297777F,  0.483691096F,
      0.478092879F,  0.472504F,     0.466925263F,  0.461357534F,  0.455801666F,
      0.450258464F,  0.444728762F,  0.439213425F,  0.433713257F,  0.428229123F,
      0.422761798F,  0.417312145F,  0.41188094F,   0.406469047F,  0.401077271F,
      0.395706385F,  0.390357256F,  0.385030657F,  0.379727393F,  0.37444827F,
      0.36919409F,   0.363965631F,  0.358763665F,  0.353589F,     0.348442405F,
      0.343324661F,  0.338236541F,  0.333178788F,  0.32815218F,   0.323157489F,
      0.318195462F,  0.313266844F,  0.308372349F,  0.303512752F,  0.29868874F,
      0.293901086F,  0.289150506F,  0.284437686F,  0.279763371F,  0.275128245F,
      0.270533F,     0.265978307F,  0.261464924F,  0.256993473F,  0.252564639F,
      0.248179093F,  0.243837491F,  0.239540488F,  0.235288739F,  0.231082886F,
      0.22692354F,   0.222811356F,  0.21874693F,   0.214730874F,  0.210763827F,
      0.206846341F,  0.202979028F,  0.199162483F,  0.195397258F,  0.191683933F,
      0.188023061F,  0.184415191F,  0.180860877F,  0.177360639F,  0.173915029F,
      0.170524538F,  0.167189687F,  0.163910985F,  0.160688922F,  0.157523975F,
      0.154416636F,  0.151367366F,  0.148376614F,  0.14544484F,   0.142572492F,
      0.139759988F,  0.137007758F,  0.134316221F,  0.131685778F,  0.129116818F,
      0.126609743F,  0.124164924F,  0.121782728F,  0.119463511F,  0.117207631F,
      0.115015417F,  0.112887204F,  0.110823311F,  0.108824052F,  0.106889732F,
      0.105020627F,  0.103217036F,  0.101479225F,  0.0998074487F, 0.0982019603F,
      0.0966630131F, 0.0951908231F, 0.0937856212F, 0.0924476236F, 0.0911770165F,
      0.0899740085F, 0.088838771F,  0.0877714753F, 0.0867722854F, 0.0858413503F,
      0.084978804F,  0.0841847882F, 0.0834594145F, 0.0828027949F, 0.082215026F,
      0.0816962F,    0.0812463909F, 0.0808656663F, 0.0805540904F, 0.0803117F,
      0.0801385418F, 0.080034636F};
  creal32_T Y[512];
  creal32_T Z[257];
  float c[512];
  float X[257];
  float b_c[257];
  float linearSpectrum[257];
  float temp[257];
  float c_c[256];
  float b_centroid_tmp;
  float centroid;
  float centroid_tmp;
  float f;
  float spread;
  float x;
  int eint;
  int i;
  int idx;
  short ii_data;
  bool exitg1;
  if (!isInitialized_streamingClassifier) {
    streamingClassifier_initialize();
  }
  //    Copyright 2020 The MathWorks, Inc.
  if (!airCompNet_not_empty) {
    coder::DeepLearningNetwork_setup(&airCompNet);
    airCompNet_not_empty = true;
  }
  //  Extract features using function
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
  //    Generated by audioFeatureExtractor on 19-Mar-2021 14:55:32 -0700
  //  Preallocate feature vector
  //  Fourier transform
  for (i = 0; i < 512; i++) {
    c[i] = audioIn[i] * fv[i];
  }
  coder::internal::FFTImplementationCallback::doHalfLengthRadix2(c, Y);
  for (idx = 0; idx < 257; idx++) {
    Z[idx] = Y[config.OneSidedSpectrumBins[idx] - 1];
  }
  //  Linear spectrum
  for (idx = 0; idx < 257; idx++) {
    i = config.linearSpectrum.FrequencyBins[idx] - 1;
    linearSpectrum[idx] =
        (Z[i].re * Z[i].re - Z[i].im * -Z[i].im) * 2.61639143E-5F;
  }
  linearSpectrum[0] *= 0.5F;
  linearSpectrum[256] *= 0.5F;
  //  Spectral descriptors
  centroid_tmp = linearSpectrum[0];
  for (i = 0; i < 256; i++) {
    centroid_tmp += linearSpectrum[i + 1];
  }
  for (i = 0; i < 257; i++) {
    b_c[i] =
        linearSpectrum[i] * config.SpectralDescriptorInput.FrequencyVector[i];
  }
  x = b_c[0];
  for (i = 0; i < 256; i++) {
    x += b_c[i + 1];
  }
  centroid = x / centroid_tmp;
  for (i = 0; i < 257; i++) {
    f = config.SpectralDescriptorInput.FrequencyVector[i] - centroid;
    f *= f;
    temp[i] = f;
    X[i] = f * linearSpectrum[i];
  }
  x = X[0];
  spread = linearSpectrum[0];
  for (i = 0; i < 256; i++) {
    x += X[i + 1];
    spread += linearSpectrum[i + 1];
  }
  spread = std::sqrt(x / spread);
  for (i = 0; i < 257; i++) {
    f = temp[i];
    X[i] = f * f * linearSpectrum[i];
  }
  x = X[0];
  features[9] = spread;
  features[0] = centroid;
  b_centroid_tmp = linearSpectrum[0];
  for (i = 0; i < 256; i++) {
    x += X[i + 1];
    b_centroid_tmp += linearSpectrum[i + 1];
  }
  features[5] = x / (rt_powf_snf(spread, 4.0F) * centroid_tmp);
  for (i = 0; i < 257; i++) {
    b_c[i] =
        linearSpectrum[i] * config.SpectralDescriptorInput.FrequencyVector[i];
  }
  x = b_c[0];
  for (i = 0; i < 256; i++) {
    x += b_c[i + 1];
  }
  centroid = x / b_centroid_tmp;
  for (i = 0; i < 257; i++) {
    f = config.SpectralDescriptorInput.FrequencyVector[i] - centroid;
    temp[i] = f;
    X[i] = f * f * linearSpectrum[i];
  }
  x = X[0];
  spread = linearSpectrum[0];
  for (i = 0; i < 256; i++) {
    x += X[i + 1];
    spread += linearSpectrum[i + 1];
  }
  for (i = 0; i < 257; i++) {
    X[i] = rt_powf_snf(temp[i], 3.0F) * linearSpectrum[i];
  }
  centroid = X[0];
  for (i = 0; i < 256; i++) {
    centroid += X[i + 1];
  }
  features[7] =
      centroid / (rt_powf_snf(std::sqrt(x / spread), 3.0F) * b_centroid_tmp);
  if (!std::isnan(linearSpectrum[0])) {
    idx = 1;
  } else {
    idx = 0;
    i = 2;
    exitg1 = false;
    while ((!exitg1) && (i < 258)) {
      if (!std::isnan(linearSpectrum[i - 1])) {
        idx = i;
        exitg1 = true;
      } else {
        i++;
      }
    }
  }
  if (idx == 0) {
    centroid = linearSpectrum[0];
  } else {
    centroid = linearSpectrum[idx - 1];
    idx++;
    for (i = idx; i < 258; i++) {
      f = linearSpectrum[i - 1];
      if (centroid < f) {
        centroid = f;
      }
    }
  }
  x = linearSpectrum[0];
  for (i = 0; i < 256; i++) {
    f = linearSpectrum[i + 1];
    x += f;
    c_c[i] = (f - linearSpectrum[0]) / (static_cast<float>(i) + 1.0F);
  }
  features[1] = centroid / (x / 257.0F);
  x = c_c[0];
  spread = linearSpectrum[1];
  for (i = 0; i < 255; i++) {
    x += c_c[i + 1];
    spread += linearSpectrum[i + 2];
  }
  features[2] = x / spread;
  spread = linearSpectrum[0];
  for (i = 0; i < 256; i++) {
    spread += linearSpectrum[i + 1];
  }
  for (i = 0; i < 257; i++) {
    X[i] = linearSpectrum[i] / spread;
  }
  for (i = 0; i < 257; i++) {
    f = X[i];
    if (f == 0.0F) {
      b_c[i] = rtMinusInfF;
    } else if (f < 0.0F) {
      b_c[i] = rtNaNF;
    } else if ((!std::isinf(f)) && (!std::isnan(f))) {
      centroid = std::frexp(f, &eint);
      if (centroid == 0.5F) {
        b_c[i] = static_cast<float>(eint) - 1.0F;
      } else if ((eint == 1.0F) && (centroid < 0.75F)) {
        b_c[i] = std::log(2.0F * centroid) / 0.693147182F;
      } else {
        b_c[i] = std::log(centroid) / 0.693147182F + static_cast<float>(eint);
      }
    } else {
      b_c[i] = f;
    }
  }
  for (idx = 0; idx < 257; idx++) {
    X[idx] *= b_c[idx];
  }
  if (std::isnan(X[0])) {
    spread = 0.0F;
  } else {
    spread = X[0];
  }
  for (i = 0; i < 256; i++) {
    f = X[i + 1];
    if (!std::isnan(f)) {
      spread += f;
    }
  }
  features[3] = -spread / 8.00562477F;
  for (i = 0; i < 257; i++) {
    X[i] = std::log(linearSpectrum[i] + 1.1920929E-7F);
  }
  x = X[0];
  centroid = linearSpectrum[0];
  for (i = 0; i < 256; i++) {
    x += X[i + 1];
    centroid += linearSpectrum[i + 1];
  }
  features[4] = std::exp(x / 257.0F) / (centroid / 257.0F);
  std::copy(&linearSpectrum[0], &linearSpectrum[257], &b_c[0]);
  for (i = 0; i < 256; i++) {
    b_c[i + 1] += b_c[i];
  }
  centroid = b_c[256] * 0.95F;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 257)) {
    if (b_c[i] >= centroid) {
      ii_data = static_cast<short>(i + 1);
      exitg1 = true;
    } else {
      i++;
    }
  }
  features[6] = config.SpectralDescriptorInput.FrequencyVector[ii_data - 1];
  x = config.SpectralDescriptorInput.FrequencyVector[0];
  for (i = 0; i < 256; i++) {
    x += config.SpectralDescriptorInput.FrequencyVector[i + 1];
  }
  centroid = x / 257.0F;
  for (i = 0; i < 257; i++) {
    temp[i] = config.SpectralDescriptorInput.FrequencyVector[i] - centroid;
  }
  x = linearSpectrum[0];
  for (i = 0; i < 256; i++) {
    x += linearSpectrum[i + 1];
  }
  centroid = x / 257.0F;
  for (i = 0; i < 257; i++) {
    b_c[i] = (linearSpectrum[i] - centroid) * temp[i];
  }
  x = b_c[0];
  for (i = 0; i < 256; i++) {
    x += b_c[i + 1];
  }
  for (i = 0; i < 257; i++) {
    f = temp[i];
    X[i] = f * f;
  }
  spread = X[0];
  for (i = 0; i < 256; i++) {
    spread += X[i + 1];
  }
  features[8] = x / spread;
  //  Normalize
  for (idx = 0; idx < 10; idx++) {
    features[idx] = (features[idx] - M[idx]) / S[idx];
  }
  //  Classify
  coder::DeepLearningNetwork_predictAndUpdateState(&airCompNet, features,
                                                   scores);
}

//
// This is a streaming classifier function
//
// Arguments    : void
// Return Type  : void
//
void streamingClassifier_init()
{
  airCompNet_not_empty = false;
}

//
// File trailer for streamingClassifier.cpp
//
// [EOF]
//
