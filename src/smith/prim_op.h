//
// BAGEL - Parallel electron correlation program.
// Filename: prim_op.h
// Copyright (C) 2012 Toru Shiozaki
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


#ifndef __SRC_SMITH_PRIM_OP_H
#define __SRC_SMITH_PRIM_OP_H

#include <stddef.h>
#include <memory>
#include <vector>
#include <cassert>
#include <src/util/f77.h>

namespace bagel {
namespace SMITH {


template <int an, int ad, int fn, int fd, class T>
static void sort_indices(const std::unique_ptr<T[]>& unsorted, std::unique_ptr<T[]>& sorted) {
  const T afac = static_cast<T>(an) /static_cast<T>(ad);
  const T factor = static_cast<T>(fn) /static_cast<T>(fd);
  if (an != 0)
    sorted[0] = sorted[0]*afac + unsorted[0]*factor;
  else
    sorted[0] = unsorted[0]*factor;
}


template <int i, int an, int ad, int fn, int fd, class T>
static void sort_indices(const std::unique_ptr<T[]>& unsorted, std::unique_ptr<T[]>& sorted,
                         const int a) { // according to unsorted
  static_assert(ad != 0 && fd != 0, "sort_indices, prefactor");
  const T afac = static_cast<T>(an) /static_cast<T>(ad);
  const T factor = static_cast<T>(fn) /static_cast<T>(fd);
  {
    int id[1];
    int jd[1] = {a};
    long iall=0;
    for(int j0=0;j0<(int)a;++j0,++iall){
      id[0]=j0;
      long ib=id[i];
      if (an != 0)
        sorted[ib]=afac*sorted[ib]+unsorted[iall]*factor;
      else
        sorted[ib]=unsorted[iall]*factor;
    }
    assert(iall == a);
  }
}


template <int i, int j, int an, int ad, int fn, int fd, class T>
static void sort_indices(const std::unique_ptr<T[]>& unsorted, std::unique_ptr<T[]>& sorted,
                         const int b, const int a) { // according to unsorted
  static_assert(ad != 0 && fd != 0, "sort_indices, prefactor");
  const T afac = static_cast<T>(an) /static_cast<T>(ad);
  const T factor = static_cast<T>(fn) /static_cast<T>(fd);
  {
    int id[2];
    int jd[2] = {b, a};
    long iall=0;
    for(int j0=0;j0<(int)a;++j0){
      id[1]=j0;
      for(int j1=0;j1<(int)b;++j1,++iall){
        id[0]=j1;
        long ib=id[i]+jd[i]*id[j];
        if (an != 0)
          sorted[ib]=afac*sorted[ib]+unsorted[iall]*factor;
        else
          sorted[ib]=unsorted[iall]*factor;
      }
    }
    assert(iall == b*a);
  }
}


template<int i, int j, int k, int an, int ad, int fn, int fd, class T>
static void sort_indices(const T* const unsorted, T* const sorted,
                         const int d,const int c,const int b) { // according to unsorted
  static_assert(ad != 0 && fd != 0, "sort_indices, prefactor");
  const T afac = static_cast<T>(an) /static_cast<T>(ad);
  const T factor = static_cast<T>(fn) /static_cast<T>(fd);
  int id[3];
  int jd[3] = {d, c, b};

  long iall=0;
  for(int j1=0;j1<b;++j1){
    id[2]=j1;
    for(int j2=0;j2<c;++j2){
      id[1]=j2;
      for (int j3=0;j3<d;++j3,++iall){
        id[0]=j3;
        long ib=id[i]+jd[i]*(id[j]+jd[j]*id[k]);
        if (an != 0)
          sorted[ib]=afac*sorted[ib]+unsorted[iall]*factor;
        else
          sorted[ib]=unsorted[iall]*factor;
      }
    }
  }
}


template<int i, int j, int k, int an, int ad, int fn, int fd, class T>
static void sort_indices(const std::unique_ptr<T[]>& unsorted, std::unique_ptr<T[]>& sorted,
                         const int d,const int c,const int b) { // according to unsorted
  sort_indices<i,j,k,an,ad,fn,fd>(unsorted.get(), sorted.get(), d, c, b);
}


// CAUTION :: I have changed the convention from that in mpqc.
template<int i, int j, int k, int l, int an, int ad, int fn, int fd, class T>
static void sort_indices(const T* unsorted, T* sorted,
                         const int d, const int c, const int b, const int a) { // according to unsorted
  static_assert(ad != 0 && fd != 0, "sort_indices, prefactor");
  const T afac = static_cast<T>(an) /static_cast<T>(ad);
  const T factor = static_cast<T>(fn) /static_cast<T>(fd);
  int id[4];
  int jd[4] = {d, c, b, a};

  long iall=0;
  for(int j0=0;j0<a;++j0){
    id[3]=j0;
    for(int j1=0;j1<b;++j1){
      id[2]=j1;
      for(int j2=0;j2<c;++j2){
        id[1]=j2;
        for(int j3=0;j3<d;++j3,++iall){
          id[0]=j3;
          long ib=id[i]+jd[i]*(id[j]+jd[j]*(id[k]+jd[k]*id[l]));
          if (an != 0)
            sorted[ib]=afac*sorted[ib]+unsorted[iall]*factor;
          else
            sorted[ib]=unsorted[iall]*factor;
        }
      }
    }
  }
}


template<int i, int j, int k, int l, int an, int ad, int fn, int fd, class T>
static void sort_indices(const std::unique_ptr<T[]>& unsorted, std::unique_ptr<T[]>& sorted,
                         const int d, const int c, const int b, const int a) { // according to unsorted
  sort_indices<i,j,k,l,an,ad,fn,fd>(unsorted.get(), sorted.get(), d, c, b, a);
}


template<int i, int j, int k, int l, int m, int an, int ad, int fn, int fd, class T>
static void sort_indices(const T* unsorted, T* sorted,
                         const int e, const int d, const int c, const int b, const int a) { // according to unsorted
  static_assert(ad != 0 && fd != 0, "sort_indices, prefactor");
  const T afac = static_cast<T>(an) /static_cast<T>(ad);
  const T factor = static_cast<T>(fn) /static_cast<T>(fd);
  int id[5];
  int jd[5] = {e, d, c, b, a};

  long iall=0;
  for(int j0=0;j0<a;++j0){
    id[4]=j0;
    for(int j1=0;j1<b;++j1){
      id[3]=j1;
      for(int j2=0;j2<c;++j2){
        id[2]=j2;
        for(int j3=0;j3<d;++j3){
          id[1]=j3;
          for(int j4=0;j4<e;++j4,++iall){
            id[0]=j4;
            long ib=id[i]+jd[i]*(id[j]+jd[j]*(id[k]+jd[k]*(id[l]+jd[l]*id[m])));
            if (an != 0)
              sorted[ib]=afac*sorted[ib]+unsorted[iall]*factor;
            else
              sorted[ib]=unsorted[iall]*factor;
          }
        }
      }
    }
  }
}


template<int i, int j, int k, int l, int m, int an, int ad, int fn, int fd, class T>
static void sort_indices(const std::unique_ptr<T[]>& unsorted, std::unique_ptr<T[]>& sorted,
                         const int e, const int d, const int c, const int b, const int a) { // according to unsorted
  sort_indices<i,j,k,l,m,an,ad,fn,fd>(unsorted.get(), sorted.get(), e, d, c, b, a);
}


template<int i, int j, int k, int l, int m, int n, int an, int ad, int fn, int fd, class T>
static void sort_indices(const T* unsorted, T* sorted,
                         const int f, const int e, const int d, const int c, const int b, const int a) { // according to unsorted
  static_assert(ad != 0 && fd != 0, "sort_indices, prefactor");
  const T afac = static_cast<T>(an) /static_cast<T>(ad);
  const T factor = static_cast<T>(fn) /static_cast<T>(fd);
  int id[6];
  int jd[6] = {f, e, d, c, b, a};

  long iall=0;
  for(int j0=0;j0<a;++j0){
    id[5]=j0;
    for(int j1=0;j1<b;++j1){
      id[4]=j1;
      for(int j2=0;j2<c;++j2){
        id[3]=j2;
        for(int j3=0;j3<d;++j3){
          id[2]=j3;
          for(int j4=0;j4<e;++j4){
            id[1]=j4;
            for (int j5=0;j5<f;++j5,++iall){
              id[0]=j5;
              long ib=id[i]+jd[i]*(id[j]+jd[j]*(id[k]+jd[k]*(id[l]+jd[l]*(id[m]+jd[m]*(id[n])))));
              if (an != 0)
                sorted[ib]=afac*sorted[ib]+unsorted[iall]*factor;
              else
                sorted[ib]=unsorted[iall]*factor;
            }
          }
        }
      }
    }
  }
}


template<int i, int j, int k, int l, int m, int n, int an, int ad, int fn, int fd, class T>
static void sort_indices(const std::unique_ptr<T[]>& unsorted, std::unique_ptr<T[]>& sorted,
                         const int f, const int e, const int d, const int c, const int b, const int a) { // according to unsorted
  sort_indices<i,j,k,l,m,n,an,ad,fn,fd>(unsorted.get(), sorted.get(), f, e, d, c, b, a);
}


template<int i, int j, int k, int l, int m, int n, int o, int an, int ad, int fn, int fd, class T>
static void sort_indices(const T* unsorted, T* sorted,
                         const int g, const int f, const int e, const int d, const int c, const int b, const int a) { // according to unsorted
  static_assert(ad != 0 && fd != 0, "sort_indices, prefactor");
  const T afac = static_cast<T>(an) /static_cast<T>(ad);
  const T factor = static_cast<T>(fn) /static_cast<T>(fd);
  int id[7];
  int jd[7] = {g, f, e, d, c, b, a};

  long iall=0;
  for(int j0=0;j0<a;++j0){
    id[5]=j0;
    for(int j1=0;j1<b;++j1){
      id[5]=j1;
      for(int j2=0;j2<c;++j2){
        id[4]=j2;
        for(int j3=0;j3<d;++j3){
          id[3]=j3;
          for(int j4=0;j4<e;++j4){
            id[2]=j4;
            for(int j5=0;j5<f;++j5){
              id[1]=j5;
              for (int j6=0;j6<g;++j6,++iall){
                id[0]=j6;
                long ib=id[i]+jd[i]*(id[j]+jd[j]*(id[k]+jd[k]*(id[l]+jd[l]*(id[m]+jd[m]*(id[n]+jd[n]*(id[o]))))));
                if (an != 0)
                  sorted[ib]=afac*sorted[ib]+unsorted[iall]*factor;
                else
                  sorted[ib]=unsorted[iall]*factor;
              }
            }
          }
        }
      }
    }
  }
}

template<int i, int j, int k, int l, int m, int n, int o, int an, int ad, int fn, int fd, class T>
static void sort_indices(const std::unique_ptr<T[]>& unsorted, std::unique_ptr<T[]>& sorted,
                         const int g, const int f, const int e, const int d, const int c, const int b, const int a) { // according to unsorted
  sort_indices<i,j,k,l,m,n,o,an,ad,fn,fd>(unsorted.get(), sorted.get(), g, f, e, d, c, b, a);
}


template<int i, int j, int k, int l, int m, int n, int o, int p, int an, int ad, int fn, int fd, class T>
static void sort_indices(const T* unsorted, T* sorted,
                         const int h, const int g, const int f, const int e, const int d, const int c, const int b, const int a) { // according to unsorted
  static_assert(ad != 0 && fd != 0, "sort_indices, prefactor");
  const T afac = static_cast<T>(an) /static_cast<T>(ad);
  const T factor = static_cast<T>(fn) /static_cast<T>(fd);
  int id[8];
  int jd[8] = {h, g, f, e, d, c, b, a};

  long iall=0;
  for(int j0=0;j0<a;++j0){
    id[7]=j0;
    for(int j1=0;j1<b;++j1){
      id[6]=j1;
      for(int j2=0;j2<c;++j2){
        id[5]=j2;
        for(int j3=0;j3<d;++j3){
          id[4]=j3;
          for(int j4=0;j4<e;++j4){
            id[3]=j4;
            for (int j5=0;j5<f;++j5){
              id[2]=j5;
              for (int j6=0;j6<g;++j6){
                id[1]=j6;
                for (int j7=0;j7<h;++j7,++iall){
                  id[0]=j7;
                  long ib=id[i]+jd[i]*(id[j]+jd[j]*(id[k]+jd[k]*(id[l]+jd[l]*(id[m]+jd[m]*(id[n]+jd[n]*(id[o]+jd[o]*(id[p])))))));
                  if (an != 0)
                    sorted[ib]=afac*sorted[ib]+unsorted[iall]*factor;
                  else
                    sorted[ib]=unsorted[iall]*factor;
                }
              }
            }
          }
        }
      }
    }
  }
}

template<int i, int j, int k, int l, int m, int n, int o, int p, int an, int ad, int fn, int fd, class T>
static void sort_indices(const std::unique_ptr<T[]>& unsorted, std::unique_ptr<T[]>& sorted,
                         const int h, const int g, const int f, const int e, const int d, const int c, const int b, const int a) { // according to unsorted
  sort_indices<i,j,k,l,m,n,o,p,an,ad,fn,fd>(unsorted.get(), sorted.get(), h, g, f, e, d, c, b, a);
}


template<int i, int j, int k, int l, int m, int n, int o, int p, int q, int an, int ad, int fn, int fd, class T>
static void sort_indices(const T* unsorted, T* sorted,
                         const int ia, const int h, const int g, const int f, const int e, const int d, const int c, const int b, const int a) { // according to unsorted
  static_assert(ad != 0 && fd != 0, "sort_indices, prefactor");
  const T afac = static_cast<T>(an) /static_cast<T>(ad);
  const T factor = static_cast<T>(fn) /static_cast<T>(fd);
  int id[9];
  int jd[9] = {ia, h, g, f, e, d, c, b, a};

  long iall=0;
  for(int j0=0;j0<a;++j0){
    id[8]=j0;
    for(int j1=0;j1<b;++j1){
      id[7]=j1;
      for(int j2=0;j2<c;++j2){
        id[6]=j2;
        for(int j3=0;j3<d;++j3){
          id[5]=j3;
          for(int j4=0;j4<e;++j4){
            id[4]=j4;
            for(int j5=0;j5<f;++j5){
              id[3]=j5;
              for (int j6=0;j6<g;++j6){
                id[2]=j6;
                for (int j7=0;j7<h;++j7){
                  id[1]=j7;
                  for (int j8=0;j8<ia;++j8,++iall){
                    id[0]=j8;
                    long ib=id[i]+jd[i]*(id[j]+jd[j]*(id[k]+jd[k]*(id[l]+jd[l]*(id[m]+jd[m]*(id[n]+jd[n]*(id[o]+jd[o]*(id[p]+jd[p]*(id[q]))))))));
                    if (an != 0)
                      sorted[ib]=afac*sorted[ib]+unsorted[iall]*factor;
                    else
                      sorted[ib]=unsorted[iall]*factor;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

template<int i, int j, int k, int l, int m, int n, int o, int p, int q, int an, int ad, int fn, int fd, class T>
static void sort_indices(const std::unique_ptr<T[]>& unsorted, std::unique_ptr<T[]>& sorted,
                         const int ia, const int h, const int g, const int f, const int e, const int d, const int c, const int b, const int a) { // according to unsorted
  sort_indices<i,j,k,l,m,n,o,p,q,an,ad,fn,fd>(unsorted.get(), sorted.get(), ia, h, g, f, e, d, c, b, a);
}



}
}

#endif
