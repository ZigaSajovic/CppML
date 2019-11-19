/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_ALL_OF_HPP
#define CPPML_ALL_OF_HPP
#include "../Algorithm/FindIfNot.hpp"
#include "../Functional/Identity.hpp"
#include "../Functional/Invoke.hpp"
#include "../Vocabulary/Value.hpp"
namespace ml {
/*
 * AllOf:
 * Checks if all values satisfy the predicate
 */
template <typename Predicate, typename Pipe = ml::Identity> struct AllOf {
  template <typename... Ts>
  using f =
      ml::f<Pipe, ml::Bool<(ml::f<ml::FindIfNot<Predicate>, Ts...>::value ==
                            sizeof...(Ts))>>;
};
} // namespace ml
#endif
