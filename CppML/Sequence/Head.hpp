//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_TAIL_HPP
#define CPPML_TAIL_HPP
#include "../Algorithm/Apply.hpp"
#include "../Functional/ToList.hpp"
#include "PackExtractor.hpp"
#include "Range.hpp"

/*
 * Implementation of Head. It only ever instantiates one type
 * (the pack extractor).
 */
namespace ml {
namespace Implementations {
struct Head {
  template <int N, typename Pipe, typename... Ts>
  using f = typename ml::TypeRange<
      ml::Apply<ml::PackExtractor<Ts...>, Pipe>>::template f<0, N>;
};
} // namespace Implementations

/*
 * # Head:
 * Returns the first N elements
 */
template <int N, typename Pipe = ml::ToList> struct Head {
  template <typename... Ts>
  using f = Implementations::Head::template f<N, Pipe, Ts...>;
};
} // namespace ml
