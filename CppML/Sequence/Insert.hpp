//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_INSERT_HPP
#define CPPML_INSERT_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/Invoke.hpp"
#include "../Functional/ToList.hpp"
#include "../Vocabulary/Const.hpp"
#include "PackExtractor.hpp"
namespace ml {
namespace Implementations {
/*
 * Implementation of Insert.
 */
template <bool Continue> struct InsertImpl {
  template <typename I, typename T, typename start, typename end, typename Pipe,
            typename Getter, typename... Ts>
  using f = typename ml::DelayedEval<
      InsertImpl<(start::value + 1 < end::value)>, sizeof...(Ts),
      ml::Int<(start::value != I::value ? I::value : -1)>, T,
      ml::Int<start::value + (start::value != I::value)>, end, Pipe, Getter,
      Ts...,
      ml::Invoke<ml::IfElse<start::value == I::value>, T,
                 ml::Invoke<Getter, start>>>;
};

template <> struct InsertImpl<false> {
  template <typename I, typename T, typename start, typename end, typename Pipe,
            typename Getter, typename... Ts>
  using f = ml::DelayedEval<Pipe, sizeof...(Ts), Ts...>;
};
struct Insert {
  template <int I, typename T, typename Pipe, typename... Ts>
  using f = typename Implementations::InsertImpl<static_cast<bool>(sizeof...(
      Ts))>::template f<ml::Int<I>, T, ml::Int<0>, ml::Int<sizeof...(Ts)>, Pipe,
                        ml::PackExtractor<Ts...>>;
};
}; // namespace Implementations
/*
 * # Insert:
 * Inserts T as the I-th element of the paramater pack.
 */
template <int I, typename T, typename Pipe = ml::ToList> struct Insert {
  template <typename... Ts>
  using f = ml::Implementations::Insert::template f<I, T, Pipe, Ts...>;
};
} // namespace ml
#endif
