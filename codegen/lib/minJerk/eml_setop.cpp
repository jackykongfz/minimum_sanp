//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: eml_setop.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 10-Oct-2020 11:13:02
//

// Include Files
#include <math.h>
#include "rt_nonfinite.h"
#include "minJerk.h"
#include "eml_setop.h"
#include "minJerk_emxutil.h"

// Function Declarations
static double skip_to_last_equal_value(int *k, const emxArray_real_T *x);

// Function Definitions

//
// Arguments    : int *k
//                const emxArray_real_T *x
// Return Type  : double
//
static double skip_to_last_equal_value(int *k, const emxArray_real_T *x)
{
  double xk;
  boolean_T exitg1;
  double absxk;
  int exponent;
  xk = x->data[*k - 1];
  exitg1 = false;
  while ((!exitg1) && (*k < x->size[1])) {
    absxk = fabs(xk / 2.0);
    if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
      if (absxk <= 2.2250738585072014E-308) {
        absxk = 4.94065645841247E-324;
      } else {
        frexp(absxk, &exponent);
        absxk = ldexp(1.0, exponent - 53);
      }
    } else {
      absxk = rtNaN;
    }

    if ((fabs(xk - x->data[*k]) < absxk) || (rtIsInf(x->data[*k]) && rtIsInf(xk)
         && ((x->data[*k] > 0.0) == (xk > 0.0)))) {
      (*k)++;
    } else {
      exitg1 = true;
    }
  }

  return xk;
}

//
// Arguments    : const emxArray_real_T *a
//                const emxArray_real_T *b
//                emxArray_real_T *c
//                emxArray_int32_T *ia
//                int ib_size[1]
// Return Type  : void
//
void do_vectors(const emxArray_real_T *a, const emxArray_real_T *b,
                emxArray_real_T *c, emxArray_int32_T *ia, int ib_size[1])
{
  int na;
  unsigned int unnamed_idx_1;
  int iafirst;
  int nc;
  int nia;
  int ialast;
  int iblast;
  int b_ialast;
  double ak;
  double bk;
  boolean_T exitg1;
  double r;
  int exponent;
  int b_exponent;
  boolean_T b0;
  na = a->size[1];
  unnamed_idx_1 = (unsigned int)a->size[1];
  iafirst = c->size[0] * c->size[1];
  c->size[0] = 1;
  c->size[1] = (int)unnamed_idx_1;
  emxEnsureCapacity_real_T(c, iafirst);
  iafirst = ia->size[0];
  ia->size[0] = a->size[1];
  emxEnsureCapacity_int32_T(ia, iafirst);
  ib_size[0] = 0;
  nc = 0;
  nia = 0;
  iafirst = 0;
  ialast = 1;
  iblast = 1;
  while ((ialast <= na) && (iblast <= b->size[0])) {
    b_ialast = ialast;
    ak = skip_to_last_equal_value(&b_ialast, a);
    ialast = b_ialast;
    bk = b->data[iblast - 1];
    exitg1 = false;
    while ((!exitg1) && (iblast < b->size[0])) {
      r = fabs(bk / 2.0);
      if ((!rtIsInf(r)) && (!rtIsNaN(r))) {
        if (r <= 2.2250738585072014E-308) {
          r = 4.94065645841247E-324;
        } else {
          frexp(r, &b_exponent);
          r = ldexp(1.0, b_exponent - 53);
        }
      } else {
        r = rtNaN;
      }

      if ((fabs(bk - b->data[iblast]) < r) || (rtIsInf(b->data[iblast]) &&
           rtIsInf(bk) && ((b->data[iblast] > 0.0) == (bk > 0.0)))) {
        iblast++;
      } else {
        exitg1 = true;
      }
    }

    r = fabs(bk / 2.0);
    if ((!rtIsInf(r)) && (!rtIsNaN(r))) {
      if (r <= 2.2250738585072014E-308) {
        r = 4.94065645841247E-324;
      } else {
        frexp(r, &exponent);
        r = ldexp(1.0, exponent - 53);
      }
    } else {
      r = rtNaN;
    }

    if ((fabs(bk - ak) < r) || (rtIsInf(ak) && rtIsInf(bk) && ((ak > 0.0) == (bk
           > 0.0)))) {
      ialast = b_ialast + 1;
      iafirst = b_ialast;
      iblast++;
    } else {
      if (rtIsNaN(bk)) {
        b0 = !rtIsNaN(ak);
      } else {
        b0 = ((!rtIsNaN(ak)) && (ak < bk));
      }

      if (b0) {
        nc++;
        nia++;
        c->data[nc - 1] = ak;
        ia->data[nia - 1] = iafirst + 1;
        ialast = b_ialast + 1;
        iafirst = b_ialast;
      } else {
        iblast++;
      }
    }
  }

  while (ialast <= na) {
    iafirst = ialast;
    ak = skip_to_last_equal_value(&iafirst, a);
    nc++;
    nia++;
    c->data[nc - 1] = ak;
    ia->data[nia - 1] = ialast;
    ialast = iafirst + 1;
  }

  if (a->size[1] > 0) {
    if (1 > nia) {
      ia->size[0] = 0;
    } else {
      iafirst = ia->size[0];
      ia->size[0] = nia;
      emxEnsureCapacity_int32_T(ia, iafirst);
    }

    if (1 > nc) {
      c->size[1] = 0;
    } else {
      iafirst = c->size[0] * c->size[1];
      c->size[1] = nc;
      emxEnsureCapacity_real_T(c, iafirst);
    }
  }
}

//
// File trailer for eml_setop.cpp
//
// [EOF]
//
