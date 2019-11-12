/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_REMOVE_IF_HPP
#define CPPML_REMOVE_IF_HPP
#include "../Arithmetic/Not.hpp"
#include "../Functional/Compose.hpp"
#include "./Filter.hpp"

namespace ml {
/*
 * # RemoveIf:
 * Removes elements satifying the predicate
 */
template <typename Predicate, typename Pipe = ml::ToList> struct RemoveIf {
  template <typename... Ts>
  using f = ml::DelayedEval<Implementations::Filter, sizeof...(Ts),
                            ml::Compose<ml::Not<>, Predicate>, Pipe, ml::Get<0>,
                            Ts...>;
};
} // namespace ml
#endif
