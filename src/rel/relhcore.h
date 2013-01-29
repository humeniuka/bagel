//
// BAGEL - Parallel electron correlation program.
// Filename: relhcore.h
// Copyright (C) 2012 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// The BAGEL package is free software; you can redistribute it and/or modify
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


#ifndef __SRC_REL_RELHCORE_H
#define __SRC_REL_RELHCORE_H

#include <src/wfn/geometry.h>
#include <src/scf/hcore.h>
#include <src/scf/kinetic.h>
#include <src/util/matrix.h>
#include <src/util/zmatrix.h>
#include <src/rel/smallnai.h>
#include <src/util/input.h>

namespace bagel {

class RelHcore : public ZMatrix {
  protected:
    const std::shared_ptr<const Geometry> geom_;
    const std::shared_ptr<const Matrix> kinetic_;
    const std::shared_ptr<const Matrix> hcore_;
    const std::shared_ptr<const Matrix> nai_;
    const std::shared_ptr<const SmallNAI> smallnai_;

    void compute_();

  public:
    RelHcore(const std::shared_ptr<const Geometry> geom) : ZMatrix(geom->nbasis()*4, geom->nbasis()*4), geom_(geom),
            kinetic_(new Kinetic(geom_)), hcore_(new Hcore(geom_)), nai_(new Matrix(*hcore_ - *kinetic_)), smallnai_(new SmallNAI(geom_)) {

      compute_();

    }

    ~RelHcore() {};
};

}

#endif