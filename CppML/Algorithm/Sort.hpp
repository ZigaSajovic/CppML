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
template <typename Pipe = ml::ToList> struct ReplaceAndPrepend {
  template <typename T, typename U, typename... Ts>
  using f = typename ml::Prepend<typename ml::ReplaceIf<
      ml::Partial<ml::IsSame<>, T>, U, Pipe>::template f<Ts...>>::template f<T>;
};

template <bool Continue> struct Sort {
  template <typename Compare, typename T, typename... Ts>
  using f =
      typename ReplaceAndPrepend<Sort<static_cast<bool>(sizeof...(Ts) != 1)>> //
      ::template f<typename ml::MaxElement<Compare>::template f<Ts...>,       //
                   T,                                                         //
                   Compare,                                                   //
                   Ts...>;
};
template <> struct Sort<false> {
  template <typename Compare, typename T> using f = ml::ListT<T>;
};
template <bool Zero> struct SortBase {
  template <typename Compare, typename... Ts>
  using f = typename Sort<(sizeof...(Ts) > 1)>::template f<Compare, Ts...>;
};
template <> struct SortBase<true> {
  template <typename Compare> using f = ml::ListT<>;
};
} // namespace Implementations
template <typename Compare, typename Pipe = ml::ToList> struct Sort {
  template <typename... Ts>
  using f = typename Implementations::SortBase<sizeof...(Ts) ==
                                               0>::template f<Compare, Ts...>;
};
} // namespace ml
#endif
