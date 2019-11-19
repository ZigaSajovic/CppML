/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_IF_VALID_OR_HPP
#define CPPML_IF_VALID_OR_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Value.hpp"
#include "./VoidT.hpp"
namespace ml {
namespace Implementations {
template <typename T> struct R { using f = T; };

template <typename, class U, class T, class... Ts>
struct IfValidOr_impl : R<U> {};

template <class U, class F, typename... Ts>
struct IfValidOr_impl<VoidT<ml::f<ml::DelayedEval<F, sizeof...(Ts)>, Ts...>>, U,
                      F, Ts...>
    : R<ml::f<ml::DelayedEval<F, sizeof...(Ts)>, Ts...>> {};
}; // namespace Implementations
/*
 * IfValidOr:
 * If the metafunction F is valid, evaluate to its result,
 * else evaluate to Default.
 */
template <typename Pipe = ml::Identity> struct IfValidOr {
  template <class Default, class F, class... Ts>
  using f = typename Pipe::template f<
      typename Implementations::IfValidOr_impl<void, Default, F, Ts...>::f>;
};

} // namespace ml
#endif
