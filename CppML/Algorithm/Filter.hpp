//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_FILTER_HPP
#define CPPML_FILTER_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/Invoke.hpp"
#include "../Functional/ToList.hpp"
#include "../Vocabulary/Const.hpp"

namespace ml {
/*
 * Implementation of Filter. Only ever instantiates 4 types
 */
namespace Implementations {
template <bool Continue> struct Filter;
namespace Detail {
template <bool Take> struct Filter {
  template <typename I, typename Predicate, typename Pipe, typename T,
            typename... Ts>
  using f =
      ml::DelayedEval<Implementations::Filter<(I::value > 1)>, sizeof...(Ts),
                      ml::Int<I::value - 1>, Predicate, Pipe, Ts..., T>;
};
template <> struct Filter<false> {
  template <typename I, typename Predicate, typename Pipe, typename T,
            typename... Ts>
  using f =
      ml::DelayedEval<Implementations::Filter<(I::value > 1)>, sizeof...(Ts),
                      ml::Int<I::value - 1>, Predicate, Pipe, Ts...>;
};
} // namespace Detail

template <bool Continue> struct Filter {
  template <typename I, typename Predicate, typename Pipe, typename T,
            typename... Ts>
  using f = ml::DelayedEval<Detail::Filter<ml::Invoke<Predicate, T>::value>,
                            sizeof...(Ts), I, Predicate, Pipe, T, Ts...>;
};
template <> struct Filter<false> {
  template <typename I, typename Predicate, typename Pipe, typename... Ts>
  using f = ml::DelayedEval<Pipe, sizeof...(Ts), Ts...>;
};
}; // namespace Implementations
/*
 * # Filter:
 * Returns elements satifying a predicate
 */
template <typename Predicate, typename Pipe = ml::ToList> struct Filter {
  template <typename... Ts>
  using f = ml::DelayedEval<
      Implementations::Filter<static_cast<bool>(sizeof...(Ts))>, sizeof...(Ts),
      ml::Int<sizeof...(Ts)>, Predicate, Pipe, Ts...>;
};

} // namespace ml
#endif
