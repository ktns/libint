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

#ifndef _libint2_src_bin_libint_compxyz_h_
#define _libint2_src_bin_libint_compxyz_h_

#include <generic_rr.h>

using namespace std;

namespace libint2 {

//  class CR_DerivGauss_GenericInstantiator {
//      static CR_DerivGauss_GenericInstantiator instance_;
//
//      CR_DerivGauss_GenericInstantiator(); // this is a singleton
//      ~CR_DerivGauss_GenericInstantiator();
//
//      // pairs of L,vectorize specify the instances of GenericGaussDeriv template to be created
//      std::set<std::pair<unsigned int, bool> > template_instances_;
//
//    public:
//      static CR_DerivGauss_GenericInstantiator& instance();
//      void add(unsigned int L, bool vectorize);
//  };

  /**
   * this computes integral over Oper over CGShell/CGF as a product of 1-d integrals
   * @tparam F basis function type. valid choices are CGShell or CGF
  */
  template <typename F, typename Oper, typename AuxQuanta = EmptySet>
  class CR_XYZ_1_1 : public GenericRecurrenceRelation< CR_XYZ_1_1<F,Oper,AuxQuanta>,
                                                       F,
                                                       GenIntegralSet_1_1<F,Oper,AuxQuanta> >
  {
    public:
      typedef CR_XYZ_1_1<F, Oper, AuxQuanta> ThisType;
      typedef F BasisFunctionType;
      typedef GenIntegralSet_1_1<F,Oper,AuxQuanta> TargetType;
      typedef GenericRecurrenceRelation<ThisType,BasisFunctionType,TargetType> ParentType;
      friend class GenericRecurrenceRelation<ThisType,BasisFunctionType,TargetType>;
      static const unsigned int max_nchildren = 100;

      using ParentType::Instance;

      static bool directional() { return false; }

    private:
      using ParentType::RecurrenceRelation::expr_;
      using ParentType::RecurrenceRelation::nflops_;
      using ParentType::target_;
      using ParentType::is_simple;

      /// Constructor is private, used by ParentType::Instance that mainains registry of these objects
      CR_XYZ_1_1(const SafePtr<TargetType>&, unsigned int dir = 0);

      static std::string descr() { return "CR"; }

      /// specialize this for the given operator type and CGF
      void compute(const BasisFunctionType& bra, const BasisFunctionType& ket);
  };

  template <typename F, typename Oper, typename AuxQuanta>
  CR_XYZ_1_1<F,Oper,AuxQuanta>::CR_XYZ_1_1(const SafePtr< TargetType >& Tint,
                                           unsigned int dir) :
    ParentType(Tint,dir)
    {
      // WARNING assuming one function per position
      const auto& a = Tint->bra(0,0);
      const auto& b = Tint->ket(0,0);
      const auto& aux = Tint->aux();
      const auto& oper = Tint->oper();

      {
        // can't apply to contracted basis functions
        if (a.contracted() || b.contracted())
          return;
        // can't apply to differentiated CGF (derivatives will be expanded first)
        if (TrivialBFSet<F>::result &&
            (a.deriv().norm() != 0 ||
             b.deriv().norm() != 0))
          return;
      }

      // shell set? for now assume it will be unrolled
//      auto F_is_shell = std::is_same<F,CGShell>::value;
//      assert (not F_is_shell);
//        {
//          typedef CGShell1d<CartesianAxis_X> F1;
//          typedef GenIntegralSet_1_1<F1,Oper,AuxQuanta> ChildType;
//          ChildFactory<ThisType,ChildType> factory(this);
//          F1 a_(a.norm() + a.deriv().norm());
//          F1 b_(b.norm() + b.deriv().norm());
//          auto _ = factory.make_child(a_,b_);
//        }
//        {
//          typedef CGShell1d<CartesianAxis_Y> F1;
//          typedef GenIntegralSet_1_1<F1,Oper,AuxQuanta> ChildType;
//          ChildFactory<ThisType,ChildType> factory(this);
//          F1 a_(a.norm() + a.deriv().norm());
//          F1 b_(b.norm() + b.deriv().norm());
//          auto _ = factory.make_child(a_,b_);
//        }
//        {
//          typedef CGShell1d<CartesianAxis_Z> F1;
//          typedef GenIntegralSet_1_1<F1,Oper,AuxQuanta> ChildType;
//          ChildFactory<ThisType,ChildType> factory(this);
//          F1 a_(a.norm() + a.deriv().norm());
//          F1 b_(b.norm() + b.deriv().norm());
//          auto _ = factory.make_child(a_,b_);
//        }

      compute(a,b);

      return;
    } // CR_XYZ_1_1<F,Oper,AuxQuanta>::CR_XYZ_1_1

}; // namespace libint2

#endif