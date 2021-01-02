/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_minJerk_mex.cpp
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 10-Oct-2020 11:13:02
 */

/* Include Files */
#include "_coder_minJerk_api.h"
#include "_coder_minJerk_mex.h"

/* Function Declarations */
static void minJerk_mexFunction(int32_T nlhs, mxArray *plhs[10], int32_T nrhs,
  const mxArray *prhs[5]);

/* Function Definitions */

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[10]
 *                int32_T nrhs
 *                const mxArray *prhs[5]
 * Return Type  : void
 */
static void minJerk_mexFunction(int32_T nlhs, mxArray *plhs[10], int32_T nrhs,
  const mxArray *prhs[5])
{
  const mxArray *outputs[10];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 5) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 5, 4, 7,
                        "minJerk");
  }

  if (nlhs > 10) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 7,
                        "minJerk");
  }

  /* Call the function. */
  minJerk_api(prhs, nlhs, outputs);

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
  mexAtExit(minJerk_atexit);

  /* Module initialization. */
  minJerk_initialize();

  /* Dispatch the entry-point. */
  minJerk_mexFunction(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  minJerk_terminate();
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
 * File trailer for _coder_minJerk_mex.cpp
 *
 * [EOF]
 */
