//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_SORT_HPP
#define CPPML_SORT_HPP
#include "../Functional/Invoke.hpp"
#include "../Functional/MaxElement.hpp"
#include "../Functional/Partial.hpp"
#include "../Functional/ToList.hpp"
#include "../Functional/UnList.hpp"
#include "../Sequence/Prepend.hpp"
#include "../TypeTraits/IsSame.hpp"
#include "ReplaceIf.hpp"

namespace ml {
namespace Implementations {
template <typename T, typename U, typename Pipe = ToList>
struct ReplaceAndPrepend {
  template <typename... Ts>
  using f = typename Prepend<typename ml::ReplaceIf<
      ml::Partial<ml::IsSame<>, T>, U, Pipe>::template f<Ts...>>::template f<T>;
};

template <bool, typename Compare> struct SortImpl {
  template <typename T, typename... Ts>
  using f = typename ReplaceAndPrepend<
      typename ml::MaxEement<Compare>::template f<Ts...>, T,
      SortImpl<(sizeof...(Ts) != 1), Compare>>::template f<Ts...>;
};

template <typename Compare> struct SortImpl<false, Compare> {
  template <typename T> using f = ListT<T>;
};

template <bool, typename Compare, typename Pipe> struct SortBase {
  template <typename... Ts>
  using f =
      Invoke<UnList<Pipe>,
             typename SortImpl<sizeof...(Ts) != 1, Compare>::template f<Ts...>>;
};

template <typename Compare, typename Pipe>
struct SortBase<false, Compare, Pipe> {
  template <typename... Ts> using f = typename Pipe::template f<Ts...>;
};
}; // namespace Implementations
/*
 * Sort:
 * Sorts a unique list of types
 */
template <typename Compare, typename Pipe = ToList> struct Sort {
  template <typename... Ts>
  using f = typename Implementations::SortBase<sizeof...(Ts) != 0, Compare,
                                               Pipe>::template f<Ts...>;
};
} // namespace ml
#endif
