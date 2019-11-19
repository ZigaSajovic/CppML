/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_UNIQUE_HPP
#define CPPML_UNIQUE_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/Invoke.hpp"
#include "../Functional/PartialR.hpp"
#include "../Functional/ToList.hpp"
#include "../Pack/Get.hpp"
#include "../TypeTraits/IsSame.hpp"
#include "../Vocabulary/Value.hpp"
#include "./AnyOf.hpp"

namespace ml {
namespace Implementations {
namespace Detail {
template <bool Continue> struct Unique;
template <bool Take> struct UniqueGet {
  template <typename I, typename Comparator, typename Pipe, typename T,
            typename... Ts>
  using f = ml::f<ml::DelayedEval<Detail::Unique<(I::value > 1)>, sizeof...(Ts)>,
                            ml::Int<I::value - 1>, Comparator, Pipe, Ts..., T>;
};
template <> struct UniqueGet<false> {
  template <typename I, typename Comparator, typename Pipe, typename T,
            typename... Ts>
  using f = ml::f<ml::DelayedEval<Detail::Unique<(I::value > 1)>, sizeof...(Ts)>,
                            ml::Int<I::value - 1>, Comparator, Pipe, Ts...>;
};

template <bool Continue> struct Unique {
  template <typename I, typename Comparator, typename Pipe, typename T,
            typename... Ts>
  using f = ml::f<ml::DelayedEval<
      Detail::UniqueGet<!ml::Invoke<
          ml::Drop<I::value - 1, ml::AnyOf<ml::PartialR<Comparator, T>>>,
          Ts...>::value>,
      sizeof...(Ts)>, I, Comparator, Pipe, T, Ts...>;
};
template <> struct Unique<false> {
  template <typename I, typename Comparator, typename Pipe, typename... Ts>
  using f = ml::f<ml::DelayedEval<Pipe, sizeof...(Ts)>, Ts...>;
};
} // namespace Detail
struct Unique {
  template <typename Comparator, typename Pipe, typename... Ts>
  using f = ml::f<ml::DelayedEval<Detail::Unique<static_cast<bool>(sizeof...(Ts))>,
                            sizeof...(Ts)>, ml::Int<sizeof...(Ts)>, Comparator,
                            Pipe, Ts...>;
};
} // namespace Implementations
template <typename Pipe = ml::ToList> struct Unique {
  template <typename... Ts>
  using f = ml::f<ml::DelayedEval<Implementations::Unique, sizeof...(Ts)>,
                            ml::IsSame<>, Pipe, Ts...>;
};
} // namespace ml
#endif
