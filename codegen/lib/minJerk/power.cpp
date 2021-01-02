//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: power.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 10-Oct-2020 11:13:02
//

// Include Files
#include "rt_nonfinite.h"
#include "minJerk.h"
#include "power.h"
#include "polys_vals.h"
#include "minJerk_emxutil.h"
#include "minJerk_rtwutil.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *a
//                double b
//                emxArray_real_T *y
// Return Type  : void
//
void power(const emxArray_real_T *a, double b, emxArray_real_T *y)
{
  unsigned int a_idx_0;
  int nx;
  int k;
  a_idx_0 = (unsigned int)a->size[0];
  nx = y->size[0];
  y->size[0] = (int)a_idx_0;
  emxEnsureCapacity_real_T(y, nx);
  a_idx_0 = (unsigned int)a->size[0];
  nx = (int)a_idx_0;
  for (k = 0; k < nx; k++) {
    y->data[k] = rt_powd_snf(a->data[k], b);
  }
}

//
// File trailer for power.cpp
//
// [EOF]
//
