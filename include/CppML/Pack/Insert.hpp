/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_INSERT_HPP
#define CPPML_INSERT_HPP
#include "../Algorithm/Pivot.hpp"
#include "../Functional/Invoke.hpp"
#include "../Functional/ToList.hpp"
#include "../Pack/Prepend.hpp"
namespace ml {
/*
 * # Insert:
 * Inserts T as the I-th element of the pack.
 */
template <int I, typename T, typename Pipe = ml::ToList> struct Insert {
  template <typename... Ts>
  using f = ml::f<
      ml::Pivot<I, ml::Prepend<T, ml::Pivot<sizeof...(Ts) - I + 1, Pipe>>>,
      Ts...>;
};
} // namespace ml
#endif
