//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_IS_CONSTRUCTIBLE_HPP
#define CPPML_IS_CONSTRUCTIBLE_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Const.hpp"
#include <type_traits>

namespace ml {
/*
 * IsConstrucitble:
 * Checks if a type is constructable from given arguments
 */
template <typename Pipe = Identity> struct IsConstrucitble {
  template <typename T, typename... Args>
  using f =
      typename Pipe::template f<Bool<std::is_constructible<T, Args...>::value>>;
};
} // namespace ml
#endif
