/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_GROUP_IDS_BY_HPP
#define CPPML_GROUP_IDS_BY_HPP
#include "../Algorithm/FilterIds.hpp"
#include "../Algorithm/UniqueCompare.hpp"
#include "../Functional/Compose.hpp"
#include "../Functional/CurryR.hpp"
#include "../Functional/InvokeWith.hpp"
#include "../Functional/Map.hpp"

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
      ml::Map<By, ml::IsSame<>>,
      ml::Map<ml::Compose<ml::InvokeWith<Ts...>, ml::F<ml::FilterIds>,
                          ml::CurryR<ml::Map<By, ml::IsSame<>>>>,
              Pipe>>::template f<Ts...>;
};
} // namespace ml
#endif
