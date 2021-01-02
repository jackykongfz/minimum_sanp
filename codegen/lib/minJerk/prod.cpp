//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: prod.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 10-Oct-2020 11:13:02
//

// Include Files
#include "rt_nonfinite.h"
#include "minJerk.h"
#include "prod.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *x
// Return Type  : double
//
double prod(const emxArray_real_T *x)
{
  double y;
  int vlen;
  int k;
  vlen = x->size[1];
  if (x->size[1] == 0) {
    y = 1.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= vlen; k++) {
      y *= x->data[k - 1];
    }
  }

  return y;
}

//
// File trailer for prod.cpp
//
// [EOF]
//
