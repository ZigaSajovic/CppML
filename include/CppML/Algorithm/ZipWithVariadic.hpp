//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_ZIP_WITH_VARIADIC_HPP
#define CPPML_ZIP_WITH_VARIADIC_HPP
#include "../Functional/ToList.hpp"
#include "../Vocabulary/List.hpp"
#include "ZipWith.hpp"

namespace ml {
/*
 * ZipWithVariadic:
 * Zips a pack of types in a Zipper.
 * Note:
 * Zipper needs to be a variadic template. It can thus be
 * more efficient than ZipWith.
 */
template <template <class...> class With, typename Pipe = ml::ToList>
struct ZipWithVariadic {
  template <typename... Ts>
  using f = typename ml::IfElse<(sizeof...(Ts) < 10000)>::template f<
      Implementations::ZipStart, void>::template f<Pipe, With, Ts...>;
};
} // namespace ml
#endif
