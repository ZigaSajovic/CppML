//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_INVOKE_WITH_HPP
#define CPPML_INVOKE_WITH_HPP

namespace ml {
/*
 * InvokeWith:
 * A metafunction that will invoke the metafunction it is passed,
 * with the arguments Ts
 */
template <class... Ts> struct InvokeWith {
  template <typename F> using f = typename F::template f<Ts...>;
};
} // namespace ml
#endif
