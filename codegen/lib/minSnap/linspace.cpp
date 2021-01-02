//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: linspace.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 11-Feb-2020 14:34:08
//

// Include Files
#include <cmath>
#include "rt_nonfinite.h"
#include "minSnap.h"
#include "linspace.h"
#include "minSnap_emxutil.h"

// Function Definitions

//
// Arguments    : double d1
//                double d2
//                double n1
//                emxArray_real_T *y
// Return Type  : void
//
void linspace(double d1, double d2, double n1, emxArray_real_T *y)
{
  int i0;
  double delta1;
  double delta2;
  int k;
  if (n1 < 0.0) {
    n1 = 0.0;
  }

  i0 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = (int)std::floor(n1);
  emxEnsureCapacity_real_T(y, i0);
  if (y->size[1] >= 1) {
    y->data[y->size[1] - 1] = d2;
    if (y->size[1] >= 2) {
      y->data[0] = d1;
      if (y->size[1] >= 3) {
        if (((d1 < 0.0) != (d2 < 0.0)) && ((std::abs(d1) >
              8.9884656743115785E+307) || (std::abs(d2) >
              8.9884656743115785E+307))) {
          delta1 = d1 / ((double)y->size[1] - 1.0);
          delta2 = d2 / ((double)y->size[1] - 1.0);
          i0 = y->size[1];
          for (k = 0; k <= i0 - 3; k++) {
            y->data[k + 1] = (d1 + delta2 * (1.0 + (double)k)) - delta1 * (1.0 +
              (double)k);
          }
        } else {
          delta1 = (d2 - d1) / ((double)y->size[1] - 1.0);
          i0 = y->size[1];
          for (k = 0; k <= i0 - 3; k++) {
            y->data[k + 1] = d1 + (1.0 + (double)k) * delta1;
          }
        }
      }
    }
  }
}

//
// File trailer for linspace.cpp
//
// [EOF]
//
