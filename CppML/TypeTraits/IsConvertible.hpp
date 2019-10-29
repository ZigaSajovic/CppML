//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_IS_CONVERTIBLE_HPP
#define CPPML_IS_CONVERIBLE_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Const.hpp"
#include <type_traits>

namespace ml {
/*
 * IsConvertible:
 * Checks if one type is convertible to the other
 */
template <typename Pipe = Identity> struct IsConvertible {
  template <typename T, typename U>
  using f = typename Pipe::template f<Bool<std::is_convertible<T, U>::value>>;
};
}
#endif
