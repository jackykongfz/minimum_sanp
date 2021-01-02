//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: closeform.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 10-Oct-2020 11:13:02
//

// Include Files
#include <math.h>
#include "rt_nonfinite.h"
#include "minJerk.h"
#include "closeform.h"
#include "minJerk_emxutil.h"
#include "inv.h"
#include "eml_setop.h"
#include "sortrows.h"
#include "ifWhileCond.h"
#include "eye.h"
#include "prod.h"
#include "power.h"
#include "computeQ.h"

// Function Definitions

//
// number of ploynomial
// Arguments    : const emxArray_real_T *new_waypts
//                const emxArray_real_T *cons_waypts
//                double N_order
//                const emxArray_real_T *ts
//                const emxArray_real_T *ts_smallsize
//                double optimize_order
//                double continous_order
//                emxArray_real_T *polys_x
//                emxArray_real_T *polys_y
//                emxArray_real_T *polys_z
// Return Type  : void
//
void closeform(const emxArray_real_T *new_waypts, const emxArray_real_T
               *cons_waypts, double N_order, const emxArray_real_T *ts, const
               emxArray_real_T *ts_smallsize, double optimize_order, double
               continous_order, emxArray_real_T *polys_x, emxArray_real_T
               *polys_y, emxArray_real_T *polys_z)
{
  emxArray_real_T *Q_all;
  int rowsA;
  int n;
  int i3;
  int i4;
  int loop_ub;
  emxArray_real_T *C;
  int j;
  emxArray_real_T *tk;
  int i;
  double d0;
  int i5;
  emxArray_real_T *fix_idxanddf;
  int aoffset;
  int i6;
  emxArray_real_T *A;
  int nm1d2;
  emxArray_real_T b_ts;
  int c_ts[1];
  emxArray_real_T *A_temp;
  emxArray_real_T *fix_idx;
  emxArray_real_T *M;
  int k;
  unsigned int b_k;
  double t1;
  double t2;
  double num_d;
  int i7;
  double ndbl;
  double apnd;
  double cdiff;
  double d1;
  unsigned int u0;
  unsigned int u1;
  int nx;
  int pos2;
  emxArray_real_T *d_F;
  emxArray_real_T *b_fix_idxanddf;
  emxArray_real_T *pos;
  emxArray_real_T *temp;
  emxArray_real_T *ts_new;
  emxArray_boolean_T *tf;
  emxArray_real_T *a;
  emxArray_int32_T *ii;
  emxArray_boolean_T *d_ts;
  boolean_T rowmatch;
  boolean_T exitg1;
  int exponent;
  int ib_size[1];
  boolean_T guard1 = false;
  emxArray_real_T *b_a;
  emxInit_real_T(&Q_all, 2);
  rowsA = new_waypts->size[1];
  n = new_waypts->size[1];

  //  compute Q
  //  xyz
  i3 = new_waypts->size[1];
  i4 = Q_all->size[0] * Q_all->size[1];
  i3 = (int)(((double)i3 - 1.0) * (N_order + 1.0) * 3.0);
  Q_all->size[0] = i3;
  Q_all->size[1] = i3;
  emxEnsureCapacity_real_T(Q_all, i4);
  loop_ub = i3 * i3;
  for (i3 = 0; i3 < loop_ub; i3++) {
    Q_all->data[i3] = 0.0;
  }

  emxInit_real_T(&C, 2);
  for (j = 0; j < 3; j++) {
    for (i = 0; i <= n - 2; i++) {
      d0 = ((double)j * ((double)n - 1.0) * (N_order + 1.0) + ((1.0 + (double)i)
             - 1.0) * (N_order + 1.0)) + 1.0;
      if (d0 > (double)j * ((double)n - 1.0) * (N_order + 1.0) + (1.0 + (double)
           i) * (N_order + 1.0)) {
        i3 = 0;
        i4 = 0;
      } else {
        i3 = (int)d0 - 1;
        i4 = (int)d0 - 1;
      }

      computeQ(N_order, optimize_order, ts->data[i], ts->data[i + 1], C);
      loop_ub = C->size[1];
      for (i5 = 0; i5 < loop_ub; i5++) {
        aoffset = C->size[0];
        for (i6 = 0; i6 < aoffset; i6++) {
          Q_all->data[(i3 + i6) + Q_all->size[0] * (i4 + i5)] = C->data[i6 +
            C->size[0] * i5];
        }
      }
    }
  }

  emxInit_real_T(&tk, 2);

  //  compute Tk   Tk(i,j) = ts(i)^(j-1)
  i3 = new_waypts->size[1];
  i4 = tk->size[0] * tk->size[1];
  tk->size[0] = i3;
  i5 = (int)(N_order + 1.0);
  tk->size[1] = i5;
  emxEnsureCapacity_real_T(tk, i4);
  loop_ub = i3 * i5;
  for (i3 = 0; i3 < loop_ub; i3++) {
    tk->data[i3] = 0.0;
  }

  emxInit_real_T(&fix_idxanddf, 1);
  for (i = 0; i < i5; i++) {
    nm1d2 = ts->size[1];
    b_ts = *ts;
    c_ts[0] = nm1d2;
    b_ts.size = &c_ts[0];
    b_ts.numDimensions = 1;
    power(&b_ts, (1.0 + (double)i) - 1.0, fix_idxanddf);
    loop_ub = fix_idxanddf->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      tk->data[i3 + tk->size[0] * i] = fix_idxanddf->data[i3];
    }
  }

  emxInit_real_T(&A, 2);

  //  compute A (n_continuous*2*n_poly) * (n_coef*n_poly)
  //  represent
  //  1:p  2:pv  3:pva  4:pvaj  5:pvajs
  i3 = new_waypts->size[1];
  i4 = new_waypts->size[1];
  i6 = A->size[0] * A->size[1];
  d0 = (continous_order + 1.0) * 2.0;
  i3 = (int)(d0 * ((double)i3 - 1.0) * 3.0);
  A->size[0] = i3;
  i4 = (int)((N_order + 1.0) * ((double)i4 - 1.0) * 3.0);
  A->size[1] = i4;
  emxEnsureCapacity_real_T(A, i6);
  loop_ub = i3 * i4;
  for (i3 = 0; i3 < loop_ub; i3++) {
    A->data[i3] = 0.0;
  }

  emxInit_real_T(&A_temp, 2);
  i3 = new_waypts->size[1];
  i4 = new_waypts->size[1];
  i6 = A_temp->size[0] * A_temp->size[1];
  i3 = (int)((continous_order + 1.0) * 2.0 * ((double)i3 - 1.0));
  A_temp->size[0] = i3;
  i4 = (int)((N_order + 1.0) * ((double)i4 - 1.0));
  A_temp->size[1] = i4;
  emxEnsureCapacity_real_T(A_temp, i6);
  loop_ub = i3 * i4;
  for (i3 = 0; i3 < loop_ub; i3++) {
    A_temp->data[i3] = 0.0;
  }

  i3 = new_waypts->size[1];
  emxInit_real_T(&fix_idx, 2);
  for (i = 0; i <= i3 - 2; i++) {
    i4 = (int)(continous_order + 1.0);
    for (j = 0; j < i4; j++) {
      i6 = (int)((N_order + 1.0) + (1.0 - (1.0 + (double)j)));
      for (k = 0; k < i6; k++) {
        b_k = ((unsigned int)j + k) + 1U;
        if (b_k == 1U + j) {
          t1 = 1.0;
          t2 = 1.0;
        } else {
          // k>j
          t1 = tk->data[i + tk->size[0] * (((int)b_k - j) - 1)];
          t2 = tk->data[(i + tk->size[0] * (((int)b_k - j) - 1)) + 1];
        }

        num_d = ((double)b_k - (1.0 + (double)j)) + 1.0;
        if ((double)b_k - 1.0 < num_d) {
          fix_idx->size[0] = 1;
          fix_idx->size[1] = 0;
        } else if (num_d == num_d) {
          i7 = fix_idx->size[0] * fix_idx->size[1];
          fix_idx->size[0] = 1;
          loop_ub = ((int)b_k - (int)num_d) - 1;
          fix_idx->size[1] = loop_ub + 1;
          emxEnsureCapacity_real_T(fix_idx, i7);
          for (i7 = 0; i7 <= loop_ub; i7++) {
            fix_idx->data[i7] = num_d + (double)i7;
          }
        } else {
          ndbl = floor((((double)b_k - 1.0) - num_d) + 0.5);
          apnd = num_d + ndbl;
          cdiff = apnd - ((double)b_k - 1.0);
          u0 = (unsigned int)fabs(num_d);
          u1 = b_k - 1U;
          if (u0 > u1) {
            u1 = u0;
          }

          if (fabs(cdiff) < 4.4408920985006262E-16 * (double)u1) {
            ndbl++;
            apnd = (double)b_k - 1.0;
          } else if (cdiff > 0.0) {
            apnd = num_d + (ndbl - 1.0);
          } else {
            ndbl++;
          }

          if (ndbl >= 0.0) {
            loop_ub = (int)ndbl;
          } else {
            loop_ub = 0;
          }

          i7 = fix_idx->size[0] * fix_idx->size[1];
          fix_idx->size[0] = 1;
          fix_idx->size[1] = loop_ub;
          emxEnsureCapacity_real_T(fix_idx, i7);
          if (loop_ub > 0) {
            fix_idx->data[0] = num_d;
            if (loop_ub > 1) {
              fix_idx->data[loop_ub - 1] = apnd;
              nm1d2 = (loop_ub - 1) / 2;
              for (nx = 0; nx <= nm1d2 - 2; nx++) {
                fix_idx->data[1 + nx] = num_d + (1.0 + (double)nx);
                fix_idx->data[(loop_ub - nx) - 2] = apnd - (1.0 + (double)nx);
              }

              if (nm1d2 << 1 == loop_ub - 1) {
                fix_idx->data[nm1d2] = (num_d + apnd) / 2.0;
              } else {
                fix_idx->data[nm1d2] = num_d + (double)nm1d2;
                fix_idx->data[nm1d2 + 1] = apnd - (double)nm1d2;
              }
            }
          }
        }

        d1 = d0 * ((1.0 + (double)i) - 1.0);
        A_temp->data[((int)(d1 + (1.0 + (double)j)) + A_temp->size[0] * ((int)
          ((N_order + 1.0) * ((1.0 + (double)i) - 1.0) + (double)b_k) - 1)) - 1]
          = prod(fix_idx) * t1;
        if ((double)b_k - 1.0 < num_d) {
          fix_idx->size[0] = 1;
          fix_idx->size[1] = 0;
        } else if (num_d == num_d) {
          i7 = fix_idx->size[0] * fix_idx->size[1];
          fix_idx->size[0] = 1;
          fix_idx->size[1] = (int)b_k - (int)num_d;
          emxEnsureCapacity_real_T(fix_idx, i7);
          loop_ub = ((int)b_k - (int)num_d) - 1;
          for (i7 = 0; i7 <= loop_ub; i7++) {
            fix_idx->data[i7] = num_d + (double)i7;
          }
        } else {
          ndbl = floor((((double)b_k - 1.0) - num_d) + 0.5);
          apnd = num_d + ndbl;
          cdiff = apnd - ((double)b_k - 1.0);
          u0 = (unsigned int)fabs(num_d);
          u1 = b_k - 1U;
          if (u0 > u1) {
            u1 = u0;
          }

          if (fabs(cdiff) < 4.4408920985006262E-16 * (double)u1) {
            ndbl++;
            apnd = (double)b_k - 1.0;
          } else if (cdiff > 0.0) {
            apnd = num_d + (ndbl - 1.0);
          } else {
            ndbl++;
          }

          if (ndbl >= 0.0) {
            loop_ub = (int)ndbl;
          } else {
            loop_ub = 0;
          }

          i7 = fix_idx->size[0] * fix_idx->size[1];
          fix_idx->size[0] = 1;
          fix_idx->size[1] = loop_ub;
          emxEnsureCapacity_real_T(fix_idx, i7);
          if (loop_ub > 0) {
            fix_idx->data[0] = num_d;
            if (loop_ub > 1) {
              fix_idx->data[loop_ub - 1] = apnd;
              nm1d2 = (loop_ub - 1) / 2;
              for (nx = 0; nx <= nm1d2 - 2; nx++) {
                fix_idx->data[1 + nx] = num_d + (1.0 + (double)nx);
                fix_idx->data[(loop_ub - nx) - 2] = apnd - (1.0 + (double)nx);
              }

              if (nm1d2 << 1 == loop_ub - 1) {
                fix_idx->data[nm1d2] = (num_d + apnd) / 2.0;
              } else {
                fix_idx->data[nm1d2] = num_d + (double)nm1d2;
                fix_idx->data[nm1d2 + 1] = apnd - (double)nm1d2;
              }
            }
          }
        }

        A_temp->data[((int)((d1 + (continous_order + 1.0)) + (1.0 + (double)j))
                      + A_temp->size[0] * ((int)((N_order + 1.0) * ((1.0 +
          (double)i) - 1.0) + (double)b_k) - 1)) - 1] = prod(fix_idx) * t2;
      }
    }
  }

  for (i = 0; i < 3; i++) {
    d0 = ((1.0 + (double)i) - 1.0) * (continous_order + 1.0) * 2.0 * ((double)n
      - 1.0) + 1.0;
    if (d0 > (1.0 + (double)i) * (continous_order + 1.0) * 2.0 * ((double)n -
         1.0)) {
      i3 = 0;
    } else {
      i3 = (int)d0 - 1;
    }

    d0 = ((1.0 + (double)i) - 1.0) * (N_order + 1.0) * ((double)n - 1.0) + 1.0;
    if (d0 > (1.0 + (double)i) * (N_order + 1.0) * ((double)n - 1.0)) {
      i4 = 0;
    } else {
      i4 = (int)d0 - 1;
    }

    loop_ub = A_temp->size[1];
    for (i6 = 0; i6 < loop_ub; i6++) {
      aoffset = A_temp->size[0];
      for (i7 = 0; i7 < aoffset; i7++) {
        A->data[(i3 + i7) + A->size[0] * (i4 + i6)] = A_temp->data[i7 +
          A_temp->size[0] * i6];
      }
    }
  }

  emxInit_real_T(&M, 2);

  //  compute M
  i3 = new_waypts->size[1];
  i4 = new_waypts->size[1];
  i6 = M->size[0] * M->size[1];
  i3 = (int)(((double)i3 - 1.0) * 2.0 * (continous_order + 1.0) * 3.0);
  M->size[0] = i3;
  i4 = (int)((continous_order + 1.0) * (((double)i4 - 1.0) + 1.0) * 3.0);
  M->size[1] = i4;
  emxEnsureCapacity_real_T(M, i6);
  loop_ub = i3 * i4;
  for (i3 = 0; i3 < loop_ub; i3++) {
    M->data[i3] = 0.0;
  }

  i3 = new_waypts->size[1];
  i4 = new_waypts->size[1];
  i6 = tk->size[0] * tk->size[1];
  i3 = (int)(((double)i3 - 1.0) * 2.0 * (continous_order + 1.0));
  tk->size[0] = i3;
  i4 = (int)((continous_order + 1.0) * (((double)i4 - 1.0) + 1.0));
  tk->size[1] = i4;
  emxEnsureCapacity_real_T(tk, i6);
  loop_ub = i3 * i4;
  for (i3 = 0; i3 < loop_ub; i3++) {
    tk->data[i3] = 0.0;
  }

  i3 = (rowsA - 1) << 1;
  for (i = 0; i < i3; i++) {
    t1 = (continous_order + 1.0) * ((1.0 + (double)i) - 1.0) + 1.0;
    t2 = (continous_order + 1.0) * ((floor((1.0 + (double)i) / 2.0) + 1.0) - 1.0)
      + 1.0;
    if (t1 > (t1 + (continous_order + 1.0)) - 1.0) {
      i4 = 0;
    } else {
      i4 = (int)t1 - 1;
    }

    if (t2 > (t2 + (continous_order + 1.0)) - 1.0) {
      i6 = 0;
    } else {
      i6 = (int)t2 - 1;
    }

    eye(continous_order + 1.0, C);
    loop_ub = C->size[1];
    for (i7 = 0; i7 < loop_ub; i7++) {
      aoffset = C->size[0];
      for (pos2 = 0; pos2 < aoffset; pos2++) {
        tk->data[(i4 + pos2) + tk->size[0] * (i6 + i7)] = C->data[pos2 + C->
          size[0] * i7];
      }
    }
  }

  for (i = 0; i < 3; i++) {
    d0 = ((1.0 + (double)i) - 1.0) * (continous_order + 1.0);
    d1 = d0 * 2.0 * ((double)n - 1.0) + 1.0;
    if (d1 > (1.0 + (double)i) * (continous_order + 1.0) * 2.0 * ((double)n -
         1.0)) {
      i3 = 0;
    } else {
      i3 = (int)d1 - 1;
    }

    d0 = d0 * (((double)n - 1.0) + 1.0) + 1.0;
    if (d0 > (1.0 + (double)i) * (continous_order + 1.0) * (((double)n - 1.0) +
         1.0)) {
      i4 = 0;
    } else {
      i4 = (int)d0 - 1;
    }

    loop_ub = tk->size[1];
    for (i6 = 0; i6 < loop_ub; i6++) {
      aoffset = tk->size[0];
      for (i7 = 0; i7 < aoffset; i7++) {
        M->data[(i3 + i7) + M->size[0] * (i4 + i6)] = tk->data[i7 + tk->size[0] *
          i6];
      }
    }
  }

  // compute C
  i3 = new_waypts->size[1];
  num_d = (continous_order + 1.0) * (((double)i3 - 1.0) + 1.0) * 3.0;
  eye(num_d, C);
  rowsA = cons_waypts->size[1];
  i3 = fix_idx->size[0] * fix_idx->size[1];
  fix_idx->size[0] = 1;
  loop_ub = (int)(3.0 * (double)rowsA + continous_order * 3.0 * 2.0);
  fix_idx->size[1] = loop_ub;
  emxEnsureCapacity_real_T(fix_idx, i3);
  for (i3 = 0; i3 < loop_ub; i3++) {
    fix_idx->data[i3] = 0.0;
  }

  emxInit_real_T(&d_F, 1);
  rowsA = cons_waypts->size[1];
  i3 = d_F->size[0];
  d_F->size[0] = (int)(3.0 * (double)rowsA + continous_order * 3.0 * 2.0);
  emxEnsureCapacity_real_T(d_F, i3);
  loop_ub = (int)(3.0 * (double)rowsA + continous_order * 3.0 * 2.0);
  for (i3 = 0; i3 < loop_ub; i3++) {
    d_F->data[i3] = 0.0;
  }

  emxInit_real_T(&b_fix_idxanddf, 2);
  rowsA = cons_waypts->size[1];
  i3 = b_fix_idxanddf->size[0] * b_fix_idxanddf->size[1];
  b_fix_idxanddf->size[0] = (int)(3.0 * (double)rowsA + continous_order * 3.0 *
    2.0);
  b_fix_idxanddf->size[1] = 2;
  emxEnsureCapacity_real_T(b_fix_idxanddf, i3);
  loop_ub = (int)(3.0 * (double)rowsA + continous_order * 3.0 * 2.0) << 1;
  for (i3 = 0; i3 < loop_ub; i3++) {
    b_fix_idxanddf->data[i3] = 0.0;
  }

  pos2 = 1;

  //  middle waypoints position constraints
  i3 = cons_waypts->size[1];
  emxInit_real_T(&pos, 1);
  emxInit_real_T(&temp, 2);
  emxInit_real_T(&ts_new, 1);
  emxInit_boolean_T(&tf, 1);
  emxInit_real_T(&a, 2);
  emxInit_int32_T(&ii, 1);
  emxInit_boolean_T(&d_ts, 2);
  for (i = 0; i < i3; i++) {
    // find waypoints ts position
    i4 = a->size[0] * a->size[1];
    a->size[0] = cons_waypts->size[1];
    a->size[1] = 3;
    emxEnsureCapacity_real_T(a, i4);
    for (i4 = 0; i4 < 3; i4++) {
      loop_ub = cons_waypts->size[1];
      for (i6 = 0; i6 < loop_ub; i6++) {
        a->data[i6 + a->size[0] * i4] = cons_waypts->data[i4 + 3 * i6];
      }
    }

    rowsA = a->size[0];
    i4 = tf->size[0];
    tf->size[0] = a->size[0];
    emxEnsureCapacity_boolean_T(tf, i4);
    loop_ub = a->size[0];
    for (i4 = 0; i4 < loop_ub; i4++) {
      tf->data[i4] = false;
    }

    for (k = 0; k < rowsA; k++) {
      tf->data[k] = false;
      rowmatch = true;
      j = 0;
      exitg1 = false;
      while ((!exitg1) && (j < 3)) {
        t2 = a->data[k + a->size[0] * j];
        nm1d2 = j + 3 * i;
        t1 = fabs(cons_waypts->data[nm1d2] / 2.0);
        if ((!rtIsInf(t1)) && (!rtIsNaN(t1))) {
          if (t1 <= 2.2250738585072014E-308) {
            t1 = 4.94065645841247E-324;
          } else {
            frexp(t1, &exponent);
            t1 = ldexp(1.0, exponent - 53);
          }
        } else {
          t1 = rtNaN;
        }

        if ((fabs(cons_waypts->data[nm1d2] - t2) < t1) || (rtIsInf(t2) &&
             rtIsInf(cons_waypts->data[nm1d2]) && ((t2 > 0.0) ==
              (cons_waypts->data[nm1d2] > 0.0)))) {
          j++;
        } else {
          rowmatch = false;
          exitg1 = true;
        }
      }

      if (rowmatch) {
        tf->data[k] = true;
      }
    }

    i4 = tf->size[0];
    emxEnsureCapacity_boolean_T(tf, i4);
    nx = tf->size[0];
    rowsA = 0;
    i4 = ii->size[0];
    ii->size[0] = tf->size[0];
    emxEnsureCapacity_int32_T(ii, i4);
    nm1d2 = 0;
    exitg1 = false;
    while ((!exitg1) && (nm1d2 <= nx - 1)) {
      if (tf->data[nm1d2]) {
        rowsA++;
        ii->data[rowsA - 1] = nm1d2 + 1;
        if (rowsA >= nx) {
          exitg1 = true;
        } else {
          nm1d2++;
        }
      } else {
        nm1d2++;
      }
    }

    if (tf->size[0] == 1) {
      if (rowsA == 0) {
        ii->size[0] = 0;
      }
    } else if (1 > rowsA) {
      ii->size[0] = 0;
    } else {
      i4 = ii->size[0];
      ii->size[0] = rowsA;
      emxEnsureCapacity_int32_T(ii, i4);
    }

    i4 = pos->size[0];
    pos->size[0] = ii->size[0];
    emxEnsureCapacity_real_T(pos, i4);
    loop_ub = ii->size[0];
    for (i4 = 0; i4 < loop_ub; i4++) {
      pos->data[i4] = ii->data[i4];
    }

    // [value, pos2] = min(abs(ts-ts_smallsize(:,pos)));
    i4 = temp->size[0] * temp->size[1];
    temp->size[0] = 1;
    temp->size[1] = ii->size[0];
    emxEnsureCapacity_real_T(temp, i4);
    loop_ub = ii->size[0];
    for (i4 = 0; i4 < loop_ub; i4++) {
      temp->data[i4] = ts_smallsize->data[ii->data[i4] - 1];
    }

    i4 = ts_new->size[0];
    ts_new->size[0] = ts->size[1];
    emxEnsureCapacity_real_T(ts_new, i4);
    loop_ub = ts->size[1];
    for (i4 = 0; i4 < loop_ub; i4++) {
      ts_new->data[i4] = 0.0;
    }

    i4 = ts->size[1];
    for (j = 0; j < i4; j++) {
      i6 = d_ts->size[0] * d_ts->size[1];
      d_ts->size[0] = 1;
      d_ts->size[1] = temp->size[1];
      emxEnsureCapacity_boolean_T(d_ts, i6);
      t1 = ts->data[j];
      loop_ub = temp->size[0] * temp->size[1];
      for (i6 = 0; i6 < loop_ub; i6++) {
        d_ts->data[i6] = (t1 - temp->data[i6] < 0.0);
      }

      if (ifWhileCond(d_ts)) {
        ts_new->data[j] = -(ts->data[j] - temp->data[0]);
      } else {
        ts_new->data[j] = ts->data[j] - ts_smallsize->data[(int)pos->data[0] - 1];
      }
    }

    // ts_new  = abs(ts-temp);
    loop_ub = ts_new->size[0];
    if (ts_new->size[0] <= 2) {
      if (ts_new->size[0] == 1) {
        t1 = ts_new->data[0];
      } else if ((ts_new->data[0] > ts_new->data[1]) || (rtIsNaN(ts_new->data[0])
                  && (!rtIsNaN(ts_new->data[1])))) {
        t1 = ts_new->data[1];
      } else {
        t1 = ts_new->data[0];
      }
    } else {
      if (!rtIsNaN(ts_new->data[0])) {
        rowsA = 1;
      } else {
        rowsA = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= ts_new->size[0])) {
          if (!rtIsNaN(ts_new->data[k - 1])) {
            rowsA = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (rowsA == 0) {
        t1 = ts_new->data[0];
      } else {
        t1 = ts_new->data[rowsA - 1];
        i4 = rowsA + 1;
        for (k = i4; k <= loop_ub; k++) {
          if (t1 > ts_new->data[k - 1]) {
            t1 = ts_new->data[k - 1];
          }
        }
      }
    }

    // pos2 = find(ts_new == value);
    i4 = ts_new->size[0];
    for (j = 0; j < i4; j++) {
      if (ts_new->data[j] == t1) {
        pos2 = 1 + j;
      }
    }

    // x direction
    d0 = ((double)pos2 - 1.0) * (continous_order + 1.0);
    fix_idx->data[i * 3] = d0 + 1.0;
    d_F->data[i * 3] = cons_waypts->data[3 * i];

    // y direction
    i4 = i * 3 + 1;
    fix_idx->data[i4] = ((continous_order + 1.0) * (((double)n - 1.0) + 1.0) +
                         d0) + 1.0;
    d_F->data[i4] = cons_waypts->data[1 + 3 * i];

    // z direction
    i4 = i * 3 + 2;
    fix_idx->data[i4] = ((continous_order + 1.0) * (((double)n - 1.0) + 1.0) *
                         2.0 + d0) + 1.0;
    d_F->data[i4] = cons_waypts->data[2 + 3 * i];
  }

  emxFree_boolean_T(&d_ts);
  emxFree_real_T(&a);
  emxFree_boolean_T(&tf);
  i3 = cons_waypts->size[1];
  t1 = (((double)i3 - 1.0) * 3.0 + 3.0) + 1.0;

  //  start point
  i3 = (int)continous_order;
  for (i = 0; i < i3; i++) {
    // x direction
    i4 = (int)t1 - 1;
    fix_idx->data[i4] = 1.0 + (1.0 + (double)i);
    d_F->data[i4] = 0.0;
    t1++;

    // y direction
    i4 = (int)t1 - 1;
    fix_idx->data[i4] = ((continous_order + 1.0) * (((double)n - 1.0) + 1.0) +
                         1.0) + (1.0 + (double)i);
    d_F->data[i4] = 0.0;
    t1++;

    // z direction
    i4 = (int)t1 - 1;
    fix_idx->data[i4] = ((continous_order + 1.0) * (((double)n - 1.0) + 1.0) *
                         2.0 + 1.0) + (1.0 + (double)i);
    d_F->data[i4] = 0.0;
    t1++;
  }

  //  end point
  for (i = 0; i < i3; i++) {
    // x direction
    i4 = (int)t1 - 1;
    fix_idx->data[i4] = ((continous_order + 1.0) * (((double)n - 1.0) + 1.0) -
                         continous_order) + (1.0 + (double)i);
    d_F->data[i4] = 0.0;
    t1++;

    // y direction
    i4 = (int)t1 - 1;
    fix_idx->data[i4] = ((continous_order + 1.0) * (((double)n - 1.0) + 1.0) *
                         2.0 - continous_order) + (1.0 + (double)i);
    d_F->data[i4] = 0.0;
    t1++;

    // z direction
    i4 = (int)t1 - 1;
    fix_idx->data[i4] = ((continous_order + 1.0) * (((double)n - 1.0) + 1.0) *
                         3.0 - continous_order) + (1.0 + (double)i);
    d_F->data[i4] = 0.0;
    t1++;
  }

  // fix_idx = [1:(continous_order+1):num_d,2:(continous_order+1),num_d-(continous_order+1)+1:num_d]; 
  i3 = pos->size[0];
  pos->size[0] = fix_idx->size[1];
  emxEnsureCapacity_real_T(pos, i3);
  loop_ub = fix_idx->size[1];
  for (i3 = 0; i3 < loop_ub; i3++) {
    pos->data[i3] = fix_idx->data[i3];
  }

  loop_ub = pos->size[0];
  for (i3 = 0; i3 < loop_ub; i3++) {
    b_fix_idxanddf->data[i3] = pos->data[i3];
  }

  loop_ub = d_F->size[0];
  for (i3 = 0; i3 < loop_ub; i3++) {
    b_fix_idxanddf->data[i3 + b_fix_idxanddf->size[0]] = d_F->data[i3];
  }

  sortrows(b_fix_idxanddf);
  loop_ub = b_fix_idxanddf->size[0];
  i3 = d_F->size[0];
  d_F->size[0] = loop_ub;
  emxEnsureCapacity_real_T(d_F, i3);
  for (i3 = 0; i3 < loop_ub; i3++) {
    d_F->data[i3] = b_fix_idxanddf->data[i3 + b_fix_idxanddf->size[0]];
  }

  if (rtIsNaN(num_d)) {
    i3 = fix_idx->size[0] * fix_idx->size[1];
    fix_idx->size[0] = 1;
    fix_idx->size[1] = 1;
    emxEnsureCapacity_real_T(fix_idx, i3);
    fix_idx->data[0] = rtNaN;
  } else if (num_d < 1.0) {
    fix_idx->size[0] = 1;
    fix_idx->size[1] = 0;
  } else if (rtIsInf(num_d) && (1.0 == num_d)) {
    i3 = fix_idx->size[0] * fix_idx->size[1];
    fix_idx->size[0] = 1;
    fix_idx->size[1] = 1;
    emxEnsureCapacity_real_T(fix_idx, i3);
    fix_idx->data[0] = rtNaN;
  } else {
    i3 = fix_idx->size[0] * fix_idx->size[1];
    fix_idx->size[0] = 1;
    loop_ub = (int)floor(num_d - 1.0);
    fix_idx->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(fix_idx, i3);
    for (i3 = 0; i3 <= loop_ub; i3++) {
      fix_idx->data[i3] = 1.0 + (double)i3;
    }
  }

  loop_ub = b_fix_idxanddf->size[0];
  i3 = fix_idxanddf->size[0];
  fix_idxanddf->size[0] = loop_ub;
  emxEnsureCapacity_real_T(fix_idxanddf, i3);
  for (i3 = 0; i3 < loop_ub; i3++) {
    fix_idxanddf->data[i3] = b_fix_idxanddf->data[i3];
  }

  do_vectors(fix_idx, fix_idxanddf, temp, ii, ib_size);
  loop_ub = C->size[0];
  aoffset = b_fix_idxanddf->size[0];
  i3 = tk->size[0] * tk->size[1];
  tk->size[0] = loop_ub;
  tk->size[1] = aoffset;
  emxEnsureCapacity_real_T(tk, i3);
  emxFree_real_T(&fix_idxanddf);
  emxFree_int32_T(&ii);
  emxFree_real_T(&fix_idx);
  for (i3 = 0; i3 < aoffset; i3++) {
    for (i4 = 0; i4 < loop_ub; i4++) {
      tk->data[i4 + tk->size[0] * i3] = C->data[i4 + C->size[0] * ((int)
        b_fix_idxanddf->data[i3] - 1)];
    }
  }

  loop_ub = C->size[0];
  i3 = A_temp->size[0] * A_temp->size[1];
  A_temp->size[0] = loop_ub;
  A_temp->size[1] = temp->size[1];
  emxEnsureCapacity_real_T(A_temp, i3);
  aoffset = temp->size[1];
  for (i3 = 0; i3 < aoffset; i3++) {
    for (i4 = 0; i4 < loop_ub; i4++) {
      A_temp->data[i4 + A_temp->size[0] * i3] = C->data[i4 + C->size[0] * ((int)
        temp->data[i3] - 1)];
    }
  }

  i3 = C->size[0];
  i4 = b_fix_idxanddf->size[0];
  if ((i3 != 0) && (i4 != 0)) {
    nx = C->size[0];
  } else {
    i3 = C->size[0];
    i4 = ts_new->size[0];
    ts_new->size[0] = temp->size[1];
    emxEnsureCapacity_real_T(ts_new, i4);
    loop_ub = temp->size[1];
    for (i4 = 0; i4 < loop_ub; i4++) {
      ts_new->data[i4] = temp->data[i4];
    }

    if ((i3 != 0) && (ts_new->size[0] != 0)) {
      nx = C->size[0];
    } else {
      i3 = C->size[0];
      if (i3 > 0) {
        nx = C->size[0];
      } else {
        nx = 0;
      }

      i3 = C->size[0];
      if (i3 > nx) {
        nx = C->size[0];
      }
    }
  }

  rowmatch = (nx == 0);
  if (rowmatch) {
    rowsA = b_fix_idxanddf->size[0];
  } else {
    i3 = C->size[0];
    i4 = b_fix_idxanddf->size[0];
    if ((i3 != 0) && (i4 != 0)) {
      rowsA = b_fix_idxanddf->size[0];
    } else {
      rowsA = 0;
    }
  }

  guard1 = false;
  if (rowmatch) {
    guard1 = true;
  } else {
    i3 = C->size[0];
    i4 = ts_new->size[0];
    ts_new->size[0] = temp->size[1];
    emxEnsureCapacity_real_T(ts_new, i4);
    loop_ub = temp->size[1];
    for (i4 = 0; i4 < loop_ub; i4++) {
      ts_new->data[i4] = temp->data[i4];
    }

    if ((i3 != 0) && (ts_new->size[0] != 0)) {
      guard1 = true;
    } else {
      nm1d2 = 0;
    }
  }

  if (guard1) {
    i3 = ts_new->size[0];
    ts_new->size[0] = temp->size[1];
    emxEnsureCapacity_real_T(ts_new, i3);
    loop_ub = temp->size[1];
    for (i3 = 0; i3 < loop_ub; i3++) {
      ts_new->data[i3] = temp->data[i3];
    }

    nm1d2 = ts_new->size[0];
  }

  emxFree_real_T(&temp);
  i3 = C->size[0] * C->size[1];
  C->size[0] = nx;
  C->size[1] = rowsA + nm1d2;
  emxEnsureCapacity_real_T(C, i3);
  for (i3 = 0; i3 < rowsA; i3++) {
    for (i4 = 0; i4 < nx; i4++) {
      C->data[i4 + C->size[0] * i3] = tk->data[i4 + nx * i3];
    }
  }

  for (i3 = 0; i3 < nm1d2; i3++) {
    for (i4 = 0; i4 < nx; i4++) {
      C->data[i4 + C->size[0] * (i3 + rowsA)] = A_temp->data[i4 + nx * i3];
    }
  }

  emxInit_real_T(&b_a, 2);

  //  %compute K
  //  K = pinv(M)*C;
  //  R = (K')*Q_all*K;
  inv(A, b_a);
  if ((b_a->size[1] == 1) || (M->size[0] == 1)) {
    i3 = A->size[0] * A->size[1];
    A->size[0] = b_a->size[0];
    A->size[1] = M->size[1];
    emxEnsureCapacity_real_T(A, i3);
    loop_ub = b_a->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      aoffset = M->size[1];
      for (i4 = 0; i4 < aoffset; i4++) {
        A->data[i3 + A->size[0] * i4] = 0.0;
        nm1d2 = b_a->size[1];
        for (i6 = 0; i6 < nm1d2; i6++) {
          A->data[i3 + A->size[0] * i4] += b_a->data[i3 + b_a->size[0] * i6] *
            M->data[i6 + M->size[0] * i4];
        }
      }
    }
  } else {
    nm1d2 = b_a->size[0];
    nx = b_a->size[1];
    loop_ub = M->size[1];
    i3 = A->size[0] * A->size[1];
    A->size[0] = b_a->size[0];
    A->size[1] = M->size[1];
    emxEnsureCapacity_real_T(A, i3);
    for (j = 0; j < loop_ub; j++) {
      rowsA = j * nm1d2;
      pos2 = j * nx;
      for (i = 0; i < nm1d2; i++) {
        A->data[rowsA + i] = 0.0;
      }

      for (k = 0; k < nx; k++) {
        aoffset = k * nm1d2;
        t1 = M->data[pos2 + k];
        for (i = 0; i < nm1d2; i++) {
          i3 = rowsA + i;
          A->data[i3] += t1 * b_a->data[aoffset + i];
        }
      }
    }
  }

  if ((A->size[1] == 1) || (C->size[0] == 1)) {
    i3 = M->size[0] * M->size[1];
    M->size[0] = A->size[0];
    M->size[1] = C->size[1];
    emxEnsureCapacity_real_T(M, i3);
    loop_ub = A->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      aoffset = C->size[1];
      for (i4 = 0; i4 < aoffset; i4++) {
        M->data[i3 + M->size[0] * i4] = 0.0;
        nm1d2 = A->size[1];
        for (i6 = 0; i6 < nm1d2; i6++) {
          M->data[i3 + M->size[0] * i4] += A->data[i3 + A->size[0] * i6] *
            C->data[i6 + C->size[0] * i4];
        }
      }
    }
  } else {
    nm1d2 = A->size[0];
    nx = A->size[1];
    loop_ub = C->size[1];
    i3 = M->size[0] * M->size[1];
    M->size[0] = A->size[0];
    M->size[1] = C->size[1];
    emxEnsureCapacity_real_T(M, i3);
    for (j = 0; j < loop_ub; j++) {
      rowsA = j * nm1d2;
      pos2 = j * nx;
      for (i = 0; i < nm1d2; i++) {
        M->data[rowsA + i] = 0.0;
      }

      for (k = 0; k < nx; k++) {
        aoffset = k * nm1d2;
        t1 = C->data[pos2 + k];
        for (i = 0; i < nm1d2; i++) {
          i3 = rowsA + i;
          M->data[i3] += t1 * A->data[aoffset + i];
        }
      }
    }
  }

  i3 = b_a->size[0] * b_a->size[1];
  b_a->size[0] = M->size[1];
  b_a->size[1] = M->size[0];
  emxEnsureCapacity_real_T(b_a, i3);
  loop_ub = M->size[0];
  for (i3 = 0; i3 < loop_ub; i3++) {
    aoffset = M->size[1];
    for (i4 = 0; i4 < aoffset; i4++) {
      b_a->data[i4 + b_a->size[0] * i3] = M->data[i3 + M->size[0] * i4];
    }
  }

  if ((b_a->size[1] == 1) || (Q_all->size[0] == 1)) {
    i3 = A->size[0] * A->size[1];
    A->size[0] = b_a->size[0];
    A->size[1] = Q_all->size[1];
    emxEnsureCapacity_real_T(A, i3);
    loop_ub = b_a->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      aoffset = Q_all->size[1];
      for (i4 = 0; i4 < aoffset; i4++) {
        A->data[i3 + A->size[0] * i4] = 0.0;
        nm1d2 = b_a->size[1];
        for (i6 = 0; i6 < nm1d2; i6++) {
          A->data[i3 + A->size[0] * i4] += b_a->data[i3 + b_a->size[0] * i6] *
            Q_all->data[i6 + Q_all->size[0] * i4];
        }
      }
    }
  } else {
    nm1d2 = b_a->size[0];
    nx = b_a->size[1];
    loop_ub = Q_all->size[1];
    i3 = A->size[0] * A->size[1];
    A->size[0] = b_a->size[0];
    A->size[1] = Q_all->size[1];
    emxEnsureCapacity_real_T(A, i3);
    for (j = 0; j < loop_ub; j++) {
      rowsA = j * nm1d2;
      pos2 = j * nx;
      for (i = 0; i < nm1d2; i++) {
        A->data[rowsA + i] = 0.0;
      }

      for (k = 0; k < nx; k++) {
        aoffset = k * nm1d2;
        t1 = Q_all->data[pos2 + k];
        for (i = 0; i < nm1d2; i++) {
          i3 = rowsA + i;
          A->data[i3] += t1 * b_a->data[aoffset + i];
        }
      }
    }
  }

  emxFree_real_T(&Q_all);
  if ((A->size[1] == 1) || (M->size[0] == 1)) {
    i3 = tk->size[0] * tk->size[1];
    tk->size[0] = A->size[0];
    tk->size[1] = M->size[1];
    emxEnsureCapacity_real_T(tk, i3);
    loop_ub = A->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      aoffset = M->size[1];
      for (i4 = 0; i4 < aoffset; i4++) {
        tk->data[i3 + tk->size[0] * i4] = 0.0;
        nm1d2 = A->size[1];
        for (i6 = 0; i6 < nm1d2; i6++) {
          tk->data[i3 + tk->size[0] * i4] += A->data[i3 + A->size[0] * i6] *
            M->data[i6 + M->size[0] * i4];
        }
      }
    }
  } else {
    nm1d2 = A->size[0];
    nx = A->size[1];
    loop_ub = M->size[1];
    i3 = tk->size[0] * tk->size[1];
    tk->size[0] = A->size[0];
    tk->size[1] = M->size[1];
    emxEnsureCapacity_real_T(tk, i3);
    for (j = 0; j < loop_ub; j++) {
      rowsA = j * nm1d2;
      pos2 = j * nx;
      for (i = 0; i < nm1d2; i++) {
        tk->data[rowsA + i] = 0.0;
      }

      for (k = 0; k < nx; k++) {
        aoffset = k * nm1d2;
        t1 = M->data[pos2 + k];
        for (i = 0; i < nm1d2; i++) {
          i3 = rowsA + i;
          tk->data[i3] += t1 * A->data[aoffset + i];
        }
      }
    }
  }

  if (pos->size[0] + 1U > (unsigned int)tk->size[0]) {
    i3 = 0;
    i4 = 0;
  } else {
    i3 = pos->size[0];
    i4 = tk->size[0];
  }

  if (pos->size[0] + 1U > (unsigned int)tk->size[1]) {
    i6 = 0;
    i7 = 0;
  } else {
    i6 = pos->size[0];
    i7 = tk->size[1];
  }

  if (1 > pos->size[0]) {
    loop_ub = 0;
  } else {
    loop_ub = pos->size[0];
  }

  if (pos->size[0] + 1U > (unsigned int)tk->size[1]) {
    pos2 = 0;
    nx = 0;
  } else {
    pos2 = pos->size[0];
    nx = tk->size[1];
  }

  rowsA = C->size[0] * C->size[1];
  aoffset = i4 - i3;
  C->size[0] = aoffset;
  nm1d2 = i7 - i6;
  C->size[1] = nm1d2;
  emxEnsureCapacity_real_T(C, rowsA);
  for (i4 = 0; i4 < nm1d2; i4++) {
    for (i7 = 0; i7 < aoffset; i7++) {
      C->data[i7 + C->size[0] * i4] = tk->data[(i3 + i7) + tk->size[0] * (i6 +
        i4)];
    }
  }

  inv(C, b_a);
  i3 = b_a->size[0] * b_a->size[1];
  i4 = b_a->size[0] * b_a->size[1];
  emxEnsureCapacity_real_T(b_a, i4);
  aoffset = i3 - 1;
  emxFree_real_T(&C);
  for (i3 = 0; i3 <= aoffset; i3++) {
    b_a->data[i3] = -b_a->data[i3];
  }

  i3 = A_temp->size[0] * A_temp->size[1];
  aoffset = nx - pos2;
  A_temp->size[0] = aoffset;
  A_temp->size[1] = loop_ub;
  emxEnsureCapacity_real_T(A_temp, i3);
  for (i3 = 0; i3 < loop_ub; i3++) {
    for (i4 = 0; i4 < aoffset; i4++) {
      A_temp->data[i4 + A_temp->size[0] * i3] = tk->data[i3 + tk->size[0] *
        (pos2 + i4)];
    }
  }

  emxFree_real_T(&tk);
  if ((b_a->size[1] == 1) || (A_temp->size[0] == 1)) {
    i3 = A->size[0] * A->size[1];
    A->size[0] = b_a->size[0];
    A->size[1] = A_temp->size[1];
    emxEnsureCapacity_real_T(A, i3);
    loop_ub = b_a->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      aoffset = A_temp->size[1];
      for (i4 = 0; i4 < aoffset; i4++) {
        A->data[i3 + A->size[0] * i4] = 0.0;
        nm1d2 = b_a->size[1];
        for (i6 = 0; i6 < nm1d2; i6++) {
          A->data[i3 + A->size[0] * i4] += b_a->data[i3 + b_a->size[0] * i6] *
            A_temp->data[i6 + A_temp->size[0] * i4];
        }
      }
    }
  } else {
    nm1d2 = b_a->size[0];
    nx = b_a->size[1];
    loop_ub = A_temp->size[1];
    i3 = A->size[0] * A->size[1];
    A->size[0] = b_a->size[0];
    A->size[1] = A_temp->size[1];
    emxEnsureCapacity_real_T(A, i3);
    for (j = 0; j < loop_ub; j++) {
      rowsA = j * nm1d2;
      pos2 = j * nx;
      for (i = 0; i < nm1d2; i++) {
        A->data[rowsA + i] = 0.0;
      }

      for (k = 0; k < nx; k++) {
        aoffset = k * nm1d2;
        t1 = A_temp->data[pos2 + k];
        for (i = 0; i < nm1d2; i++) {
          i3 = rowsA + i;
          A->data[i3] += t1 * b_a->data[aoffset + i];
        }
      }
    }
  }

  emxFree_real_T(&b_a);
  emxFree_real_T(&A_temp);
  guard1 = false;
  if (A->size[1] == 1) {
    guard1 = true;
  } else {
    i3 = b_fix_idxanddf->size[0];
    if (i3 == 1) {
      guard1 = true;
    } else {
      nm1d2 = A->size[0];
      nx = A->size[1];
      i3 = pos->size[0];
      pos->size[0] = A->size[0];
      emxEnsureCapacity_real_T(pos, i3);
      for (i = 0; i < nm1d2; i++) {
        pos->data[i] = 0.0;
      }

      for (k = 0; k < nx; k++) {
        aoffset = k * nm1d2;
        for (i = 0; i < nm1d2; i++) {
          pos->data[i] += b_fix_idxanddf->data[k + b_fix_idxanddf->size[0]] *
            A->data[aoffset + i];
        }
      }
    }
  }

  if (guard1) {
    i3 = pos->size[0];
    pos->size[0] = A->size[0];
    emxEnsureCapacity_real_T(pos, i3);
    loop_ub = A->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      pos->data[i3] = 0.0;
      aoffset = A->size[1];
      for (i4 = 0; i4 < aoffset; i4++) {
        pos->data[i3] += A->data[i3 + A->size[0] * i4] * d_F->data[i4];
      }
    }
  }

  emxFree_real_T(&b_fix_idxanddf);
  emxFree_real_T(&A);

  //  p = K*[d_F;d_P];
  i3 = ts_new->size[0];
  ts_new->size[0] = d_F->size[0] + pos->size[0];
  emxEnsureCapacity_real_T(ts_new, i3);
  loop_ub = d_F->size[0];
  for (i3 = 0; i3 < loop_ub; i3++) {
    ts_new->data[i3] = d_F->data[i3];
  }

  loop_ub = pos->size[0];
  for (i3 = 0; i3 < loop_ub; i3++) {
    ts_new->data[i3 + d_F->size[0]] = pos->data[i3];
  }

  emxFree_real_T(&d_F);
  if ((M->size[1] == 1) || (ts_new->size[0] == 1)) {
    i3 = pos->size[0];
    pos->size[0] = M->size[0];
    emxEnsureCapacity_real_T(pos, i3);
    loop_ub = M->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      pos->data[i3] = 0.0;
      aoffset = M->size[1];
      for (i4 = 0; i4 < aoffset; i4++) {
        pos->data[i3] += M->data[i3 + M->size[0] * i4] * ts_new->data[i4];
      }
    }
  } else {
    nm1d2 = M->size[0];
    nx = M->size[1];
    i3 = pos->size[0];
    pos->size[0] = M->size[0];
    emxEnsureCapacity_real_T(pos, i3);
    for (i = 0; i < nm1d2; i++) {
      pos->data[i] = 0.0;
    }

    for (k = 0; k < nx; k++) {
      aoffset = k * nm1d2;
      for (i = 0; i < nm1d2; i++) {
        pos->data[i] += ts_new->data[k] * M->data[aoffset + i];
      }
    }
  }

  emxFree_real_T(&ts_new);
  emxFree_real_T(&M);
  i3 = polys_x->size[0] * polys_x->size[1];
  polys_x->size[0] = i5;
  polys_x->size[1] = n - 1;
  emxEnsureCapacity_real_T(polys_x, i3);
  nm1d2 = i5 * (n - 1);
  for (i3 = 0; i3 < nm1d2; i3++) {
    polys_x->data[i3] = pos->data[i3];
  }

  d0 = (double)pos->size[0] / 3.0 + 1.0;
  d1 = 2.0 * (double)pos->size[0] / 3.0;
  if (d0 > d1) {
    i3 = 0;
  } else {
    i3 = (int)d0 - 1;
  }

  i4 = polys_y->size[0] * polys_y->size[1];
  polys_y->size[0] = i5;
  polys_y->size[1] = n - 1;
  emxEnsureCapacity_real_T(polys_y, i4);
  for (i4 = 0; i4 < nm1d2; i4++) {
    polys_y->data[i4] = pos->data[i3 + i4];
  }

  d0 = 2.0 * (double)pos->size[0] / 3.0 + 1.0;
  if (d0 > pos->size[0]) {
    i3 = 0;
  } else {
    i3 = (int)d0 - 1;
  }

  i4 = polys_z->size[0] * polys_z->size[1];
  polys_z->size[0] = i5;
  polys_z->size[1] = n - 1;
  emxEnsureCapacity_real_T(polys_z, i4);
  for (i4 = 0; i4 < nm1d2; i4++) {
    polys_z->data[i4] = pos->data[i3 + i4];
  }

  emxFree_real_T(&pos);
}

//
// File trailer for closeform.cpp
//
// [EOF]
//
