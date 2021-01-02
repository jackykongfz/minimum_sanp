//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeQ.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 10-Oct-2020 11:13:02
//

// Include Files
#include <math.h>
#include "rt_nonfinite.h"
#include "minJerk.h"
#include "computeQ.h"
#include "minJerk_emxutil.h"
#include "prod.h"
#include "polys_vals.h"
#include "minJerk_rtwutil.h"

// Function Definitions

//
// Arguments    : double n
//                double r
//                double t1
//                double t2
//                emxArray_real_T *Q
// Return Type  : void
//
void computeQ(double n, double r, double t1, double t2, emxArray_real_T *Q)
{
  emxArray_real_T *T;
  int i8;
  int nm1d2;
  int i;
  int i9;
  emxArray_real_T *y;
  emxArray_real_T *b_y;
  double b_i;
  int j;
  double b_j;
  double k1;
  double k2;
  double k;
  double b;
  int b_k;
  double ndbl;
  double apnd;
  double cdiff;
  int b_n;
  emxInit_real_T(&T, 1);

  //  n:polynormial order
  //  r:derivertive order, 1:minimum vel 2:minimum acc 3:minimum jerk 4:minimum snap 
  //  t1:start timestamp for polynormial
  //  t2:end timestap for polynormial
  i8 = T->size[0];
  nm1d2 = (int)((n - r) * 2.0 + 1.0);
  T->size[0] = nm1d2;
  emxEnsureCapacity_real_T(T, i8);
  for (i8 = 0; i8 < nm1d2; i8++) {
    T->data[i8] = 0.0;
  }

  for (i = 0; i < nm1d2; i++) {
    T->data[i] = rt_powd_snf(t2, 1.0 + (double)i) - rt_powd_snf(t1, 1.0 +
      (double)i);
  }

  i8 = Q->size[0] * Q->size[1];
  i9 = (int)(n + 1.0);
  Q->size[0] = i9;
  Q->size[1] = i9;
  emxEnsureCapacity_real_T(Q, i8);
  nm1d2 = i9 * i9;
  for (i8 = 0; i8 < nm1d2; i8++) {
    Q->data[i8] = 0.0;
  }

  i8 = (int)((n + 1.0) + (1.0 - (r + 1.0)));
  emxInit_real_T(&y, 2);
  emxInit_real_T(&b_y, 2);
  for (i = 0; i < i8; i++) {
    b_i = (r + 1.0) + (double)i;
    i9 = (int)((n + 1.0) + (1.0 - b_i));
    for (j = 0; j < i9; j++) {
      b_j = b_i + (double)j;
      k1 = (b_i - r) - 1.0;
      k2 = (b_j - r) - 1.0;
      k = (k1 + k2) + 1.0;
      b = k1 + r;
      if (rtIsNaN(k1 + 1.0) || rtIsNaN(b)) {
        b_k = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, b_k);
        y->data[0] = rtNaN;
      } else if (b < k1 + 1.0) {
        y->size[0] = 1;
        y->size[1] = 0;
      } else if ((rtIsInf(k1 + 1.0) || rtIsInf(b)) && (k1 + 1.0 == b)) {
        b_k = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, b_k);
        y->data[0] = rtNaN;
      } else if (floor(k1 + 1.0) == k1 + 1.0) {
        b_k = y->size[0] * y->size[1];
        y->size[0] = 1;
        nm1d2 = (int)floor(b - (k1 + 1.0));
        y->size[1] = nm1d2 + 1;
        emxEnsureCapacity_real_T(y, b_k);
        for (b_k = 0; b_k <= nm1d2; b_k++) {
          y->data[b_k] = (k1 + 1.0) + (double)b_k;
        }
      } else {
        ndbl = floor((b - (k1 + 1.0)) + 0.5);
        apnd = (k1 + 1.0) + ndbl;
        cdiff = apnd - b;
        if (fabs(cdiff) < 4.4408920985006262E-16 * fmax(fabs(k1 + 1.0), fabs(b)))
        {
          ndbl++;
          apnd = b;
        } else if (cdiff > 0.0) {
          apnd = (k1 + 1.0) + (ndbl - 1.0);
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          b_n = (int)ndbl;
        } else {
          b_n = 0;
        }

        b_k = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = b_n;
        emxEnsureCapacity_real_T(y, b_k);
        if (b_n > 0) {
          y->data[0] = k1 + 1.0;
          if (b_n > 1) {
            y->data[b_n - 1] = apnd;
            nm1d2 = (b_n - 1) / 2;
            for (b_k = 0; b_k <= nm1d2 - 2; b_k++) {
              y->data[1 + b_k] = (k1 + 1.0) + (1.0 + (double)b_k);
              y->data[(b_n - b_k) - 2] = apnd - (1.0 + (double)b_k);
            }

            if (nm1d2 << 1 == b_n - 1) {
              y->data[nm1d2] = ((k1 + 1.0) + apnd) / 2.0;
            } else {
              y->data[nm1d2] = (k1 + 1.0) + (double)nm1d2;
              y->data[nm1d2 + 1] = apnd - (double)nm1d2;
            }
          }
        }
      }

      b = k2 + r;
      if (rtIsNaN(k2 + 1.0) || rtIsNaN(b)) {
        b_k = b_y->size[0] * b_y->size[1];
        b_y->size[0] = 1;
        b_y->size[1] = 1;
        emxEnsureCapacity_real_T(b_y, b_k);
        b_y->data[0] = rtNaN;
      } else if (b < k2 + 1.0) {
        b_y->size[0] = 1;
        b_y->size[1] = 0;
      } else if ((rtIsInf(k2 + 1.0) || rtIsInf(b)) && (k2 + 1.0 == b)) {
        b_k = b_y->size[0] * b_y->size[1];
        b_y->size[0] = 1;
        b_y->size[1] = 1;
        emxEnsureCapacity_real_T(b_y, b_k);
        b_y->data[0] = rtNaN;
      } else if (floor(k2 + 1.0) == k2 + 1.0) {
        b_k = b_y->size[0] * b_y->size[1];
        b_y->size[0] = 1;
        nm1d2 = (int)floor(b - (k2 + 1.0));
        b_y->size[1] = nm1d2 + 1;
        emxEnsureCapacity_real_T(b_y, b_k);
        for (b_k = 0; b_k <= nm1d2; b_k++) {
          b_y->data[b_k] = (k2 + 1.0) + (double)b_k;
        }
      } else {
        ndbl = floor((b - (k2 + 1.0)) + 0.5);
        apnd = (k2 + 1.0) + ndbl;
        cdiff = apnd - b;
        if (fabs(cdiff) < 4.4408920985006262E-16 * fmax(fabs(k2 + 1.0), fabs(b)))
        {
          ndbl++;
          apnd = b;
        } else if (cdiff > 0.0) {
          apnd = (k2 + 1.0) + (ndbl - 1.0);
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          b_n = (int)ndbl;
        } else {
          b_n = 0;
        }

        b_k = b_y->size[0] * b_y->size[1];
        b_y->size[0] = 1;
        b_y->size[1] = b_n;
        emxEnsureCapacity_real_T(b_y, b_k);
        if (b_n > 0) {
          b_y->data[0] = k2 + 1.0;
          if (b_n > 1) {
            b_y->data[b_n - 1] = apnd;
            nm1d2 = (b_n - 1) / 2;
            for (b_k = 0; b_k <= nm1d2 - 2; b_k++) {
              b_y->data[1 + b_k] = (k2 + 1.0) + (1.0 + (double)b_k);
              b_y->data[(b_n - b_k) - 2] = apnd - (1.0 + (double)b_k);
            }

            if (nm1d2 << 1 == b_n - 1) {
              b_y->data[nm1d2] = ((k2 + 1.0) + apnd) / 2.0;
            } else {
              b_y->data[nm1d2] = (k2 + 1.0) + (double)nm1d2;
              b_y->data[nm1d2 + 1] = apnd - (double)nm1d2;
            }
          }
        }
      }

      b_k = (int)b_i;
      nm1d2 = (int)b_j;
      Q->data[(b_k + Q->size[0] * (nm1d2 - 1)) - 1] = prod(y) * prod(b_y) / k *
        T->data[(int)k - 1];
      Q->data[(nm1d2 + Q->size[0] * (b_k - 1)) - 1] = Q->data[((int)b_i +
        Q->size[0] * ((int)b_j - 1)) - 1];
    }
  }

  emxFree_real_T(&b_y);
  emxFree_real_T(&y);
  emxFree_real_T(&T);
}

//
// File trailer for computeQ.cpp
//
// [EOF]
//
