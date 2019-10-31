//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_UNIQUE_HPP
#define CPPML_UNIQUE_HPP
#include "../Algorithm/Any.hpp"
#include "../Algorithm/Apply.hpp"
#include "../Functional/Partial.hpp"
#include "../Functional/ToList.hpp"
#include "../Functional/UnList.hpp"
#include "../Sequence/Append.hpp"
#include "../Sequence/PackExtractor.hpp"
#include "../TypeTraits/IsSame.hpp"

namespace ml {
/*
 * Implementation of Unique. Only ever instantiates two types.
 * **NOTE** that it works with indexes instead of elements.
 */
namespace Implementations {
template <bool Continue> struct Unique {
  template <int i, typename Comparator, typename KeepList, typename T,
            typename... Ts>
  using f = typename Unique<static_cast<bool>(sizeof...(Ts))>::template f<
      i + 1, Comparator,
      typename ml::IfElse<
          !ml::Invoke<ml::Any<ml::Partial<Comparator, T>>, Ts...>::value>::
          template f<typename ml::Append<KeepList>::template f<ml::Int<i>>,
                     KeepList>,
      Ts...>;
};

template <> struct Unique<false> {
  template <int i, typename Comparator, typename KeepList> using f = KeepList;
};
} // namespace Implementations
/*
 * # UniqueIdsComp:
 * Returns Ids of unique elements, given a Comparator
 */
template <typename Comparator, typename Pipe = ml::ToList>
struct UniqueIdsComp {
  template <typename... Ts>
  using f = typename ml::UnList<Pipe>::template f<
      typename Implementations::Unique<static_cast<bool>(
          sizeof...(Ts))>::template f<0, Comparator, ml::ListT<>, Ts...>>;
};
/*
 * # UniqueIds:
 * Returns Ids of unique elements
 */
template <typename Pipe = ml::ToList> struct UniqueIds {
  template <typename... Ts>
  using f = typename ml::UnList<Pipe>::template f<
      typename Implementations::Unique<static_cast<bool>(
          sizeof...(Ts))>::template f<0, ml::IsSame<>, ml::ListT<>, Ts...>>;
};
/*
 * # UniqueComp:
 * Returns unique elements, given a Comparator
 */
template <typename Comparator, typename Pipe = ml::ToList> struct UniqueComp {
  template <typename... Ts>
  using f = typename ml::UnList<ml::Apply<ml::PackExtractor<Ts...>, Pipe>>::
      template f<typename Implementations::Unique<static_cast<bool>(
          sizeof...(Ts))>::template f<0, Comparator, ml::ListT<>, Ts...>>;
};
/*
 * # Unique:
 * Returns unique elements
 */
template <typename Pipe = ml::ToList> struct Unique {
  template <typename... Ts>
  using f = typename ml::UnList<ml::Apply<ml::PackExtractor<Ts...>, Pipe>>::
      template f<typename Implementations::Unique<static_cast<bool>(
          sizeof...(Ts))>::template f<0, ml::IsSame<>, ml::ListT<>, Ts...>>;
};

} // namespace ml
#endif
