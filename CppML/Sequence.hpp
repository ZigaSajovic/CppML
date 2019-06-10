//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_SEQUENCE_HPP
#define CPPML_SEQUENCE_HPP
#include "Const.hpp"
#include "ControlFlow.hpp"
#include "Functional.hpp"
#include "Identity.hpp"
#include "List.hpp"
#include "Range.hpp"
namespace ml {
/*
 * Append:
 * Appends elements to a list-like structure
 */
template <typename> struct Append;
template <template <class...> class List, typename... Ts>
struct Append<List<Ts...>> {
  template <typename... Us> using f = List<Ts..., Us...>;
};

/*
 * Prepend:
 * Prepends elements to a list-like structure
 */
template <typename> struct Prepend;
template <template <class...> class List, typename... Ts>
struct Prepend<List<Ts...>> {
  template <typename... Us> using f = List<Us..., Ts...>;
};

/*
 * GetN:
 * Retrives the N-th element in a pack
 */
template <int N, typename Pipe = Identity> struct GetN {
  template <typename T, typename... Ts>
  using f = typename IfElse<sizeof...(Ts)>::template f<GetN<N - 1, Pipe>,
                                                       void>::template f<Ts...>;
};

template <typename Pipe> struct GetN<0, Pipe> {
  template <typename T, typename... Ts> using f = typename Pipe::template f<T>;
};

namespace ZipDetail {
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
}; // namespace ZipDetail

/*
 * ZipWith:
 * Zips a pack of types in a Zipper
 */
template <template <class...> class Zipper, typename Pipe = ToList>
struct ZipWith {
  template <typename... Fs>
  using f = typename ZipDetail::ZipBase<Zipper, Pipe, Fs...>::f;
};

/*
 * Zip:
 * Zips a pack of types in a ListT
 */
template <typename Pipe = ToList> using Zip = ZipWith<ListT, Pipe>;

namespace MaxElementDetail {
template <bool Done, typename Compare> struct MaxEementImpl {
  template <typename T0, typename T1, typename... Ts>
  using f = typename IfElse<(sizeof...(Ts) < 10000)>::template f<
      MaxEementImpl<static_cast<bool>(sizeof...(Ts)), Compare>,
      void>::template f<typename IfElse<Compare::template f<T0, T1>::value>::
                            template f<T0, T1>,
                        Ts...>;
};
template <typename Compare> struct MaxEementImpl<false, Compare> {
  template <typename T> using f = T;
};
}; // namespace MaxElementDetail

/*
 * MaxEement:
 * Max element in a pack, given a comparison operator
 */
template <typename Compare> struct MaxEement {
  template <typename... Ts>
  using f =
      typename MaxElementDetail::MaxEementImpl<(sizeof...(Ts) > 1),
                                               Compare>::template f<Ts...>;
};

namespace SortDetail {
template <typename T, typename U, typename Pipe = ToList>
struct ReplaceAndPrepend {
  template <typename... Ts>
  using f = typename Prepend<
      typename Replace<T, U, Pipe>::template f<Ts...>>::template f<T>;
};

template <bool, typename Compare> struct SortImpl {
  template <typename T, typename... Ts>
  using f = typename ReplaceAndPrepend<
      typename ml::MaxEement<Compare>::template f<Ts...>, T,
      SortImpl<(sizeof...(Ts) != 1), Compare>>::template f<Ts...>;
};

template <typename Compare> struct SortImpl<false, Compare> {
  template <typename T> using f = ListT<T>;
};

template <bool, typename Compare, typename Pipe> struct SortBase {
  template <typename... Ts>
  using f =
      Invoke<UnList<Pipe>,
             typename SortImpl<sizeof...(Ts) != 1, Compare>::template f<Ts...>>;
};

template <typename Compare, typename Pipe>
struct SortBase<false, Compare, Pipe> {
  template <typename... Ts> using f = typename Pipe::template f<Ts...>;
};
}; // namespace SortDetail
/*
 * Sort:
 * Sorts a unique list of types
 */
template <typename Compare, typename Pipe = ToList> struct Sort {
  template <typename... Ts>
  using f = typename SortDetail::SortBase<sizeof...(Ts) != 0, Compare,
                                          Pipe>::template f<Ts...>;
};
/*
 * Tag:
 * Tags each element in a pack
 */
template <typename Pipe = ToList> struct Tag {
  template <typename... Ts>
  using f = ml::Invoke<
      ml::UnList<Pipe>,
      ml::Zip<>::f<typename ml::TypeRange<>::template f<0, sizeof...(Ts)>,
                    ml::ListT<Ts...>>>;
};
}; // namespace ml
#endif
