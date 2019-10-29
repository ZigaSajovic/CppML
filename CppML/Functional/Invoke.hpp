//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_INVOKE_HPP
#define CPPML_INVOKE_HPP

namespace ml {
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
} // namespace ml
#endif
