/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_IF_ELSE_HPP
#define CPPML_IF_ELSE_HPP
#include "../Vocabulary/Value.hpp"
#include "./Identity.hpp"
namespace ml {

namespace Implementations {
template <bool> struct IfElse;
template <> struct IfElse<true> {
  template <typename T, typename U> using f = T;
};
template <> struct IfElse<false> {
  template <typename T, typename U> using f = U;
};
} // namespace Implementations
/*
 * IfElse:
 * An If Else type block.
 */
template <typename T, typename Pipe = ml::Identity> struct IfElse;
template <bool B, typename Pipe> struct IfElse<Bool<B>, Pipe> {
  template <typename T, typename U>
  using f = typename Pipe::template f<
      typename Implementations::IfElse<B>::template f<T, U>>;
};
}; // namespace ml
#endif
