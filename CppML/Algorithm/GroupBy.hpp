//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_GROUP_BY_HPP
#define CPPML_GROUP_BY_HPP
#include "../Algorithm/Filter.hpp"
#include "../Algorithm/UniqueCompare.hpp"
#include "../Functional/Compose.hpp"
#include "../Functional/InvokeWith.hpp"
#include "../Functional/Map.hpp"
#include "../Functional/PartialEvaluator.hpp"

namespace ml {
/*
 * # GroupBy:
 * Group indexes of elements given a By metafunction.
 * By :: T -> U
 */
template <typename By, typename Pipe = ml::ToList> struct GroupBy {
  template <typename... Ts>
  using f = typename ml::UniqueCompare<
      ml::Map<By, ml::IsSame<>>,
      ml::Map<ml::Compose<ml::InvokeWith<Ts...>, ml::F<ml::Filter>,
                          ml::PartialEvaluator<ml::Map<By, ml::IsSame<>>>>,
              Pipe>>::template f<Ts...>;
};
} // namespace ml
#endif
