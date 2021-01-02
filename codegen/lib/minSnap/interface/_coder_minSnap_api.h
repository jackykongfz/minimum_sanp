/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_minSnap_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 11-Feb-2020 14:34:08
 */

#ifndef _CODER_MINSNAP_API_H
#define _CODER_MINSNAP_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_minSnap_api.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void minSnap(emxArray_real_T *waypts_noatti, emxArray_real_T *waypts_atti,
                    emxArray_real_T *tt, emxArray_real_T *xx, emxArray_real_T
                    *yy, emxArray_real_T *zz, emxArray_real_T *vx,
                    emxArray_real_T *vy, emxArray_real_T *vz, emxArray_real_T
                    *ax, emxArray_real_T *ay, emxArray_real_T *az);
extern void minSnap_api(const mxArray * const prhs[2], int32_T nlhs, const
  mxArray *plhs[10]);
extern void minSnap_atexit(void);
extern void minSnap_initialize(void);
extern void minSnap_terminate(void);
extern void minSnap_xil_terminate(void);

#endif

/*
 * File trailer for _coder_minSnap_api.h
 *
 * [EOF]
 */
