/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_ZIP_WITH_HPP
#define CPPML_ZIP_WITH_HPP
#include "../Functional/F.hpp"
#include "../Functional/Map.hpp"
#include "../Functional/Unwrap.hpp"
#include "../Pack/Append.hpp"
#include "../Vocabulary/List.hpp"

namespace ml {
namespace Implementations {
template <typename...> struct Zip;

template <typename With, typename Pipe, template <class...> class Result,
          typename... Rs>
struct Zip<With, Pipe, Result<Rs...>> {
  using f = typename Pipe::template f<Rs...>;
};
template <typename With, typename Pipe, template <class...> class Result,
          typename... Rs, template <class...> class Next, typename... Ns,
          typename... Rest>
struct Zip<With, Pipe, Result<Rs...>, Next<Ns...>, Rest...> {
  using f = typename Zip<
      With, Pipe,
      Result<typename ml::Unwrap<Append<Ns, With>>::template f<Rs>...>,
      Rest...>::f;
};

struct ZipStart {
  template <typename Pipe, template <class...> class With, typename T,
            typename... Ts>
  using f =
      typename Zip<ml::F<With>, Pipe,
                   typename ml::Unwrap<ml::Map<ml::F<With>>>::template f<T>,
                   Ts...>::f;
};

struct ZipForward {
  template <typename Pipe, template <class...> class With, typename... Ts>
  using f = ml::f<ml::DelayedEval<Pipe, sizeof...(Ts)>, Ts...>;
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
  using f =
      typename ml::Implementations::IfElse<(sizeof...(Ts) > 0)>::template f<
          Implementations::ZipStart, Implementations::ZipForward>::
          template f<ml::Map<ml::Unwrap<ml::F<With>>, Pipe>, ml::ListT, Ts...>;
};
} // namespace ml
#endif
