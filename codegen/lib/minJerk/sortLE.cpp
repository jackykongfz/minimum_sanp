//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sortLE.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 10-Oct-2020 11:13:02
//

// Include Files
#include "rt_nonfinite.h"
#include "minJerk.h"
#include "sortLE.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *v
//                int idx1
//                int idx2
// Return Type  : boolean_T
//
boolean_T sortLE(const emxArray_real_T *v, int idx1, int idx2)
{
  boolean_T p;
  double v1;
  double v2;
  p = true;
  v1 = v->data[idx1 - 1];
  v2 = v->data[idx2 - 1];
  if ((v1 == v2) || (rtIsNaN(v1) && rtIsNaN(v2)) || (v1 <= v2) || rtIsNaN(v2)) {
  } else {
    p = false;
  }

  return p;
}

//
// File trailer for sortLE.cpp
//
// [EOF]
//
