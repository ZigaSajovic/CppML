//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_IS_VALID_HPP
#define CPPML_IS_VALID_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Value.hpp"
#include <type_traits>
namespace ml {
namespace Implementations {
template <typename T> struct R { using f = T; };

template <typename, class U, class T, class... Ts>
struct IfValidOr_impl : R<U> {};

template <class U, class T, typename... Ts>
struct IfValidOr_impl<std::void_t<typename T::template f<Ts...>>, U, T, Ts...>
    : R<typename T::template f<Ts...>> {};
}; // namespace Implementations
/*
 * IfValidOr:
 * If the metafunction T is valid, evaluate to its result,
 * else evaluate to Default.
 */
template <typename Pipe = ml::Identity> struct IfValidOr {
  template <class Default, class T, class... Ts>
  using f = typename Pipe::template f<
      typename Implementations::IfValidOr_impl<void, Default, T, Ts...>::f>;
};

} // namespace ml
#endif
