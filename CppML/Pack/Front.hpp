//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_FRONT_HPP
#define CPPML_FRONT_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/Identity.hpp"
#include "../Functional/Invoke.hpp"

namespace ml {
namespace Implementations {
struct Front {
  template <typename Pipe, typename T, typename... Ts>
  using f = ml::Invoke<Pipe, T>;
};
} // namespace Implementations
/*
 * # Front:
 * First element of a pack
 */
template <typename Pipe = ml::Identity> struct Front {
  template <typename... Ts>
  using f = ml::DelayedEval<Implementations::Front, sizeof...(Ts), Pipe, Ts...>;
};
} // namespace ml
#endif
