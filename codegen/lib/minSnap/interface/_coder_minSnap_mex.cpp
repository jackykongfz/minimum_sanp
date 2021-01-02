/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_minSnap_mex.cpp
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 11-Feb-2020 14:34:08
 */

/* Include Files */
#include "_coder_minSnap_api.h"
#include "_coder_minSnap_mex.h"

/* Function Declarations */
static void minSnap_mexFunction(int32_T nlhs, mxArray *plhs[10], int32_T nrhs,
  const mxArray *prhs[2]);

/* Function Definitions */

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[10]
 *                int32_T nrhs
 *                const mxArray *prhs[2]
 * Return Type  : void
 */
static void minSnap_mexFunction(int32_T nlhs, mxArray *plhs[10], int32_T nrhs,
  const mxArray *prhs[2])
{
  const mxArray *outputs[10];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4, 7,
                        "minSnap");
  }

  if (nlhs > 10) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 7,
                        "minSnap");
  }

  /* Call the function. */
  minSnap_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray * const plhs[]
 *                int32_T nrhs
 *                const mxArray * const prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(minSnap_atexit);

  /* Module initialization. */
  minSnap_initialize();

  /* Dispatch the entry-point. */
  minSnap_mexFunction(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  minSnap_terminate();
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/*
 * File trailer for _coder_minSnap_mex.cpp
 *
 * [EOF]
 */
