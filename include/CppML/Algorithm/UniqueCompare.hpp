/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_UNIQUE_COMPARE_HPP
#define CPPML_UNIQUE_COMPARE_HPP
#include "./Unique.hpp"

namespace ml {
template <typename Comparator, typename Pipe = ml::ToList>
struct UniqueCompare {
  template <typename... Ts>
  using f = ml::f<ml::DelayedEval<Implementations::Unique, sizeof...(Ts)>, Comparator,
                            Pipe, Ts...>;
};
} // namespace ml
#endif
