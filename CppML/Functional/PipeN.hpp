//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_PIPE_N_HPP
#define CPPML_PIPE_N_HPP

namespace ml {
/*
 * Implementation of PipeN. Only ever instantiates two types.
 */
namespace Implementations {
template <bool Continue> struct PipeN {
  template <int i, typename Result, typename Pipe>
  using f = typename PipeN<(
      i > 1)>::template f<i - 1, typename Pipe::template f<Result>, Pipe>;
};
template <> struct PipeN<false> {
  template <int i, typename Result, typename Pipe> using f = Result;
};
} // namespace Implementations

/*
 * PipeN:
 * Applies Pipe to Result N times.
 */
template <int N> struct PipeN {
  template <typename Result, typename Pipe>
  using f =
      typename Implementations::PipeN<(N > 1)>::template f<N, Result, Pipe>;
};
} // namespace ml
#endif
