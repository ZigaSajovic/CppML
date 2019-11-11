/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
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
