//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: generate_corridor.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 11-Feb-2020 14:34:08
//

// Include Files
#include <cmath>
#include "rt_nonfinite.h"
#include "minSnap.h"
#include "generate_corridor.h"
#include "minSnap_emxutil.h"
#include "linspace.h"
#include "sortLE.h"

// Function Definitions

//
// regenerate waypoints
// Arguments    : const emxArray_real_T *waypts_noatti
//                const emxArray_real_T *waypts_atti
//                emxArray_real_T *cons_waypts
//                emxArray_real_T *new_waypts2
// Return Type  : void
//
void generate_corridor(const emxArray_real_T *waypts_noatti, const
  emxArray_real_T *waypts_atti, emxArray_real_T *cons_waypts, emxArray_real_T
  *new_waypts2)
{
  int j;
  int i2;
  int qEnd;
  int q;
  emxArray_real_T *temp_waypts;
  emxArray_real_T *temp2_waypts;
  int pEnd;
  emxArray_int32_T *idx;
  int n;
  emxArray_int32_T *iwork;
  int k;
  emxArray_real_T *ycol;
  unsigned int temp2_waypts_idx_0;
  int i;
  int p;
  int kEnd;
  emxArray_real_T *sample_pts;
  emxArray_real_T *varargin_1;
  emxArray_real_T *varargin_2;
  emxArray_real_T *varargin_3;
  emxArray_real_T *b_new_waypts2;
  double x1;
  double b_y1;
  double z1;
  double x2;
  double y2;
  double z2;
  double a;
  double b_a;
  double c_a;
  if (waypts_noatti->size[1] == 0) {
    j = waypts_atti->size[1];
    qEnd = cons_waypts->size[0] * cons_waypts->size[1];
    cons_waypts->size[0] = 3;
    cons_waypts->size[1] = j;
    emxEnsureCapacity_real_T(cons_waypts, qEnd);
    q = 3 * j;
    for (qEnd = 0; qEnd < q; qEnd++) {
      cons_waypts->data[qEnd] = 0.0;
    }
  } else {
    j = waypts_atti->size[1];
    i2 = waypts_noatti->size[1];
    qEnd = cons_waypts->size[0] * cons_waypts->size[1];
    cons_waypts->size[0] = 3;
    i2 += (unsigned int)j;
    cons_waypts->size[1] = i2;
    emxEnsureCapacity_real_T(cons_waypts, qEnd);
    q = 3 * i2;
    for (qEnd = 0; qEnd < q; qEnd++) {
      cons_waypts->data[qEnd] = 0.0;
    }
  }

  emxInit_real_T(&temp_waypts, 2);
  j = cons_waypts->size[1];
  qEnd = temp_waypts->size[0] * temp_waypts->size[1];
  temp_waypts->size[0] = 4;
  temp_waypts->size[1] = j;
  emxEnsureCapacity_real_T(temp_waypts, qEnd);
  q = j << 2;
  for (qEnd = 0; qEnd < q; qEnd++) {
    temp_waypts->data[qEnd] = 0.0;
  }

  q = waypts_atti->size[1] - 1;
  for (qEnd = 0; qEnd <= q; qEnd++) {
    i2 = qEnd << 3;
    j = qEnd << 2;
    temp_waypts->data[j] = waypts_atti->data[i2];
    temp_waypts->data[1 + j] = waypts_atti->data[1 + i2];
    temp_waypts->data[2 + j] = waypts_atti->data[2 + i2];
    temp_waypts->data[3 + j] = waypts_atti->data[3 + i2];
  }

  if (waypts_noatti->size[1] != 0) {
    qEnd = waypts_atti->size[1];
    i2 = waypts_noatti->size[1];
    j = waypts_atti->size[1];
    if (j + 1U > (unsigned int)qEnd + i2) {
      qEnd = 0;
    } else {
      qEnd = waypts_atti->size[1];
    }

    q = waypts_noatti->size[1] - 1;
    for (i2 = 0; i2 <= q; i2++) {
      j = i2 << 2;
      pEnd = (qEnd + i2) << 2;
      temp_waypts->data[pEnd] = waypts_noatti->data[j];
      temp_waypts->data[1 + pEnd] = waypts_noatti->data[1 + j];
      temp_waypts->data[2 + pEnd] = waypts_noatti->data[2 + j];
      temp_waypts->data[3 + pEnd] = waypts_noatti->data[3 + j];
    }
  }

  emxInit_real_T(&temp2_waypts, 2);

  //  resort
  qEnd = temp2_waypts->size[0] * temp2_waypts->size[1];
  temp2_waypts->size[0] = temp_waypts->size[1];
  temp2_waypts->size[1] = 4;
  emxEnsureCapacity_real_T(temp2_waypts, qEnd);
  q = temp_waypts->size[1];
  for (qEnd = 0; qEnd < q; qEnd++) {
    temp2_waypts->data[qEnd] = temp_waypts->data[qEnd << 2];
  }

  q = temp_waypts->size[1];
  for (qEnd = 0; qEnd < q; qEnd++) {
    temp2_waypts->data[qEnd + temp2_waypts->size[0]] = temp_waypts->data[1 +
      (qEnd << 2)];
  }

  q = temp_waypts->size[1];
  for (qEnd = 0; qEnd < q; qEnd++) {
    temp2_waypts->data[qEnd + (temp2_waypts->size[0] << 1)] = temp_waypts->data
      [2 + (qEnd << 2)];
  }

  q = temp_waypts->size[1];
  for (qEnd = 0; qEnd < q; qEnd++) {
    temp2_waypts->data[qEnd + temp2_waypts->size[0] * 3] = temp_waypts->data[3 +
      (qEnd << 2)];
  }

  emxFree_real_T(&temp_waypts);
  emxInit_int32_T(&idx, 1);
  n = temp2_waypts->size[0] + 1;
  qEnd = idx->size[0];
  idx->size[0] = temp2_waypts->size[0];
  emxEnsureCapacity_int32_T(idx, qEnd);
  q = temp2_waypts->size[0];
  for (qEnd = 0; qEnd < q; qEnd++) {
    idx->data[qEnd] = 0;
  }

  if (temp2_waypts->size[0] == 0) {
    for (k = 0; k <= n - 2; k++) {
      idx->data[k] = k + 1;
    }
  } else {
    emxInit_int32_T(&iwork, 1);
    qEnd = iwork->size[0];
    iwork->size[0] = temp2_waypts->size[0];
    emxEnsureCapacity_int32_T(iwork, qEnd);
    qEnd = temp2_waypts->size[0] - 1;
    for (k = 1; k <= qEnd; k += 2) {
      if (sortLE(temp2_waypts, k, k + 1)) {
        idx->data[k - 1] = k;
        idx->data[k] = k + 1;
      } else {
        idx->data[k - 1] = k + 1;
        idx->data[k] = k;
      }
    }

    if ((temp2_waypts->size[0] & 1) != 0) {
      idx->data[temp2_waypts->size[0] - 1] = temp2_waypts->size[0];
    }

    i = 2;
    while (i < n - 1) {
      i2 = i << 1;
      j = 1;
      for (pEnd = 1 + i; pEnd < n; pEnd = qEnd + i) {
        p = j;
        q = pEnd;
        qEnd = j + i2;
        if (qEnd > n) {
          qEnd = n;
        }

        k = 0;
        kEnd = qEnd - j;
        while (k + 1 <= kEnd) {
          if (sortLE(temp2_waypts, idx->data[p - 1], idx->data[q - 1])) {
            iwork->data[k] = idx->data[p - 1];
            p++;
            if (p == pEnd) {
              while (q < qEnd) {
                k++;
                iwork->data[k] = idx->data[q - 1];
                q++;
              }
            }
          } else {
            iwork->data[k] = idx->data[q - 1];
            q++;
            if (q == qEnd) {
              while (p < pEnd) {
                k++;
                iwork->data[k] = idx->data[p - 1];
                p++;
              }
            }
          }

          k++;
        }

        for (k = 0; k < kEnd; k++) {
          idx->data[(j + k) - 1] = iwork->data[k];
        }

        j = qEnd;
      }

      i = i2;
    }

    emxFree_int32_T(&iwork);
  }

  emxInit_real_T(&ycol, 1);
  j = temp2_waypts->size[0] - 1;
  temp2_waypts_idx_0 = (unsigned int)temp2_waypts->size[0];
  qEnd = ycol->size[0];
  ycol->size[0] = (int)temp2_waypts_idx_0;
  emxEnsureCapacity_real_T(ycol, qEnd);
  for (i = 0; i <= j; i++) {
    ycol->data[i] = temp2_waypts->data[idx->data[i] - 1];
  }

  for (i = 0; i <= j; i++) {
    temp2_waypts->data[i] = ycol->data[i];
  }

  for (i = 0; i <= j; i++) {
    ycol->data[i] = temp2_waypts->data[(idx->data[i] + temp2_waypts->size[0]) -
      1];
  }

  for (i = 0; i <= j; i++) {
    temp2_waypts->data[i + temp2_waypts->size[0]] = ycol->data[i];
  }

  for (i = 0; i <= j; i++) {
    ycol->data[i] = temp2_waypts->data[(idx->data[i] + (temp2_waypts->size[0] <<
      1)) - 1];
  }

  for (i = 0; i <= j; i++) {
    temp2_waypts->data[i + (temp2_waypts->size[0] << 1)] = ycol->data[i];
  }

  for (i = 0; i <= j; i++) {
    ycol->data[i] = temp2_waypts->data[(idx->data[i] + temp2_waypts->size[0] * 3)
      - 1];
  }

  for (i = 0; i <= j; i++) {
    temp2_waypts->data[i + temp2_waypts->size[0] * 3] = ycol->data[i];
  }

  emxFree_real_T(&ycol);
  emxFree_int32_T(&idx);
  q = temp2_waypts->size[0];
  qEnd = cons_waypts->size[0] * cons_waypts->size[1];
  cons_waypts->size[0] = 3;
  cons_waypts->size[1] = q;
  emxEnsureCapacity_real_T(cons_waypts, qEnd);
  for (qEnd = 0; qEnd < q; qEnd++) {
    cons_waypts->data[3 * qEnd] = temp2_waypts->data[qEnd + temp2_waypts->size[0]];
    cons_waypts->data[1 + 3 * qEnd] = temp2_waypts->data[qEnd +
      temp2_waypts->size[0] * 2];
    cons_waypts->data[2 + 3 * qEnd] = temp2_waypts->data[qEnd +
      temp2_waypts->size[0] * 3];
  }

  emxFree_real_T(&temp2_waypts);

  //  linear interpolation
  qEnd = new_waypts2->size[0] * new_waypts2->size[1];
  new_waypts2->size[0] = 3;
  new_waypts2->size[1] = 1;
  emxEnsureCapacity_real_T(new_waypts2, qEnd);
  new_waypts2->data[0] = cons_waypts->data[0];
  new_waypts2->data[1] = cons_waypts->data[1];
  new_waypts2->data[2] = cons_waypts->data[2];
  qEnd = cons_waypts->size[1];
  emxInit_real_T(&sample_pts, 2);
  emxInit_real_T(&varargin_1, 2);
  emxInit_real_T(&varargin_2, 2);
  emxInit_real_T(&varargin_3, 2);
  emxInit_real_T(&b_new_waypts2, 2);
  for (i = 0; i <= qEnd - 2; i++) {
    x1 = cons_waypts->data[3 * i];
    b_y1 = cons_waypts->data[1 + 3 * i];
    z1 = cons_waypts->data[2 + 3 * i];
    i2 = 3 * (1 + i);
    x2 = cons_waypts->data[i2];
    y2 = cons_waypts->data[1 + i2];
    z2 = cons_waypts->data[2 + i2];
    a = x1 - x2;
    b_a = b_y1 - y2;
    c_a = z1 - z2;
    a = std::ceil(std::sqrt((a * a + b_a * b_a) + c_a * c_a) / 0.5);
    linspace(x1, x2, a + 1.0, varargin_1);
    linspace(b_y1, y2, a + 1.0, varargin_2);
    linspace(z1, z2, a + 1.0, varargin_3);
    i2 = sample_pts->size[0] * sample_pts->size[1];
    sample_pts->size[0] = 3;
    sample_pts->size[1] = varargin_1->size[1];
    emxEnsureCapacity_real_T(sample_pts, i2);
    q = varargin_1->size[1];
    for (i2 = 0; i2 < q; i2++) {
      sample_pts->data[3 * i2] = varargin_1->data[i2];
    }

    q = varargin_2->size[1];
    for (i2 = 0; i2 < q; i2++) {
      sample_pts->data[1 + 3 * i2] = varargin_2->data[i2];
    }

    q = varargin_3->size[1];
    for (i2 = 0; i2 < q; i2++) {
      sample_pts->data[2 + 3 * i2] = varargin_3->data[i2];
    }

    if (2 > sample_pts->size[1]) {
      i2 = 0;
      j = 0;
    } else {
      i2 = 1;
      j = sample_pts->size[1];
    }

    pEnd = b_new_waypts2->size[0] * b_new_waypts2->size[1];
    b_new_waypts2->size[0] = 3;
    b_new_waypts2->size[1] = (new_waypts2->size[1] + j) - i2;
    emxEnsureCapacity_real_T(b_new_waypts2, pEnd);
    q = new_waypts2->size[1];
    for (pEnd = 0; pEnd < q; pEnd++) {
      b_new_waypts2->data[3 * pEnd] = new_waypts2->data[3 * pEnd];
      p = 1 + 3 * pEnd;
      b_new_waypts2->data[p] = new_waypts2->data[p];
      p = 2 + 3 * pEnd;
      b_new_waypts2->data[p] = new_waypts2->data[p];
    }

    q = j - i2;
    for (j = 0; j < q; j++) {
      pEnd = 3 * (i2 + j);
      b_new_waypts2->data[3 * (j + new_waypts2->size[1])] = sample_pts->
        data[pEnd];
      b_new_waypts2->data[1 + 3 * (j + new_waypts2->size[1])] = sample_pts->
        data[1 + pEnd];
      b_new_waypts2->data[2 + 3 * (j + new_waypts2->size[1])] = sample_pts->
        data[2 + pEnd];
    }

    i2 = new_waypts2->size[0] * new_waypts2->size[1];
    new_waypts2->size[0] = 3;
    new_waypts2->size[1] = b_new_waypts2->size[1];
    emxEnsureCapacity_real_T(new_waypts2, i2);
    q = b_new_waypts2->size[0] * b_new_waypts2->size[1];
    for (i2 = 0; i2 < q; i2++) {
      new_waypts2->data[i2] = b_new_waypts2->data[i2];
    }
  }

  emxFree_real_T(&b_new_waypts2);
  emxFree_real_T(&varargin_3);
  emxFree_real_T(&varargin_2);
  emxFree_real_T(&varargin_1);
  emxFree_real_T(&sample_pts);
}

//
// File trailer for generate_corridor.cpp
//
// [EOF]
//
