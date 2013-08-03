//
// BAGEL - Parallel electron correlation program.
// Filename: lexical_cast.h
// Copyright (C) 2013 Toru Shiozaki
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

// Degraded version of lexical_cast.

#ifndef __SRC_UTIL_LEXICAL_CAST
#define __SRC_UTIL_LEXICAL_CAST

#include <sstream>

namespace bagel {
template<typename T, typename U> T lexical_cast(U in) {
  std::stringstream ss;
  ss << in;
  T out;
  ss >> out;
  return out;
}
}

#endif
