//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: prod.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 11-Feb-2020 14:34:08
//

// Include Files
#include "rt_nonfinite.h"
#include "minSnap.h"
#include "prod.h"

// Function Definitions

//
// Arguments    : const double x_data[]
//                const int x_size[2]
// Return Type  : double
//
double prod(const double x_data[], const int x_size[2])
{
  double y;
  int vlen;
  int k;
  vlen = x_size[1];
  if (x_size[1] == 0) {
    y = 1.0;
  } else {
    y = x_data[0];
    for (k = 2; k <= vlen; k++) {
      y *= x_data[k - 1];
    }
  }

  return y;
}

//
// File trailer for prod.cpp
//
// [EOF]
//
