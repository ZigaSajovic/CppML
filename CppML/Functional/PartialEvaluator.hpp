//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_PARTIAL_EVALUATOR_HPP
#define CPPML_PARTIAL_EVALUATOR_HPP
#include "F.hpp"
#include "Partial.hpp"
namespace ml {
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
} // namespace ml
#endif
