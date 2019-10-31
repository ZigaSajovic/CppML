//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_INSERT_HPP
#define CPPML_INSERT_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/Invoke.hpp"
#include "../Functional/ToList.hpp"
#include "../Sequence/Append.hpp"
#include "../Sequence/Drop.hpp"
#include "../Sequence/Head.hpp"
namespace ml {
template <int I, typename T, typename Pipe = ml::ToList> struct Insert {
  template <typename... Ts>
  using f = ml::Invoke<
      ml::Drop<I, ml::Append<ml::Invoke<ml::Append<ml::DelayedEval<
                                            ml::Head<I>, sizeof...(Ts), Ts...>>,
                                        T>>>,
      Ts...>;
};
} // namespace ml
#endif
