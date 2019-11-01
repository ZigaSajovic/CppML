//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_SORT_HPP
#define CPPML_SORT_HPP
#include "../Algorithm/FindIf.hpp"
#include "../Arithmetic/Not.hpp"
#include "../Functional/Compose.hpp"
#include "../Functional/Invoke.hpp"
#include "../Functional/Partial.hpp"
#include "../Functional/ToList.hpp"
#include "../Pack/Get.hpp"
#include "Rotate.hpp"

namespace ml {
/*
 * Implementation of sort.
 */
namespace Implementations {
template <bool Continue> struct Sort {
  template <typename I, typename Pipe, typename Compare, typename... Ts>
  using f =
      ml::Invoke<ml::Rotate<                            //
                     ml::Invoke<                        //
                         ml::FindIf<                    //
                             ml::Partial<               //
                                 Compare,               //
                                 ml::DelayedEval<       //
                                     ml::Get<I::value>, //
                                     sizeof...(Ts),     //
                                     Ts...>>>,          //
                         Ts...                          //
                         >::value +
                         3,
                     I::value + 3, I::value + 4,
                     Implementations::Sort<(I::value + 1 < sizeof...(Ts))>>,
                 ml::Int<I::value + 1>, Pipe, Compare, Ts...>;
};

template <> struct Sort<false> {
  template <typename I, typename Pipe, typename Compare, typename... Ts>
  using f = ml::DelayedEval<Pipe, sizeof...(Ts), Ts...>;
};
}; // namespace Implementations
/*
 * # Sort:
 * Sorts a parameter pack, given a comparator
 */
template <typename Compare, typename Pipe = ml::ToList> struct Sort {
  template <typename... Ts>
  using f = ml::Invoke<Implementations::Sort<(sizeof...(Ts) > 1)>, ml::Int<1>,
                       Pipe, ml::Compose<ml::Not<>, Compare>, Ts...>;
};

} // namespace ml
#endif
