//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_CONST_H
#define CPPML_CONST_H
namespace ml {
/*
 * Const:
 * Represents a typed whole number value
 *
 */
template <typename T, T t> struct Const {
  using type = T;
  static constexpr T value = t;
};

template <int N> using Int = Const<int, N>;

template <bool N> using Bool = Const<bool, N>;

template <char C> using Char = Const<char, C>;

}; // namespace ml
#endif
