/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_TO_LIST_HPP
#define CPPML_TO_LIST_HPP
#include "../Vocabulary/List.hpp"
#include "F.hpp"
namespace ml {
/*
 * ToList:
 * Wraps the pack in a list
 */
using ToList = ml::F<ListT>;
} // namespace ml
#endif
