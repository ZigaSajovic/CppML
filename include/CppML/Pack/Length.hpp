/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_LENGTH_HPP
#define CPPML_LENGTH_HPP
#include "../Functional/Identity.hpp"
#include "../Functional/Invoke.hpp"
#include "../Vocabulary/Value.hpp"
namespace ml {
/*
 * Length:
 * Length of a parameter pack
 */
template <typename Pipe = ml::Identity> struct Length {
  template <typename... Ts> using f = ml::f<Pipe, ml::Int<sizeof...(Ts)>>;
};
} // namespace ml
#endif
