//
// BAGEL - Parallel electron correlation program.
// Filename: rotfile.h
// Copyright (C) 2011 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
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


#ifndef __BAGEL_CASSCF_ROTFILE_H
#define __BAGEL_CASSCF_ROTFILE_H

#include <src/math/matrix.h>

namespace bagel {

class RotFile {
  protected:
    const int nclosed_;
    const int nact_;
    const int nvirt_;
    const bool superci_;
    const int size_;
    std::unique_ptr<double[]> data_;

  public:
    RotFile(const int iclos, const int iact, const int ivirt, const bool superci = true)
     : nclosed_(iclos), nact_(iact), nvirt_(ivirt), superci_(superci), size_(iclos*iact+iclos*ivirt+iact*ivirt+(superci ? 1 : 0)), data_(new double[size_]) {
      zero();
    }
    RotFile(const RotFile& o) : nclosed_(o.nclosed_), nact_(o.nact_), nvirt_(o.nvirt_), superci_(o.superci_), size_(o.size_), data_(new double[o.size_]) {
      *this = o;
    }
    RotFile(std::shared_ptr<const RotFile> o)
      : nclosed_(o->nclosed_), nact_(o->nact_), nvirt_(o->nvirt_), superci_(o->superci_), size_(o->size_), data_(new double[o->size_]) {
      *this = *o;
    }
    RotFile(std::shared_ptr<const Matrix> o, const int iclos, const int iact, const int ivirt, const bool superci = true);

    std::shared_ptr<RotFile> clone() const;
    std::shared_ptr<RotFile> copy() const;

    // overloaded operators
    RotFile operator+(const RotFile& o) const { RotFile out(*this); out.ax_plus_y(1.0, o); return out; }
    RotFile operator-(const RotFile& o) const { RotFile out(*this); out.ax_plus_y(-1.0, o); return out; }
    RotFile& operator+=(const RotFile& o) { ax_plus_y(1.0, o); return *this; }
    RotFile& operator-=(const RotFile& o) { ax_plus_y(-1.0, o); return *this; }
    RotFile& operator*=(const double a) { dscal_(size_, a, data_.get(), 1); return *this; }
    RotFile& operator/=(const RotFile& o) { for (int i = 0; i != size(); ++i) data(i)/= o.data(i); return *this; }
    RotFile operator/(const RotFile& o) const { RotFile out(*this); return out /= o; }
    RotFile& operator=(const RotFile& o) { std::copy_n(o.data(), size(), data());  return *this; }

    // size of the file
    int size() const { return size_; }
    // zero out
    void zero() { fill(0.0); }
    void fill(const double a) { std::fill_n(data(), size_, a); }
    // returns dot product
    double dot_product(const RotFile& o) const { return ddot_(size_, data(), 1, o.data(), 1); }
    double dot_product(const std::shared_ptr<const RotFile> o) const { return dot_product(*o); }
    // returns norm of the vector
    double norm() const { return std::sqrt(dot_product(*this)); }
    // daxpy added to self
    void ax_plus_y(double a, const RotFile& o) { daxpy_(size_, a, o.data(), 1, data(), 1); }
    void ax_plus_y(double a, const std::shared_ptr<const RotFile> o) { ax_plus_y(a, *o); }
    // orthogonalize to the liset of RotFile's
    double orthog(std::list<std::shared_ptr<const RotFile>> c);

    // return data_
    double* data() { return data_.get(); }
    const double* data() const { return data_.get(); }
    double& data(const size_t i) { return data_[i]; }
    const double& data(const size_t i) const { return data_[i]; }
    // return data_
    double* begin() { return data(); }
    // return data_
    double* end() { return data()+size_; }

    // closed-active block. closed runs first
    double* ptr_ca() { return data(); }
    double& ele_ca(const int ic, const int ia) { return data_[ic + ia*nclosed_]; }
    // active-virtual block. virtual runs first
    double* ptr_va() { return data() + nclosed_*nact_; }
    double& ele_va(const int iv, const int ia) { return data_[nclosed_*nact_ + iv + ia*nvirt_]; }
    // closed-virtual block. virtual runs first
    double* ptr_vc() { return data() + (nclosed_+nvirt_)*nact_; }
    double& ele_vc(const int iv, const int ic) { return data_[(nclosed_+nvirt_)*nact_ + iv + ic*nvirt_]; }
    // reference config.
    double& ele_ref() { assert(superci_); return data_[size_-1]; }
    // const references
    const double& ele_ca(const int ic, const int ia) const { return data_[ic + ia*nclosed_]; }
    const double& ele_va(const int iv, const int ia) const { return data_[nclosed_*nact_ + iv + ia*nvirt_]; }
    const double& ele_vc(const int iv, const int ic) const { return data_[(nclosed_+nvirt_)*nact_ + iv + ic*nvirt_]; }
    const double& ele_ref() const { assert(superci_); return data_[size_-1]; }

    // unpack to Matrix
    std::shared_ptr<Matrix> unpack(const double a = 0.0) const;
    std::shared_ptr<Matrix> unpack_sym(const double a = 0.0) const;

    // print matrix
    void print() const;
};


}

#endif
