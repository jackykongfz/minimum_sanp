//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: closeform.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 11-Feb-2020 14:34:08
//

// Include Files
#include <cmath>
#include <math.h>
#include "rt_nonfinite.h"
#include "minSnap.h"
#include "closeform.h"
#include "minSnap_emxutil.h"
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
//                const emxArray_real_T *ts
//                const emxArray_real_T *ts_smallsize
//                emxArray_real_T *polys_x
//                emxArray_real_T *polys_y
//                emxArray_real_T *polys_z
// Return Type  : void
//
void closeform(const emxArray_real_T *new_waypts, const emxArray_real_T
               *cons_waypts, const emxArray_real_T *ts, const emxArray_real_T
               *ts_smallsize, emxArray_real_T *polys_x, emxArray_real_T *polys_y,
               emxArray_real_T *polys_z)
{
  emxArray_real_T *Q_all;
  int varargin_2;
  int n;
  int i3;
  int i4;
  int loop_ub;
  emxArray_int32_T *r0;
  emxArray_int32_T *ii;
  int j;
  emxArray_real_T *tk;
  int i;
  double t1;
  double t2;
  int b_n;
  int idx;
  int pos2;
  double dv0[64];
  int input_sizes_idx_1;
  int rowsA;
  emxArray_real_T *fix_idxanddf;
  emxArray_real_T *A;
  emxArray_real_T b_ts;
  int c_ts[1];
  emxArray_real_T *A_temp;
  int k;
  emxArray_real_T *M;
  int y_size[2];
  double y_data[13];
  int aoffset;
  double dv1[16];
  emxArray_real_T *C;
  emxArray_real_T *fix_idx;
  double num_d;
  emxArray_real_T *d_F;
  emxArray_real_T *b_fix_idxanddf;
  emxArray_real_T *pos;
  emxArray_real_T *temp;
  emxArray_real_T *ts_new;
  emxArray_boolean_T *tf;
  emxArray_real_T *a;
  emxArray_boolean_T *d_ts;
  double neq;
  boolean_T rowmatch;
  boolean_T exitg1;
  int exponent;
  int ib_size[1];
  emxArray_real_T *b_varargin_2;
  boolean_T guard1 = false;
  emxArray_real_T *y;
  emxArray_real_T *b_a;
  emxInit_real_T(&Q_all, 2);
  varargin_2 = new_waypts->size[1];
  n = new_waypts->size[1];

  //  compute Q
  //  xyz
  i3 = new_waypts->size[1];
  i4 = Q_all->size[0] * Q_all->size[1];
  i3 = (int)(((double)i3 - 1.0) * 8.0 * 3.0);
  Q_all->size[0] = i3;
  Q_all->size[1] = i3;
  emxEnsureCapacity_real_T(Q_all, i4);
  loop_ub = i3 * i3;
  for (i3 = 0; i3 < loop_ub; i3++) {
    Q_all->data[i3] = 0.0;
  }

  emxInit_int32_T(&r0, 1);
  emxInit_int32_T(&ii, 1);
  for (j = 0; j < 3; j++) {
    for (i = 0; i <= n - 2; i++) {
      t1 = (double)j * ((double)n - 1.0) * 8.0;
      t2 = (t1 + ((1.0 + (double)i) - 1.0) * 8.0) + 1.0;
      t1 += (1.0 + (double)i) * 8.0;
      if (t2 > t1) {
        i3 = 0;
        i4 = 0;
        b_n = 0;
        idx = 0;
      } else {
        i3 = (int)t2 - 1;
        i4 = (int)t1;
        b_n = (int)t2 - 1;
        idx = (int)t1;
      }

      pos2 = ii->size[0];
      loop_ub = i4 - i3;
      ii->size[0] = loop_ub;
      emxEnsureCapacity_int32_T(ii, pos2);
      for (i4 = 0; i4 < loop_ub; i4++) {
        ii->data[i4] = i3 + i4;
      }

      i3 = r0->size[0];
      loop_ub = idx - b_n;
      r0->size[0] = loop_ub;
      emxEnsureCapacity_int32_T(r0, i3);
      for (i3 = 0; i3 < loop_ub; i3++) {
        r0->data[i3] = b_n + i3;
      }

      computeQ(ts->data[i], ts->data[i + 1], dv0);
      input_sizes_idx_1 = ii->size[0];
      rowsA = r0->size[0];
      for (i3 = 0; i3 < rowsA; i3++) {
        for (i4 = 0; i4 < input_sizes_idx_1; i4++) {
          Q_all->data[ii->data[i4] + Q_all->size[0] * r0->data[i3]] = dv0[i4 +
            input_sizes_idx_1 * i3];
        }
      }
    }
  }

  emxInit_real_T(&tk, 2);

  // compute M
  //  d_M = zeros((continous_order+1)*(n_poly+1)*3,1);%+3*6
  //  p = zeros(n_poly*n_coef*3,1);
  //  M = zeros(length(d_M),length(p));
  //
  //  for i = 1:(n_poly)
  //      for j = 1:(continous_order+1)
  //      %x direction
  //      M((continous_order+1)*(i-1)+j,(i-1)*n_coef+1:i*n_coef) = [calc_tvec(ts(i),N_order,j);]; 
  //      %y direction
  //      M((continous_order+1)*(n_poly+1)+(continous_order+1)*(i-1)+j,n_coef*n_poly+(i-1)*n_coef+1:n_coef*n_poly+i*n_coef) = [calc_tvec(ts(i),N_order,j);]; 
  //      %z direction
  //      M((continous_order+1)*(n_poly+1)*2+(continous_order+1)*(i-1)+j,n_coef*n_poly*2+(i-1)*n_coef+1:n_coef*n_poly*2+i*n_coef) = [calc_tvec(ts(i),N_order,j);]; 
  //      end
  //
  //      if (i == n_poly)
  //          i = i+1;
  //          for j = 1:(continous_order+1)
  //              %x direction
  //              M((continous_order+1)*(i-1)+j,(i-2)*n_coef+1:(i-1)*n_coef) = [calc_tvec(ts(i),N_order,j);]; 
  //              %y direction
  //              M((continous_order+1)*(n_poly+1)+(continous_order+1)*(i-1)+j,n_coef*n_poly+(i-2)*n_coef+1:n_coef*n_poly+(i-1)*n_coef) = [calc_tvec(ts(i),N_order,j);]; 
  //              %z direction
  //              M((continous_order+1)*(n_poly+1)*2+(continous_order+1)*(i-1)+j,n_coef*n_poly*2+(i-2)*n_coef+1:n_coef*n_poly*2+(i-1)*n_coef) = [calc_tvec(ts(i),N_order,j);]; 
  //          end
  //      end
  //  end
  //  compute Tk   Tk(i,j) = ts(i)^(j-1)
  i3 = new_waypts->size[1];
  i4 = tk->size[0] * tk->size[1];
  tk->size[0] = i3;
  tk->size[1] = 8;
  emxEnsureCapacity_real_T(tk, i4);
  loop_ub = i3 << 3;
  for (i3 = 0; i3 < loop_ub; i3++) {
    tk->data[i3] = 0.0;
  }

  emxInit_real_T(&fix_idxanddf, 1);
  for (i = 0; i < 8; i++) {
    input_sizes_idx_1 = ts->size[1];
    b_ts = *ts;
    c_ts[0] = input_sizes_idx_1;
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
  //  1:p  2:pv  3:pva  4:pvaj  5:pvajs
  i3 = new_waypts->size[1];
  i4 = new_waypts->size[1];
  b_n = A->size[0] * A->size[1];
  i3 = 8 * (i3 - 1) * 3;
  A->size[0] = i3;
  A->size[1] = 8 * (i4 - 1) * 3;
  emxEnsureCapacity_real_T(A, b_n);
  loop_ub = i3 * (8 * (i4 - 1) * 3);
  for (i3 = 0; i3 < loop_ub; i3++) {
    A->data[i3] = 0.0;
  }

  emxInit_real_T(&A_temp, 2);
  i3 = new_waypts->size[1];
  i4 = new_waypts->size[1];
  b_n = A_temp->size[0] * A_temp->size[1];
  A_temp->size[0] = 8 * (i3 - 1);
  A_temp->size[1] = 8 * (i4 - 1);
  emxEnsureCapacity_real_T(A_temp, b_n);
  loop_ub = 8 * (i3 - 1) * (8 * (i4 - 1));
  for (i3 = 0; i3 < loop_ub; i3++) {
    A_temp->data[i3] = 0.0;
  }

  i3 = new_waypts->size[1];
  for (i = 0; i <= i3 - 2; i++) {
    for (k = 0; k < 8; k++) {
      if (k == 0) {
        t1 = 1.0;
        t2 = 1.0;
      } else {
        // k>j
        t1 = tk->data[i + tk->size[0] * k];
        t2 = tk->data[(i + tk->size[0] * k) + 1];
      }

      rowsA = k + 1;
      if (k < rowsA) {
        y_size[0] = 1;
        y_size[1] = 0;
      } else {
        y_size[0] = 1;
        input_sizes_idx_1 = k - rowsA;
        y_size[1] = input_sizes_idx_1 + 1;
        for (i4 = 0; i4 <= input_sizes_idx_1; i4++) {
          y_data[i4] = rowsA + i4;
        }
      }

      A_temp->data[8 * i + A_temp->size[0] * (8 * i + k)] = prod(y_data, y_size)
        * t1;
      rowsA = k + 1;
      if (k < rowsA) {
        y_size[0] = 1;
        y_size[1] = 0;
      } else {
        y_size[0] = 1;
        y_size[1] = (k - rowsA) + 1;
        loop_ub = k - rowsA;
        for (i4 = 0; i4 <= loop_ub; i4++) {
          y_data[i4] = rowsA + i4;
        }
      }

      A_temp->data[(8 * i + A_temp->size[0] * (8 * i + k)) + 4] = prod(y_data,
        y_size) * t2;
    }

    for (k = 0; k < 7; k++) {
      idx = 1 + k;
      if (idx == 1) {
        t1 = 1.0;
        t2 = 1.0;
      } else {
        // k>j
        t1 = tk->data[i + tk->size[0] * (idx - 1)];
        t2 = tk->data[(i + tk->size[0] * (idx - 1)) + 1];
      }

      y_size[0] = 1;
      y_size[1] = 1;
      for (i4 = 0; i4 < 1; i4++) {
        y_data[i4] = idx + i4;
      }

      A_temp->data[(8 * i + A_temp->size[0] * (8 * i + idx)) + 1] = prod(y_data,
        y_size) * t1;
      y_size[0] = 1;
      y_size[1] = 1;
      for (i4 = 0; i4 < 1; i4++) {
        y_data[i4] = idx + i4;
      }

      A_temp->data[(8 * i + A_temp->size[0] * (8 * i + idx)) + 5] = prod(y_data,
        y_size) * t2;
    }

    for (k = 0; k < 6; k++) {
      idx = 2 + k;
      if (idx == 2) {
        t1 = 1.0;
        t2 = 1.0;
      } else {
        // k>j
        t1 = tk->data[i + tk->size[0] * (idx - 2)];
        t2 = tk->data[(i + tk->size[0] * (idx - 2)) + 1];
      }

      rowsA = idx - 1;
      if (idx < rowsA) {
        y_size[0] = 1;
        y_size[1] = 0;
      } else {
        y_size[0] = 1;
        input_sizes_idx_1 = idx - rowsA;
        y_size[1] = input_sizes_idx_1 + 1;
        for (i4 = 0; i4 <= input_sizes_idx_1; i4++) {
          y_data[i4] = rowsA + i4;
        }
      }

      A_temp->data[(8 * i + A_temp->size[0] * (8 * i + idx)) + 2] = prod(y_data,
        y_size) * t1;
      rowsA = idx - 1;
      if (idx < rowsA) {
        y_size[0] = 1;
        y_size[1] = 0;
      } else {
        y_size[0] = 1;
        y_size[1] = (idx - rowsA) + 1;
        loop_ub = idx - rowsA;
        for (i4 = 0; i4 <= loop_ub; i4++) {
          y_data[i4] = rowsA + i4;
        }
      }

      A_temp->data[(8 * i + A_temp->size[0] * (8 * i + idx)) + 6] = prod(y_data,
        y_size) * t2;
    }

    for (k = 0; k < 5; k++) {
      idx = 3 + k;
      if (idx == 3) {
        t1 = 1.0;
        t2 = 1.0;
      } else {
        // k>j
        t1 = tk->data[i + tk->size[0] * (idx - 3)];
        t2 = tk->data[(i + tk->size[0] * (idx - 3)) + 1];
      }

      rowsA = idx - 2;
      if (idx < rowsA) {
        y_size[0] = 1;
        y_size[1] = 0;
      } else {
        y_size[0] = 1;
        input_sizes_idx_1 = idx - rowsA;
        y_size[1] = input_sizes_idx_1 + 1;
        for (i4 = 0; i4 <= input_sizes_idx_1; i4++) {
          y_data[i4] = rowsA + i4;
        }
      }

      A_temp->data[(8 * i + A_temp->size[0] * (8 * i + idx)) + 3] = prod(y_data,
        y_size) * t1;
      rowsA = idx - 2;
      if (idx < rowsA) {
        y_size[0] = 1;
        y_size[1] = 0;
      } else {
        y_size[0] = 1;
        y_size[1] = (idx - rowsA) + 1;
        loop_ub = idx - rowsA;
        for (i4 = 0; i4 <= loop_ub; i4++) {
          y_data[i4] = rowsA + i4;
        }
      }

      A_temp->data[(8 * i + A_temp->size[0] * (8 * i + idx)) + 7] = prod(y_data,
        y_size) * t2;
    }
  }

  emxFree_real_T(&tk);
  for (i = 0; i < 3; i++) {
    t1 = ((1.0 + (double)i) - 1.0) * 4.0 * 2.0 * ((double)n - 1.0) + 1.0;
    if (t1 > (1.0 + (double)i) * 4.0 * 2.0 * ((double)n - 1.0)) {
      i3 = 0;
    } else {
      i3 = (int)t1 - 1;
    }

    t1 = ((1.0 + (double)i) - 1.0) * 8.0 * ((double)n - 1.0) + 1.0;
    if (t1 > (1.0 + (double)i) * 8.0 * ((double)n - 1.0)) {
      i4 = 0;
    } else {
      i4 = (int)t1 - 1;
    }

    loop_ub = A_temp->size[1];
    for (b_n = 0; b_n < loop_ub; b_n++) {
      aoffset = A_temp->size[0];
      for (idx = 0; idx < aoffset; idx++) {
        A->data[(i3 + idx) + A->size[0] * (i4 + b_n)] = A_temp->data[idx +
          A_temp->size[0] * b_n];
      }
    }
  }

  emxInit_real_T(&M, 2);

  //  compute M
  i3 = new_waypts->size[1];
  i4 = new_waypts->size[1];
  b_n = M->size[0] * M->size[1];
  i3 = (i3 - 1) * 2 * 4 * 3;
  M->size[0] = i3;
  i4 = 4 * i4 * 3;
  M->size[1] = i4;
  emxEnsureCapacity_real_T(M, b_n);
  loop_ub = i3 * i4;
  for (i3 = 0; i3 < loop_ub; i3++) {
    M->data[i3] = 0.0;
  }

  i3 = new_waypts->size[1];
  i4 = new_waypts->size[1];
  b_n = A_temp->size[0] * A_temp->size[1];
  A_temp->size[0] = (i3 - 1) * 2 * 4;
  A_temp->size[1] = 4 * i4;
  emxEnsureCapacity_real_T(A_temp, b_n);
  loop_ub = (i3 - 1) * 2 * 4 * (4 * i4);
  for (i3 = 0; i3 < loop_ub; i3++) {
    A_temp->data[i3] = 0.0;
  }

  i3 = (varargin_2 - 1) << 1;
  if (0 <= i3 - 1) {
    eye(dv1);
  }

  for (i = 0; i < i3; i++) {
    t1 = 4.0 * ((1.0 + (double)i) - 1.0) + 1.0;
    t2 = 4.0 * ((std::floor((1.0 + (double)i) / 2.0) + 1.0) - 1.0) + 1.0;
    if (t1 > (t1 + 4.0) - 1.0) {
      i4 = 0;
      b_n = 0;
    } else {
      i4 = (int)t1 - 1;
      b_n = (int)((unsigned int)t1 + 3U);
    }

    if (t2 > (t2 + 4.0) - 1.0) {
      idx = 0;
      pos2 = 0;
    } else {
      idx = (int)t2 - 1;
      pos2 = (int)((unsigned int)t2 + 3U);
    }

    rowsA = ii->size[0];
    loop_ub = b_n - i4;
    ii->size[0] = loop_ub;
    emxEnsureCapacity_int32_T(ii, rowsA);
    for (b_n = 0; b_n < loop_ub; b_n++) {
      ii->data[b_n] = i4 + b_n;
    }

    i4 = r0->size[0];
    loop_ub = pos2 - idx;
    r0->size[0] = loop_ub;
    emxEnsureCapacity_int32_T(r0, i4);
    for (i4 = 0; i4 < loop_ub; i4++) {
      r0->data[i4] = idx + i4;
    }

    input_sizes_idx_1 = ii->size[0];
    rowsA = r0->size[0];
    for (i4 = 0; i4 < rowsA; i4++) {
      for (b_n = 0; b_n < input_sizes_idx_1; b_n++) {
        A_temp->data[ii->data[b_n] + A_temp->size[0] * r0->data[i4]] = dv1[b_n +
          input_sizes_idx_1 * i4];
      }
    }
  }

  emxFree_int32_T(&r0);
  for (i = 0; i < 3; i++) {
    t1 = ((1.0 + (double)i) - 1.0) * 4.0;
    t2 = t1 * 2.0 * ((double)n - 1.0) + 1.0;
    if (t2 > (1.0 + (double)i) * 4.0 * 2.0 * ((double)n - 1.0)) {
      i3 = 0;
    } else {
      i3 = (int)t2 - 1;
    }

    t1 = t1 * (((double)n - 1.0) + 1.0) + 1.0;
    if (t1 > (1.0 + (double)i) * 4.0 * (((double)n - 1.0) + 1.0)) {
      i4 = 0;
    } else {
      i4 = (int)t1 - 1;
    }

    loop_ub = A_temp->size[1];
    for (b_n = 0; b_n < loop_ub; b_n++) {
      aoffset = A_temp->size[0];
      for (idx = 0; idx < aoffset; idx++) {
        M->data[(i3 + idx) + M->size[0] * (i4 + b_n)] = A_temp->data[idx +
          A_temp->size[0] * b_n];
      }
    }
  }

  emxInit_real_T(&C, 2);
  emxInit_real_T(&fix_idx, 2);

  // compute C
  i3 = new_waypts->size[1];
  num_d = 4.0 * (((double)i3 - 1.0) + 1.0) * 3.0;
  b_eye(num_d, C);
  varargin_2 = cons_waypts->size[1];
  i3 = fix_idx->size[0] * fix_idx->size[1];
  fix_idx->size[0] = 1;
  loop_ub = 3 * varargin_2 + 18;
  fix_idx->size[1] = loop_ub;
  emxEnsureCapacity_real_T(fix_idx, i3);
  for (i3 = 0; i3 < loop_ub; i3++) {
    fix_idx->data[i3] = 0.0;
  }

  emxInit_real_T(&d_F, 1);
  varargin_2 = cons_waypts->size[1];
  i3 = d_F->size[0];
  d_F->size[0] = 3 * varargin_2 + 18;
  emxEnsureCapacity_real_T(d_F, i3);
  loop_ub = 3 * varargin_2 + 18;
  for (i3 = 0; i3 < loop_ub; i3++) {
    d_F->data[i3] = 0.0;
  }

  emxInit_real_T(&b_fix_idxanddf, 2);
  varargin_2 = cons_waypts->size[1];
  i3 = b_fix_idxanddf->size[0] * b_fix_idxanddf->size[1];
  b_fix_idxanddf->size[0] = 3 * varargin_2 + 18;
  b_fix_idxanddf->size[1] = 2;
  emxEnsureCapacity_real_T(b_fix_idxanddf, i3);
  loop_ub = (3 * varargin_2 + 18) << 1;
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
  emxInit_boolean_T(&d_ts, 2);
  for (i = 0; i < i3; i++) {
    // find waypoints ts position
    i4 = a->size[0] * a->size[1];
    a->size[0] = cons_waypts->size[1];
    a->size[1] = 3;
    emxEnsureCapacity_real_T(a, i4);
    for (i4 = 0; i4 < 3; i4++) {
      loop_ub = cons_waypts->size[1];
      for (b_n = 0; b_n < loop_ub; b_n++) {
        a->data[b_n + a->size[0] * i4] = cons_waypts->data[i4 + 3 * b_n];
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
        input_sizes_idx_1 = j + 3 * i;
        t1 = std::abs(cons_waypts->data[input_sizes_idx_1] / 2.0);
        if ((!rtIsInf(t1)) && (!rtIsNaN(t1))) {
          if (t1 <= 2.2250738585072014E-308) {
            t1 = 4.94065645841247E-324;
          } else {
            frexp(t1, &exponent);
            t1 = std::ldexp(1.0, exponent - 53);
          }
        } else {
          t1 = rtNaN;
        }

        if ((std::abs(cons_waypts->data[input_sizes_idx_1] - t2) < t1) ||
            (rtIsInf(t2) && rtIsInf(cons_waypts->data[input_sizes_idx_1]) &&
             ((t2 > 0.0) == (cons_waypts->data[input_sizes_idx_1] > 0.0)))) {
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
    rowsA = tf->size[0];
    idx = 0;
    i4 = ii->size[0];
    ii->size[0] = tf->size[0];
    emxEnsureCapacity_int32_T(ii, i4);
    input_sizes_idx_1 = 0;
    exitg1 = false;
    while ((!exitg1) && (input_sizes_idx_1 <= rowsA - 1)) {
      if (tf->data[input_sizes_idx_1]) {
        idx++;
        ii->data[idx - 1] = input_sizes_idx_1 + 1;
        if (idx >= rowsA) {
          exitg1 = true;
        } else {
          input_sizes_idx_1++;
        }
      } else {
        input_sizes_idx_1++;
      }
    }

    if (tf->size[0] == 1) {
      if (idx == 0) {
        ii->size[0] = 0;
      }
    } else if (1 > idx) {
      ii->size[0] = 0;
    } else {
      i4 = ii->size[0];
      ii->size[0] = idx;
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
      b_n = d_ts->size[0] * d_ts->size[1];
      d_ts->size[0] = 1;
      d_ts->size[1] = temp->size[1];
      emxEnsureCapacity_boolean_T(d_ts, b_n);
      t1 = ts->data[j];
      loop_ub = temp->size[0] * temp->size[1];
      for (b_n = 0; b_n < loop_ub; b_n++) {
        d_ts->data[b_n] = (t1 - temp->data[b_n] < 0.0);
      }

      if (ifWhileCond(d_ts)) {
        ts_new->data[j] = -(ts->data[j] - temp->data[0]);
      } else {
        ts_new->data[j] = ts->data[j] - ts_smallsize->data[(int)pos->data[0] - 1];
      }
    }

    // ts_new  = abs(ts-temp);
    b_n = ts_new->size[0];
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
        idx = 1;
      } else {
        idx = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= ts_new->size[0])) {
          if (!rtIsNaN(ts_new->data[k - 1])) {
            idx = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (idx == 0) {
        t1 = ts_new->data[0];
      } else {
        t1 = ts_new->data[idx - 1];
        i4 = idx + 1;
        for (k = i4; k <= b_n; k++) {
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
    t1 = ((double)pos2 - 1.0) * 4.0;
    fix_idx->data[i * 3] = t1 + 1.0;
    d_F->data[i * 3] = cons_waypts->data[3 * i];

    // y direction
    i4 = i * 3 + 1;
    fix_idx->data[i4] = (4.0 * (((double)n - 1.0) + 1.0) + t1) + 1.0;
    d_F->data[i4] = cons_waypts->data[1 + 3 * i];

    // z direction
    i4 = i * 3 + 2;
    fix_idx->data[i4] = (4.0 * (((double)n - 1.0) + 1.0) * 2.0 + t1) + 1.0;
    d_F->data[i4] = cons_waypts->data[2 + 3 * i];
  }

  emxFree_boolean_T(&d_ts);
  emxFree_real_T(&a);
  emxFree_boolean_T(&tf);
  i3 = cons_waypts->size[1];
  neq = (((double)i3 - 1.0) * 3.0 + 3.0) + 1.0;

  //  start point
  // x direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = 2.0;
  d_F->data[i3] = 0.0;
  neq++;

  // y direction
  i3 = (int)neq - 1;
  t1 = 4.0 * (((double)n - 1.0) + 1.0) + 1.0;
  fix_idx->data[i3] = t1 + 1.0;
  d_F->data[i3] = 0.0;
  neq++;

  // z direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = (4.0 * (((double)n - 1.0) + 1.0) * 2.0 + 1.0) + 1.0;
  d_F->data[i3] = 0.0;
  neq++;

  // x direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = 3.0;
  d_F->data[i3] = 0.0;
  neq++;

  // y direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = t1 + 2.0;
  d_F->data[i3] = 0.0;
  neq++;

  // z direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = (4.0 * (((double)n - 1.0) + 1.0) * 2.0 + 1.0) + 2.0;
  d_F->data[i3] = 0.0;
  neq++;

  // x direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = 4.0;
  d_F->data[i3] = 0.0;
  neq++;

  // y direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = t1 + 3.0;
  d_F->data[i3] = 0.0;
  neq++;

  // z direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = (4.0 * (((double)n - 1.0) + 1.0) * 2.0 + 1.0) + 3.0;
  d_F->data[i3] = 0.0;
  neq++;

  //  end point
  // x direction
  i3 = (int)neq - 1;
  t1 = 4.0 * (((double)n - 1.0) + 1.0) - 3.0;
  fix_idx->data[i3] = t1 + 1.0;
  d_F->data[i3] = 0.0;
  neq++;

  // y direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = (4.0 * (((double)n - 1.0) + 1.0) * 2.0 - 3.0) + 1.0;
  d_F->data[i3] = 0.0;
  neq++;

  // z direction
  i3 = (int)neq - 1;
  t2 = 4.0 * (((double)n - 1.0) + 1.0) * 3.0 - 3.0;
  fix_idx->data[i3] = t2 + 1.0;
  d_F->data[i3] = 0.0;
  neq++;

  // x direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = t1 + 2.0;
  d_F->data[i3] = 0.0;
  neq++;

  // y direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = (4.0 * (((double)n - 1.0) + 1.0) * 2.0 - 3.0) + 2.0;
  d_F->data[i3] = 0.0;
  neq++;

  // z direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = t2 + 2.0;
  d_F->data[i3] = 0.0;
  neq++;

  // x direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = t1 + 3.0;
  d_F->data[i3] = 0.0;
  neq++;

  // y direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = (4.0 * (((double)n - 1.0) + 1.0) * 2.0 - 3.0) + 3.0;
  d_F->data[i3] = 0.0;
  neq++;

  // z direction
  i3 = (int)neq - 1;
  fix_idx->data[i3] = t2 + 3.0;
  d_F->data[i3] = 0.0;

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

  i3 = fix_idx->size[0] * fix_idx->size[1];
  fix_idx->size[0] = 1;
  loop_ub = (int)(num_d - 1.0);
  fix_idx->size[1] = loop_ub + 1;
  emxEnsureCapacity_real_T(fix_idx, i3);
  for (i3 = 0; i3 <= loop_ub; i3++) {
    fix_idx->data[i3] = 1.0 + (double)i3;
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
  i3 = A_temp->size[0] * A_temp->size[1];
  A_temp->size[0] = loop_ub;
  A_temp->size[1] = aoffset;
  emxEnsureCapacity_real_T(A_temp, i3);
  emxFree_real_T(&fix_idxanddf);
  emxFree_int32_T(&ii);
  emxFree_real_T(&fix_idx);
  for (i3 = 0; i3 < aoffset; i3++) {
    for (i4 = 0; i4 < loop_ub; i4++) {
      A_temp->data[i4 + A_temp->size[0] * i3] = C->data[i4 + C->size[0] * ((int)
        b_fix_idxanddf->data[i3] - 1)];
    }
  }

  emxInit_real_T(&b_varargin_2, 2);
  loop_ub = C->size[0];
  i3 = b_varargin_2->size[0] * b_varargin_2->size[1];
  b_varargin_2->size[0] = loop_ub;
  b_varargin_2->size[1] = temp->size[1];
  emxEnsureCapacity_real_T(b_varargin_2, i3);
  aoffset = temp->size[1];
  for (i3 = 0; i3 < aoffset; i3++) {
    for (i4 = 0; i4 < loop_ub; i4++) {
      b_varargin_2->data[i4 + b_varargin_2->size[0] * i3] = C->data[i4 + C->
        size[0] * ((int)temp->data[i3] - 1)];
    }
  }

  i3 = C->size[0];
  rowmatch = (i3 == 0);
  if (rowmatch) {
    input_sizes_idx_1 = b_fix_idxanddf->size[0];
  } else {
    i3 = b_fix_idxanddf->size[0];
    if (i3 != 0) {
      input_sizes_idx_1 = b_fix_idxanddf->size[0];
    } else {
      input_sizes_idx_1 = 0;
    }
  }

  guard1 = false;
  if (rowmatch) {
    guard1 = true;
  } else {
    i3 = ts_new->size[0];
    ts_new->size[0] = temp->size[1];
    emxEnsureCapacity_real_T(ts_new, i3);
    loop_ub = temp->size[1];
    for (i3 = 0; i3 < loop_ub; i3++) {
      ts_new->data[i3] = temp->data[i3];
    }

    if (ts_new->size[0] != 0) {
      guard1 = true;
    } else {
      rowsA = 0;
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

    rowsA = ts_new->size[0];
  }

  emxFree_real_T(&temp);
  loop_ub = C->size[0];
  aoffset = C->size[0];
  i3 = C->size[0] * C->size[1];
  C->size[0] = loop_ub;
  C->size[1] = input_sizes_idx_1 + rowsA;
  emxEnsureCapacity_real_T(C, i3);
  for (i3 = 0; i3 < input_sizes_idx_1; i3++) {
    for (i4 = 0; i4 < loop_ub; i4++) {
      C->data[i4 + C->size[0] * i3] = A_temp->data[i4 + loop_ub * i3];
    }
  }

  for (i3 = 0; i3 < rowsA; i3++) {
    for (i4 = 0; i4 < aoffset; i4++) {
      C->data[i4 + C->size[0] * (i3 + input_sizes_idx_1)] = b_varargin_2->
        data[i4 + aoffset * i3];
    }
  }

  emxInit_real_T(&y, 2);
  emxInit_real_T(&b_a, 2);

  //  %compute K
  //  K = pinv(M)*C;
  //  R = (K')*Q_all*K;
  inv(A, b_a);
  if ((b_a->size[1] == 1) || (M->size[0] == 1)) {
    i3 = y->size[0] * y->size[1];
    y->size[0] = b_a->size[0];
    y->size[1] = M->size[1];
    emxEnsureCapacity_real_T(y, i3);
    loop_ub = b_a->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      aoffset = M->size[1];
      for (i4 = 0; i4 < aoffset; i4++) {
        y->data[i3 + y->size[0] * i4] = 0.0;
        input_sizes_idx_1 = b_a->size[1];
        for (b_n = 0; b_n < input_sizes_idx_1; b_n++) {
          y->data[i3 + y->size[0] * i4] += b_a->data[i3 + b_a->size[0] * b_n] *
            M->data[b_n + M->size[0] * i4];
        }
      }
    }
  } else {
    input_sizes_idx_1 = b_a->size[0];
    rowsA = b_a->size[1];
    b_n = M->size[1];
    i3 = y->size[0] * y->size[1];
    y->size[0] = b_a->size[0];
    y->size[1] = M->size[1];
    emxEnsureCapacity_real_T(y, i3);
    for (j = 0; j < b_n; j++) {
      idx = j * input_sizes_idx_1;
      pos2 = j * rowsA;
      for (i = 0; i < input_sizes_idx_1; i++) {
        y->data[idx + i] = 0.0;
      }

      for (k = 0; k < rowsA; k++) {
        aoffset = k * input_sizes_idx_1;
        t1 = M->data[pos2 + k];
        for (i = 0; i < input_sizes_idx_1; i++) {
          i3 = idx + i;
          y->data[i3] += t1 * b_a->data[aoffset + i];
        }
      }
    }
  }

  emxFree_real_T(&M);
  if ((y->size[1] == 1) || (C->size[0] == 1)) {
    i3 = A->size[0] * A->size[1];
    A->size[0] = y->size[0];
    A->size[1] = C->size[1];
    emxEnsureCapacity_real_T(A, i3);
    loop_ub = y->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      aoffset = C->size[1];
      for (i4 = 0; i4 < aoffset; i4++) {
        A->data[i3 + A->size[0] * i4] = 0.0;
        input_sizes_idx_1 = y->size[1];
        for (b_n = 0; b_n < input_sizes_idx_1; b_n++) {
          A->data[i3 + A->size[0] * i4] += y->data[i3 + y->size[0] * b_n] *
            C->data[b_n + C->size[0] * i4];
        }
      }
    }
  } else {
    input_sizes_idx_1 = y->size[0];
    rowsA = y->size[1];
    b_n = C->size[1];
    i3 = A->size[0] * A->size[1];
    A->size[0] = y->size[0];
    A->size[1] = C->size[1];
    emxEnsureCapacity_real_T(A, i3);
    for (j = 0; j < b_n; j++) {
      idx = j * input_sizes_idx_1;
      pos2 = j * rowsA;
      for (i = 0; i < input_sizes_idx_1; i++) {
        A->data[idx + i] = 0.0;
      }

      for (k = 0; k < rowsA; k++) {
        aoffset = k * input_sizes_idx_1;
        t1 = C->data[pos2 + k];
        for (i = 0; i < input_sizes_idx_1; i++) {
          i3 = idx + i;
          A->data[i3] += t1 * y->data[aoffset + i];
        }
      }
    }
  }

  emxFree_real_T(&C);
  i3 = b_a->size[0] * b_a->size[1];
  b_a->size[0] = A->size[1];
  b_a->size[1] = A->size[0];
  emxEnsureCapacity_real_T(b_a, i3);
  loop_ub = A->size[0];
  for (i3 = 0; i3 < loop_ub; i3++) {
    aoffset = A->size[1];
    for (i4 = 0; i4 < aoffset; i4++) {
      b_a->data[i4 + b_a->size[0] * i3] = A->data[i3 + A->size[0] * i4];
    }
  }

  if ((b_a->size[1] == 1) || (Q_all->size[0] == 1)) {
    i3 = y->size[0] * y->size[1];
    y->size[0] = b_a->size[0];
    y->size[1] = Q_all->size[1];
    emxEnsureCapacity_real_T(y, i3);
    loop_ub = b_a->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      aoffset = Q_all->size[1];
      for (i4 = 0; i4 < aoffset; i4++) {
        y->data[i3 + y->size[0] * i4] = 0.0;
        input_sizes_idx_1 = b_a->size[1];
        for (b_n = 0; b_n < input_sizes_idx_1; b_n++) {
          y->data[i3 + y->size[0] * i4] += b_a->data[i3 + b_a->size[0] * b_n] *
            Q_all->data[b_n + Q_all->size[0] * i4];
        }
      }
    }
  } else {
    input_sizes_idx_1 = b_a->size[0];
    rowsA = b_a->size[1];
    b_n = Q_all->size[1];
    i3 = y->size[0] * y->size[1];
    y->size[0] = b_a->size[0];
    y->size[1] = Q_all->size[1];
    emxEnsureCapacity_real_T(y, i3);
    for (j = 0; j < b_n; j++) {
      idx = j * input_sizes_idx_1;
      pos2 = j * rowsA;
      for (i = 0; i < input_sizes_idx_1; i++) {
        y->data[idx + i] = 0.0;
      }

      for (k = 0; k < rowsA; k++) {
        aoffset = k * input_sizes_idx_1;
        t1 = Q_all->data[pos2 + k];
        for (i = 0; i < input_sizes_idx_1; i++) {
          i3 = idx + i;
          y->data[i3] += t1 * b_a->data[aoffset + i];
        }
      }
    }
  }

  if ((y->size[1] == 1) || (A->size[0] == 1)) {
    i3 = A_temp->size[0] * A_temp->size[1];
    A_temp->size[0] = y->size[0];
    A_temp->size[1] = A->size[1];
    emxEnsureCapacity_real_T(A_temp, i3);
    loop_ub = y->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      aoffset = A->size[1];
      for (i4 = 0; i4 < aoffset; i4++) {
        A_temp->data[i3 + A_temp->size[0] * i4] = 0.0;
        input_sizes_idx_1 = y->size[1];
        for (b_n = 0; b_n < input_sizes_idx_1; b_n++) {
          A_temp->data[i3 + A_temp->size[0] * i4] += y->data[i3 + y->size[0] *
            b_n] * A->data[b_n + A->size[0] * i4];
        }
      }
    }
  } else {
    input_sizes_idx_1 = y->size[0];
    rowsA = y->size[1];
    b_n = A->size[1];
    i3 = A_temp->size[0] * A_temp->size[1];
    A_temp->size[0] = y->size[0];
    A_temp->size[1] = A->size[1];
    emxEnsureCapacity_real_T(A_temp, i3);
    for (j = 0; j < b_n; j++) {
      idx = j * input_sizes_idx_1;
      pos2 = j * rowsA;
      for (i = 0; i < input_sizes_idx_1; i++) {
        A_temp->data[idx + i] = 0.0;
      }

      for (k = 0; k < rowsA; k++) {
        aoffset = k * input_sizes_idx_1;
        t1 = A->data[pos2 + k];
        for (i = 0; i < input_sizes_idx_1; i++) {
          i3 = idx + i;
          A_temp->data[i3] += t1 * y->data[aoffset + i];
        }
      }
    }
  }

  if (pos->size[0] + 1U > (unsigned int)A_temp->size[0]) {
    i3 = 0;
    i4 = 0;
  } else {
    i3 = pos->size[0];
    i4 = A_temp->size[0];
  }

  if (pos->size[0] + 1U > (unsigned int)A_temp->size[1]) {
    b_n = 0;
    idx = 0;
  } else {
    b_n = pos->size[0];
    idx = A_temp->size[1];
  }

  if (pos->size[0] + 1U > (unsigned int)A_temp->size[1]) {
    pos2 = 0;
    rowsA = 0;
  } else {
    pos2 = pos->size[0];
    rowsA = A_temp->size[1];
  }

  input_sizes_idx_1 = Q_all->size[0] * Q_all->size[1];
  loop_ub = i4 - i3;
  Q_all->size[0] = loop_ub;
  aoffset = idx - b_n;
  Q_all->size[1] = aoffset;
  emxEnsureCapacity_real_T(Q_all, input_sizes_idx_1);
  for (i4 = 0; i4 < aoffset; i4++) {
    for (idx = 0; idx < loop_ub; idx++) {
      Q_all->data[idx + Q_all->size[0] * i4] = A_temp->data[(i3 + idx) +
        A_temp->size[0] * (b_n + i4)];
    }
  }

  inv(Q_all, b_a);
  i3 = b_a->size[0] * b_a->size[1];
  i4 = b_a->size[0] * b_a->size[1];
  emxEnsureCapacity_real_T(b_a, i4);
  loop_ub = i3 - 1;
  emxFree_real_T(&Q_all);
  for (i3 = 0; i3 <= loop_ub; i3++) {
    b_a->data[i3] = -b_a->data[i3];
  }

  loop_ub = pos->size[0];
  i3 = b_varargin_2->size[0] * b_varargin_2->size[1];
  aoffset = rowsA - pos2;
  b_varargin_2->size[0] = aoffset;
  b_varargin_2->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b_varargin_2, i3);
  for (i3 = 0; i3 < loop_ub; i3++) {
    for (i4 = 0; i4 < aoffset; i4++) {
      b_varargin_2->data[i4 + b_varargin_2->size[0] * i3] = A_temp->data[i3 +
        A_temp->size[0] * (pos2 + i4)];
    }
  }

  emxFree_real_T(&A_temp);
  if ((b_a->size[1] == 1) || (b_varargin_2->size[0] == 1)) {
    i3 = y->size[0] * y->size[1];
    y->size[0] = b_a->size[0];
    y->size[1] = b_varargin_2->size[1];
    emxEnsureCapacity_real_T(y, i3);
    loop_ub = b_a->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      aoffset = b_varargin_2->size[1];
      for (i4 = 0; i4 < aoffset; i4++) {
        y->data[i3 + y->size[0] * i4] = 0.0;
        input_sizes_idx_1 = b_a->size[1];
        for (b_n = 0; b_n < input_sizes_idx_1; b_n++) {
          y->data[i3 + y->size[0] * i4] += b_a->data[i3 + b_a->size[0] * b_n] *
            b_varargin_2->data[b_n + b_varargin_2->size[0] * i4];
        }
      }
    }
  } else {
    input_sizes_idx_1 = b_a->size[0];
    rowsA = b_a->size[1];
    b_n = b_varargin_2->size[1];
    i3 = y->size[0] * y->size[1];
    y->size[0] = b_a->size[0];
    y->size[1] = b_varargin_2->size[1];
    emxEnsureCapacity_real_T(y, i3);
    for (j = 0; j < b_n; j++) {
      idx = j * input_sizes_idx_1;
      pos2 = j * rowsA;
      for (i = 0; i < input_sizes_idx_1; i++) {
        y->data[idx + i] = 0.0;
      }

      for (k = 0; k < rowsA; k++) {
        aoffset = k * input_sizes_idx_1;
        t1 = b_varargin_2->data[pos2 + k];
        for (i = 0; i < input_sizes_idx_1; i++) {
          i3 = idx + i;
          y->data[i3] += t1 * b_a->data[aoffset + i];
        }
      }
    }
  }

  emxFree_real_T(&b_a);
  emxFree_real_T(&b_varargin_2);
  if (y->size[1] == 1) {
    i3 = pos->size[0];
    pos->size[0] = y->size[0];
    emxEnsureCapacity_real_T(pos, i3);
    loop_ub = y->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      pos->data[i3] = 0.0;
      aoffset = y->size[1];
      for (i4 = 0; i4 < aoffset; i4++) {
        pos->data[i3] += y->data[i3 + y->size[0] * i4] * d_F->data[i4];
      }
    }
  } else {
    input_sizes_idx_1 = y->size[0];
    rowsA = y->size[1];
    i3 = pos->size[0];
    pos->size[0] = y->size[0];
    emxEnsureCapacity_real_T(pos, i3);
    for (i = 0; i < input_sizes_idx_1; i++) {
      pos->data[i] = 0.0;
    }

    for (k = 0; k < rowsA; k++) {
      aoffset = k * input_sizes_idx_1;
      for (i = 0; i < input_sizes_idx_1; i++) {
        pos->data[i] += b_fix_idxanddf->data[k + b_fix_idxanddf->size[0]] *
          y->data[aoffset + i];
      }
    }
  }

  emxFree_real_T(&y);
  emxFree_real_T(&b_fix_idxanddf);

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
  if (A->size[1] == 1) {
    i3 = pos->size[0];
    pos->size[0] = A->size[0];
    emxEnsureCapacity_real_T(pos, i3);
    loop_ub = A->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      pos->data[i3] = 0.0;
      aoffset = A->size[1];
      for (i4 = 0; i4 < aoffset; i4++) {
        pos->data[i3] += A->data[i3 + A->size[0] * i4] * ts_new->data[i4];
      }
    }
  } else {
    input_sizes_idx_1 = A->size[0];
    rowsA = A->size[1];
    i3 = pos->size[0];
    pos->size[0] = A->size[0];
    emxEnsureCapacity_real_T(pos, i3);
    for (i = 0; i < input_sizes_idx_1; i++) {
      pos->data[i] = 0.0;
    }

    for (k = 0; k < rowsA; k++) {
      aoffset = k * input_sizes_idx_1;
      for (i = 0; i < input_sizes_idx_1; i++) {
        pos->data[i] += ts_new->data[k] * A->data[aoffset + i];
      }
    }
  }

  emxFree_real_T(&ts_new);
  emxFree_real_T(&A);
  i3 = polys_x->size[0] * polys_x->size[1];
  polys_x->size[0] = 8;
  polys_x->size[1] = n - 1;
  emxEnsureCapacity_real_T(polys_x, i3);
  input_sizes_idx_1 = (n - 1) << 3;
  for (i3 = 0; i3 < input_sizes_idx_1; i3++) {
    polys_x->data[i3] = pos->data[i3];
  }

  t1 = (double)pos->size[0] / 3.0 + 1.0;
  t2 = 2.0 * (double)pos->size[0] / 3.0;
  if (t1 > t2) {
    i3 = 0;
  } else {
    i3 = (int)t1 - 1;
  }

  i4 = polys_y->size[0] * polys_y->size[1];
  polys_y->size[0] = 8;
  polys_y->size[1] = n - 1;
  emxEnsureCapacity_real_T(polys_y, i4);
  for (i4 = 0; i4 < input_sizes_idx_1; i4++) {
    polys_y->data[i4] = pos->data[i3 + i4];
  }

  t1 = 2.0 * (double)pos->size[0] / 3.0 + 1.0;
  if (t1 > pos->size[0]) {
    i3 = 0;
  } else {
    i3 = (int)t1 - 1;
  }

  i4 = polys_z->size[0] * polys_z->size[1];
  polys_z->size[0] = 8;
  polys_z->size[1] = n - 1;
  emxEnsureCapacity_real_T(polys_z, i4);
  for (i4 = 0; i4 < input_sizes_idx_1; i4++) {
    polys_z->data[i4] = pos->data[i3 + i4];
  }

  emxFree_real_T(&pos);
}

//
// File trailer for closeform.cpp
//
// [EOF]
//
