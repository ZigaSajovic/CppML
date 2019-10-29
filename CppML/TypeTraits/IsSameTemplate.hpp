//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_IS_SAME_TEMPLATE_HPP
#define CPPML_IS_SAME_TEMPLATE_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Const.hpp"
#include <type_traits>

namespace ml {
namespace Implementations {
template <class> struct IsSameTemplateHelper {
  template <typename T> using f = ml::Bool<false>;
};
template <template <class> class Template, typename... Us>
struct IsSameTemplateHelper<Template<Us...>> {
  template <typename... Ts>
  static ml::Bool<true> test(const volatile Template<Ts...> *);
  static ml::Bool<false> test(const volatile void *);
  template <typename U>
  using f = decltype(
      IsSameTemplateHelper<Template<Us...>>::test(std::declval<U *>()));
};
} // namespace Implementations
/*
 * IsSameTemplate:
 * Check if two types are wrapped in the same template.
 */
template <typename Pipe = ml::Identity> struct IsSameTemplate {
  template <typename T1, typename T2>
  using f = typename Pipe::template f<
      typename Implementations::IsSameTemplateHelper<T1>::template f<T2>>;
};

} // namespace ml
#endif
