//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_PARTITION_HPP
#define CPPML_PARTITION_HPP
#include "../Functional/Product.hpp"
#include "Filter.hpp"
#include "RemoveIf.hpp"

namespace ml {
/*
 * # Partition:
 * Paritions the parameter pack, given a predicate, into two Lists.
 */
template <typename Predicate, typename Pipe = ml::ToList>
struct Partition
    : ml::Product<ml::Filter<Predicate>, ml::RemoveIf<Predicate>, Pipe> {};
} // namespace ml
#endif
