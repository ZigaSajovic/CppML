/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_IF_ELSE_HPP
#define CPPML_IF_ELSE_HPP
namespace ml {
/*
 * IfElse:
 * And If Else type block.
 *
 */
template <bool> struct IfElse;
template <> struct IfElse<true> {
  template <typename T, typename U> using f = T;
};
template <> struct IfElse<false> {
  template <typename T, typename U> using f = U;
};
}; // namespace ml
#endif
