//
// File: main.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 19-Mar-2021 15:00:36
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include Files
#include "main.h"
#include "rt_nonfinite.h"
#include "streamingClassifier.h"
#include "streamingClassifier_terminate.h"

// Function Declarations
static void argInit_1x10_real32_T(float result[10]);

static void argInit_512x1_real32_T(float result[512]);

static float argInit_real32_T();

static void main_streamingClassifier();

// Function Definitions
//
// Arguments    : float result[10]
// Return Type  : void
//
static void argInit_1x10_real32_T(float result[10])
{
  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < 10; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = argInit_real32_T();
  }
}

//
// Arguments    : float result[512]
// Return Type  : void
//
static void argInit_512x1_real32_T(float result[512])
{
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < 512; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real32_T();
  }
}

//
// Arguments    : void
// Return Type  : float
//
static float argInit_real32_T()
{
  return 0.0F;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_streamingClassifier()
{
  float fv[512];
  float M_tmp[10];
  float features[10];
  float scores[8];
  // Initialize function 'streamingClassifier' input arguments.
  // Initialize function input argument 'audioIn'.
  // Initialize function input argument 'M'.
  argInit_1x10_real32_T(M_tmp);
  // Initialize function input argument 'S'.
  // Call the entry-point 'streamingClassifier'.
  argInit_512x1_real32_T(fv);
  streamingClassifier(fv, M_tmp, M_tmp, scores, features);
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int, char **)
{
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  main_streamingClassifier();
  // Terminate the application.
  // You do not need to do this more than one time.
  streamingClassifier_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
