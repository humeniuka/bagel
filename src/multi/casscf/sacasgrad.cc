//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: supercigrad.cc
// Copyright (C) 2012 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//


#include <src/multi/casscf/superci.h>
#include <src/multi/casscf/cassecond.h>
#include <src/multi/casscf/casbfgs.h>
#include <src/multi/casscf/casnoopt.h>
#include <src/grad/gradeval.h>
#include <src/grad/cpcasscf.h>
#include <src/prop/multipole.h>

using namespace std;
using namespace bagel;

template<>
void GradEval<CASSCF>::init() {
  if (geom_->external())
    throw logic_error("Gradients with external fields have not been implemented.");
  // target has to be passed to T (for CASPT2, for instance)
  auto idata_out = make_shared<PTree>(*idata_);
  idata_out->put("_target", target_state_);

  const string algorithm = idata_out->get<string>("algorithm", "");
  const string bfgstype = idata_out->get<string>("bfgstype", "");

  if (algorithm == "superci")
    task_ = make_shared<SuperCI>(idata_out, geom_, ref_);
  else if (algorithm == "second" || algorithm == "")
    task_ = make_shared<CASSecond>(idata_out, geom_, ref_);
  else if (algorithm == "bfgs" && bfgstype != "alglib")
    task_ = make_shared<CASBFGS1>(idata_out, geom_, ref_);
  else if (algorithm == "bfgs" && bfgstype == "alglib")
    task_ = make_shared<CASBFGS2>(idata_out, geom_, ref_);
  else if (algorithm == "noopt")
    task_ = make_shared<CASNoopt>(idata_out, geom_, ref_);
  else
    throw runtime_error("unknown CASSCF algorithm specified: " + algorithm);

  task_->compute();
  ref_  = task_->conv_to_ref();
  energy_ = ref_->energy(target_state_);
  geom_ = ref_->geom();
}


template<>
shared_ptr<GradFile> GradEval<CASSCF>::compute() {
  Timer timer;
  shared_ptr<GradFile> gradient;
  // if single state calculation, we use specialized code
  if (ref_->nstate() == 1) {
    //- One ELECTRON PART -//
    const MatView coeff_occ = ref_->coeff()->slice(0,ref_->nocc());
    shared_ptr<const Matrix> rdm1 = make_shared<Matrix>(coeff_occ * *ref_->rdm1_mat() ^ coeff_occ);
    shared_ptr<const Matrix> erdm1 = ref_->erdm1();

    //- TWO ELECTRON PART -//
    shared_ptr<const DFHalfDist> half = geom_->df()->compute_half_transform(coeff_occ);
    shared_ptr<const DFFullDist> qij  = half->compute_second_transform(coeff_occ)->apply_JJ();
    shared_ptr<const DFFullDist> qijd = qij->apply_2rdm(*ref_->rdm2(0), *ref_->rdm1(0), ref_->nclosed(), ref_->nact());
    shared_ptr<const Matrix> qq  = qij->form_aux_2index(qijd, 1.0);
    shared_ptr<const DFDist> qrs = qijd->back_transform(coeff_occ)->back_transform(coeff_occ);

    gradient = contract_gradient(rdm1, erdm1, qrs, qq);

  } else {
    shared_ptr<const Coeff> coeff = ref_->coeff();
    assert(task_->coeff() == coeff);

    const int nclosed = ref_->nclosed();
    const int nact = ref_->nact();
    const int nocc = ref_->nocc();

    const MatView ocoeff = ref_->coeff()->slice(0,nocc);

    // state-averaged density matrices
    shared_ptr<const RDM<1>> rdm1_av = task_->fci()->rdm1_av();
    shared_ptr<const RDM<2>> rdm2_av = task_->fci()->rdm2_av();

    // related to denominators
    const int nmobasis = coeff->mdim();
    assert(nmobasis == nclosed+nact+ref_->nvirt());

    // TODO they are redundant, though...
    shared_ptr<DFHalfDist> half  = geom_->df()->compute_half_transform(ocoeff)->apply_J();
    shared_ptr<DFHalfDist> halfjj = half->apply_J();

    // orbital derivative is nonzero
    auto g0 = make_shared<Matrix>(nmobasis, nmobasis);
    // 1/2 Y_ri = hd_ri + K^{kl}_{rj} D^{lk}_{ji}
    //          = hd_ri + (kr|G)(G|jl) D(lj, ki)
    // 1) one-electron contribution
    auto hmo = make_shared<const Matrix>(*ref_->coeff() % *ref_->hcore() * ocoeff);
    shared_ptr<const Matrix> rdm1 = ref_->rdm1_mat(target_state_);
    assert(rdm1->ndim() == nocc && rdm1->mdim() == nocc);
    g0->add_block(2.0, 0, 0, nmobasis, nocc, *hmo * *rdm1);
    // 2) two-electron contribution
    shared_ptr<const DFFullDist> full  = half->compute_second_transform(ocoeff);
    shared_ptr<const DFFullDist> fulld = full->apply_2rdm(*ref_->rdm2(target_state_), *ref_->rdm1(target_state_), nclosed, nact);
    shared_ptr<const Matrix> buf = half->form_2index(fulld, 1.0);
    g0->add_block(2.0, 0, 0, nmobasis, nocc, *ref_->coeff() % *buf);

    // Recalculate the CI vectors (which can be avoided... TODO)
    shared_ptr<const Dvec> civ = task_->fci()->civectors();

    // CI derivative is zero
    auto g1 = make_shared<Dvec>(task_->fci()->det(), ref_->nstate());
    // combine gradient file
    auto grad = make_shared<PairFile<Matrix, Dvec>>(g0, g1);

    // compute unrelaxed dipole...
    shared_ptr<Matrix> dtot = ref_->rdm1_mat(target_state_)->resize(nmobasis, nmobasis);
    {
      Dipole dipole(geom_, make_shared<Matrix>(*ref_->coeff() * *dtot ^ *ref_->coeff()), "Unrelaxed");
      dipole.compute();
    }

    // solve CP-CASSCF
    auto cp = make_shared<CPCASSCF>(grad, civ, half, ref_, task_->fci());
    shared_ptr<const Matrix> zmat, xmat, dummy;
    shared_ptr<const Dvec> zvec;
    tie(zmat, zvec, xmat, dummy) = cp->solve(task_->thresh());

    // form Zd + dZ^+
    shared_ptr<const Matrix> dsa = rdm1_av->rdm1_mat(nclosed)->resize(nmobasis, nmobasis);
    auto dm = make_shared<Matrix>(*zmat * *dsa + (*dsa ^ *zmat));

    dtot->ax_plus_y(1.0, dm);

    // form zdensity
    auto detex = make_shared<Determinants>(task_->fci()->norb(), task_->fci()->nelea(), task_->fci()->neleb(), false, /*mute=*/true);
    shared_ptr<const RDM<1>> zrdm1;
    shared_ptr<const RDM<2>> zrdm2;
    tie(zrdm1, zrdm2) = task_->fci()->compute_rdm12_av_from_dvec(zvec, civ, detex);

    shared_ptr<Matrix> zrdm1_mat = zrdm1->rdm1_mat(nclosed, false)->resize(nmobasis, nmobasis);
    zrdm1_mat->symmetrize();
    dtot->ax_plus_y(1.0, zrdm1_mat);

    // here dtot is the relaxed 1RDM in the MO basis
    auto dtotao = make_shared<Matrix>(*ref_->coeff() * *dtot ^ *ref_->coeff());

    // compute relaxed dipole moment
    {
      Dipole dipole(geom_, dtotao, "Relaxed");
      dipole.compute();
    }

    // xmat in the AO basis
    auto xmatao = make_shared<Matrix>(*ref_->coeff() * *xmat ^ *ref_->coeff());

    //- TWO ELECTRON PART -//
    // half is computed long before
    shared_ptr<const DFFullDist> qij  = halfjj->compute_second_transform(ocoeff);
    shared_ptr<DFHalfDist> qri;
    {
      shared_ptr<const Matrix> ztrans = make_shared<Matrix>(*ref_->coeff() * zmat->slice(0,nocc));
      {
        RDM<2> D(*ref_->rdm2(target_state_)+*zrdm2);
        RDM<1> dd(*ref_->rdm1(target_state_)+*zrdm1);
        // symetrize dd (zrdm1 needs symmetrization)
        for (int i = 0; i != nact; ++i)
          for (int j = 0; j != nact; ++j)
            dd(j,i) = dd(i,j) = 0.5*(dd(j,i)+dd(i,j));

        shared_ptr<DFFullDist> qijd = qij->apply_2rdm(D, dd, nclosed, nact);
        qijd->ax_plus_y(2.0, halfjj->compute_second_transform(ztrans)->apply_2rdm(*rdm2_av, *rdm1_av, nclosed, nact));
        qri = qijd->back_transform(ocoeff);
      }
      {
        shared_ptr<const DFFullDist> qijd2 = qij->apply_2rdm(*rdm2_av, *rdm1_av, nclosed, nact);
        qri->ax_plus_y(2.0, qijd2->back_transform(ztrans));
      }
    }

    shared_ptr<const Matrix> qq  = qri->form_aux_2index(halfjj, 1.0);
    shared_ptr<const DFDist> qrs = qri->back_transform(ocoeff);

    gradient = contract_gradient(dtotao, xmatao, qrs, qq);
  }
  gradient->print();
  cout << setw(50) << left << "  * Gradient computed with " << setprecision(2) << right << setw(10) << timer.tick() << endl << endl;

  return gradient;
}
