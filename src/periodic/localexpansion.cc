//
// BAGEL - Parallel electron correlation program.
// Filename: localexpansion.cc
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


#include <src/periodic/localexpansion.h>

using namespace std;
using namespace bagel;

const static Legendre plm;
const static Factorial f;

LocalExpansion::LocalExpansion(const array<double, 3> c, vector<complex<double>> m, const int lmax)
 : centre_(c), moments_(m), lmax_(lmax) {

  assert(m.size() == (lmax + 1) * (lmax + 1));
}


void LocalExpansion::compute_local_moments() {

  const double r = sqrt(centre_[0]*centre_[0] + centre_[1]*centre_[1] + centre_[2]*centre_[2]);
  const double theta = acos(centre_[2]/r);
  const double phi = atan2(centre_[1], centre_[0]);

  local_moments_.resize((lmax_ + 1) * (lmax_ + 1));

  int i1 = 0;
  for (int l = 0; l != lmax_; ++l) {
    for (int m = 0; m != 2 * l; ++m, ++i1) {

      int i2 = 0;
      for (int j = 0; j != lmax_; ++j) {
        for (int k = 0; j != 2 * j; ++k, ++i2) {
          const int a = l + j;
          const int b = m - l + k - j;
          const double prefactor = f(a - abs(b)) * plm.compute(a, abs(b), cos(theta)) / pow(r, a + 1);
          const double real = prefactor * cos(b * phi);
          const double imag = prefactor * sin(b * phi);
          complex<double> coeff(real, imag);

          local_moments_[i1] += coeff * moments_[i2];
        }
      }
    }
  }
}
