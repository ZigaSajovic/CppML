//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_FILTER_IDS_HPP
#define CPPML_FILTER_IDS_HPP
#include "Filter.hpp"

namespace ml {
/*
 * # FilterIds:
 * Returns elements satifying a predicate
 */
template <typename Predicate, typename Pipe = ml::ToList> struct FilterIds {
  template <typename... Ts>
  using f = ml::DelayedEval<Implementations::Filter, sizeof...(Ts), Predicate,
                            Pipe, ml::Get<1>, Ts...>;
};
} // namespace ml
#endif
