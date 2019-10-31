//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_HEAD_HPP
#define CPPML_HEAD_HPP
#include "../Algorithm/Pivot.hpp"
#include "../Functional/ToList.hpp"
#include "../Sequence/Drop.hpp"
namespace ml {
/*
 * # Head:
 * Returns the first N elements
 */
template <int N, typename Pipe = ml::ToList> struct Head {
  template <typename... Ts>
  using f =
      typename ml::Pivot<N,
                         ml::Drop<sizeof...(Ts) - N, Pipe>>::template f<Ts...>;
};
} // namespace ml
#endif
