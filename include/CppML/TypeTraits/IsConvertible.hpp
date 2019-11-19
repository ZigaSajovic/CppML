/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_IS_CONVERTIBLE_HPP
#define CPPML_IS_CONVERTIBLE_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Value.hpp"
#include <type_traits>

namespace ml {
/*
 * IsConvertible:
 * Checks if one type is convertible to the other
 */
template <typename Pipe = Identity> struct IsConvertible {
  template <typename T, typename U>
  using f = typename Pipe::template f<Bool<std::is_convertible<T, U>::value>>;
};
} // namespace ml
#endif
