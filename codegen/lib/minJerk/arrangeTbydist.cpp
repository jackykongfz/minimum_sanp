//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: arrangeTbydist.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 10-Oct-2020 11:13:02
//

// Include Files
#include <math.h>
#include "rt_nonfinite.h"
#include "minJerk.h"
#include "arrangeTbydist.h"
#include "minJerk_emxutil.h"
#include "sum.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *waypts
//                emxArray_real_T *ts
// Return Type  : void
//
void arrangeTbydist(const emxArray_real_T *waypts, emxArray_real_T *ts)
{
  int i1;
  int nx;
  emxArray_real_T *x;
  int xpageoffset;
  int npages;
  emxArray_real_T *y;
  int i2;
  emxArray_real_T *b_y;
  emxArray_real_T *dist;
  double b;
  if (2 > waypts->size[1]) {
    i1 = 0;
    nx = 0;
  } else {
    i1 = 1;
    nx = waypts->size[1];
  }

  emxInit_real_T(&x, 2);
  xpageoffset = x->size[0] * x->size[1];
  x->size[0] = 3;
  npages = nx - i1;
  x->size[1] = npages;
  emxEnsureCapacity_real_T(x, xpageoffset);
  for (nx = 0; nx < npages; nx++) {
    xpageoffset = 3 * (i1 + nx);
    x->data[3 * nx] = waypts->data[xpageoffset] - waypts->data[3 * nx];
    i2 = 1 + 3 * nx;
    x->data[i2] = waypts->data[1 + xpageoffset] - waypts->data[i2];
    i2 = 2 + 3 * nx;
    x->data[i2] = waypts->data[2 + xpageoffset] - waypts->data[i2];
  }

  emxInit_real_T(&y, 2);
  i1 = y->size[0] * y->size[1];
  y->size[0] = 3;
  y->size[1] = x->size[1];
  emxEnsureCapacity_real_T(y, i1);
  nx = 3 * x->size[1];
  for (xpageoffset = 0; xpageoffset < nx; xpageoffset++) {
    y->data[xpageoffset] = x->data[xpageoffset] * x->data[xpageoffset];
  }

  emxFree_real_T(&x);
  emxInit_real_T(&b_y, 2);
  if (y->size[1] == 0) {
    b_y->size[0] = 1;
    b_y->size[1] = 0;
  } else {
    npages = y->size[1];
    i1 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    b_y->size[1] = y->size[1];
    emxEnsureCapacity_real_T(b_y, i1);
    for (nx = 0; nx < npages; nx++) {
      xpageoffset = nx * 3;
      b_y->data[nx] = y->data[xpageoffset];
      b_y->data[nx] += y->data[xpageoffset + 1];
      b_y->data[nx] += y->data[xpageoffset + 2];
    }
  }

  emxFree_real_T(&y);
  emxInit_real_T(&dist, 2);
  i1 = dist->size[0] * dist->size[1];
  dist->size[0] = 1;
  dist->size[1] = b_y->size[1];
  emxEnsureCapacity_real_T(dist, i1);
  nx = b_y->size[1];
  for (xpageoffset = 0; xpageoffset < nx; xpageoffset++) {
    dist->data[xpageoffset] = sqrt(b_y->data[xpageoffset]);
  }

  emxFree_real_T(&b_y);
  b = sum(dist) / 0.8 / sum(dist);
  i1 = dist->size[0] * dist->size[1];
  nx = dist->size[0] * dist->size[1];
  dist->size[0] = 1;
  emxEnsureCapacity_real_T(dist, nx);
  npages = i1 - 1;
  for (i1 = 0; i1 <= npages; i1++) {
    dist->data[i1] *= b;
  }

  if ((dist->size[1] != 0) && (dist->size[1] != 1)) {
    i1 = dist->size[1];
    for (xpageoffset = 0; xpageoffset <= i1 - 2; xpageoffset++) {
      dist->data[xpageoffset + 1] += dist->data[xpageoffset];
    }
  }

  i1 = ts->size[0] * ts->size[1];
  ts->size[0] = 1;
  ts->size[1] = 1 + dist->size[1];
  emxEnsureCapacity_real_T(ts, i1);
  ts->data[0] = 0.0;
  npages = dist->size[1];
  for (i1 = 0; i1 < npages; i1++) {
    ts->data[i1 + 1] = dist->data[i1];
  }

  emxFree_real_T(&dist);
}

//
// File trailer for arrangeTbydist.cpp
//
// [EOF]
//
