//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: polys_vals.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 10-Oct-2020 11:13:02
//

// Include Files
#include "rt_nonfinite.h"
#include "minJerk.h"
#include "polys_vals.h"
#include "minJerk_emxutil.h"
#include "prod.h"
#include "minJerk_rtwutil.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *polys
//                const emxArray_real_T *ts
//                const emxArray_real_T *tt
//                emxArray_real_T *vals
// Return Type  : void
//
void b_polys_vals(const emxArray_real_T *polys, const emxArray_real_T *ts, const
                  emxArray_real_T *tt, emxArray_real_T *vals)
{
  int idx;
  int i15;
  int i16;
  emxArray_real_T *y;
  int i;
  double t;
  double val;
  int b_i;
  int i17;
  idx = 1;
  i15 = tt->size[1];
  i16 = vals->size[0] * vals->size[1];
  vals->size[0] = 1;
  vals->size[1] = tt->size[1];
  emxEnsureCapacity_real_T(vals, i16);
  emxInit_real_T(&y, 2);
  for (i = 0; i < i15; i++) {
    t = tt->data[i];
    if (tt->data[i] < ts->data[idx - 1]) {
      vals->data[i] = 0.0;
    } else {
      while ((idx < ts->size[1]) && (t > ts->data[idx] + 0.0001)) {
        idx++;
      }

      val = 0.0;
      i16 = polys->size[0];
      for (b_i = 0; b_i <= i16 - 2; b_i++) {
        i17 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i17);
        for (i17 = 0; i17 < 1; i17++) {
          y->data[i17] = (b_i + i17) + 1;
        }

        val += polys->data[(b_i + polys->size[0] * (idx - 1)) + 1] * prod(y) *
          rt_powd_snf(t, (1.0 + (double)b_i) - 1.0);
      }

      vals->data[i] = val;
    }
  }

  emxFree_real_T(&y);
}

//
// Arguments    : const emxArray_real_T *polys
//                const emxArray_real_T *ts
//                const emxArray_real_T *tt
//                emxArray_real_T *vals
// Return Type  : void
//
void c_polys_vals(const emxArray_real_T *polys, const emxArray_real_T *ts, const
                  emxArray_real_T *tt, emxArray_real_T *vals)
{
  int idx;
  int i18;
  int i19;
  emxArray_real_T *y;
  int i;
  double t;
  double val;
  int b_i;
  int i20;
  idx = 1;
  i18 = tt->size[1];
  i19 = vals->size[0] * vals->size[1];
  vals->size[0] = 1;
  vals->size[1] = tt->size[1];
  emxEnsureCapacity_real_T(vals, i19);
  emxInit_real_T(&y, 2);
  for (i = 0; i < i18; i++) {
    t = tt->data[i];
    if (tt->data[i] < ts->data[idx - 1]) {
      vals->data[i] = 0.0;
    } else {
      while ((idx < ts->size[1]) && (t > ts->data[idx] + 0.0001)) {
        idx++;
      }

      val = 0.0;
      i19 = polys->size[0];
      for (b_i = 0; b_i <= i19 - 3; b_i++) {
        if (2 + b_i < b_i + 1) {
          y->size[0] = 1;
          y->size[1] = 0;
        } else {
          i20 = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = 2;
          emxEnsureCapacity_real_T(y, i20);
          for (i20 = 0; i20 < 2; i20++) {
            y->data[i20] = (b_i + i20) + 1;
          }
        }

        val += polys->data[(b_i + polys->size[0] * (idx - 1)) + 2] * prod(y) *
          rt_powd_snf(t, (2.0 + (double)b_i) - 2.0);
      }

      vals->data[i] = val;
    }
  }

  emxFree_real_T(&y);
}

//
// Arguments    : const emxArray_real_T *polys
//                const emxArray_real_T *ts
//                const emxArray_real_T *tt
//                emxArray_real_T *vals
// Return Type  : void
//
void polys_vals(const emxArray_real_T *polys, const emxArray_real_T *ts, const
                emxArray_real_T *tt, emxArray_real_T *vals)
{
  int idx;
  int i13;
  int i14;
  int i;
  double t;
  double val;
  int b_i;
  idx = 1;
  i13 = tt->size[1];
  i14 = vals->size[0] * vals->size[1];
  vals->size[0] = 1;
  vals->size[1] = tt->size[1];
  emxEnsureCapacity_real_T(vals, i14);
  for (i = 0; i < i13; i++) {
    t = tt->data[i];
    if (tt->data[i] < ts->data[idx - 1]) {
      vals->data[i] = 0.0;
    } else {
      while ((idx < ts->size[1]) && (t > ts->data[idx] + 0.0001)) {
        idx++;
      }

      val = 0.0;
      i14 = polys->size[0];
      for (b_i = 0; b_i < i14; b_i++) {
        val += polys->data[b_i + polys->size[0] * (idx - 1)] * rt_powd_snf(t,
          (double)b_i);
      }

      vals->data[i] = val;
    }
  }
}

//
// File trailer for polys_vals.cpp
//
// [EOF]
//
