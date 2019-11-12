/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_ANY_OF_HPP
#define CPPML_ANY_OF_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Value.hpp"
#include "./FindIf.hpp"
namespace ml {
/*
 * AnyOf:
 * Checks if any value satisfies the predicate
 */
#ifdef __cpp_fold_expressions
template <typename Predicate, typename Pipe = Identity> struct AnyOf {
  template <typename... Ts>
  using f = typename Pipe::template f<
      Bool<(Predicate::template f<Ts>::value || ...)>>;
};
#else
template <typename Predicate, typename Pipe = ml::Identity> struct AnyOf {
  template <typename... Ts>
  using f =
      ml::Invoke<Pipe, ml::Bool<(ml::Invoke<ml::FindIf<Predicate>,
                                            Ts...>::value < sizeof...(Ts))>>;
};
#endif
} // namespace ml
#endif
