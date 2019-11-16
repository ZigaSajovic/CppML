/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_CONSTANT_HPP
#define CPPML_CONSTANT_HPP
#include "./Identity.hpp"
#include "./Invoke.hpp"
namespace ml {
/*
 * # Constant:
 * Constant function
 */
template <typename T, typename Pipe = ml::Identity> struct Constant {
  template <typename...> using f = ml::f<Pipe, T>;
};
} // namespace ml
#endif
