//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_IS_CLASS_HPP
#define CPPML_IS_CLASS_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Const.hpp"
#include <type_traits>

namespace ml {
/*
 * IsClass:
 * Checks if a type is a class
 */
template <typename Pipe = Identity> struct IsClass {
  template <typename T>
  using f = typename Pipe::template f<Bool<std::is_class<T>::value>>;
};
} // namespace ml
#endif
