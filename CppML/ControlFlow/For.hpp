//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_FOR_HPP
#define CPPML_FOR_HPP
#include "../Functional/Identity.hpp"
#include "../Functional/Invoke.hpp"
#include "../Vocabulary/Value.hpp"

namespace ml {
/*
 * Implementation of For. Only ever instantiates two types.
 */
namespace Implementations {
template <bool Continue> struct For {
  template <int From, int To, typename Result, typename F>
  using f = typename For<(From + 1 < To)>::template f<
      From + 1, To, typename F::template f<ml::Int<From>, Result>, F>;
};
template <> struct For<false> {
  template <int From, int To, typename Result, typename F> using f = Result;
};
} // namespace Implementations

/*
 * For:
 * F(ml::Int<To - 1>, F(ml::Int<To - 2>, F....F(ml::Int<From>, State)))
 */
template <int From, int To, typename Pipe = ml::Identity> struct For {
  template <typename F, typename State>
  using f = ml::Invoke<Pipe, typename Implementations::For<(
                                 From < To)>::template f<From, To, State, F>>;
};
} // namespace ml
