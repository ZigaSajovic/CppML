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
#include "TypeTraits.hpp"
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
  using f = typename Filter<static_cast<bool>(sizeof...(Ts))>::template f<
      i + 1,
      typename ml::IfElse<Predicate::template f<T>::value>::template f<
          typename ml::Append<KeepList>::template f<ml::Int<i>>, KeepList>,
      Predicate, Ts...>;
};

template <> struct Filter<false> {
  template <int i, typename KeepList, typename Predicate> using f = KeepList;
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
 * **NOTE** that it works with indexes instead of elements.
 */
template <typename Predicate, typename Pipe = ml::ToList> struct FilterIds {
  template <typename... Ts>
  using f = typename ml::UnList<Pipe>::template f<
      typename Implementations::Filter<(sizeof...(Ts) < 100000)>::template f<
          0, ml::ListT<>, Predicate, Ts...>>;
};
/*
 * Filter:
 * Filters elements, given a predicate.
 */
template <typename Predicate, typename Pipe = ml::ToList> struct Filter {
  template <typename... Ts>
  using f = typename ml::UnList<
      ml::Apply<Implementations::PackExtractor<Ts...>, Pipe>>::
      template f<typename Implementations::Filter<(sizeof...(Ts) < 100000)>::
                     template f<0, ml::ListT<>, Predicate, Ts...>>;
};

/*
 * # Contains:
 * Checks if a parameter pack contains T
 */
template <typename T, typename Pipe = ml::Identity> struct Contains {
  template <typename... Ts>
  using f =
      typename ml::Any<ml::PrePartial<ml::IsSame, T>, Pipe>::template f<Ts...>;
};

/*
 * Implementation of Unique. Only ever instantiates two types.
 * **NOTE** that it works with indexes instead of elements.
 */
namespace Implementations {
template <bool Continue> struct Unique {
  template <int i, typename KeepList, typename T, typename... Ts>
  using f = typename Unique<static_cast<bool>(sizeof...(Ts))>::template f<
      i + 1,
      typename ml::IfElse<!ml::Invoke<ml::Contains<T>, Ts...>::value>::
          template f<typename ml::Append<KeepList>::template f<ml::Int<i>>,
                     KeepList>,
      Ts...>;
};

template <> struct Unique<false> {
  template <int i, typename KeepList> using f = KeepList;
};
} // namespace Implementations
/*
 * # UniqueIds:
 * Returns Ids of unique elements
 */
template <typename Pipe = ml::ToList> struct UniqueIds {
  template <typename... Ts>
  using f =
      typename ml::UnList<Pipe>::template f<typename Implementations::Unique<(
          sizeof...(Ts) < 100000)>::template f<0, ml::ListT<>, Ts...>>;
};
/*
 * # Unique:
 * Returns unique elements
 */
template <typename Pipe = ml::ToList> struct Unique {
  template <typename... Ts>
  using f = typename ml::UnList<
      ml::Apply<ml::Implementations::PackExtractor<Ts...>, Pipe>>::
      template f<typename Implementations::Unique<(
          sizeof...(Ts) < 100000)>::template f<0, ml::ListT<>, Ts...>>;
};

/*
 * Implementation of Drop. Only ever instantiates two types.
 */
namespace Implementations {
template <bool Countinue> struct Drop {
  template <int i, typename Pipe, typename T, typename... Ts>
  using f = typename Drop<static_cast<bool>(sizeof...(Ts)) &&
                          (i > 1)>::template f<i - 1, Pipe, Ts...>;
};
template <> struct Drop<false> {
  template <int i, typename Pipe, typename... Ts>
  using f = typename Pipe::template f<Ts...>;
};
} // namespace Implementations
/*
 * # Drop:
 * Drop first N elements of a parameter pack.
 */
template <int N, typename Pipe = ml::ToList> struct Drop {
  template <typename... Ts>
  using f = typename Implementations::Drop<static_cast<bool>(sizeof...(Ts)) &&
                                           (N > 0)>::template f<N, Pipe, Ts...>;
};
/*
 * Implementation of Reduce. Only ever instantiates two types.
 */
namespace Implementations {
template <bool Continue> struct Reduce {
  template <typename Result, typename F, typename T, typename... Ts>
  using f = typename Reduce<static_cast<bool>(
      sizeof...(Ts))>::template f<typename F::template f<Result, T>, F, Ts...>;
};
template <> struct Reduce<false> {
  template <typename Result, typename F> using f = Result;
};
} // namespace Implementations

/*
 * # Reduce:
 * Reduces the parameter pack, as dictated by F, where
 *  * Init: initial type
 *  * F: maps (Init, T) -> Init
 *  * Ts... : parameter pack to execute on
 */
template <typename Pipe = ml::Identity> struct Reduce {
  template <typename Init, typename F, typename... Ts>
  using f = typename Pipe::template f<typename Implementations::Reduce<
      static_cast<bool>(sizeof...(Ts))>::template f<Init, F, Ts...>>;
};

/*
 * Implementation of FindIf. Only ever instantiates two types.
 */
namespace Implementations {
template <bool Continue> struct FindIf {
  template <int i, typename Predicate, typename T, typename... Ts>
  using f = typename ml::IfElse<Predicate::template f<T>::value>::template f<
      ml::Int<i>, typename FindIf<static_cast<bool>(
                      sizeof...(Ts) > 1)>::template f<i + 1, Predicate, Ts...>>;
};

template <> struct FindIf<false> {
  template <int i, typename Predicate, typename T>
  using f = typename ml::IfElse<Predicate::template f<T>::value>::template f<
      ml::Int<i>, ml::Int<i + 1>>;
};
}; // namespace Implementations

/*
 * # FindIf:
 * Returns index of the element matching the predicate
 */
template <typename Predicate, typename Pipe = ml::Identity> struct FindIf {
  template <typename... Ts>
  using f =
      ml::Invoke<Pipe,
                 typename Implementations::FindIf<static_cast<bool>(
                     sizeof...(Ts) > 1)>::template f<0, Predicate, Ts...>>;
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

namespace Implementations {
template <bool Done> struct MaxEement {
  template <typename Compare, typename T0, typename T1, typename... Ts>
  using f = typename IfElse<(sizeof...(Ts) < 10000)>::
      template f<MaxEement<static_cast<bool>(sizeof...(Ts))>, void>::template f<
          Compare,
          typename IfElse<Compare::template f<T0, T1>::value>::template f<T0,
                                                                          T1>,
          Ts...>;
};
template <> struct MaxEement<false> { template <typename T> using f = T; };
}; // namespace Implementations

/*
 * MaxEement:
 * Max element in a pack, given a comparison operator
 */
template <typename Compare> struct MaxEement {
  template <typename... Ts>
  using f = typename Implementations::MaxEement<(
      sizeof...(Ts) > 1)>::template f<Compare, Ts...>;
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
