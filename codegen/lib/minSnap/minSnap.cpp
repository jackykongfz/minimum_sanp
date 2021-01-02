//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: minSnap.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 11-Feb-2020 14:34:08
//

// Include Files
#include <cmath>
#include "rt_nonfinite.h"
#include "minSnap.h"
#include "minSnap_emxutil.h"
#include "polys_vals.h"
#include "closeform.h"
#include "arrangeTbydist.h"
#include "generate_corridor.h"

// Function Definitions

//
// % waypoints without attitude constraints
//  % first element is the sequence number of the waypoint
//  % can be empty 3 4 0 0 3 3.0 -0.5 0.5
//  waypts_noatti = [2 2 -1 0]';
//
//  % waypoints with attitude constraints(first element is the sequence number of the waypoint)
//  waypts_atti = [1 0.0 0.0 0.0 1.0 0.0 0.0 0.0;
//                 %2 2.0 -1 1.0 0.7090        0.7053     0         0;
//                 %2 2.0 -1.0 1.0 0.8660       0.5000      0         0;
//                 %2 2.0 -1.0 1.0 0.9239    0.3827         0         0;
//                 %2 2 -1 0 0.9990    0.0436         0         0;
//                 4 4.0 0.0 0.0 1.0 0.0 0.0 0.0]';
// Arguments    : const emxArray_real_T *waypts_noatti
//                const emxArray_real_T *waypts_atti
//                emxArray_real_T *tt
//                emxArray_real_T *xx
//                emxArray_real_T *yy
//                emxArray_real_T *zz
//                emxArray_real_T *vx
//                emxArray_real_T *vy
//                emxArray_real_T *vz
//                emxArray_real_T *ax
//                emxArray_real_T *ay
//                emxArray_real_T *az
// Return Type  : void
//
void minSnap(const emxArray_real_T *waypts_noatti, const emxArray_real_T
             *waypts_atti, emxArray_real_T *tt, emxArray_real_T *xx,
             emxArray_real_T *yy, emxArray_real_T *zz, emxArray_real_T *vx,
             emxArray_real_T *vy, emxArray_real_T *vz, emxArray_real_T *ax,
             emxArray_real_T *ay, emxArray_real_T *az)
{
  emxArray_real_T *ts;
  emxArray_real_T *ts_smallsize;
  emxArray_real_T *cons_waypts;
  emxArray_real_T *new_waypts;
  emxArray_real_T *polys_x;
  emxArray_real_T *polys_y;
  emxArray_real_T *polys_z;
  int nm1d2;
  double ndbl;
  double apnd;
  double cdiff;
  int n;
  int k;
  emxInit_real_T(&ts, 2);
  emxInit_real_T(&ts_smallsize, 2);
  emxInit_real_T(&cons_waypts, 2);
  emxInit_real_T(&new_waypts, 2);
  emxInit_real_T(&polys_x, 2);
  emxInit_real_T(&polys_y, 2);
  emxInit_real_T(&polys_z, 2);

  //  20200102 Minimum Snap programmed by jacky.kong
  //  waypts_atti = [1 0.0 0.0 0.0 1.0 0.0 0.0 0.0;
  //                 2 4.0 0.0 0.0 1.0 0.0 0.0 0.0]';
  //  start state and final state
  //  declaration
  //  4snap , 3jerk
  //  generate corridor
  generate_corridor(waypts_noatti, waypts_atti, cons_waypts, new_waypts);

  //  constant velocity time allocation
  arrangeTbydist(new_waypts, ts);
  arrangeTbydist(cons_waypts, ts_smallsize);

  //  generate trajectory
  // [polys_x polys_y polys_z] = SE3byaccel(new_waypts,waypts_atti,cons_waypts,N_order,ts,ts_smallsize,v0,v_end,corridor_r,flag_corridor,optimize_order,continous_order); 
  closeform(new_waypts, cons_waypts, ts, ts_smallsize, polys_x, polys_y, polys_z);
  emxFree_real_T(&new_waypts);
  emxFree_real_T(&cons_waypts);
  emxFree_real_T(&ts_smallsize);
  if (rtIsNaN(ts->data[ts->size[1] - 1])) {
    nm1d2 = tt->size[0] * tt->size[1];
    tt->size[0] = 1;
    tt->size[1] = 1;
    emxEnsureCapacity_real_T(tt, nm1d2);
    tt->data[0] = rtNaN;
  } else if (ts->data[ts->size[1] - 1] < 0.0) {
    tt->size[0] = 1;
    tt->size[1] = 0;
  } else if (rtIsInf(ts->data[ts->size[1] - 1]) && (0.0 == ts->data[ts->size[1]
              - 1])) {
    nm1d2 = tt->size[0] * tt->size[1];
    tt->size[0] = 1;
    tt->size[1] = 1;
    emxEnsureCapacity_real_T(tt, nm1d2);
    tt->data[0] = rtNaN;
  } else {
    ndbl = std::floor(ts->data[ts->size[1] - 1] / 0.01 + 0.5);
    apnd = ndbl * 0.01;
    cdiff = apnd - ts->data[ts->size[1] - 1];
    if (std::abs(cdiff) < 4.4408920985006262E-16 * std::abs(ts->data[ts->size[1]
         - 1])) {
      ndbl++;
      apnd = ts->data[ts->size[1] - 1];
    } else if (cdiff > 0.0) {
      apnd = (ndbl - 1.0) * 0.01;
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }

    nm1d2 = tt->size[0] * tt->size[1];
    tt->size[0] = 1;
    tt->size[1] = n;
    emxEnsureCapacity_real_T(tt, nm1d2);
    if (n > 0) {
      tt->data[0] = 0.0;
      if (n > 1) {
        tt->data[n - 1] = apnd;
        nm1d2 = (n - 1) / 2;
        for (k = 0; k <= nm1d2 - 2; k++) {
          ndbl = (1.0 + (double)k) * 0.01;
          tt->data[1 + k] = ndbl;
          tt->data[(n - k) - 2] = apnd - ndbl;
        }

        if (nm1d2 << 1 == n - 1) {
          tt->data[nm1d2] = apnd / 2.0;
        } else {
          ndbl = (double)nm1d2 * 0.01;
          tt->data[nm1d2] = ndbl;
          tt->data[nm1d2 + 1] = apnd - ndbl;
        }
      }
    }
  }

  //  ts_smallsize = ts;
  polys_vals(polys_x, ts, tt, xx);
  polys_vals(polys_y, ts, tt, yy);
  polys_vals(polys_z, ts, tt, zz);
  b_polys_vals(polys_x, ts, tt, vx);
  b_polys_vals(polys_y, ts, tt, vy);
  b_polys_vals(polys_z, ts, tt, vz);
  c_polys_vals(polys_x, ts, tt, ax);
  c_polys_vals(polys_y, ts, tt, ay);
  c_polys_vals(polys_z, ts, tt, az);
  emxFree_real_T(&polys_z);
  emxFree_real_T(&polys_y);
  emxFree_real_T(&polys_x);
  emxFree_real_T(&ts);
}

//
// File trailer for minSnap.cpp
//
// [EOF]
//
