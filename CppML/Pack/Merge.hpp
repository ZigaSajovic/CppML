//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_MERGE_HPP
#define CPPML_MERGE_HPP
#include "../Functional/ToList.hpp"

namespace ml {
namespace Implementations {
template <typename, typename> struct Merge2;
template <template <class...> class List, typename... Ts, typename... Us>
struct Merge2<List<Ts...>, List<Us...>> {
  using f = List<Ts..., Us...>;
};

template <bool Continue> struct Merge_impl {
  template <typename T, typename U, typename... Ts>
  using f = typename Merge_impl<(static_cast<bool>(
      sizeof...(Ts)))>::template f<typename Merge2<T, U>::f, Ts...>;
};

template <> struct Merge_impl<false> { template <typename T> using f = T; };
}; // namespace Implementations

/*
 * # Merge:
 * Merges `n` **List**-like types.
 */
struct Merge {
  template <typename T, typename... Ts>
  using f = typename Implementations::Merge_impl<static_cast<bool>(
      sizeof...(Ts))>::template f<T, Ts...>;
};
} // namespace ml
#endif
