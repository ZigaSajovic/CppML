//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_ZIP_HPP
#define CPPML_ZIP_HPP
#include "../Algorithm/Apply.hpp"
#include "../Functional/Invoke.hpp"
#include "../Functional/UnList.hpp"
#include "../Sequence/Append.hpp"
#include "../Vocabulary/List.hpp"

namespace ml {
namespace Implementations {
template <typename Pipe, typename Result, typename...> struct ZipImpl {
  using f = Invoke<UnList<Pipe>, Result>;
};

template <typename Pipe, template <class...> class Result, typename... Rs,
          template <class...> class Next, typename... Ns, typename... Rest>
struct ZipImpl<Pipe, Result<Rs...>, Next<Ns...>, Rest...> {
  using f =
      typename ZipImpl<Pipe, ListT<typename Append<Rs>::template f<Ns>...>,
                       Rest...>::f;
};

template <template <class...> class Zipper, typename Pipe, typename T,
          typename... Ts>
struct ZipBase {
  using f = typename ZipImpl<Pipe, Invoke<UnList<Apply<WrapIn<Zipper>>>, T>,
                             Ts...>::f;
};
}; // namespace Implementations

/*
 * ZipWith:
 * Zips a pack of types in a Zipper
 * NOTE:
 * It is implemented as it is, because the Zipper of ZipBase
 * is used to construct the zip, by appending. If user provided
 * Zipper needs foe example exactly 2 arguments, than you cannot
 * treat it as a list and append to it. So, to amend this, we
 * first zip using the ml::ListT, and than change the zipper
 * to the user provided one.
 * If your zipper is a variadic template, than you can use
 * ml::ZipWithVar, which is more efficient (as it uses the
 * Zipper directly to construct the result).
 */
template <template <class...> class Zipper, typename Pipe = ml::ToList>
struct ZipWith {
  template <typename... Fs>
  using f = typename ml::UnList<ml::Apply< // Unlist and apply to each element
      ml::UnList<ml::WrapIn<Zipper>>, Pipe>>:: // Unlist and wrap in the
                                               // provided Zipper, and Pipe to
                                               // Pipe
      template f<typename ml::Implementations::ZipBase<ml::ListT, ml::ToList,
                                                       Fs...>::f>;
};

/*
 * ZipWithVar:
 * Zips a pack of types in a Zipper.
 * Note:
 * Zipper needs to be a variadic template.
 */
template <template <class...> class Zipper, typename Pipe = ToList>
struct ZipWithVar {
  template <typename... Fs>
  using f = typename Implementations::ZipBase<Zipper, Pipe, Fs...>::f;
};

/*
 * Zip:
 * Zips a pack of types in a ListT
 */
template <typename Pipe = ToList> using Zip = ZipWith<ListT, Pipe>;
} // namespace ml
#endif
