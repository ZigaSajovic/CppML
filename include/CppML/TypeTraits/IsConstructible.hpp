/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_IS_CONSTRUCTIBLE_HPP
#define CPPML_IS_CONSTRUCTIBLE_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Value.hpp"
#include <type_traits>

namespace ml {
/*
 * IsConstructible:
 * Checks if a type is constructable from given arguments
 */
template <typename Pipe = Identity> struct IsConstructible {
  template <typename T, typename... Args>
  using f =
      typename Pipe::template f<Bool<std::is_constructible<T, Args...>::value>>;
};
} // namespace ml
#endif
