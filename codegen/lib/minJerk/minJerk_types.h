//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: minJerk_types.h
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 10-Oct-2020 11:13:02
//
#ifndef MINJERK_TYPES_H
#define MINJERK_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
struct emxArray_boolean_T
{
  boolean_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif

//
// File trailer for minJerk_types.h
//
// [EOF]
//
