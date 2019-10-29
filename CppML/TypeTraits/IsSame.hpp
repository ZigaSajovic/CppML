//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_IS_SAME_HPP
#define CPPML_IS_SAME_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Const.hpp"
#include <type_traits>

namespace ml {
namespace TypeTraitsImplementations {
template <typename T> struct IsSameHelper {
  static ml::Bool<true> test(const volatile IsSameHelper<T> *);
  static ml::Bool<false> test(const volatile void *);
  template <typename U>
  using f = decltype(IsSameHelper<T>::test(std::declval<IsSameHelper<U> *>()));
};
} // namespace TypeTraitsImplementations
/*
 * IsSame:
 * Check if two types are equal. Note that this creates linear number
 * of types, not quadratic, like std::is_same.
 */
template <typename Pipe = ml::Identity> struct IsSame {
  template <typename T1, typename T2>
  using f = typename Pipe::template f<
      typename TypeTraitsImplementations::IsSameHelper<T1>::template f<T2>>;
};

} // namespace ml
#endif
