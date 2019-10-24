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
 * Length:
 * Length of a List-like
 */
template <typename List> struct Length;
template <template <class...> class List, typename... Args>
struct Length<List<Args...>> : ml::Int<sizeof...(Args)> {};
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
 * Implementation of GetN. It only ever instantiates two types.
 * This means that it will not instantiate a type for each N. So
 * One can use this, when needed.
 */
namespace Implementations {
template <bool Continue> struct GetN {
  template <int i, typename T, typename... Ts>
  using f = typename ml::IfElse<static_cast<bool>(sizeof...(
      Ts))>::template f<GetN<(i > 1)>, void>::template f<i - 1, Ts...>;
};

template <> struct GetN<false> {
  template <int i, typename T, typename... Ts> using f = T;
};
}; // namespace Implementations

/*
 * GetN:
 * Retrives the N-th element in a pack. Instantiates a type
 * for each N.
 */
template <int N, typename Pipe = ml::Identity> struct GetN {
  template <typename... Ts>
  using f = typename Implementations::GetN<(sizeof...(Ts) >= 0) &&
                                           N != 0>::template f<N, Ts...>;
};
/*
 * Implementation of Filter. It only ever instantiates two types.
 */
namespace Implementations {
template <bool Continue> struct Filter {
  template <int i, typename KeepList, typename Predicate, typename T,
            typename... Ts>
  using f =
      typename Filter <
      i<sizeof...(Ts)>::template f<
          i + 1,
          typename ml::IfElse<
              Predicate::template f<typename ml::Implementations::GetN<(
                  i > 0)>::template f<i, T, Ts...>>::value>::
              template f<typename ml::Append<KeepList>::template f<ml::Int<i>>,
                         KeepList>,
          Predicate, T, Ts...>;
};

template <> struct Filter<false> {
  template <int i, typename KeepList, typename Predicate, typename T,
            typename... Ts>
  using f = KeepList;
};

template <typename... Ts> struct PackExtractor {
  template <typename T>
  using f = typename ml::Implementations::GetN<T::value !=
                                               0>::template f<T::value, Ts...>;
};

}; // namespace Implementations
/*
 * FilterIds:
 * Returns list of indexes of elements satifying the predicate.
 */
template <typename Predicate, typename Pipe = ml::ToList> struct FilterIds {
  template <typename T, typename... Ts>
  using f =
      typename ml::UnList<Pipe>::template f<typename Implementations::Filter<
          true>::template f<0, ml::ListT<>, Predicate, T, Ts...>>;
};
/*
 * Filter:
 * Filters elements, given a predicate. The reason it is implemented in terms
 * of indexes is that, given a predicate, it is as if only **Filter** for one
 * list is ever instantiated because only indexes take part in the type
 * signature.
 */
template <typename Predicate, typename Pipe = ml::ToList> struct Filter {
  template <typename T, typename... Ts>
  using f = typename ml::UnList<
      ml::Apply<Implementations::PackExtractor<T, Ts...>, Pipe>>::
      template f<typename Implementations::Filter<
          0, ml::ListT<>, Predicate>::template f<T, Ts...>>;
};

namespace Implementations {
template <bool Continue> struct FindIfOr {
  template <typename Default, typename Predicate, typename T, typename... Ts>
  using f = typename ml::IfElse<Predicate::template f<T>::value>::template f<
      T, typename FindIfOr<static_cast<bool>(
             sizeof...(Ts) > 1)>::template f<Default, Predicate, Ts...>>;
};

template <> struct FindIfOr<false> {
  template <typename Default, typename Predicate, typename T>
  using f =
      typename ml::IfElse<Predicate::template f<T>::value>::template f<T,
                                                                       Default>;
};
}; // namespace Implementations

/*
 * # FindIfOr:
 * Find Element or return Default
 */
template <typename Default, typename Predicate, typename Pipe = ml::Identity>
struct FindIfOr {
  template <typename... Ts>
  using f = ml::Invoke<
      Pipe, typename Implementations::FindIfOr<static_cast<bool>(
                sizeof...(Ts) > 1)>::template f<Default, Predicate, Ts...>>;
};

namespace Implementations {
template <typename, typename, typename Pipe = ml::ToList> struct Merge2;
template <template <class...> class List, typename... Ts, typename... Us,
          typename Pipe>
struct Merge2<List<Ts...>, List<Us...>, Pipe> {
  using f = typename Pipe::template f<Ts..., Us...>;
};

template <bool Continue> struct Merge_impl {
  template <typename T, typename U, typename... Ts>
  using f = typename Merge_impl<(static_cast<bool>(
      sizeof...(Ts)))>::template f<typename Merge2<T, U>::f, Ts...>;
};

template <> struct Merge_impl<false> { template <typename T> using f = T; };
}; // namespace Implementations

/*
 * # Merge:
 * Merges `n` **List**-like types.
 */
struct Merge {
  template <typename T, typename... Ts>
  using f = typename Implementations::Merge_impl<static_cast<bool>(
      sizeof...(Ts))>::template f<T, Ts...>;
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
      template f<
          typename ml::ZipDetail::ZipBase<ml::ListT, ml::ToList, Fs...>::f>;
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
