//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: closeform.h
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 10-Oct-2020 11:13:02
//
#ifndef CLOSEFORM_H
#define CLOSEFORM_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "minJerk_types.h"

// Function Declarations
extern void closeform(const emxArray_real_T *new_waypts, const emxArray_real_T
                      *cons_waypts, double N_order, const emxArray_real_T *ts,
                      const emxArray_real_T *ts_smallsize, double optimize_order,
                      double continous_order, emxArray_real_T *polys_x,
                      emxArray_real_T *polys_y, emxArray_real_T *polys_z);

#endif

//
// File trailer for closeform.h
//
// [EOF]
//
