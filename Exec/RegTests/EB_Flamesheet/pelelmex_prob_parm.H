#ifndef PELELM_PROB_PARM_H
#define PELELM_PROB_PARM_H

#include <AMReX_REAL.H>

using namespace amrex::literals;

struct ProbParm
{
  // Shared params
  amrex::Real P_mean = 101325.0_rt;
  amrex::Real T_input = 300.0_rt;
  bool is_reactive = false;
  //amrex::Real Y_fuel = 0.0445_rt;
  //amrex::Real Y_o2 = 0.223_rt;
  amrex::Real T_hot = 1800.0_rt;
  //amrex::Real Twall = 300.0_rt;
  amrex::Real meanFlowMag = 0.0;
  amrex::Real EBinflow_vel = 1.0_rt;
  amrex::Real EBinflow_T = 300.0_rt;
  amrex::Real EB_isoTwall = 300.0_rt;
};
#endif
