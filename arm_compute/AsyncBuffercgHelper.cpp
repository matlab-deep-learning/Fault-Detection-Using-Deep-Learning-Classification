//
// File: AsyncBuffercgHelper.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 20-Mar-2020 02:48:33
//

// Include Files
#include "AsyncBuffercgHelper.h"
#include "DeepLearningNetwork.h"
#include "matlabCodegenHandle.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"
#include <cstring>

// Function Definitions

//
// Arguments    : const dsp_private_AsyncBuffercgHelper *obj
//                float out_data[]
//                int out_size[1]
//                int *underrun
//                int *c
// Return Type  : void
//
void dsp_private_AsyncBuffercgHelper::ReadSamplesFromBuffer(const
  dsp_private_AsyncBuffercgHelper *obj, float out_data[], int out_size[1], int
  *underrun, int *c)
{
  int rPtr;
  int wPtr;
  int n;
  int y_data[513];
  int k;
  int readIdx_data[1024];
  int b_y_data[511];
  rPtr = obj->ReadPointer;
  wPtr = obj->WritePointer;
  *underrun = 0;
  if (rPtr > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr++;
  }

  if (rPtr > 513) {
    rPtr = 1;
  }

  *c = rPtr + 511;
  if (rPtr + 511 > 513) {
    int y_size_idx_1;
    int yk;
    int b_y_size_idx_1;
    *c = rPtr - 2;
    n = 514 - rPtr;
    y_size_idx_1 = 514 - rPtr;
    y_data[0] = rPtr;
    yk = rPtr;
    for (k = 2; k <= n; k++) {
      yk++;
      y_data[k - 1] = yk;
    }

    b_y_size_idx_1 = rPtr - 2;
    b_y_data[0] = 1;
    yk = 1;
    for (k = 2; k <= *c; k++) {
      yk++;
      b_y_data[k - 1] = yk;
    }

    n = y_size_idx_1 + b_y_size_idx_1;
    if (0 <= y_size_idx_1 - 1) {
      std::memcpy(&readIdx_data[0], &y_data[0], y_size_idx_1 * sizeof(int));
    }

    for (k = 0; k < b_y_size_idx_1; k++) {
      readIdx_data[k + y_size_idx_1] = b_y_data[k];
    }

    if (rPtr <= wPtr) {
      if (wPtr < -2147483134) {
        k = MAX_int32_T;
      } else {
        k = 513 - wPtr;
      }

      if (k > 2147483646) {
        k = MAX_int32_T;
      } else {
        k++;
      }

      yk = rPtr - 2;
      if ((k < 0) && (yk < MIN_int32_T - k)) {
        *underrun = MIN_int32_T;
      } else if ((k > 0) && (yk > MAX_int32_T - k)) {
        *underrun = MAX_int32_T;
      } else {
        *underrun = k + yk;
      }
    } else {
      if (wPtr <= rPtr - 2) {
        yk = rPtr - 2;
        if ((yk >= 0) && (wPtr < yk - MAX_int32_T)) {
          k = MAX_int32_T;
        } else if ((yk < 0) && (wPtr > yk - MIN_int32_T)) {
          k = MIN_int32_T;
        } else {
          k = yk - wPtr;
        }

        if (k > 2147483646) {
          *underrun = MAX_int32_T;
        } else {
          *underrun = k + 1;
        }
      }
    }
  } else {
    int yk;
    if (rPtr + 511 < rPtr) {
      n = 0;
    } else {
      n = 512;
    }

    if (n > 0) {
      y_data[0] = rPtr;
      yk = rPtr;
      for (k = 2; k <= n; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
    }

    if (0 <= n - 1) {
      std::memcpy(&readIdx_data[0], &y_data[0], n * sizeof(int));
    }

    if ((rPtr <= wPtr) && (wPtr <= rPtr + 511)) {
      yk = rPtr + 511;
      if ((yk >= 0) && (wPtr < yk - MAX_int32_T)) {
        k = MAX_int32_T;
      } else if ((yk < 0) && (wPtr > yk - MIN_int32_T)) {
        k = MIN_int32_T;
      } else {
        k = yk - wPtr;
      }

      if (k > 2147483646) {
        *underrun = MAX_int32_T;
      } else {
        *underrun = k + 1;
      }
    }
  }

  out_size[0] = n;
  for (k = 0; k < n; k++) {
    out_data[k] = obj->Cache[readIdx_data[k] - 1];
  }

  if (*underrun != 0) {
    if (*underrun < -2147483135) {
      k = MAX_int32_T;
    } else {
      k = 512 - *underrun;
    }

    if (k > 2147483646) {
      k = MAX_int32_T;
    } else {
      k++;
    }

    if (k > 512) {
      k = 1;
    }

    if (0 <= *underrun - 1) {
      std::memset(&out_data[k + -1], 0, ((*underrun + k) - k) * sizeof(float));
    }
  }
}

//
// Arguments    : void
// Return Type  : int
//
int dsp_private_AsyncBuffercgHelper::get_NumUnreadSamples() const
{
  int unreadSamples;
  int q0;
  int q1;
  q0 = this->WritePointer;
  q1 = this->ReadPointer;
  if ((q0 >= 0) && (q1 < q0 - MAX_int32_T)) {
    q0 = MAX_int32_T;
  } else if ((q0 < 0) && (q1 > q0 - MIN_int32_T)) {
    q0 = MIN_int32_T;
  } else {
    q0 -= q1;
  }

  if (q0 < -2147483647) {
    q0 = MIN_int32_T;
  } else {
    q0--;
  }

  q1 = this->ReadPointer;
  if (q1 < -2147483135) {
    unreadSamples = MAX_int32_T;
  } else {
    unreadSamples = 512 - q1;
  }

  q1 = this->WritePointer;
  if ((unreadSamples < 0) && (q1 < MIN_int32_T - unreadSamples)) {
    unreadSamples = MIN_int32_T;
  } else if ((unreadSamples > 0) && (q1 > MAX_int32_T - unreadSamples)) {
    unreadSamples = MAX_int32_T;
  } else {
    unreadSamples += q1;
  }

  if (this->ReadPointer < this->WritePointer) {
    unreadSamples = q0;
  } else {
    if (this->ReadPointer == this->WritePointer) {
      unreadSamples = 512;
    }
  }

  return unreadSamples;
}

//
// Arguments    : void
// Return Type  : dsp_private_AsyncBuffercgHelper *
//
dsp_private_AsyncBuffercgHelper *dsp_private_AsyncBuffercgHelper::init()
{
  dsp_private_AsyncBuffercgHelper *obj;
  obj = this;
  obj->NumChannels = -1;
  obj->isInitialized = 0;
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : float out_data[]
//                int out_size[1]
//                int *underrun
// Return Type  : void
//
void dsp_private_AsyncBuffercgHelper::read(float out_data[], int out_size[1],
  int *underrun)
{
  int wPtr;
  int c;
  int q0;
  wPtr = this->WritePointer;
  dsp_private_AsyncBuffercgHelper::ReadSamplesFromBuffer((this), (out_data),
    (out_size), (underrun), (&c));
  q0 = this->CumulativeUnderrun;
  if ((q0 < 0) && (*underrun < MIN_int32_T - q0)) {
    q0 = MIN_int32_T;
  } else if ((q0 > 0) && (*underrun > MAX_int32_T - q0)) {
    q0 = MAX_int32_T;
  } else {
    q0 += *underrun;
  }

  this->CumulativeUnderrun = q0;
  if (wPtr < -2147483647) {
    q0 = MIN_int32_T;
  } else {
    q0 = wPtr - 1;
  }

  if (*underrun != 0) {
    this->ReadPointer = q0;
  } else {
    this->ReadPointer = c;
  }
}

//
// Arguments    : const float in[256]
// Return Type  : int
//
int dsp_private_AsyncBuffercgHelper::write(const float in[256])
{
  int overrun;
  int wPtr;
  int rPtr;
  int yk;
  int c;
  int n;
  int y_data[513];
  int bc_data[768];
  int b_y_data[511];
  short tmp_data[768];
  wPtr = this->WritePointer;
  rPtr = this->ReadPointer;
  overrun = 0;
  if (wPtr > 2147483391) {
    yk = MAX_int32_T;
  } else {
    yk = wPtr + 256;
  }

  c = yk - 1;
  if (c > 513) {
    int y_size_idx_1;
    int k;
    c -= 513;
    n = 514 - wPtr;
    y_size_idx_1 = 514 - wPtr;
    y_data[0] = wPtr;
    yk = wPtr;
    for (k = 2; k <= n; k++) {
      yk++;
      y_data[k - 1] = yk;
    }

    b_y_data[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      b_y_data[k - 1] = yk;
    }

    n = y_size_idx_1 + c;
    if (0 <= y_size_idx_1 - 1) {
      std::memcpy(&bc_data[0], &y_data[0], y_size_idx_1 * sizeof(int));
    }

    for (yk = 0; yk < c; yk++) {
      bc_data[yk + y_size_idx_1] = b_y_data[yk];
    }

    if (wPtr <= rPtr) {
      if (rPtr < -2147483134) {
        yk = MAX_int32_T;
      } else {
        yk = 513 - rPtr;
      }

      if (yk > 2147483646) {
        yk = MAX_int32_T;
      } else {
        yk++;
      }

      if ((yk < 0) && (c < MIN_int32_T - yk)) {
        overrun = MIN_int32_T;
      } else if ((yk > 0) && (c > MAX_int32_T - yk)) {
        overrun = MAX_int32_T;
      } else {
        overrun = yk + c;
      }
    } else {
      if (rPtr <= c) {
        if (rPtr < c - MAX_int32_T) {
          yk = MAX_int32_T;
        } else {
          yk = c - rPtr;
        }

        if (yk > 2147483646) {
          overrun = MAX_int32_T;
        } else {
          overrun = yk + 1;
        }
      }
    }
  } else {
    if (c < wPtr) {
      n = 0;
    } else {
      n = (c - wPtr) + 1;
    }

    if (n > 0) {
      y_data[0] = wPtr;
      yk = wPtr;
      for (int k = 2; k <= n; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
    }

    if (0 <= n - 1) {
      std::memcpy(&bc_data[0], &y_data[0], n * sizeof(int));
    }

    if ((wPtr <= rPtr) && (rPtr <= c)) {
      if ((c >= 0) && (rPtr < c - MAX_int32_T)) {
        yk = MAX_int32_T;
      } else if ((c < 0) && (rPtr > c - MIN_int32_T)) {
        yk = MIN_int32_T;
      } else {
        yk = c - rPtr;
      }

      if (yk > 2147483646) {
        overrun = MAX_int32_T;
      } else {
        overrun = yk + 1;
      }
    }
  }

  for (yk = 0; yk < n; yk++) {
    tmp_data[yk] = static_cast<short>(static_cast<short>(bc_data[yk]) - 1);
  }

  for (yk = 0; yk < n; yk++) {
    this->Cache[tmp_data[yk]] = in[yk];
  }

  if (c + 1 > 513) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }

  if (overrun != 0) {
    rPtr = wPtr;
  }

  yk = this->CumulativeOverrun;
  if ((yk < 0) && (overrun < MIN_int32_T - yk)) {
    yk = MIN_int32_T;
  } else if ((yk > 0) && (overrun > MAX_int32_T - yk)) {
    yk = MAX_int32_T;
  } else {
    yk += overrun;
  }

  this->CumulativeOverrun = yk;
  this->WritePointer = wPtr;
  this->ReadPointer = rPtr;
  return overrun;
}

//
// File trailer for AsyncBuffercgHelper.cpp
//
// [EOF]
//
