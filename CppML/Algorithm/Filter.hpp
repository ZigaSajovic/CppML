//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_FILTER_HPP
#define CPPML_FILTER_HPP
#include "../Algorithm/Apply.hpp"
#include "../Functional/ToList.hpp"
#include "../Functional/UnList.hpp"
#include "../Pack/Append.hpp"
#include "../Pack/Get.hpp"
#include "../Pack/PackExtractor.hpp"
#include "../Vocabulary/Const.hpp"
#include "../Vocabulary/IfElse.hpp"
#include "../Vocabulary/List.hpp"

namespace ml {
/*
 * Implementation of Filter. It only ever instantiates two types.
 */
namespace Implementations {
template <bool Continue> struct Filter {
  template <int i, typename KeepList, typename Predicate, typename T,
            typename... Ts>
  using f = typename Filter<static_cast<bool>(sizeof...(Ts))>::template f<
      i + 1,
      typename ml::IfElse<Predicate::template f<T>::value>::template f<
          typename ml::UnList<ml::Append<ml::Int<i>>>::template f<KeepList>,
          KeepList>,
      Predicate, Ts...>;
};

template <> struct Filter<false> {
  template <int i, typename KeepList, typename Predicate> using f = KeepList;
};

}; // namespace Implementations
/*
 * FilterIds:
 * Returns list of indexes of elements satifying the predicate.
 * **NOTE** that it works with indexes instead of elements.
 */
template <typename Predicate, typename Pipe = ml::ToList> struct FilterIds {
  template <typename... Ts>
  using f = typename ml::UnList<Pipe>::template f<
      typename Implementations::Filter<(sizeof...(Ts) < 100000)>::template f<
          0, ml::ListT<>, Predicate, Ts...>>;
};
/*
 * Filter:
 * Filters elements, given a predicate.
 */
template <typename Predicate, typename Pipe = ml::ToList> struct Filter {
  template <typename... Ts>
  using f =
      typename ml::UnList<ml::Apply<PackExtractor<Ts...>, Pipe>>::template f<
          typename Implementations::Filter<(sizeof...(Ts) < 100000)>::
              template f<0, ml::ListT<>, Predicate, Ts...>>;
};

} // namespace ml
#endif
