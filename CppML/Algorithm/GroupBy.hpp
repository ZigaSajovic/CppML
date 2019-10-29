//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_GROUP_BY_HPP
#define CPPML_GROUP_BY_HPP
#include "../Algorithm/Filter.hpp"
#include "../Algorithm/Unique.hpp"
#include "../Functional/Compose.hpp"
#include "../Functional/Partial.hpp"

namespace ml {
/*
 * # GroupById:
 * GroupBy given a predicate factory. It returns lists of Indexes of elements.
 */
template <typename By, typename Pipe = ml::ToList> struct GroupById {
  template <typename... Ts>
  using f = typename ml::UniqueComp<
      By, ml::Apply<ml::Compose<ml::InvokeWith<Ts...>, ml::F<ml::FilterIds>,
                                ml::PartialEvaluator<By>>,
                    Pipe>>::template f<Ts...>;
};

/*
 * # GroupBy:
 * GroupBy given a predicate factory. It returns lists of elements.
 */
template <typename By, typename Pipe = ml::ToList> struct GroupBy {
  template <typename... Ts>
  using f = typename ml::UniqueComp<
      By, ml::Apply<ml::Compose<ml::InvokeWith<Ts...>, ml::F<ml::Filter>,
                                ml::PartialEvaluator<By>>,
                    Pipe>>::template f<Ts...>;
};
} // namespace ml
#endif
