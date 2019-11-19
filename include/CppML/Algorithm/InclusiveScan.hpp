/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_INLUSIVE_SCAN_HPP
#define CPPML_INLUSIVE_SCAN_HPP
#include "../Arithmetic/Increment.hpp"
#include "../Functional/DelayedEval.hpp"
#include "../Functional/Invoke.hpp"
#include "../Functional/ToList.hpp"
namespace ml {
/*
 * Implementation of InclusiveScan. Only ever instantiates two types.
 */
namespace Implementations {
namespace Detail {
struct InclusiveScan {
  template <typename I, typename F, typename Pipe, typename... Ts>
  using f = ml::f<ml::DelayedEval<Pipe, sizeof...(Ts)>, Ts...>;
};
} // namespace Detail
template <bool Continue> struct InclusiveScan {
  template <typename I, typename F, typename Pipe, typename Result, typename T,
            typename... Ts>
  using f = typename InclusiveScan<(I::value < sizeof...(Ts))>::template f<
      ml::f<ml::Increment<>, I>, F, Pipe, typename F::template f<Result, T>,
      Ts..., Result>;
};
template <> struct InclusiveScan<false> {
  template <typename I, typename F, typename Pipe, typename Result,
            typename... Ts>
  using f = ml::f<ml::DelayedEval<Detail::InclusiveScan, sizeof...(Ts)>, I, F, Pipe,
                            Ts..., Result>;
};
} // namespace Implementations

/*
 * # InclusiveScan:
 * Computes an inclusive prefix as dictated by F, where
 *  * F: maps (Init, T) -> Init
 *  * Ts... : parameter pack to execute on
 */
template <typename F, typename Pipe = ml::ToList> struct InclusiveScan {
  template <typename... Ts>
  using f = ml::f<ml::f<ml::Implementations::IfElse<static_cast<bool>(sizeof...(Ts))>,
                        Implementations::InclusiveScan<static_cast<bool>(
                            sizeof...(Ts) > 1)>,
                        Implementations::Detail::InclusiveScan>,
                  ml::Int<0>, F, Pipe, Ts...>;
};
} // namespace ml
#endif
