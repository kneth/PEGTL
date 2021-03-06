// Copyright (c) 2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef PEGTL_INTERNAL_BOL_HH
#define PEGTL_INTERNAL_BOL_HH

#include "../config.hh"

#include "skip_control.hh"

#include "../analysis/generic.hh"

namespace PEGTL_NAMESPACE
{
   namespace internal
   {
      struct bol
      {
         using analyze_t = analysis::generic< analysis::rule_type::OPT >;

         template< typename Input >
         static bool match( Input & in )
         {
            return in.byte_in_line() == 0;
         }
      };

      template<>
      struct skip_control< bol > : std::true_type {};

   } // namespace internal

} // namespace PEGTL_NAMESPACE

#endif
