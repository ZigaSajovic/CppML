/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_FILTER_HPP
#define CPPML_FILTER_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/Invoke.hpp"
#include "../Functional/ToList.hpp"
#include "../Pack/Get.hpp"
#include "../Vocabulary/Value.hpp"

namespace ml {
/*
 * Implementation of Filter. Only ever instantiates 4 types.
 */
namespace Implementations {
namespace Detail {
template <bool Continue> struct Filter;
template <bool Take> struct FilterGet {
  template <typename I, typename N, typename Predicate, typename Pipe,
            typename Getter, typename T, typename... Ts>
  using f =
      ml::f<ml::DelayedEval<Detail::Filter<(I::value > 1)>, sizeof...(Ts)>,
            ml::Int<I::value - 1>, N, Predicate, Pipe, Getter, Ts...,
            ml::Invoke<Getter, T, ml::Int<N::value - I::value>>>;
};
template <> struct FilterGet<false> {
  template <typename I, typename N, typename Predicate, typename Pipe,
            typename Getter, typename T, typename... Ts>
  using f =
      ml::f<ml::DelayedEval<Detail::Filter<(I::value > 1)>, sizeof...(Ts)>,
            ml::Int<I::value - 1>, N, Predicate, Pipe, Getter, Ts...>;
};

template <bool Continue> struct Filter {
  template <typename I, typename N, typename Predicate, typename Pipe,
            typename Getter, typename T, typename... Ts>
  using f =
      ml::f<ml::DelayedEval<Detail::FilterGet<ml::Invoke<Predicate, T>::value>,
                            sizeof...(Ts)>,
            I, N, Predicate, Pipe, Getter, T, Ts...>;
};
template <> struct Filter<false> {
  template <typename I, typename N, typename Predicate, typename Pipe,
            typename Getter, typename... Ts>
  using f = ml::f<ml::DelayedEval<Pipe, sizeof...(Ts)>, Ts...>;
};
} // namespace Detail
struct Filter {
  template <typename Predicate, typename Pipe, typename Getter, typename... Ts>
  using f =
      ml::f<ml::DelayedEval<Detail::Filter<static_cast<bool>(sizeof...(Ts))>,
                            sizeof...(Ts)>,
            ml::Int<sizeof...(Ts)>, ml::Int<sizeof...(Ts)>, Predicate, Pipe,
            Getter, Ts...>;
};
}; // namespace Implementations
/*
 * # Filter:
 * Returns elements satifying a predicate
 */
template <typename Predicate, typename Pipe = ml::ToList> struct Filter {
  template <typename... Ts>
  using f = ml::f<ml::DelayedEval<Implementations::Filter, sizeof...(Ts)>,
                  Predicate, Pipe, ml::Get<0>, Ts...>;
};

} // namespace ml
#endif
