/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_NONE_OF_HPP
#define CPPML_NONE_OF_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Value.hpp"
#include "./FindIf.hpp"
namespace ml {
/*
 * NoneOf:
 * Checks if none of the values satisfy the predicate
 */
template <typename Predicate, typename Pipe = ml::Identity> struct NoneOf {
  template <typename... Ts>
  using f =
      ml::Invoke<Pipe, ml::Bool<(ml::Invoke<ml::FindIf<Predicate>,
                                            Ts...>::value == sizeof...(Ts))>>;
};
} // namespace ml
#endif
