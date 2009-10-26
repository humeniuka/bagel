//
// Author : Toru Shiozaki
// Date   : August 2009
//

// compressed file of double 

#ifndef __src_util_pcompfile_h
#define __src_util_pcompfile_h

#include <cstring>
#include <cassert>
#include <vector>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <algorithm>
#include <src/macros.h>
#include <src/pscf/pgeometry.h>
#include <src/pscf/pcoeff.h>
#include <src/util/pmofile.h>
#include <src/util/filename.h>
#include <src/util/cache.h>
#include <src/util/f77.h>

template<class T>
class PCompFile {
  protected:
    boost::shared_ptr<std::fstream> file_;
    long filesize_;
    std::string filename_;
    std::string jobname_;
    std::vector<double> schwarz_;

    const boost::shared_ptr<PGeometry> geom_;
    std::vector<size_t> num_int_each_;

    std::vector<boost::shared_ptr<Shell> > basis_;
    std::vector<int> offset_;
    size_t max_num_int_;

    int K_, L_, S_;
    double A_;

    // Exponent of STG for this file. Can be different from geom_->gamma()
    const double gamma_;

  public:
    PCompFile(boost::shared_ptr<PGeometry>,  const double gam,
        const bool late_init = false, const std::string jobname = "");
    ~PCompFile(); 

    // create file...
    const std::string filename() const { return filename_; };
    void append(const long, const double*);
    // evaluates one block of integrals.
    virtual void eval_new_block(double*, int, int, int);

    // append mode cannot be read, hence reopen. Add, Put and Get operation has been implemented
    void reopen_with_inout();
    void add_block(const long, const long, const double*);
    void put_block(const long, const long, const double*);
    void get_block(const long, const long, double*);

    // returns some misc infos
    const double schwarz(int i) const { return schwarz_[i]; };
    std::vector<int> offset() const { return offset_; };
    int offset(size_t i) const { return offset_[i]; };
    std::vector<boost::shared_ptr<Shell> > basis() const { return basis_; };
    boost::shared_ptr<Shell> basis(size_t i) const { return basis_[i]; };
    const size_t nbasis(size_t i) const { return basis_[i]->nbasis(); };
    const int basissize() const { return basis_.size(); };

    // calculate integrals here
    void init_schwarz();
    std::vector<size_t> num_int_each() const { return num_int_each_; };
    const size_t num_int_each(const int i) const { return num_int_each_[i]; };
    // will be redefined in the derived classes
    virtual void calculate_num_int_each();
    virtual void store_integrals();

    // or import integrals computed externally
    void set_schwarz(const std::vector<double>& a) { schwarz_ = a; };
    void set_num_int_each(const std::vector<size_t>& nie) { num_int_each_ = nie; 
                                                            max_num_int_ = *std::max_element(nie.begin(), nie.end()); };
    void set_integrals(boost::shared_ptr<std::fstream> inp) { file_ = inp; };

    const size_t max_num_int() const { assert(max_num_int_ != 0lu); return max_num_int_; };

    const int K() const { return K_; };
    const int L() const { return L_; };
    const int S() const { return S_; };
    const double A() const { return A_; };

    // AO-to-MO integral transformation...
    boost::shared_ptr<PMOFile<std::complex<double> > > 
                mo_transform(boost::shared_ptr<PCoeff>,
                             boost::shared_ptr<PCoeff>,
                             boost::shared_ptr<PCoeff>,
                             boost::shared_ptr<PCoeff>,
                             const int istart, const int ifence,
                             const int jstart, const int jfence,
                             const int astart, const int afence,
                             const int bstart, const int bfence,
                             const std::string jobname = "intermediate");

    boost::shared_ptr<PMOFile<std::complex<double> > >
      mo_transform_cabs_obs(boost::shared_ptr<PCoeff>,
                            boost::shared_ptr<PMatrix1e>,
                            const int istart, const int ifence,
                            const int jstart, const int jfence,
                            const int astart, const int afence,
                            const int bstart, const int bfence,
                            const std::string jobname = "intermediate");

};


template<class T>
PCompFile<T>::PCompFile(boost::shared_ptr<PGeometry> gm, const double gam, const bool late_init, const std::string jobname)
 : geom_(gm), gamma_(gam), jobname_(jobname) {

  Filename tmpf;
  filename_ = tmpf.filename_next(); 

  boost::shared_ptr<std::fstream> tmp(new std::fstream(filename_.c_str(), std::ios::out | std::ios::binary));
  file_ = tmp;

  { // prepare offset and basis
    typedef boost::shared_ptr<Atom> RefAtom;
    typedef boost::shared_ptr<Shell> RefShell;

    const std::vector<RefAtom> atoms = geom_->atoms();
    int cnt = 0;
    for (std::vector<RefAtom>::const_iterator aiter = atoms.begin(); aiter != atoms.end(); ++aiter, ++cnt) {
      const std::vector<RefShell> tmp = (*aiter)->shells();
      basis_.insert(basis_.end(), tmp.begin(), tmp.end());  
      const std::vector<int> tmpoff = geom_->offset(cnt); 
      offset_.insert(offset_.end(), tmpoff.begin(), tmpoff.end());
    }
  }

  S_ = geom_->S();
  L_ = geom_->L();
  K_ = geom_->K();
  A_ = geom_->A();

  // late_init is true when constructed from PairCompFile class
  if (!late_init) {
    init_schwarz();
    calculate_num_int_each();
  }
};


template<class T>
PCompFile<T>::~PCompFile() {
  unlink(filename_.c_str());
};


template<class T>
void PCompFile<T>::add_block(const long position, const long length, const double* data) {
  long remaining = length;
  long current = 0L;
  const double cone = 1.0;
  const int unit = 1;
  double* work = (double*) work_char;

  while (remaining > 0L) {
    const long readsize = std::min(remaining, cachesize) * sizeof(double);
    const int rsize = std::min(remaining, cachesize);

    file_->clear();
    file_->seekg((position + current) * sizeof(double));
    file_->read((char*)work_char, readsize); 
    for (int i = 0; i != rsize; ++i) work[i] += data[current + i];

    file_->clear();
    file_->seekp((position + current) * sizeof(double));
    file_->write((const char*)work_char, readsize);

    remaining -= cachesize;
    current += cachesize;
  } 
};


template<class T>
void PCompFile<T>::get_block(const long position, const long length, double* data) {
  long remaining = length;
  long current = 0L;

  while (remaining > 0L) {
    const long readsize = std::min(remaining, cachesize) * sizeof(double);
    file_->clear();
    file_->seekg((position + current) * sizeof(double));
    file_->read((char*)(&data[current]), readsize); 

    remaining -= cachesize;
    current += cachesize;
  } 
};


template<class T>
void PCompFile<T>::put_block(const long position, const long length, const double* data) {
  long remaining = length;
  long current = 0L;

  while (remaining > 0L) {
    const long writesize = std::min(remaining, cachesize) * sizeof(double);
    file_->clear();
    file_->seekp((position + current) * sizeof(double));
    file_->write((const char*)(&data[current]), writesize); 

    remaining -= cachesize;
    current += cachesize;
  } 
};


template<class T>
void PCompFile<T>::append(const long length, const double* data) {
  file_->clear();
  file_->seekp(0, std::ios::end);
  long remaining = length;
  long current = 0L;

  while (remaining > 0L) {
    const long writesize = std::min(remaining, cachesize) * sizeof(double);
    file_->write((const char*)(&data[current]), writesize); 

    remaining -= cachesize;
    current += cachesize;
  } 
};


template<class T>
void PCompFile<T>::reopen_with_inout() {
  file_->close();
  file_->open(filename_.c_str(), std::ios::in | std::ios::out | std::ios::binary);
};


template<class T>
void PCompFile<T>::calculate_num_int_each() {

  typedef boost::shared_ptr<Shell> RefShell;

  unsigned long data_written = 0ul;
  num_int_each_.resize((S_ + S_ + 1) * (S_ + S_ + 1) * (L_ + 1));
  const int size = basis_.size(); // number of shells

  #pragma omp parallel for reduction(+:data_written)
  for (int m1 = - S_; m1 <= S_; ++m1) {
    const double m1disp[3] = {0.0, 0.0, m1 * A_}; 
    size_t offset = (m1 + S_) * (L_ + 1) * (S_ * 2 + 1);
    for (int m2 = 0; m2 <= L_; ++m2) { // use bra-ket symmetry!!!
      const double m2disp[3] = {0.0, 0.0, m2 * A_}; 
      for (int m3 = m2 - S_; m3 <= m2 + S_; ++m3, ++offset) {
        const double m3disp[3] = {0.0, 0.0, m3 * A_}; 
        size_t thisblock = 0ul; 
        for (int i0 = 0; i0 != size; ++i0) {
          const int b0offset = offset_[i0]; 
          const int b0size = basis_[i0]->nbasis();

          for (int i1 = 0; i1 != size; ++i1) {
            const int b1offset = offset_[i1];
            const int b1size = basis_[i1]->nbasis();

            for (int i2 = 0; i2 != size; ++i2) {
              const int b2offset = offset_[i2];
              const int b2size = basis_[i2]->nbasis();

              for (int i3 = 0; i3 != size; ++i3) {
                const int b3offset = offset_[i3]; 
                const int b3size = basis_[i3]->nbasis();

                const double integral_bound = schwarz_[(m1 + K_) * size * size + i0 * size + i1]
                                            * schwarz_[(m3 - m2 + K_) * size * size + i2 * size + i3];
                const bool skip_schwarz = integral_bound < SCHWARZ_THRESH;
                if (skip_schwarz) continue;
                data_written += b0size * b1size * b2size * b3size;
                thisblock += b0size * b1size * b2size * b3size; 
              }
            }
          }
        }
        num_int_each_[offset] = thisblock;
      }
    }
  }

  max_num_int_ = *std::max_element(num_int_each_.begin(), num_int_each_.end());

  if (jobname_ != "PAIR") {
    std::cout << "  Using ";
    const size_t data_written_byte = data_written * sizeof(double);
    if (data_written_byte > 1.0e9) {
      std::cout << std::setprecision(1) << data_written_byte / 1.0e9 << " GB";
    } else if (data_written_byte > 1.0e6) {
      std::cout << std::setprecision(1) << data_written_byte / 1.0e6 << " MB";
    } else {
      std::cout << std::setprecision(1) << data_written_byte / 1.0e3 << " KB";
    }

    std::cout << " hard disk for storing \"" << jobname_ << "\"" << std::endl;
  }
};


template<class T>
void PCompFile<T>::eval_new_block(double* out, int m1, int m2, int m3) {

  typedef boost::shared_ptr<Shell> RefShell;

  const double m1disp[3] = {0.0, 0.0, m1 * A_}; 
  const double m2disp[3] = {0.0, 0.0, m2 * A_}; 
  const double m3disp[3] = {0.0, 0.0, m3 * A_}; 

  const int size = basis_.size(); // number of shells
  int* blocks = new int[size * size * size * size + 1];
  blocks[0] = 0;
  int iall = 0;
  for (int i0 = 0; i0 != size; ++i0) {
    const int b0size = basis_[i0]->nbasis();
    for (int i1 = 0; i1 != size; ++i1) {
      const int b1size = basis_[i1]->nbasis();
      for (int i2 = 0; i2 != size; ++i2) {
        const int b2size = basis_[i2]->nbasis();
        for (int i3 = 0; i3 != size; ++i3, ++iall) {
          const int b3size = basis_[i3]->nbasis();
          const double integral_bound = schwarz_[(m1 + K_) * size * size + i0 * size + i1]
                                      * schwarz_[(m3 - m2 + K_) * size * size + i2 * size + i3];
          const bool skip_schwarz = integral_bound < SCHWARZ_THRESH;
          blocks[iall + 1] = blocks[iall] + (skip_schwarz ? 0 : (b0size * b1size * b2size * b3size)); 
        }
      }
    }
  }
  #pragma omp parallel for
  for (int i0 = 0; i0 < size; ++i0) {
    int offset = i0 * size * size * size; 
    const RefShell b0 = basis_[i0]; // b0 is the center cell
    for (int i1 = 0; i1 != size; ++i1) {
      const RefShell b1 = basis_[i1]->move_atom(m1disp); 
      for (int i2 = 0; i2 != size; ++i2) {
        const RefShell b2 = basis_[i2]->move_atom(m2disp);
        for (int i3 = 0; i3 < size; ++i3, ++offset) {
          const RefShell b3 = basis_[i3]->move_atom(m3disp);

          if (blocks[offset] == blocks[offset + 1]) continue;

          std::vector<RefShell> input;
          input.push_back(b3);
          input.push_back(b2);
          input.push_back(b1);
          input.push_back(b0);

          T batch(input, 1.0, gamma_);
          batch.compute();
          const double* bdata = batch.data();
          ::memcpy(out + blocks[offset], bdata, (blocks[offset + 1] - blocks[offset]) * sizeof(double));
        }
      }
    }
  }
  delete[] blocks;
};


template<class T>
void PCompFile<T>::store_integrals() {
  const size_t cachesize_max = 100000000lu;
  const size_t cachesize = std::max(cachesize_max, max_num_int_);
  double* dcache = new double[cachesize];
  size_t remaining = cachesize;
  size_t current = 0lu;
  size_t cnt = 0lu;
  for (int m1 = -S_; m1 <= S_; ++m1) {
    for (int m2 = 0; m2 <= L_; ++m2) { // use bra-ket symmetry!!!
      for (int m3 = m2 - S_; m3 <= m2 + S_; ++m3, ++cnt) {
        if (remaining < num_int_each(cnt)) {
          append(current, dcache);
          current = 0lu;
          remaining = cachesize;
        }
        eval_new_block(&dcache[current], m1, m2, m3);
        current += num_int_each(cnt);
        remaining -= num_int_each(cnt);
      }
    }
  } 
  append(current, dcache);
  delete[] dcache;
};


template<class T>
void PCompFile<T>::init_schwarz() {
  typedef boost::shared_ptr<Shell> RefShell;
  typedef boost::shared_ptr<Atom> RefAtom;

  const int size = basis_.size(); // the number of shells per unit cell
  schwarz_.resize(size * size * (2 * K_ + 1));

  #pragma omp prallel for
  for (int m = - K_; m <= K_; ++m) { 
    const double disp[3] = {0.0, 0.0, m * A_};
    for (int i0 = 0; i0 != size; ++i0) { // center unit cell
      const RefShell b0 = basis_[i0];
      for (int i1 = 0; i1 != size; ++i1) {
        const RefShell b1 = basis_[i1]->move_atom(disp);

        std::vector<RefShell> input;
        input.push_back(b0);
        input.push_back(b1);
        input.push_back(b0);
        input.push_back(b1);
        T batch(input, 1.0, gamma_);
        batch.compute();
        const double* data = batch.data();
        const int datasize = batch.data_size();
        double cmax = 0.0;
        for (int xi = 0; xi != datasize; ++xi, ++data) {
          const double absed = (*data) > 0.0 ? *data : -*data;
          if (absed > cmax) cmax = absed;
        }
        schwarz_[(m + K_) * size * size + i0 * size + i1] = cmax;
      }
    }
  }
};


template<class T>
boost::shared_ptr<PMOFile<std::complex<double> > > 
  PCompFile<T>::mo_transform(boost::shared_ptr<PCoeff> coeff_i,
                             boost::shared_ptr<PCoeff> coeff_j,
                             boost::shared_ptr<PCoeff> coeff_a,
                             boost::shared_ptr<PCoeff> coeff_b,
                             const int istart, const int ifence,
                             const int jstart, const int jfence,
                             const int astart, const int afence,
                             const int bstart, const int bfence,
                             const std::string jobname) {
// Loading a (2K * 2K * nov) quantity on memory 

  const int isize = ifence - istart;
  const int jsize = jfence - jstart;
  const int asize = afence - astart;
  const int bsize = bfence - bstart;
  const size_t noovv = static_cast<size_t>(isize) * jsize * asize * bsize;
  assert(noovv > 0);

  const double pi = 3.14159265358979323846; 
  const int KK = K_ + K_;

  const int maxK1 = std::max(K_, 1);
  const std::complex<double> czero(0.0, 0.0);
  const std::complex<double> cone(1.0, 0.0);

  const int unit = 1;

  const int nbasis1 = geom_->nbasis();
  const int nbasis2 = nbasis1 * nbasis1;
  const int nbasis3 = nbasis2 * nbasis1;
  const size_t nbasis4 = static_cast<size_t>(nbasis2) * nbasis2;

  const size_t filesize = noovv * std::max(KK, 1) * std::max(KK, 1) * std::max(KK, 1);
  std::cout << "  Creating " << jobname << "  of size ";
  const size_t filesize_byte = filesize * sizeof(std::complex<double>);
  if (filesize_byte > 1.0e9) {
    std::cout << std::setprecision(1) << filesize_byte / 1.0e9 << " GB" << std::endl;
  } else if (filesize_byte > 1.0e6) {
    std::cout << std::setprecision(1) << filesize_byte / 1.0e6 << " MB" << std::endl;
  } else {
    std::cout << std::setprecision(1) << filesize_byte / 1.0e3 << " KB" << std::endl;
  }
  boost::shared_ptr<PMOFile<std::complex<double> > >
    mo_int(new PMOFile<std::complex<double> >(geom_, filesize, K_,
                                              istart, ifence, jstart, jfence,
                                              astart, afence, bstart, bfence, true));

  // we are assuming that the (c.c. two-electron integrals for a unit cell)*K^2 can be
  // held in core. If that is not the case, this must be rewritten.

  // allocating a temp array
  std::complex<double>* data = new std::complex<double>[nbasis4 * std::max(KK, 1)]; 
  std::complex<double>* datas = new std::complex<double>[nbasis4 * std::max(KK, 1)]; 
  std::complex<double>* conjc = new std::complex<double>[nbasis1 * std::max(isize, jsize)]; 
  double* data_read = new double[max_num_int_ * (S_ + S_ + 1)];

  const int size = basis_.size();
  int* blocks = new int[size * size * size * size + 1];

  const int nv = nbasis3 * bsize;
  const int nov = nbasis2 * jsize * bsize;
  const int novv = nbasis1 * jsize * asize * bsize;

  const size_t sizem1 = S_ + S_ + 1lu;
  const size_t sizem2 = L_ + L_ + 1lu;
  const size_t sizem2abs = L_ + 1lu;
  const size_t num_loops = sizem1 * sizem1 * sizem2; 
  size_t loop_counter = 0lu;
  size_t loop_mod10 = 0lu;

  size_t allocsize = *std::max_element(num_int_each_.begin(), num_int_each_.end()); 

  std::complex<double>* intermediate_mmK = new std::complex<double>[nv * std::max(KK, 1)];
  std::complex<double>* intermediate_mKK = new std::complex<double>[nov * std::max(KK * KK, 1)];
  PFile<std::complex<double> > intermediate_KKK(std::max(novv * KK * KK * KK, novv), K_, true);

  for (int q1 = -S_; q1 <= S_; ++q1) {
    const bool q1_front = (q1 == -S_);
    const int m1 = q1;
    fill(intermediate_mKK, intermediate_mKK + nov * std::max(KK * KK, 1), czero);
    for (int q2 = -L_; q2 <= L_; ++q2) {
      const int m2 = q2;
      fill(intermediate_mmK, intermediate_mmK + nv * std::max(KK, 1), czero);
      for (int q3 = -S_; q3 <= S_; ++q3, ++loop_counter) {
        const int m3 = m2 + q3; 

        const double* cdata;

        if (q2 >= 0 && q3 == -S_) {
          const size_t key = sizem1 * (q2 + sizem2abs * (q1 + S_));
          size_t readsize = 0lu; 
          for (int i = 0; i <= S_ * 2; ++i) readsize += num_int_each_[key + i];
          size_t datasize_acc = 0lu;
          for (int i = 0; i != key; ++i) datasize_acc += num_int_each_[i];
          get_block(datasize_acc, readsize, data_read);
          cdata = data_read;
        } 
        else if (q2 >= 0) {
          cdata = data_read;
          const size_t key = S_ + sizem1 * (q2 + sizem2abs * (q1 + S_));
          for (int i = key - S_; i != key + q3; ++i) cdata += num_int_each_[i]; 
        }
        else { // q2 < 0
          const size_t key = q1 + S_ + sizem1 * (- q2 + sizem2abs * (q3 + S_));
          size_t datasize_acc = 0lu;
          for (int i = 0; i != key; ++i) datasize_acc += num_int_each_[i];
          get_block(datasize_acc, num_int_each_[key], data_read);
          cdata = data_read;
        }

        if (loop_mod10 < loop_counter * 10lu / num_loops) {
          loop_mod10++;
          std::cout << "  Loop " << loop_mod10 * 10lu << " percent done" << std::endl;
        }

        size_t local_counter = 0lu;

        blocks[0] = 0;
        int iall = 0;
        for (int i0 = 0; i0 != size; ++i0) {
          const int b0size = basis_[i0]->nbasis();
          for (int i1 = 0; i1 != size; ++i1) {
            const int b1size = basis_[i1]->nbasis();
            for (int i2 = 0; i2 != size; ++i2) {
              const int b2size = basis_[i2]->nbasis();
              for (int i3 = 0; i3 != size; ++i3, ++iall) {
                const int b3size = basis_[i3]->nbasis();

                double integral_bound;
                if (m2 >= 0) { 
                  integral_bound = schwarz_[((q1 + K_) * size + i0) * size + i1]
                                 * schwarz_[((q3 + K_) * size + i2) * size + i3];
                } else {
                  integral_bound = schwarz_[((q1 + K_) * size + i2) * size + i3]
                                 * schwarz_[((q3 + K_) * size + i0) * size + i1];
                }
                const bool skip_schwarz = integral_bound < SCHWARZ_THRESH;
                blocks[iall + 1] = blocks[iall] + (skip_schwarz ? 0 : (b0size * b1size * b2size * b3size)); 
              }
            }
          }
        }

        #pragma omp parallel for
        for (int i0 = 0; i0 < size; ++i0) {
          int noffset = i0 * size * size * size;
          const int b0offset = offset(i0); 
          const int b0size = nbasis(i0);
          for (int i1 = 0; i1 != size; ++i1) {
            const int b1offset = offset(i1);
            const int b1size = nbasis(i1);
            for (int i2 = 0; i2 != size; ++i2) {
              const int b2offset = offset(i2); 
              const int b2size = nbasis(i2);
              for (int i3 = 0; i3 != size; ++i3, ++noffset) {
                const int b3offset = offset(i3); 
                const int b3size = nbasis(i3);

                if (blocks[noffset] != blocks[noffset + 1]) { 
                  const double* ndata = cdata + blocks[noffset];
                  std::complex<double>* label = data + b3offset + nbasis1 * (b2offset + nbasis1 * (b1offset + nbasis1 * b0offset));
                  for (int j0 = 0; j0 != b0size; ++j0, label += nbasis3) {
                    for (int j1 = 0; j1 != b1size; ++j1, label += nbasis2) {  
                      for (int j2 = 0; j2 != b2size; ++j2, label += nbasis1) {
                        for (int j3 = 0; j3 != b3size; ++j3, ++label, ++ndata) {  
                          *label = static_cast<std::complex<double> >(*ndata);
                        }
                        label -= b3size;
                      }
                      label -= b2size * nbasis1;
                    }
                    label -= b1size * nbasis2;
                  }
                } else {
                  std::complex<double>* label = data + b3offset + nbasis1 * (b2offset + nbasis1 * (b1offset + nbasis1 * b0offset));
                  for (int j0 = 0; j0 != b0size; ++j0, label += nbasis3) {
                    for (int j1 = 0; j1 != b1size; ++j1, label += nbasis2) {  
                      for (int j2 = 0; j2 != b2size; ++j2, label += nbasis1) {
                        std::fill(label, label + b3size, czero); 
                      }
                      label -= b2size * nbasis1;
                    }
                    label -= b1size * nbasis2;
                  }
                } // end of if skip_schwarz

              }
            }
          }
        } // end of shell loops; now data is ready

        if (m2 >= 0) { // start from j & b contractions -- needs transposition
          const int mn = nbasis2;          
          mytranspose_complex_(data, &mn, &mn, datas);
          ::memcpy(data, datas, nbasis4 * sizeof(std::complex<double>));
        }

        #pragma omp parallel for
        for (int nkb = -K_; nkb < maxK1; ++nkb) {
          const int nkbc = nkb + K_;
          const std::complex<double> exponent(0.0, K_ != 0 ? (m3 * nkb * pi) / K_ : 0.0);
          const std::complex<double> prefac = exp(exponent);
          int offset1 = 0;
          int offset2 = 0;
          for (int ii = 0; ii != nbasis1; ++ii, offset1 += nbasis3,
                                                offset2 += nbasis2 * bsize) {
            zgemm_("N", "N", &nbasis2, &bsize, &nbasis1, &prefac, data + offset1, &nbasis2,
                                                         coeff_b->bp(nkb) + nbasis1 * bstart, &nbasis1, &cone,
                                                         intermediate_mmK + nv * nkbc + offset2, &nbasis2);
          }
        } // end of contraction b for given m3

      } // end of m3 loop

      // intermediate_mmK is ready
      #pragma omp parallel for
      for (int nkb = -K_; nkb < maxK1; ++nkb) {
        std::complex<double>* conjc2 = new std::complex<double>[nbasis1 * jsize];
        const int nkbc = nkb + K_; 
        int nbj = nkbc * KK;
        for (int nkj = -K_, nkjc = 0; nkj != maxK1; ++nkj, ++nbj, ++nkjc) {
          const std::complex<double> exponent(0.0, K_ != 0 ? (- m2 * nkj * pi) / K_ : 0.0);
          const std::complex<double> prefac = exp(exponent);

          const std::complex<double>* jdata = coeff_j->bp(nkj) + nbasis1 * jstart;
          for (int ii = 0; ii != nbasis1 * jsize; ++ii) conjc2[ii] = conj(jdata[ii]);
          const int nsize = nbasis2 * bsize;
          zgemm_("N", "N", &nsize, &jsize, &nbasis1, &prefac, intermediate_mmK + nv * nkbc, &nsize,
                                                              conjc2, &nbasis1, &cone,
                                                              intermediate_mKK + nov * nbj, &nsize);
        }
        delete[] conjc2;
      } // end of contraction j for given m2

    } // end of m2 loop

    // intermediate_mKK is ready
    for (int nkb = -K_, nbja = 0, nbj = 0; nkb != maxK1; ++nkb) {
      for (int nkj = -K_; nkj != maxK1; ++nkj, ++nbj) {
        ::memcpy(datas, intermediate_mKK + nov * nbj, nov * sizeof(std::complex<double>));
        {
          const int m = nbasis2; 
          const int n = jsize * bsize;
          mytranspose_complex_(datas, &m, &n, data);
          std::fill(datas, datas + novv, czero);
        }

        #pragma omp parallel for
        for (int nka = -K_; nka < maxK1; ++nka) {
          const int nkac = nka + K_;
          const std::complex<double> exponent(0.0, K_ != 0 ? (m1 * nka * pi)/ K_ : 0.0);
          const std::complex<double> prefac = exp(exponent);
          const int nsize = jsize * bsize;
          int offset1 = 0;
          int offset2 = 0;
          for (int ii = 0; ii != nbasis1; ++ii, offset1 += nsize * nbasis1,
                                                offset2 += nsize * asize) {
            zgemm_("N", "N", &nsize, &asize, &nbasis1, &prefac, data + offset1, &nsize,
                                                                coeff_a->bp(nka) + nbasis1 * astart, &nbasis1, &czero,
                                                                datas + nkac * novv + offset2, &nsize);
          }
        }
        if (q1_front)
          intermediate_KKK.append(novv * std::max(KK, 1), datas);
        else
          intermediate_KKK.add_block(novv * nbja, novv * std::max(KK, 1), datas);
        nbja += std::max(KK, 1);
      }
    } // end of contraction a for given m1

    if (q1_front)
      intermediate_KKK.reopen_with_inout();

  } // end of m1 loop

  // now intermediate_KKK is ready.
  for (int nkb = -K_; nkb != maxK1; ++nkb) {
    int nbja = (nkb + K_) * KK * KK;
    for (int nkj = -K_; nkj != maxK1; ++nkj) {
      intermediate_KKK.get_block(novv * nbja, novv * std::max(KK, 1), data);
      #pragma omp parallel for
      for (int nka = -K_; nka < maxK1; ++nka) {
        std::complex<double>* conjc2 = new std::complex<double>[nbasis1 * isize]; 

        // momentum conservation
        int nki = nka + nkb - nkj; 
        if (nki < - K_) nki += K_ * 2; 
        else if (nki >=  K_) nki -= K_ * 2; 

        const std::complex<double>* idata = coeff_i->bp(nki) + nbasis1 * istart;
        for (int ii = 0; ii != nbasis1 * isize; ++ii) conjc2[ii] = conj(idata[ii]);
        const int nsize = jsize * asize * bsize;
        zgemm_("N", "N", &nsize, &isize, &nbasis1, &cone, data + novv * (nka + K_), &nsize,
                                                          conjc2, &nbasis1, &czero,
                                                          datas + noovv * (nka + K_), &nsize);
        delete[] conjc2;
      }
      mo_int->append(noovv * std::max(KK, 1), datas);
      nbja += std::max(KK, 1);
    }
  } // end of contraction i

  delete[] data;
  delete[] datas;
  delete[] data_read;
  delete[] conjc;
  delete[] intermediate_mmK;
  delete[] intermediate_mKK;
  delete[] blocks;

  std::cout << "  done" << std::endl << std::endl;
  mo_int->reopen_with_inout();
  return mo_int;
};


template<class T>
boost::shared_ptr<PMOFile<std::complex<double> > >
  PCompFile<T>::mo_transform_cabs_obs(boost::shared_ptr<PCoeff> coeff,
                                      boost::shared_ptr<PMatrix1e> cabs_coeff,
                                      const int istart, const int ifence,
                                      const int jstart, const int jfence,
                                      const int astart, const int afence,
                                      const int bstart, const int bfence,
                                      const std::string jobname) {

  // What is different is that the coefficient of b3 is replaced by cabs_coeff.
  // Other than that, they should be the same as mo_transform.

  // Loading a (2K * 2K * nov) quantity on memory

  assert(bfence <= cabs_coeff->mdim());

  const int isize = ifence - istart;
  const int jsize = jfence - jstart;
  const int asize = afence - astart;
  const int bsize = bfence - bstart;
  const size_t noovv = static_cast<size_t>(isize) * jsize * asize * bsize;
  assert(noovv > 0);

  const double pi = 3.14159265358979323846;
  const int k = this->K_;
  const int s = this->S_;
  const int l = this->L_;

  const int KK = k + k;

  const int maxK1 = std::max(k, 1);
  const std::complex<double> czero(0.0, 0.0);
  const std::complex<double> cone(1.0, 0.0);

  const int unit = 1;

  const int nbasis1 = this->geom_->nbasis();
  const int nbasis2 = nbasis1 * nbasis1;
  const int nbasis3 = nbasis2 * nbasis1;
  const size_t nbasis4 = static_cast<size_t>(nbasis2) * nbasis2;

  const size_t filesize = noovv * std::max(KK, 1) * std::max(KK, 1) * std::max(KK, 1);
  std::cout << "  Creating " << jobname << "  of size ";
  const size_t filesize_byte = filesize * sizeof(std::complex<double>);
  if (filesize_byte > 1.0e9) {
    std::cout << std::setprecision(1) << filesize_byte / 1.0e9 << " GB" << std::endl;
  } else if (filesize_byte > 1.0e6) {
    std::cout << std::setprecision(1) << filesize_byte / 1.0e6 << " MB" << std::endl;
  } else {
    std::cout << std::setprecision(1) << filesize_byte / 1.0e3 << " KB" << std::endl;
  }
  boost::shared_ptr<PMOFile<std::complex<double> > >
    mo_int(new PMOFile<std::complex<double> >(geom_, filesize, k,
                                              istart, ifence, jstart, jfence,
                                              astart, afence, bstart, bfence, true));

  // we are assuming that the (c.a. two-electron integrals for a unit cell)*K^2 can be
  // held in core. If that is not the case, this must be rewritten.

  // allocating a temp array
  std::complex<double>* data = new std::complex<double>[nbasis3 * std::max(nbasis1, bsize) * std::max(KK, 1)];
  std::complex<double>* datas = new std::complex<double>[nbasis3 * std::max(nbasis1, bsize) * std::max(KK, 1)];
  std::complex<double>* conjc = new std::complex<double>[nbasis1 * std::max(isize, jsize)];
  double* data_read = new double[this->max_num_int_ * (s*2+1)];

  const int size = this->basis_.size();
  int* blocks = new int[size * size * size * size + 1];

  const int nv = nbasis3 * bsize;
  const int nov = nbasis2 * jsize * bsize;
  const int novv = nbasis1 * jsize * asize * bsize;

  const size_t sizem1 = s*2+1lu;
  const size_t sizem2 = l*2+1lu;
  const size_t sizem2abs = l+1lu;
  const size_t num_loops = sizem1 * sizem1 * sizem2;
  size_t loop_counter = 0lu;
  size_t loop_mod10 = 0lu;

  size_t allocsize = *std::max_element(this->num_int_each_.begin(), this->num_int_each_.end());

  std::complex<double>* intermediate_mmK = new std::complex<double>[nv * std::max(KK, 1)];
  std::complex<double>* intermediate_mKK = new std::complex<double>[nov * std::max(KK * KK, 1)];
  PFile<std::complex<double> > intermediate_KKK(std::max(novv * KK * KK * KK, novv), k, true);

  for (int q1 = -S_; q1 <= S_; ++q1) {
    const bool q1_front = (q1 == -S_);
    const int m1 = q1;
    fill(intermediate_mKK, intermediate_mKK + nov * std::max(KK * KK, 1), czero);
    for (int q2 = -L_; q2 <= L_; ++q2) {
      const int m2 = q2;
      fill(intermediate_mmK, intermediate_mmK + nv * std::max(KK, 1), czero);
      for (int q3 = -S_; q3 <= S_; ++q3, ++loop_counter) {
        const int m3 = m2 + q3;

        const double* cdata;

        if (q2 >= 0 && q3 == -S_) {
          const size_t key = sizem1 * (q2 + sizem2abs * (q1 + S_));
          size_t readsize = 0lu;
          for (int i = 0; i <= S_ * 2; ++i) readsize += num_int_each_[key + i];
          size_t datasize_acc = 0lu;
          for (int i = 0; i != key; ++i) datasize_acc += num_int_each_[i];
          get_block(datasize_acc, readsize, data_read);
          cdata = data_read;
        }
        else if (q2 >= 0) {
          cdata = data_read;
          const size_t key = S_ + sizem1 * (q2 + sizem2abs * (q1 + S_));
          for (int i = key - S_; i != key + q3; ++i) cdata += num_int_each_[i];
        }
        else { // q2 < 0
          const size_t key = q1 + S_ + sizem1 * (- q2 + sizem2abs * (q3 + S_));
          size_t datasize_acc = 0lu;
          for (int i = 0; i != key; ++i) datasize_acc += num_int_each_[i];
          get_block(datasize_acc, num_int_each_[key], data_read);
          cdata = data_read;
        }

        if (loop_mod10 < loop_counter * 10lu / num_loops) {
          loop_mod10++;
          std::cout << "  Loop " << loop_mod10 * 10lu << " percent done" << std::endl;
        }

        size_t local_counter = 0lu;

        blocks[0] = 0;
        int iall = 0;
        for (int i0 = 0; i0 != size; ++i0) {
          const int b0size = basis_[i0]->nbasis();
          for (int i1 = 0; i1 != size; ++i1) {
            const int b1size = basis_[i1]->nbasis();
            for (int i2 = 0; i2 != size; ++i2) {
              const int b2size = basis_[i2]->nbasis();
              for (int i3 = 0; i3 != size; ++i3, ++iall) {
                const int b3size = basis_[i3]->nbasis();

                double integral_bound;
                if (m2 >= 0) {
                  integral_bound = schwarz_[((q1 + K_) * size + i0) * size + i1]
                                 * schwarz_[((q3 + K_) * size + i2) * size + i3];
                } else {
                  integral_bound = schwarz_[((q1 + K_) * size + i2) * size + i3]
                                 * schwarz_[((q3 + K_) * size + i0) * size + i1];
                }
                const bool skip_schwarz = integral_bound < SCHWARZ_THRESH;
                blocks[iall + 1] = blocks[iall] + (skip_schwarz ? 0 : (b0size * b1size * b2size * b3size));
              }
            }
          }
        }

        #pragma omp parallel for
        for (int i0 = 0; i0 < size; ++i0) {
          int noffset = i0 * size * size * size;
          const int b0offset = offset(i0);
          const int b0size = nbasis(i0);
          for (int i1 = 0; i1 != size; ++i1) {
            const int b1offset = offset(i1);
            const int b1size = nbasis(i1);
            for (int i2 = 0; i2 != size; ++i2) {
              const int b2offset = offset(i2);
              const int b2size = nbasis(i2);
              for (int i3 = 0; i3 != size; ++i3, ++noffset) {
                const int b3offset = offset(i3);
                const int b3size = nbasis(i3);

                if (blocks[noffset] != blocks[noffset + 1]) {
                  const double* ndata = cdata + blocks[noffset];
                  std::complex<double>* label = data + b3offset + nbasis1 * (b2offset + nbasis1 * (b1offset + nbasis1 * b0offset));
                  for (int j0 = 0; j0 != b0size; ++j0, label += nbasis3) {
                    for (int j1 = 0; j1 != b1size; ++j1, label += nbasis2) {
                      for (int j2 = 0; j2 != b2size; ++j2, label += nbasis1) {
                        for (int j3 = 0; j3 != b3size; ++j3, ++label, ++ndata) {
                          *label = static_cast<std::complex<double> >(*ndata);
                        }
                        label -= b3size;
                      }
                      label -= b2size * nbasis1;
                    }
                    label -= b1size * nbasis2;
                  }
                } else {
                  std::complex<double>* label = data + b3offset + nbasis1 * (b2offset + nbasis1 * (b1offset + nbasis1 * b0offset));
                  for (int j0 = 0; j0 != b0size; ++j0, label += nbasis3) {
                    for (int j1 = 0; j1 != b1size; ++j1, label += nbasis2) {
                      for (int j2 = 0; j2 != b2size; ++j2, label += nbasis1) {
                        std::fill(label, label + b3size, czero);
                      }
                      label -= b2size * nbasis1;
                    }
                    label -= b1size * nbasis2;
                  }
                } // end of if skip_schwarz

              }
            }
          }
        } // end of shell loops; now data is ready

        if (m2 >= 0) { // start from j & b contractions -- needs transposition
          const int mn = nbasis2;
          mytranspose_complex_(data, &mn, &mn, datas);
          ::memcpy(data, datas, nbasis4 * sizeof(std::complex<double>));
        }

        #pragma omp parallel for
        for (int nkb = -K_; nkb < maxK1; ++nkb) {
          const int nkbc = nkb + K_;
          const std::complex<double> exponent(0.0, K_ != 0 ? (m3 * nkb * pi) / K_ : 0.0);
          const std::complex<double> prefac = exp(exponent);
          int offset1 = 0;
          int offset2 = 0;
          for (int ii = 0; ii != nbasis1; ++ii, offset1 += nbasis3,
                                                offset2 += nbasis2 * bsize) {
            zgemm_("N", "N", &nbasis2, &bsize, &nbasis1, &prefac, data + offset1, &nbasis2,
                                                         cabs_coeff->bp(nkb) + nbasis1 * bstart, &nbasis1, &cone,
                                                         intermediate_mmK + nv * nkbc + offset2, &nbasis2);
          }
        } // end of contraction b for given m3

      } // end of m3 loop

      // intermediate_mmK is ready
      #pragma omp parallel for
      for (int nkb = -K_; nkb < maxK1; ++nkb) {
        std::complex<double>* conjc2 = new std::complex<double>[nbasis1 * isize];
        const int nkbc = nkb + K_;
        int nbj = nkbc * KK;
        for (int nkj = -K_, nkjc = 0; nkj != maxK1; ++nkj, ++nbj, ++nkjc) {
          const std::complex<double> exponent(0.0, K_ != 0 ? (- m2 * nkj * pi) / K_ : 0.0);
          const std::complex<double> prefac = exp(exponent);

          const std::complex<double>* jdata = coeff->bp(nkj) + nbasis1 * jstart;
          for (int ii = 0; ii != nbasis1 * jsize; ++ii) conjc2[ii] = conj(jdata[ii]);
          const int nsize = nbasis2 * bsize;
          zgemm_("N", "N", &nsize, &jsize, &nbasis1, &prefac, intermediate_mmK + nv * nkbc, &nsize,
                                                              conjc2, &nbasis1, &cone,
                                                              intermediate_mKK + nov * nbj, &nsize);
        }
        delete[] conjc2;
      } // end of contraction j for given m2

    } // end of m2 loop

    // intermediate_mKK is ready
    for (int nkb = -K_, nbja = 0, nbj = 0; nkb != maxK1; ++nkb) {
      for (int nkj = -K_; nkj != maxK1; ++nkj, ++nbj) {
        ::memcpy(datas, intermediate_mKK + nov * nbj, nov * sizeof(std::complex<double>));
        {
          const int m = nbasis2;
          const int n = jsize * bsize;
          mytranspose_complex_(datas, &m, &n, data);
          std::fill(datas, datas + novv, czero);
        }

        #pragma omp parallel for
        for (int nka = -K_; nka < maxK1; ++nka) {
          const int nkac = nka + K_;
          const std::complex<double> exponent(0.0, K_ != 0 ? (m1 * nka * pi)/ K_ : 0.0);
          const std::complex<double> prefac = exp(exponent);
          const int nsize = jsize * bsize;
          int offset1 = 0;
          int offset2 = 0;
          for (int ii = 0; ii != nbasis1; ++ii, offset1 += nsize * nbasis1,
                                                offset2 += nsize * asize) {
            zgemm_("N", "N", &nsize, &asize, &nbasis1, &prefac, data + offset1, &nsize,
                                                                coeff->bp(nka) + nbasis1 * astart, &nbasis1, &czero,
                                                                datas + nkac * novv + offset2, &nsize);
          }
        }
        if (q1_front)
          intermediate_KKK.append(novv * std::max(KK, 1), datas);
        else
          intermediate_KKK.add_block(novv * nbja, novv * std::max(KK, 1), datas);
        nbja += std::max(KK, 1);
      }
    } // end of contraction a for given m1

    if (q1_front)
      intermediate_KKK.reopen_with_inout();

  } // end of m1 loop

  // now intermediate_KKK is ready.
  for (int nkb = -K_; nkb != maxK1; ++nkb) {
    int nbja = (nkb + K_) * KK * KK;
    for (int nkj = -K_; nkj != maxK1; ++nkj) {
      intermediate_KKK.get_block(novv * nbja, novv * std::max(KK, 1), data);
      #pragma omp parallel for
      for (int nka = -K_; nka < maxK1; ++nka) {
        std::complex<double>* conjc2 = new std::complex<double>[nbasis1 * isize];

        // momentum conservation
        int nki = nka + nkb - nkj;
        if (nki < - K_) nki += K_ * 2;
        else if (nki >=  K_) nki -= K_ * 2;

        const std::complex<double>* idata = coeff->bp(nki) + nbasis1 * istart;
        for (int ii = 0; ii != nbasis1 * isize; ++ii) conjc2[ii] = conj(idata[ii]);
        const int nsize = jsize * asize * bsize;
        zgemm_("N", "N", &nsize, &isize, &nbasis1, &cone, data + novv * (nka + K_), &nsize,
                                                          conjc2, &nbasis1, &czero,
                                                          datas + noovv * (nka + K_), &nsize);
        delete[] conjc2;
      }
      mo_int->append(noovv * std::max(KK, 1), datas);
      nbja += std::max(KK, 1);
    }
  } // end of contraction i

  delete[] data;
  delete[] datas;
  delete[] data_read;
  delete[] conjc;
  delete[] intermediate_mmK;
  delete[] intermediate_mKK;
  delete[] blocks;

  std::cout << "  done" << std::endl <<std::endl;
  mo_int->reopen_with_inout();
  return mo_int;

};


#endif

