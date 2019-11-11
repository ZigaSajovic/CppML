/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_NOT_HPP
#define CPPML_NOT_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Value.hpp"
namespace ml {
/*
 * Not:
 * Negation
 */
template <typename Pipe = Identity> struct Not {
  template <typename T>
  using f = typename Pipe::template f<Bool<!static_cast<bool>(T::value)>>;
};

} // namespace ml
#endif
