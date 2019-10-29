//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_REPLACE_IF_HPP
#define CPPML_REPLACE_IF_HPP
#include "../Functional/ToList.hpp"
#include "../Vocabulary/IfElse.hpp"
#include "Apply.hpp"
namespace ml {
namespace Implementations {
template <typename Predicate, typename With> struct ReplaceSingle {
  template <typename T>
  using f =
      typename ml::IfElse<Predicate::template f<T>::value>::template f<With, T>;
};

} // namespace Implementations

template <typename Predicate, typename With, typename Pipe = ml::ToList>
struct ReplaceIf {
  template <typename... Ts>
  using f = typename ml::Apply<Implementations::ReplaceSingle<Predicate, With>,
                               Pipe>::template f<Ts...>;
};
} // namespace ml
#endif
