//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: polys_vals.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 11-Feb-2020 14:34:08
//

// Include Files
#include "rt_nonfinite.h"
#include "minSnap.h"
#include "polys_vals.h"
#include "prod.h"
#include "minSnap_emxutil.h"
#include "minSnap_rtwutil.h"

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
  int i9;
  int i10;
  int i;
  double t;
  double val;
  int b_i;
  int y_size[2];
  double y_data[13];
  idx = 1;
  i9 = tt->size[1];
  i10 = vals->size[0] * vals->size[1];
  vals->size[0] = 1;
  vals->size[1] = tt->size[1];
  emxEnsureCapacity_real_T(vals, i10);
  for (i = 0; i < i9; i++) {
    t = tt->data[i];
    if (tt->data[i] < ts->data[idx - 1]) {
      vals->data[i] = 0.0;
    } else {
      while ((idx < ts->size[1]) && (t > ts->data[idx] + 0.0001)) {
        idx++;
      }

      val = 0.0;
      for (b_i = 0; b_i < 7; b_i++) {
        y_size[0] = 1;
        y_size[1] = 1;
        for (i10 = 0; i10 < 1; i10++) {
          y_data[i10] = (b_i + i10) + 1;
        }

        val += polys->data[(b_i + ((idx - 1) << 3)) + 1] * prod(y_data, y_size) *
          rt_powd_snf(t, (1.0 + (double)b_i) - 1.0);
      }

      vals->data[i] = val;
    }
  }
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
  int i11;
  int y_size_tmp;
  int i;
  double t;
  double val;
  int b_i;
  int y_size[2];
  double y_data[13];
  idx = 1;
  i11 = tt->size[1];
  y_size_tmp = vals->size[0] * vals->size[1];
  vals->size[0] = 1;
  vals->size[1] = tt->size[1];
  emxEnsureCapacity_real_T(vals, y_size_tmp);
  for (i = 0; i < i11; i++) {
    t = tt->data[i];
    if (tt->data[i] < ts->data[idx - 1]) {
      vals->data[i] = 0.0;
    } else {
      while ((idx < ts->size[1]) && (t > ts->data[idx] + 0.0001)) {
        idx++;
      }

      val = 0.0;
      for (b_i = 0; b_i < 6; b_i++) {
        y_size[0] = 1;
        y_size[1] = 2;
        for (y_size_tmp = 0; y_size_tmp < 2; y_size_tmp++) {
          y_data[y_size_tmp] = (b_i + y_size_tmp) + 1;
        }

        val += polys->data[(b_i + ((idx - 1) << 3)) + 2] * prod(y_data, y_size) *
          rt_powd_snf(t, (2.0 + (double)b_i) - 2.0);
      }

      vals->data[i] = val;
    }
  }
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
  int i8;
  int i;
  double t;
  double val;
  int b_i;
  idx = 1;
  i8 = tt->size[1];
  i = vals->size[0] * vals->size[1];
  vals->size[0] = 1;
  vals->size[1] = tt->size[1];
  emxEnsureCapacity_real_T(vals, i);
  for (i = 0; i < i8; i++) {
    t = tt->data[i];
    if (tt->data[i] < ts->data[idx - 1]) {
      vals->data[i] = 0.0;
    } else {
      while ((idx < ts->size[1]) && (t > ts->data[idx] + 0.0001)) {
        idx++;
      }

      val = 0.0;
      for (b_i = 0; b_i < 8; b_i++) {
        val += polys->data[b_i + ((idx - 1) << 3)] * rt_powd_snf(t, (double)b_i);
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
