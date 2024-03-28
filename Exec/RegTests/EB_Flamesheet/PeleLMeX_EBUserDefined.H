#ifndef EBUSERDEFINED_H
#define EBUSERDEFINED_H

using namespace amrex;

#ifdef AMREX_USE_EB
#include <AMReX_EB2.H>
#include <AMReX_EB2_IF.H>
void
EBUserDefined(
  const Geometry& geom,
  const int required_coarsening_level,
  const int max_coarsening_level)
{
  // ParmParse your geometry parameters
  amrex::ParmParse pp("eb2");
  
  // Build geometry pieces using EB2::* methods
  RealArray b1_lo = {AMREX_D_DECL(-0.17,0.066,-0.01)};
  RealArray b1_hi = {AMREX_D_DECL(0.042,0.07,0.031)};
  RealArray b2_lo = {AMREX_D_DECL(0.012,0.032,-0.01)};
  RealArray b2_hi = {AMREX_D_DECL(0.09,0.036,0.031)};
  RealArray b3_lo = {AMREX_D_DECL(0.042,0.036,-0.01)};
  RealArray b3_hi = {AMREX_D_DECL(0.09,0.09,0.031)};
  RealArray b4_lo = {AMREX_D_DECL(-0.17,0.068,-0.01)};
  RealArray b4_hi = {AMREX_D_DECL(-0.12,0.1,0.031)};

  // EB upper tongue 
  EB2::BoxIF box1(b1_lo, b1_hi, false);
  // EB lower tongue
  EB2::BoxIF box2(b2_lo, b2_hi, false);
  // upper right box for substraction with half sphere
  EB2::BoxIF box3(b3_lo, b3_hi, false);
  // sphere
  Real radius = 0.022;
  Array<Real,AMREX_SPACEDIM> center{AMREX_D_DECL(0.042, 0.058,0.015)}; //Center of the sphere
  // EB inlet upper left box
  EB2::BoxIF box4(b4_lo, b4_hi, false);

#if AMREX_SPACEDIM == 2
  EB2::SphereIF sphere1(radius, center, true); //liquid inside sphere1

  auto halfSphere = EB2::makeIntersection(sphere1, box3);
#else
  EB2::CylinderIF cylinder1(radius, 100.0, 2, center, true);

  auto halfSphere = EB2::makeIntersection(cylinder1, box3);
#endif

  auto threeboxes = EB2::makeUnion(box1,box2,box4);
  auto EBprofile = EB2::makeUnion(threeboxes,halfSphere);

  // Build your geometry shop using EB2::makeShop
  auto gshop = EB2::makeShop(EBprofile);

  // Build geom using EB2::Build
  EB2::Build(gshop, geom, required_coarsening_level, max_coarsening_level);
}
#endif
#endif
