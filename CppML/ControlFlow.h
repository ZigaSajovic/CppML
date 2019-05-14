//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_X_CONTROL_FLOW
#define CPPML_X_CONTROL_FLOW
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
