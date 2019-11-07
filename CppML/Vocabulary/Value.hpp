//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

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
