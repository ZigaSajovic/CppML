/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_ALIGN_OF_HPP
#define CPPML_ALIGN_OF_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Value.hpp"

namespace ml {
/*
 * AlignOf:
 * Returns an Int type of aligment of T
 */
template <typename Pipe = Identity> struct AlignOf {
  template <typename T> using f = typename Pipe::template f<Int<alignof(T)>>;
};
}
#endif
