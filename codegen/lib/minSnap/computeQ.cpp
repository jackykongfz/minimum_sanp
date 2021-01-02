//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeQ.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 11-Feb-2020 14:34:08
//

// Include Files
#include <string.h>
#include "rt_nonfinite.h"
#include "minSnap.h"
#include "computeQ.h"
#include "prod.h"
#include "polys_vals.h"
#include "minSnap_rtwutil.h"

// Function Definitions

//
// Arguments    : double t1
//                double t2
//                double Q[64]
// Return Type  : void
//
void computeQ(double t1, double t2, double Q[64])
{
  int i;
  double T[7];
  int j;
  int b_j;
  int k;
  int y_size[2];
  int b_y_size[2];
  double y_data[13];
  double b_y_data[13];

  //  n:polynormial order
  //  r:derivertive order, 1:minimum vel 2:minimum acc 3:minimum jerk 4:minimum snap 
  //  t1:start timestamp for polynormial
  //  t2:end timestap for polynormial
  for (i = 0; i < 7; i++) {
    T[i] = rt_powd_snf(t2, 1.0 + (double)i) - rt_powd_snf(t1, 1.0 + (double)i);
  }

  memset(&Q[0], 0, sizeof(double) << 6);
  for (j = 0; j < 4; j++) {
    b_j = j + 4;
    k = b_j - 3;
    y_size[0] = 1;
    y_size[1] = 4;
    for (i = 0; i < 4; i++) {
      y_data[i] = 1.0 + (double)i;
    }

    b_y_size[0] = 1;
    b_y_size[1] = 4;
    for (i = 0; i < 4; i++) {
      b_y_data[i] = (b_j + i) - 3;
    }

    i = (b_j << 3) + 4;
    Q[i] = prod(y_data, y_size) * prod(b_y_data, b_y_size) / (double)k * T[k - 1];
    Q[b_j + 32] = Q[i];
  }

  for (j = 0; j < 3; j++) {
    b_j = j + 5;
    k = b_j - 2;
    y_size[0] = 1;
    y_size[1] = 4;
    for (i = 0; i < 4; i++) {
      y_data[i] = 2.0 + (double)i;
    }

    b_y_size[0] = 1;
    b_y_size[1] = 4;
    for (i = 0; i < 4; i++) {
      b_y_data[i] = (b_j + i) - 3;
    }

    i = (b_j << 3) + 5;
    Q[i] = prod(y_data, y_size) * prod(b_y_data, b_y_size) / (double)k * T[k - 1];
    Q[b_j + 40] = Q[i];
  }

  for (j = 0; j < 2; j++) {
    b_j = j + 6;
    k = b_j - 1;
    y_size[0] = 1;
    y_size[1] = 4;
    for (i = 0; i < 4; i++) {
      y_data[i] = 3.0 + (double)i;
    }

    b_y_size[0] = 1;
    b_y_size[1] = 4;
    for (i = 0; i < 4; i++) {
      b_y_data[i] = (b_j + i) - 3;
    }

    i = (b_j << 3) + 6;
    Q[i] = prod(y_data, y_size) * prod(b_y_data, b_y_size) / (double)k * T[k - 1];
    Q[b_j + 48] = Q[i];
  }

  for (j = 0; j < 1; j++) {
    y_size[0] = 1;
    y_size[1] = 4;
    for (i = 0; i < 4; i++) {
      y_data[i] = 4.0 + (double)i;
    }

    b_y_size[0] = 1;
    b_y_size[1] = 4;
    for (i = 0; i < 4; i++) {
      b_y_data[i] = 4.0 + (double)i;
    }

    Q[63] = prod(y_data, y_size) * prod(b_y_data, b_y_size) / 7.0 * T[6];
  }
}

//
// File trailer for computeQ.cpp
//
// [EOF]
//
