// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_ROTATE_HPP
#define CPPML_ROTATE_HPP
#include "../Functional/UnList.hpp"
#include "../Sequence/Head.hpp"
#include "../Sequence/Prepend.hpp"
#include "../Sequence/Tail.hpp"
#include "../Vocabulary/IfElse.hpp"

namespace ml {
/*
 * Implementation of Rotate. It only instantiates 3 types for a
 * rotation.
 */
namespace Implementations {
struct Rotate {
  template <int N, typename Pipe, typename... Ts>
  using f = typename ml::UnList<Pipe>::template f<
      typename Implementations::Tail::template f<
          (sizeof...(Ts) - N),
          ml::Prepend<
              typename Implementations::Head::template f<N, ml::ToList, Ts...>>,
          Ts...>>;
};
} // namespace Implementations
/*
 * # Rotate:
 * Rotates the elements `(start ..., M, N, ... end)` in such a way
 * that the ending configuration is `(N, ...End, start, ... M)`
 */

template <int N, typename Pipe = ml::ToList> struct Rotate {
  template <typename... Ts>
  using f = Implementations::Rotate::template f<N, Pipe, Ts...>;
};
} // namespace ml
#endif
