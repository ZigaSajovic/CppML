/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_VALUE_HPP
#define CPPML_VALUE_HPP
namespace ml {
/*
 * Value:
 * Represents a typed value
 *
 */
template <typename T, T t> struct Value {
  using type = T;
  static constexpr T value = t;
};

template <int N> using Int = Value<int, N>;

template <bool N> using Bool = Value<bool, N>;

template <char C> using Char = Value<char, C>;

}; // namespace ml
#endif
