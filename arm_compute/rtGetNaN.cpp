//
//  File: rtGetNaN.cpp
//
//  MATLAB Coder version            : 5.0
//  C/C++ source code generated on  : 08-May-2020 10:27:24


//
//  Abstract:
//        MATLAB for code generation function to initialize non-finite, NaN

#include "rtGetNaN.h"

// Function: rtGetNaN ======================================================================
//  Abstract:
//  Initialize rtNaN needed by the generated code.
//  NaN is initialized as non-signaling. Assumes IEEE.

real_T rtGetNaN(void)
{
  return rtNaN;
}

// Function: rtGetNaNF =====================================================================
//  Abstract:
//  Initialize rtNaNF needed by the generated code.
//  NaN is initialized as non-signaling. Assumes IEEE.

real32_T rtGetNaNF(void)
{
  return rtNaNF;
}

//
//  File trailer for rtGetNaN.cpp
//
//  [EOF]

