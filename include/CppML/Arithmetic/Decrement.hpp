/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_DECREMENT_HPP
#define CPPML_DECREMENT_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Value.hpp"
namespace ml {
/*
 * Increment:
 * Increments the value of the type
 */
template <typename Pipe = ml::Identity> struct Decrement {
  template <typename T>
  using f = typename Pipe::template f<ml::Int<T::value - 1>>;
};

} // namespace ml
#endif
