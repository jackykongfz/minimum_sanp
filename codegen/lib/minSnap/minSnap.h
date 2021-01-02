//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: minSnap.h
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 11-Feb-2020 14:34:08
//
#ifndef MINSNAP_H
#define MINSNAP_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "minSnap_types.h"

// Function Declarations
extern void minSnap(const emxArray_real_T *waypts_noatti, const emxArray_real_T *
                    waypts_atti, emxArray_real_T *tt, emxArray_real_T *xx,
                    emxArray_real_T *yy, emxArray_real_T *zz, emxArray_real_T
                    *vx, emxArray_real_T *vy, emxArray_real_T *vz,
                    emxArray_real_T *ax, emxArray_real_T *ay, emxArray_real_T
                    *az);

#endif

//
// File trailer for minSnap.h
//
// [EOF]
//
