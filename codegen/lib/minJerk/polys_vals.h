//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: polys_vals.h
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 10-Oct-2020 11:13:02
//
#ifndef POLYS_VALS_H
#define POLYS_VALS_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "minJerk_types.h"

// Function Declarations
extern void b_polys_vals(const emxArray_real_T *polys, const emxArray_real_T *ts,
  const emxArray_real_T *tt, emxArray_real_T *vals);
extern void c_polys_vals(const emxArray_real_T *polys, const emxArray_real_T *ts,
  const emxArray_real_T *tt, emxArray_real_T *vals);
extern void polys_vals(const emxArray_real_T *polys, const emxArray_real_T *ts,
  const emxArray_real_T *tt, emxArray_real_T *vals);

#endif

//
// File trailer for polys_vals.h
//
// [EOF]
//
