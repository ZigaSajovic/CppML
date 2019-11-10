//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_FIND_IF_NOT_HPP
#define CPPML_FIND_IF_NOT_HPP
#include "../Arithmetic/Not.hpp"
#include "../Functional/Compose.hpp"
#include "FindIf.hpp"

namespace ml {
/*
 * # FindIfNot:
 * Returns index of the element not matching the predicate
 */
template <typename Predicate, typename Pipe = ml::Identity> struct FindIfNot {
  template <typename... Ts>
  using f =
      ml::Invoke<Implementations::FindIf<static_cast<bool>(sizeof...(Ts) > 0)>,
                 ml::Int<0>, Pipe, ml::Compose<ml::Not<>, Predicate>, Ts...>;
};
} // namespace ml
#endif
