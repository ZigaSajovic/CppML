/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_IDENTITY_HPP
#define CPPML_IDENTITY_HPP
namespace ml {
/*
 * Identity:
 * Returns self
 */
struct Identity {
  template <typename T> using f = T;
};
}; // namespace ml
#endif
