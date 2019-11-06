//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_ZIP_WITH_HPP
#define CPPML_ZIP_WITH_HPP
#include "../Functional/F.hpp"
#include "../Functional/Map.hpp"
#include "../Functional/UnList.hpp"
#include "../Pack/Append.hpp"
#include "../Vocabulary/List.hpp"

namespace ml {
namespace Implementations {
template <typename...> struct Zip;

template <typename Pipe, template <class...> class Result, typename... Rs>
struct Zip<Pipe, Result<Rs...>> {
  using f = typename Pipe::template f<Rs...>;
};
template <typename Pipe, template <class...> class Result, typename... Rs,
          template <class...> class Next, typename... Ns, typename... Rest>
struct Zip<Pipe, Result<Rs...>, Next<Ns...>, Rest...> {
  using f =
      typename Zip<Pipe,
                   Result<typename ml::UnList<Append<Ns>>::template f<Rs>...>,
                   Rest...>::f;
};

struct ZipStart {
  template <typename Pipe, template <class...> class With, typename T,
            typename... Ts>
  using f = typename Zip<
      Pipe, typename ml::UnList<ml::Map<ml::WrapIn<With>>>::template f<T>,
      Ts...>::f;
};
} // namespace Implementations

/*
 * ZipWith:
 * Zips a pack of types in a Zipper
 * NOTE:
 * It is implemented as it is, because the Zipper of ZipBase
 * is used to construct the zip, by appending. If user provided
 * Zipper needs for example exactly 2 arguments, than you cannot
 * treat it as a list and append to it. So, to amend this, we
 * first zip using the ml::ListT, and than change the zipper
 * to the user provided one.
 * If your zipper is a variadic template, than you can use
 * ml::ZipWithVariadic, which is more efficient (as it uses the
 * Zipper directly to construct the result).
 */
template <template <class...> class With, typename Pipe = ml::ToList>
struct ZipWith {
  template <typename... Ts>
  using f = typename ml::IfElse<(
      sizeof...(Ts) < 10000)>::template f<Implementations::ZipStart, void>::
      template f<ml::Map<ml::UnList<ml::F<With>>, Pipe>, ml::ListT, Ts...>;
};
} // namespace ml
#endif
