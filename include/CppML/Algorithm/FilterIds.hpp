/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_FILTER_IDS_HPP
#define CPPML_FILTER_IDS_HPP
#include "./Filter.hpp"

namespace ml {
/*
 * # FilterIds:
 * Returns indexes of elements satifying a predicate
 */
template <typename Predicate, typename Pipe = ml::ToList> struct FilterIds {
  template <typename... Ts>
  using f = ml::f<ml::DelayedEval<Implementations::Filter, sizeof...(Ts)>,
                  Predicate, Pipe, ml::Get<1>, Ts...>;
};
} // namespace ml
#endif
