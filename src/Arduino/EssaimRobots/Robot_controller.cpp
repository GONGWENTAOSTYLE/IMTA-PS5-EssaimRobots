/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Robot_controller.c
 *
 * Code generated for Simulink model 'decouplante'.
 *
 * Model version                  : 1.12
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Wed Feb 16 20:57:46 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Robot_controller.h"

/* System initialize for atomic system: '<Root>/Robot_controller' */
void decouplan_Robot_controller_Init(DW_Robot_controller_decouplan_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE = 2.0;
}

/* Output and update for atomic system: '<Root>/Robot_controller' */
void decouplante_Robot_controller(real32_T rtu_x_ref, real32_T rtu_y_ref, real32_T
  rtu_x_feedback, real32_T rtu_y_feedback, real32_T rtu_theta, real32_T rtu_v_center, real32_T Ts,
  real32_T *rty_Vd, real32_T *rty_Vg, DW_Robot_controller_decouplan_T *localDW)
{
  real32_T rtb_Product;
  real32_T rtb_Sum;
  real32_T rtb_FilterCoefficient;
  real32_T rtb_Sum1;
  real32_T rtb_FilterCoefficient_l;
  real32_T rtb_Sum_o;
  real32_T rtb_Sum_l;
  real32_T rtb_Product_tmp;
  real32_T rtb_Product_tmp_0;

  /* Saturate: '<S1>/Saturation1' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   */
  if (localDW->DiscreteTimeIntegrator_DSTATE > Vm) {
    *rty_Vg = Vm;
  } else if (localDW->DiscreteTimeIntegrator_DSTATE < -Vm) {
    *rty_Vg = -Vm;
  } else {
    *rty_Vg = localDW->DiscreteTimeIntegrator_DSTATE;
  }

  /* End of Saturate: '<S1>/Saturation1' */

  /* Sum: '<S1>/Sum' */
  rtb_Sum = rtu_x_ref - rtu_x_feedback;

  /* Gain: '<S36>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S28>/Filter'
   *  Gain: '<S27>/Derivative Gain'
   *  Sum: '<S28>/SumD'
   */
  rtb_FilterCoefficient = (D_t * rtb_Sum - localDW->Filter_DSTATE) * N_t;

  /* Sum: '<S42>/Sum' incorporates:
   *  DiscreteIntegrator: '<S33>/Integrator'
   *  Gain: '<S38>/Proportional Gain'
   */
  rtb_Sum_o = (P_t * rtb_Sum + localDW->Integrator_DSTATE) +
    rtb_FilterCoefficient;

  /* Sum: '<S1>/Sum1' */
  rtb_Sum1 = rtu_y_ref - rtu_y_feedback;

  /* Gain: '<S80>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S72>/Filter'
   *  Gain: '<S71>/Derivative Gain'
   *  Sum: '<S72>/SumD'
   */
  rtb_FilterCoefficient_l = (D_t * rtb_Sum1 - localDW->Filter_DSTATE_c) * N_t;

  /* Sum: '<S86>/Sum' incorporates:
   *  DiscreteIntegrator: '<S77>/Integrator'
   *  Gain: '<S82>/Proportional Gain'
   */
  rtb_Sum_l = (P_t * rtb_Sum1 + localDW->Integrator_DSTATE_g) +
    rtb_FilterCoefficient_l;

  /* Fcn: '<S1>/linearisation calcul u2' incorporates:
   *  Fcn: '<S1>/linearisation calcul u1'
   */
  rtb_Product_tmp = cos(rtu_theta);
  rtb_Product_tmp_0 = sin(rtu_theta);

  /* Product: '<S1>/Product' incorporates:
   *  Constant: '<S1>/L//2'
   *  Fcn: '<S1>/linearisation calcul u2'
   */
  rtb_Product = (-rtb_Product_tmp_0 / rtu_v_center * rtb_Sum_o + rtb_Product_tmp
                 / rtu_v_center * rtb_Sum_l) * (L / 2.0);

  /* Sum: '<S1>/Sum2' */
  *rty_Vd = *rty_Vg + rtb_Product;

  /* Sum: '<S1>/Sum3' */
  *rty_Vg -= rtb_Product;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' incorporates:
   *  Fcn: '<S1>/linearisation calcul u1'
   */
  localDW->DiscreteTimeIntegrator_DSTATE += (rtb_Product_tmp * rtb_Sum_o +
    rtb_Product_tmp_0 * rtb_Sum_l) * Ts;

  /* Update for DiscreteIntegrator: '<S33>/Integrator' incorporates:
   *  Gain: '<S30>/Integral Gain'
   */
  localDW->Integrator_DSTATE += I_t * rtb_Sum * Ts;

  /* Update for DiscreteIntegrator: '<S28>/Filter' */
  localDW->Filter_DSTATE += Ts * rtb_FilterCoefficient;

  /* Update for DiscreteIntegrator: '<S77>/Integrator' incorporates:
   *  Gain: '<S74>/Integral Gain'
   */
  localDW->Integrator_DSTATE_g += I_t * rtb_Sum1 * Ts;

  /* Update for DiscreteIntegrator: '<S72>/Filter' */
  localDW->Filter_DSTATE_c += Ts * rtb_FilterCoefficient_l;
}
