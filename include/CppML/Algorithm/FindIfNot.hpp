/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_FIND_IF_NOT_HPP
#define CPPML_FIND_IF_NOT_HPP
#include "../Arithmetic/Not.hpp"
#include "../Functional/Compose.hpp"
#include "./FindIf.hpp"

namespace ml {
/*
 * # FindIfNot:
 * Returns index of the element not matching the predicate
 */
template <typename Predicate, typename Pipe = ml::Identity> struct FindIfNot {
  template <typename... Ts>
  using f = ml::f<Implementations::FindIf<static_cast<bool>(sizeof...(Ts) > 0)>,
                  ml::Int<0>, Pipe, ml::Compose<ml::Not<>, Predicate>, Ts...>;
};
} // namespace ml
#endif
