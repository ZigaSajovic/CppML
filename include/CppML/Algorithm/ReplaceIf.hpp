/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_REPLACE_IF_HPP
#define CPPML_REPLACE_IF_HPP
#include "../Functional/IfElse.hpp"
#include "../Functional/Map.hpp"
#include "../Functional/ToList.hpp"
namespace ml {
namespace Implementations {
template <typename Predicate, typename With> struct ReplaceSingle {
  template <typename T>
  using f = typename ml::Implementations::IfElse<
      Predicate::template f<T>::value>::template f<With, T>;
};

} // namespace Implementations

template <typename Predicate, typename With, typename Pipe = ml::ToList>
struct ReplaceIf {
  template <typename... Ts>
  using f = typename ml::Map<Implementations::ReplaceSingle<Predicate, With>,
                             Pipe>::template f<Ts...>;
};
} // namespace ml
#endif
