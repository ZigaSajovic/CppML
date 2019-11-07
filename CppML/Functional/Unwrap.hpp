//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_UNWRAP_HPP
#define CPPML_UNWRAP_HPP

namespace ml {
namespace Implementations {
template <typename...> struct Unwrap;
template <typename Pipe, template <class...> class List, typename... Es>
struct Unwrap<Pipe, List<Es...>> {
  using type = typename Pipe::template f<Es...>;
};
}; // namespace Implementations
/*
 * Unwrap:
 * Pipes the un-wrapped elements of a list like type
 */
template <typename Pipe> struct Unwrap {
  template <typename Ls>
  using f = typename Implementations::Unwrap<Pipe, Ls>::type;
};
} // namespace ml
#endif
