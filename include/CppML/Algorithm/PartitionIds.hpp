//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_PARTITION_IDS_HPP
#define CPPML_PARTITION_IDS_HPP
#include "../Functional/Product.hpp"
#include "FilterIds.hpp"
#include "RemoveIdsIf.hpp"

namespace ml {
/*
 * # PartitionIds:
 * Paritions indexes of the parameter pack, given a predicate, into two Lists.
 */
template <typename Predicate, typename Pipe = ml::ToList>
struct PartitionId
    : ml::Product<ml::FilterIds<Predicate>, ml::RemoveIdsIf<Predicate>, Pipe> {
};
} // namespace ml
#endif
