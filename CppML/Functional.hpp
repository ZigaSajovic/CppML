//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_FUNCTIONAL_HPP
#define CPPML_FUNCTIONAL_HPP
#include "Const.hpp"
#include "ControlFlow.hpp"
#include "Identity.hpp"
#include "List.hpp"
#include <type_traits>
namespace ml {
/*
 * F:
 * Creates a metafunction out of a template
 */
template <template <class...> class F_> struct F {
  template <typename... Args> using f = F_<Args...>;
};
/*
 * InvokeWith:
 * A metafunction that will invoke the metafunction it is passed,
 * with the arguments Ts
 */
template <class... Ts> struct InvokeWith {
  template <typename F> using f = typename F::template f<Ts...>;
};
/*
 * Invoke:
 * Invokes a meta function
 */
template <typename Pipe, typename... Ts>
using Invoke = typename Pipe::template f<Ts...>;
/*
 * InvokeA:
 * Invokes a meta function
 */
#ifdef __cpp_nontype_template_parameter_auto
template <typename Pipe, auto... Ts>
using InvokeA = typename Pipe::template f<Ts...>;
#endif
/*
 * # DelayedEval:
 * Delays a call, so compiler knows the number of arguments.
 */
struct DelayedEval {
  template <typename F, typename... Ts>
  using f = typename ml::IfElse<(
      sizeof...(Ts) < 10000)>::template f<F, void>::template f<Ts...>;
};
/*
 * Implementation of Compose. Only ever instantiates two types.
 */
namespace Implementations {
template <bool Continue> struct Compose_impl {
  template <int i, typename Result, typename... Ts>
  using f = typename Result::template f<typename Compose_impl<
      (sizeof...(Ts) >= 0) && (i > 2)>::template f<i - 1, Ts...>>;
};
template <> struct Compose_impl<false> {
  template <int i, typename Result, typename... Us>
  using f = typename Result::template f<Us...>;
};
}; // namespace Implementations
/*
 * # Compose:
 * Composes one or more metafunctions.
 */
template <typename T, typename... Ts> struct Compose {
  template <typename... Us>
  using f = typename Implementations::Compose_impl<(
      sizeof...(Ts) > 0)>::template f<sizeof...(Ts) + 1, T, Ts..., Us...>;
};

namespace UnListDetail {
template <typename...> struct UnListImpl;
template <typename Pipe, template <class...> class List, typename... Es>
struct UnListImpl<Pipe, List<Es...>> {
  using type = typename Pipe::template f<Es...>;
};
}; // namespace UnListDetail
/*
 * UnList:
 * Pipes the un-wrapped elements of a list like type
 */
template <typename Pipe> struct UnList {
  template <typename Ls>
  using f = typename UnListDetail::UnListImpl<Pipe, Ls>::type;
};
/*
 * WrapIn:
 * Wraps a type in a wrapper
 */
template <template <class...> class Wrapper> struct WrapIn {
  template <typename... Ts> using f = Wrapper<Ts...>;
};
/*
 * WrapInSingle:
 * Wraps a type in a wrapper. We need it because WrapIn (above) only
 * works for parameter pack aliases.
 */
template <template <class> class Wrapper> struct WrapInSingle {
  template <typename T> using f = Wrapper<T>;
};
/*
 * ToList:
 * Wraps the pack in a list
 */
using ToList = WrapIn<ListT>;
/*
 * ToValue:
 * Returns an auto list of underlying values
 */
#ifdef __cpp_nontype_template_parameter_auto
struct ToValue {
  template <typename... Ts> using f = ListA<Ts::value...>;
};
#endif
/*
 * All:
 * Checks if all values satisfy the predicate
 */
#ifdef __cpp_fold_expressions
template <typename Predicate, typename Pipe = Identity> struct All {
  template <typename... Ts>
  using f = typename Pipe::template f<
      Bool<(Predicate::template f<Ts>::value && ...)>>;
};
#else
/*
 * Implementation of All. It only ever instantiates 4 types.
 */
namespace Implementations {
template <bool Continue> struct AllImpl {
  template <typename Predicate, typename T>
  using f = ml::Bool<Predicate::template f<T>::value>;
};
template <> struct AllImpl<true> {
  template <typename Predicate, typename T, typename... Ts>
  using f = typename ml::IfElse<!Predicate::template f<T>::value>::template f<
      ml::Bool<false>,
      typename AllImpl<(sizeof...(Ts) > 1)>::template f<Predicate, Ts...>>;
};
template <bool Zero> struct AllBase {
  template <typename Predicate, typename... Ts>
  using f = typename AllImpl<(sizeof...(Ts) > 1)>::template f<Predicate, Ts...>;
};
template <> struct AllBase<true> {
  template <typename Predicate, typename... Ts> using f = ml::Bool<true>;
};
}; // namespace Implementations
/*
 * # All
 * Checks if all elements of the parameter pack satisfy a predicate
 */
template <typename Predicate, typename Pipe = ml::Identity> struct All {
  template <typename... Ts>
  using f =
      ml::Invoke<Pipe, typename Implementations::AllBase<!static_cast<bool>(
                           sizeof...(Ts))>::template f<Predicate, Ts...>>;
};

#endif

/*
 * Any:
 * Checks if any value satisfies the predicate
 */
#ifdef __cpp_fold_expressions
template <typename Predicate, typename Pipe = Identity> struct Any {
  template <typename... Ts>
  using f = typename Pipe::template f<
      Bool<(Predicate::template f<Ts>::value || ...)>>;
};
#else
/*
 * Implementation of Any. It only ever instantiates 4 types.
 */
namespace Implementations {
template <bool Continue> struct AnyImpl {
  template <typename Predicate, typename T>
  using f = ml::Bool<Predicate::template f<T>::value>;
};
template <> struct AnyImpl<true> {
  template <typename Predicate, typename T, typename... Ts>
  using f = typename ml::IfElse<Predicate::template f<T>::value>::template f<
      ml::Bool<true>,
      typename AnyImpl<(sizeof...(Ts) > 1)>::template f<Predicate, Ts...>>;
};
template <bool Zero> struct AnyBase {
  template <typename Predicate, typename... Ts>
  using f = typename AnyImpl<(sizeof...(Ts) > 1)>::template f<Predicate, Ts...>;
};
template <> struct AnyBase<true> {
  template <typename Predicate, typename... Ts> using f = ml::Bool<false>;
};
}; // namespace Implementations

/*
 * # Any:
 * Checks if any element of the parameter pack satisfies a predicate.
 */
template <typename Predicate, typename Pipe = ml::Identity> struct Any {
  template <typename... Ts>
  using f =
      ml::Invoke<Pipe, typename Implementations::AnyBase<
                           sizeof...(Ts) == 0>::template f<Predicate, Ts...>>;
};
#endif

/*
 * Implementation of CountIf. Only ever instantiates two types.
 */
namespace Implementations {
template <bool Continue> struct CountIf {
  template <int i, typename Predicate, typename T, typename... Ts>
  using f = typename Implementations::CountIf<static_cast<bool>(sizeof...(
      Ts))>::template f<i + ml::Invoke<Predicate, T>::value, Predicate, Ts...>;
};
template <> struct CountIf<false> {
  template <int i, typename Predicate, typename... Ts> using f = ml::Int<i>;
};
} // namespace Implementations

/*
 * # CountIf:
 * Counts the number of elements satisfying a predicate.
 */
template <typename Predicate, typename Pipe = ml::Identity> struct CountIf {
  template <typename... Ts>
  using f =
      ml::Invoke<Pipe, typename Implementations::CountIf<static_cast<bool>(
                           sizeof...(Ts))>::template f<0, Predicate, Ts...>>;
};

/*
 * Apply:
 * Applies the function to all types
 */
template <typename F, typename Pipe = ToList> struct Apply {
  template <typename... Ts>
  using f = typename IfElse<(sizeof...(Ts) < 10000)>::template f<
      Pipe, void>::template f<typename F::template f<Ts>...>;
};

/*
 * Partial:
 * Partial evaluation of a metafunction
 */
template <typename Pipe, typename... Ts> struct Partial {
  template <typename... Us>
  using f = ml::DelayedEval::template f<Pipe, Us..., Ts...>;
};

/*
 * lPartial:
 * Partial evaluation of a metaList like
 */
template <template <class...> class Pipe, typename... Ts> struct lPartial {
  template <typename... Us> using f = Pipe<Us..., Ts...>;
};

/*
 * PrePartial:
 * Partial evaluation of a metafunction
 */
template <typename Pipe, typename... Ts> struct PrePartial {
  template <typename... Us>
  using f = typename DelayedEval::template f<Pipe, Ts..., Us...>;
};
/*
 * # PartialEvaluator:
 * Creates an metafunction, that will partially evaluate F on the
 * arguments it is invoked on. Example:
 * using F = PartialEvaluator<ml::IsSame>;
 * using Comp = ml::Invoke<F, int>;
 * ml::Invoke<Comp, int> == true;
 */
template <typename F>
using PartialEvaluator = ml::PrePartial<ml::F<ml::Partial>, F>;
/*
 * # PrePartialEvaluator:
 * Creates an metafunction, that will prepartially evaluate F on the
 * arguments it is invoked on. Example:
 * using F = PartialEvaluator<ml::IsSame>;
 * using Comp = ml::Invoke<F, int>;
 * ml::Invoke<Comp, int> == true;
 */
template <typename F>
using PrePartialEvaluator = ml::PrePartial<ml::F<ml::PrePartial>, F>;
/*
 * PartialA:
 * Partial evaluation of a metafunction
 */
#ifdef __cpp_nontype_template_parameter_auto
template <typename Pipe, auto... Ts> struct PartialA {
  template <typename... Us>
  using f =
      typename ml::IfElse<(sizeof...(Ts) < 10000 && sizeof...(Us) < 10000)>::
          template f<Pipe, void>::template f<Us..., Ts...>;
};
#endif

namespace ReplaceDetail {
template <typename T, typename U, typename Pipe = Identity>
struct ReplaceSingleImpl {
  template <typename Z>
  using f = typename Pipe::template f<
      typename IfElse<std::is_same<T, Z>::value>::template f<U, Z>>;
};
}; // namespace ReplaceDetail

/*
 * Replace:
 * Replaces all ocurences of T, with U
 */
template <typename T, typename U, typename Pipe = ToList> struct Replace {
  template <typename... Ts>
  using f = typename Apply<ReplaceDetail::ReplaceSingleImpl<T, U>,
                           Pipe>::template f<Ts...>;
};

/*
 * Implementation of PipeN. Only ever instantiates two types.
 */
namespace Implementations {
template <bool Continue> struct PipeN {
  template <int i, typename Result, typename Pipe>
  using f = typename PipeN<(
      i > 1)>::template f<i - 1, typename Pipe::template f<Result>, Pipe>;
};
template <> struct PipeN<false> {
  template <int i, typename Result, typename Pipe> using f = Result;
};
} // namespace Implementations

/*
 * PipeN:
 * Applies Pipe to Result N times.
 */
template <int N> struct PipeN {
  template <typename Result, typename Pipe>
  using f =
      typename Implementations::PipeN<(N > 1)>::template f<N, Result, Pipe>;
};

/*
 * Greater:
 * Greater than meta function
 */
template <typename Pipe = Identity> struct Greater {
  template <typename T1, typename T2>
  using f = typename Pipe::template f<Bool<(T1::value > T2::value)>>;
};

/*
 * Less:
 * Less than meta function
 */
template <typename Pipe = Identity> struct Less {
  template <typename T1, typename T2>
  using f = typename Pipe::template f<Bool<(T1::value < T2::value)>>;
};
/*
 * # Not
 * Negates
 */
struct Not {
  template <typename T> using f = ml::Bool<!static_cast<bool>(T::value)>;
};
}; // namespace ml
#endif
