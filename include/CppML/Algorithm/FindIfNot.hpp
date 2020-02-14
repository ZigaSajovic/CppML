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
#include "../Pack/Get.hpp"
#include "FindIdIf.hpp"

namespace ml {
/*
 * # FindIf:
 * Returns the element matching the predicate
 */
template <typename Predicate, typename Pipe = ml::Identity> struct FindIfNot {
  template <typename... Ts>
  using f =
      ml::Invoke<Implementations::FindIf<static_cast<bool>(sizeof...(Ts) > 0)>,
                 ml::None, ml::Int<0>, ml::Get<0>, Pipe,
                 ml::Compose<ml::Not<>, Predicate>, Ts...>;
};
} // namespace ml
#endif
