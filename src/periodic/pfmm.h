//
// BAGEL - Parallel electron correlation program.
// Filename: pfmm.h
// Copyright (C) 2015 Toru Shiozaki
//
// Author: Hai-Anh Le <anh@u.northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// The BAGEL package is free software; you can redistribute it and/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
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


#ifndef __SRC_PERIODIC_PFMM_H
#define __SRC_PERIODIC_PFMM_H

#include <src/periodic/simulationcell.h>
#include <src/periodic/pdata.h>

namespace bagel {

class PFMM {
  protected:
    std::shared_ptr<const SimulationCell> scell_;
    int lmax_, ws_;
    int ndim_;
    int num_multipoles_;
    std::vector<std::complex<double>> mlm_;

  public:
    PFMM(std::shared_ptr<const SimulationCell>, const int lmax = ANG_HRR_END, const int ws = 2, const double thresh = PRIM_SCREEN_THRESH);
    ~PFMM() { }

    std::vector<std::complex<double>> mlm() const { return mlm_; }

    bool is_in_cff(std::array<double, 3> lvector);
    void compute_mlm(const int limit = 100, const double thresh = PRIM_SCREEN_THRESH);
    void compute_Sn(const double thresh = PRIM_SCREEN_THRESH, const int max_iter = 20);
    std::shared_ptr<PData> compute_Jop(std::shared_ptr<const PData> density);

};

}

#endif
