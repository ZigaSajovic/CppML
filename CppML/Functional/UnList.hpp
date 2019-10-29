//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_UNLIST_HPP
#define CPPML_UNLIST_HPP

namespace ml {
namespace Implementations {
template <typename...> struct UnList;
template <typename Pipe, template <class...> class List, typename... Es>
struct UnList<Pipe, List<Es...>> {
  using type = typename Pipe::template f<Es...>;
};
}; // namespace Implementations
/*
 * UnList:
 * Pipes the un-wrapped elements of a list like type
 */
template <typename Pipe> struct UnList {
  template <typename Ls>
  using f = typename Implementations::UnList<Pipe, Ls>::type;
};
} // namespace ml
#endif
