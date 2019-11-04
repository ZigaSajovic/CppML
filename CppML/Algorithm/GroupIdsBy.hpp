//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_GROUP_IDS_BY_HPP
#define CPPML_GROUP_IDS_BY_HPP
#include "../Algorithm/Apply.hpp"
#include "../Algorithm/FilterIds.hpp"
#include "../Algorithm/UniqueCompare.hpp"
#include "../Functional/Compose.hpp"
#include "../Functional/Partial.hpp"

namespace ml {
/*
 * # GroupIdsBy:
 * Group indexes of elements given a By metafunction.
 * By :: T -> U
 * By operates on elements, not indexes.
 */
template <typename By, typename Pipe = ml::ToList> struct GroupIdsBy {
  template <typename... Ts>
  using f = typename ml::UniqueCompare<
      ml::Apply<By, ml::IsSame<>>,
      ml::Apply<ml::Compose<ml::InvokeWith<Ts...>, ml::F<ml::FilterIds>,
                            ml::PartialEvaluator<ml::Apply<By, ml::IsSame<>>>>,
                Pipe>>::template f<Ts...>;
};
} // namespace ml
#endif
