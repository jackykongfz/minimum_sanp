//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: eye.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 11-Feb-2020 14:34:08
//

// Include Files
#include <string.h>
#include "rt_nonfinite.h"
#include "minSnap.h"
#include "eye.h"
#include "minSnap_emxutil.h"

// Function Definitions

//
// Arguments    : double varargin_1
//                emxArray_real_T *b_I
// Return Type  : void
//
void b_eye(double varargin_1, emxArray_real_T *b_I)
{
  int m_tmp;
  int k;
  int loop_ub;
  m_tmp = (int)varargin_1;
  k = b_I->size[0] * b_I->size[1];
  b_I->size[0] = m_tmp;
  b_I->size[1] = m_tmp;
  emxEnsureCapacity_real_T(b_I, k);
  loop_ub = m_tmp * m_tmp;
  for (k = 0; k < loop_ub; k++) {
    b_I->data[k] = 0.0;
  }

  for (k = 0; k < m_tmp; k++) {
    b_I->data[k + b_I->size[0] * k] = 1.0;
  }
}

//
// Arguments    : double b_I[16]
// Return Type  : void
//
void eye(double b_I[16])
{
  memset(&b_I[0], 0, sizeof(double) << 4);
  b_I[0] = 1.0;
  b_I[5] = 1.0;
  b_I[10] = 1.0;
  b_I[15] = 1.0;
}

//
// File trailer for eye.cpp
//
// [EOF]
//
