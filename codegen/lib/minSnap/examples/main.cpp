//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 11-Feb-2020 14:34:08
//

//***********************************************************************
// This automatically generated example C main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************
// Include Files
#include "rt_nonfinite.h"
#include "minSnap.h"
#include "main.h"
#include "minSnap_terminate.h"
#include "minSnap_emxAPI.h"
#include "minSnap_initialize.h"

// Function Declarations
static emxArray_real_T *argInit_4xUnbounded_real_T();
static emxArray_real_T *argInit_8xUnbounded_real_T();
static double argInit_real_T();
static void main_minSnap();

// Function Definitions

//
// Arguments    : void
// Return Type  : emxArray_real_T *
//
static emxArray_real_T *argInit_4xUnbounded_real_T()
{
  emxArray_real_T *result;
  int idx1;

  // Set the size of the array.
  // Change this size to the value that the application requires.
  result = emxCreate_real_T(4, 2);

  // Loop over the array to initialize each element.
  for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result->data[idx1 << 2] = argInit_real_T();
  }

  for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result->data[1 + (idx1 << 2)] = argInit_real_T();
  }

  for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result->data[2 + (idx1 << 2)] = argInit_real_T();
  }

  for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result->data[3 + (idx1 << 2)] = argInit_real_T();
  }

  return result;
}

//
// Arguments    : void
// Return Type  : emxArray_real_T *
//
static emxArray_real_T *argInit_8xUnbounded_real_T()
{
  emxArray_real_T *result;
  int idx0;
  int idx1;

  // Set the size of the array.
  // Change this size to the value that the application requires.
  result = emxCreate_real_T(8, 2);

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 8; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result->data[idx0 + (idx1 << 3)] = argInit_real_T();
    }
  }

  return result;
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_minSnap()
{
  emxArray_real_T *tt;
  emxArray_real_T *xx;
  emxArray_real_T *yy;
  emxArray_real_T *zz;
  emxArray_real_T *vx;
  emxArray_real_T *vy;
  emxArray_real_T *vz;
  emxArray_real_T *ax;
  emxArray_real_T *ay;
  emxArray_real_T *az;
  emxArray_real_T *waypts_noatti;
  emxArray_real_T *waypts_atti;
  emxInitArray_real_T(&tt, 2);
  emxInitArray_real_T(&xx, 2);
  emxInitArray_real_T(&yy, 2);
  emxInitArray_real_T(&zz, 2);
  emxInitArray_real_T(&vx, 2);
  emxInitArray_real_T(&vy, 2);
  emxInitArray_real_T(&vz, 2);
  emxInitArray_real_T(&ax, 2);
  emxInitArray_real_T(&ay, 2);
  emxInitArray_real_T(&az, 2);

  // Initialize function 'minSnap' input arguments.
  // Initialize function input argument 'waypts_noatti'.
  waypts_noatti = argInit_4xUnbounded_real_T();

  // Initialize function input argument 'waypts_atti'.
  waypts_atti = argInit_8xUnbounded_real_T();

  // Call the entry-point 'minSnap'.
  minSnap(waypts_noatti, waypts_atti, tt, xx, yy, zz, vx, vy, vz, ax, ay, az);
  emxDestroyArray_real_T(az);
  emxDestroyArray_real_T(ay);
  emxDestroyArray_real_T(ax);
  emxDestroyArray_real_T(vz);
  emxDestroyArray_real_T(vy);
  emxDestroyArray_real_T(vx);
  emxDestroyArray_real_T(zz);
  emxDestroyArray_real_T(yy);
  emxDestroyArray_real_T(xx);
  emxDestroyArray_real_T(tt);
  emxDestroyArray_real_T(waypts_atti);
  emxDestroyArray_real_T(waypts_noatti);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const [])
{
  // Initialize the application.
  // You do not need to do this more than one time.
  minSnap_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_minSnap();

  // Terminate the application.
  // You do not need to do this more than one time.
  minSnap_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
