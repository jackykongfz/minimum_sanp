//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: inv.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 10-Oct-2020 11:13:02
//

// Include Files
#include <math.h>
#include "rt_nonfinite.h"
#include "minJerk.h"
#include "inv.h"
#include "minJerk_emxutil.h"

// Function Declarations
static void invNxN(const emxArray_real_T *x, emxArray_real_T *y);

// Function Definitions

//
// Arguments    : const emxArray_real_T *x
//                emxArray_real_T *y
// Return Type  : void
//
static void invNxN(const emxArray_real_T *x, emxArray_real_T *y)
{
  int n;
  int i11;
  int yk;
  emxArray_real_T *b_x;
  int b_n;
  emxArray_int32_T *ipiv;
  int ldap1;
  int k;
  int u1;
  emxArray_int32_T *p;
  int j;
  int mmj_tmp;
  int jj;
  int jp1j;
  int ix;
  double smax;
  int i;
  double s;
  int i12;
  n = x->size[0];
  i11 = y->size[0] * y->size[1];
  y->size[0] = x->size[0];
  y->size[1] = x->size[1];
  emxEnsureCapacity_real_T(y, i11);
  yk = x->size[0] * x->size[1];
  for (i11 = 0; i11 < yk; i11++) {
    y->data[i11] = 0.0;
  }

  emxInit_real_T(&b_x, 2);
  i11 = b_x->size[0] * b_x->size[1];
  b_x->size[0] = x->size[0];
  b_x->size[1] = x->size[1];
  emxEnsureCapacity_real_T(b_x, i11);
  yk = x->size[0] * x->size[1];
  for (i11 = 0; i11 < yk; i11++) {
    b_x->data[i11] = x->data[i11];
  }

  b_n = x->size[0];
  if (b_n < 1) {
    b_n = 0;
  }

  emxInit_int32_T(&ipiv, 2);
  i11 = ipiv->size[0] * ipiv->size[1];
  ipiv->size[0] = 1;
  ipiv->size[1] = b_n;
  emxEnsureCapacity_int32_T(ipiv, i11);
  if (b_n > 0) {
    ipiv->data[0] = 1;
    yk = 1;
    for (k = 2; k <= b_n; k++) {
      yk++;
      ipiv->data[k - 1] = yk;
    }
  }

  if (x->size[0] < 1) {
    b_n = 0;
  } else {
    ldap1 = x->size[0];
    yk = x->size[0] - 1;
    u1 = x->size[0];
    if (yk < u1) {
      u1 = yk;
    }

    for (j = 0; j < u1; j++) {
      mmj_tmp = n - j;
      b_n = j * (n + 1);
      jj = j * (ldap1 + 1);
      jp1j = b_n + 2;
      if (mmj_tmp < 1) {
        yk = -1;
      } else {
        yk = 0;
        if (mmj_tmp > 1) {
          ix = b_n;
          smax = fabs(b_x->data[b_n]);
          for (k = 2; k <= mmj_tmp; k++) {
            ix++;
            s = fabs(b_x->data[ix]);
            if (s > smax) {
              yk = k - 1;
              smax = s;
            }
          }
        }
      }

      if (b_x->data[jj + yk] != 0.0) {
        if (yk != 0) {
          yk += j;
          ipiv->data[j] = yk + 1;
          ix = j;
          for (k = 0; k < n; k++) {
            smax = b_x->data[ix];
            b_x->data[ix] = b_x->data[yk];
            b_x->data[yk] = smax;
            ix += n;
            yk += n;
          }
        }

        i11 = (jj + mmj_tmp) - 1;
        for (i = jp1j; i <= i11 + 1; i++) {
          b_x->data[i - 1] /= b_x->data[jj];
        }
      }

      yk = b_n + n;
      b_n = jj + ldap1;
      for (jp1j = 0; jp1j <= mmj_tmp - 2; jp1j++) {
        smax = b_x->data[yk];
        if (b_x->data[yk] != 0.0) {
          ix = jj;
          i11 = b_n + 2;
          i12 = (mmj_tmp + b_n) - 1;
          for (i = i11; i <= i12 + 1; i++) {
            b_x->data[i - 1] += b_x->data[ix + 1] * -smax;
            ix++;
          }
        }

        yk += n;
        b_n += n;
      }
    }

    b_n = x->size[0];
  }

  emxInit_int32_T(&p, 2);
  i11 = p->size[0] * p->size[1];
  p->size[0] = 1;
  p->size[1] = b_n;
  emxEnsureCapacity_int32_T(p, i11);
  if (b_n > 0) {
    p->data[0] = 1;
    yk = 1;
    for (k = 2; k <= b_n; k++) {
      yk++;
      p->data[k - 1] = yk;
    }
  }

  i11 = ipiv->size[1];
  for (k = 0; k < i11; k++) {
    if (ipiv->data[k] > 1 + k) {
      yk = p->data[ipiv->data[k] - 1];
      p->data[ipiv->data[k] - 1] = p->data[k];
      p->data[k] = yk;
    }
  }

  emxFree_int32_T(&ipiv);
  for (k = 0; k < n; k++) {
    yk = p->data[k] - 1;
    y->data[k + y->size[0] * (p->data[k] - 1)] = 1.0;
    for (j = k + 1; j <= n; j++) {
      if (y->data[(j + y->size[0] * yk) - 1] != 0.0) {
        i11 = j + 1;
        for (i = i11; i <= n; i++) {
          y->data[(i + y->size[0] * yk) - 1] -= y->data[(j + y->size[0] * yk) -
            1] * b_x->data[(i + b_x->size[0] * (j - 1)) - 1];
        }
      }
    }
  }

  emxFree_int32_T(&p);
  if ((x->size[0] == 0) || ((y->size[0] == 0) || (y->size[1] == 0))) {
  } else {
    for (j = 0; j < n; j++) {
      yk = n * j - 1;
      for (k = n; k >= 1; k--) {
        b_n = n * (k - 1) - 1;
        i11 = k + yk;
        if (y->data[i11] != 0.0) {
          y->data[i11] /= b_x->data[k + b_n];
          for (i = 0; i <= k - 2; i++) {
            i12 = (i + yk) + 1;
            y->data[i12] -= y->data[i11] * b_x->data[(i + b_n) + 1];
          }
        }
      }
    }
  }

  emxFree_real_T(&b_x);
}

//
// Arguments    : const emxArray_real_T *x
//                emxArray_real_T *y
// Return Type  : void
//
void inv(const emxArray_real_T *x, emxArray_real_T *y)
{
  int i10;
  int loop_ub;
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    i10 = y->size[0] * y->size[1];
    y->size[0] = x->size[0];
    y->size[1] = x->size[1];
    emxEnsureCapacity_real_T(y, i10);
    loop_ub = x->size[0] * x->size[1];
    for (i10 = 0; i10 < loop_ub; i10++) {
      y->data[i10] = x->data[i10];
    }
  } else {
    invNxN(x, y);
  }
}

//
// File trailer for inv.cpp
//
// [EOF]
//
