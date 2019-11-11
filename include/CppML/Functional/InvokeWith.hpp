/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
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
