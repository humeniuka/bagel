//
// BAGEL - Parallel electron correlation program.
// Filename: _s2vrr_drv.h
// Copyright (C) 2012 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// The BAGEL package is free software; you can redistribute it and\/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// The BAGEL package is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with the BAGEL package; see COPYING.  If not, write to
// the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
//

#ifndef __SRC_RYSINT____S2VRR_DRIVER_H
#define __SRC_RYSINT____S2VRR_DRIVER_H

#include <numeric>
#include <algorithm>
#include <array>
#include <src/rysint/int2d.h>
#include <src/rysint/scaledata.h>

namespace bagel {

template<int a_, int b_, int c_, int d_, int rank_>
void s2vrr_driver(double* out, const double* const roots, const double* const weights, const double& coeff,
                  const std::array<double,3>& a, const std::array<double,3>& b, const std::array<double,3>& c, const std::array<double,3>& d,
                  const double* const p, const double* const q, const double& xp, const double& xq, const size_t& size_block,
                  const int* const amap, const int* const cmap, const int& asize_, double* const workx, double* const worky, double* const workz,
                  double* const worktx, double* const workty, double* const worktz, double* const worksx, double* const worksy, double* const worksz) {

  const int amin_ = a_;
  const int cmin_ = c_;
  const int amax_ = a_+b_;
  const int cmax_ = c_+d_;
  const int amax1_ = amax_+1;
  const int cmax1_ = cmax_+1;
  const int amax2 = amax_+2;
  const int cmax2 = cmax_+2;
  const int isize = amax2 * cmax2;
  const int worksize = rank_ * isize;

  double iyiz_nn[rank_];
  double iyiz_tn[rank_];
  double iyiz_nt[rank_];
  double iyiz_tt[rank_];
  double iyiz_sn[rank_];
  double iyiz_ns[rank_];

  const double oxp2 = 0.5 / xp;
  const double oxq2 = 0.5 / xq;
  const double opq = 1.0 / (xp + xq);

  const double rho = xp*xq*opq;

  int2d<amax1_,cmax1_,rank_>(p[0], q[0], a[0], b[0], c[0], d[0], xp, xq, oxp2, oxq2, opq, roots, workx);
  scaledata<rank_, worksize>(workx, weights, coeff*rho*rho*4.0/3.0, workx);

  int2d<amax1_,cmax1_,rank_>(p[1], q[1], a[1], b[1], c[1], d[1], xp, xq, oxp2, oxq2, opq, roots, worky);
  int2d<amax1_,cmax1_,rank_>(p[2], q[2], a[2], b[2], c[2], d[2], xp, xq, oxp2, oxq2, opq, roots, workz);


  const double pq[3] = {p[0]-q[0], p[1]-q[1], p[2]-q[2]};
  const double ac[3] = {a[0]-c[0], a[1]-c[1], a[2]-c[2]};

  // next compute \\tidle{I}_x,y,z up to amax_, cmax_
  for (int ic = 0; ic <= cmax1_; ++ic)
    for (int ia = 0; ia <= amax1_; ++ia)
      for (int i = 0; i != rank_; ++i) {
        worktx[i+rank_*(ia+amax2*ic)] = pq[0]*workx[i+rank_*(ia+amax2*ic)] + (ia==0 ? 0.0 : ia*oxp2*workx[i+rank_*(ia-1+amax2*ic)]) - (ic==0 ? 0.0 : ic*oxq2*workx[i+rank_*(ia+amax2*(ic-1))]);
        workty[i+rank_*(ia+amax2*ic)] = pq[1]*worky[i+rank_*(ia+amax2*ic)] + (ia==0 ? 0.0 : ia*oxp2*worky[i+rank_*(ia-1+amax2*ic)]) - (ic==0 ? 0.0 : ic*oxq2*worky[i+rank_*(ia+amax2*(ic-1))]);
        worktz[i+rank_*(ia+amax2*ic)] = pq[2]*workz[i+rank_*(ia+amax2*ic)] + (ia==0 ? 0.0 : ia*oxp2*workz[i+rank_*(ia-1+amax2*ic)]) - (ic==0 ? 0.0 : ic*oxq2*workz[i+rank_*(ia+amax2*(ic-1))]);
      }
  // then compute \\tilde{\\tilde{I_x,y,z up to amax_-1, cmax_-1
  for (int ic = 0; ic != cmax1_; ++ic)
    for (int ia = 0; ia != amax1_; ++ia)
      for (int i = 0; i != rank_; ++i) {
        worksx[i+rank_*(ia+amax2*ic)] = worktx[i+rank_*((ia+1)+amax2*ic)] - worktx[i+rank_*(ia+amax2*(ic+1))] + ac[0]*worktx[i+rank_*(ia+amax2*ic)];
        worksy[i+rank_*(ia+amax2*ic)] = workty[i+rank_*((ia+1)+amax2*ic)] - workty[i+rank_*(ia+amax2*(ic+1))] + ac[1]*workty[i+rank_*(ia+amax2*ic)];
        worksz[i+rank_*(ia+amax2*ic)] = worktz[i+rank_*((ia+1)+amax2*ic)] - worktz[i+rank_*(ia+amax2*(ic+1))] + ac[2]*worktz[i+rank_*(ia+amax2*ic)];
      }

  double* const dataxx = out;
  double* const dataxy = dataxx + size_block;
  double* const dataxz = dataxy + size_block;
  double* const datayy = dataxz + size_block;
  double* const datayz = dataxz + size_block;
  double* const datazz = datayz + size_block;

  // assemble up to amax_, cmax_
  for (int iz = 0; iz <= cmax_; ++iz) {
    for (int iy = 0; iy <= cmax_ - iz; ++iy) {
      for (int jz = 0; jz <= amax_; ++jz) {
        for (int jy = 0; jy <= amax_ - jz; ++jy) {
          const int offsetz = rank_ * (amax2 * iz + jz);
          const int offsety = rank_ * (amax2 * iy + jy);
          const int iyz = cmax1_ * (iy + cmax1_ * iz);
          const int jyz = amax1_ * (jy + amax1_ * jz);
          for (int i = 0; i != rank_; ++i) {
            const double fac = 1.0 / (1.0-roots[i]);
            iyiz_nn[i] = worky [offsety + i] * workz [offsetz + i] * fac; 
            iyiz_tn[i] = workty[offsety + i] * workz [offsetz + i];
            iyiz_nt[i] = worky [offsety + i] * worktz[offsetz + i];
            iyiz_tt[i] = workty[offsety + i] * worktz[offsetz + i];
            iyiz_sn[i] = worksy[offsety + i] * workz [offsetz + i] * fac; 
            iyiz_ns[i] = worky [offsety + i] * worksz[offsetz + i] * fac; 
          }
          for (int ix = std::max(0, cmin_ - iy - iz); ix <= cmax_ - iy - iz; ++ix) {
            const int iposition = cmap[ix + iyz];
            const int ipos_asize = iposition * asize_;
            for (int jx = std::max(0, amin_ - jy - jz); jx <= amax_ - jy - jz; ++jx) {
              const int offsetx = rank_ * (amax2 * ix + jx);
              const int jposition = amap[jx + jyz];
              const int ijposition = jposition + ipos_asize;
              const double xx = std::inner_product(iyiz_nn, iyiz_nn+rank_, worksx+offsetx, 0.0);
              const double yy = std::inner_product(iyiz_sn, iyiz_sn+rank_, workx +offsetx, 0.0); 
              const double zz = std::inner_product(iyiz_ns, iyiz_ns+rank_, workx +offsetx, 0.0);
              dataxx[ijposition] = 2.0*xx - yy - zz;
              dataxy[ijposition] = std::inner_product(iyiz_tn, iyiz_tn+rank_, worktx+offsetx, 0.0);
              dataxz[ijposition] = std::inner_product(iyiz_nt, iyiz_nt+rank_, worktx+offsetx, 0.0);
              datayy[ijposition] = 2.0*yy - zz - xx; 
              datayz[ijposition] = std::inner_product(iyiz_tt, iyiz_tt+rank_, workx +offsetx, 0.0);
              datazz[ijposition] = 2.0*zz - xx - yy; 
            }
          }
        }
      }
    }
  }

}

}

#endif