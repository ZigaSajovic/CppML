/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_CONCAT_HPP
#define CPPML_CONCAT_HPP
#include "../Functional/ToList.hpp"

namespace ml {
namespace Implementations {
template <typename, typename> struct Concat2;
template <template <class...> class List, typename... Ts, typename... Us>
struct Concat2<List<Ts...>, List<Us...>> {
  using f = List<Ts..., Us...>;
};

template <bool Continue> struct Concat_impl {
  template <typename T, typename U, typename... Ts>
  using f = typename Concat_impl<(static_cast<bool>(
      sizeof...(Ts)))>::template f<typename Concat2<T, U>::f, Ts...>;
};

template <> struct Concat_impl<false> { template <typename T> using f = T; };
}; // namespace Implementations

/*
 * # Concat:
 * Concats `n` **List**-like types.
 */
struct Concat {
  template <typename T, typename... Ts>
  using f = typename Implementations::Concat_impl<static_cast<bool>(
      sizeof...(Ts))>::template f<T, Ts...>;
};
} // namespace ml
#endif
