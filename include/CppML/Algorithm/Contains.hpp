/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_CONTAINS_HPP
#define CPPML_CONTAINS_HPP
#include "../Algorithm/AnyOf.hpp"
#include "../Functional/Identity.hpp"
#include "../Functional/Partial.hpp"
#include "../TypeTraits/IsSame.hpp"

namespace ml {
/*
 * # Contains:
 * Checks if a parameter pack contains T
 */
template <typename T, typename Pipe = ml::Identity> struct Contains {
  template <typename... Ts>
  using f = typename ml::AnyOf<ml::Partial<ml::IsSame<>, T>,
                             Pipe>::template f<Ts...>;
};
} // namespace ml
#endif
