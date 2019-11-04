//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_FILTER_IDS_HPP
#define CPPML_FILTER_IDS_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/Invoke.hpp"
#include "../Functional/ToList.hpp"
#include "../Vocabulary/Const.hpp"

namespace ml {
/*
 * Implementation of FilterIds. Only ever instantiates 4 types
 */
namespace Implementations {
template <bool Continue> struct FilterIds;
namespace Detail {
template <bool Take> struct FilterIds {
  template <typename I, typename N, typename Predicate, typename Pipe,
            typename T, typename... Ts>
  using f = ml::DelayedEval<Implementations::FilterIds<(I::value > 1)>,
                            sizeof...(Ts), ml::Int<I::value - 1>, N, Predicate,
                            Pipe, Ts..., ml::Int<N::value - I::value>>;
};
template <> struct FilterIds<false> {
  template <typename I, typename N, typename Predicate, typename Pipe,
            typename T, typename... Ts>
  using f =
      ml::DelayedEval<Implementations::FilterIds<(I::value > 1)>, sizeof...(Ts),
                      ml::Int<I::value - 1>, N, Predicate, Pipe, Ts...>;
};
} // namespace Detail

template <bool Continue> struct FilterIds {
  template <typename I, typename N, typename Predicate, typename Pipe,
            typename T, typename... Ts>
  using f = ml::DelayedEval<Detail::FilterIds<ml::Invoke<Predicate, T>::value>,
                            sizeof...(Ts), I, N, Predicate, Pipe, T, Ts...>;
};
template <> struct FilterIds<false> {
  template <typename I, typename N, typename Predicate, typename Pipe,
            typename... Ts>
  using f = ml::DelayedEval<Pipe, sizeof...(Ts), Ts...>;
};
}; // namespace Implementations

/*
 * # FilterIds:
 * Return indexes of elements satifying a predicate
 */
template <typename Predicate, typename Pipe = ml::ToList> struct FilterIds {
  template <typename... Ts>
  using f = ml::DelayedEval<
      Implementations::FilterIds<static_cast<bool>(sizeof...(Ts))>,
      sizeof...(Ts), ml::Int<sizeof...(Ts)>, ml::Int<sizeof...(Ts)>, Predicate,
      Pipe, Ts...>;
};

} // namespace ml
#endif
