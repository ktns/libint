/*
 *  This file is a part of Libint.
 *  Copyright (C) 2004-2014 Edward F. Valeev
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see http://www.gnu.org/licenses/.
 *
 */

#ifndef _libint2_src_bin_libint_r12kg121111_h_
#define _libint2_src_bin_libint_r12kg121111_h_

#include <integral.h>
#include <integral_11_11.h>

using namespace std;

namespace libint2 {

  template <>
  inline bool
    GenIntegralSet_11_11<CGF,R12kG12,mType>::this_precomputed() const
    {
#if USE_BRAKET_H
      if (parent_type::bra_.member(0,0).zero() && parent_type::bra_.member(1,0).zero() &&
          parent_type::ket_.member(0,0).zero() && parent_type::ket_.member(1,0).zero())
#else
      if (parent_type::bra_.member(0,0)->zero() && parent_type::bra_.member(1,0)->zero() &&
          parent_type::ket_.member(0,0)->zero() && parent_type::ket_.member(1,0)->zero())
#endif
        return true;
      else
         return false;
    }
};

#endif

