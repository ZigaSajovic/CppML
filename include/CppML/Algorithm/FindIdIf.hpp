/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_FIND_ID_IF_HPP
#define CPPML_FIND_ID_IF_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/Identity.hpp"
#include "../Functional/IfElse.hpp"
#include "../Functional/Invoke.hpp"
#include "../Pack/Get.hpp"
#include "../Vocabulary/None.hpp"
#include "../Vocabulary/Value.hpp"

namespace ml {
/*
 * Implementation of FindIdIf. Only ever instantiates two types.
 */
namespace Implementations {
namespace Detail {
/*
 * This is used to short circuit when found.
 */
struct FindIfPipeOn {
  template <typename Prev, typename I, typename Getter, typename Pipe,
            typename... Ts>
  using f = ml::Invoke<Pipe, ml::f<Getter, Prev, ml::Int<I::value - 1>>>;
};
}; // namespace Detail
template <bool Continue> struct FindIf {
  template <typename Prev, typename I, typename Getter, typename Pipe,
            typename Predicate, typename T, typename... Ts>
  using f =
      ml::f<ml::DelayedEval<
                ml::Invoke<ml::Implementations::IfElse<
                               ml::Invoke<Predicate, T>::value>,
                           Detail::FindIfPipeOn, FindIf<(sizeof...(Ts) > 0)>>,
                sizeof...(Ts)>,
            T, ml::Int<I::value + 1>, Getter, Pipe, Predicate, Ts...>;
};

template <> struct FindIf<false> {
  template <typename Prev, typename I, typename Getter, typename Pipe,
            typename Predicate>
  using f = ml::Invoke<Pipe, ml::f<Getter, ml::None, I>>;
};
}; // namespace Implementations

/*
 * # FindIdIf:
 * Returns index of the element matching the predicate
 */
template <typename Predicate, typename Pipe = ml::Identity> struct FindIdIf {
  template <typename... Ts>
  using f =
      ml::Invoke<Implementations::FindIf<static_cast<bool>(sizeof...(Ts) > 0)>,
                 ml::None, ml::Int<0>, ml::Get<1>, Pipe, Predicate, Ts...>;
};
} // namespace ml
#endif
