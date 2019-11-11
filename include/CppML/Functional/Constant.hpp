/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_CONSTANT_HPP
#define CPPML_CONSTANT_HPP

namespace ml {
/*
 * # Constant:
 * Constant function
 */
template <typename T> struct Constant { template <typename...> using f = T; };
} // namespace ml
#endif
