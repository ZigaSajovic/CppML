# `<CppML/TypeTraits/IfValidOr.hpp>`

## `IfValidOr`

```c++
template <typename Pipe = ml::Identity>
struct IfValidOr {
template<typename Default, typename F, typename ...Args>
  using f = /* .... */;
};
```
### `IfValidOr<Pipe>`

Than `IfValidOr<Pipe>` is a metafunction that passes to `Pipe` the type `T`, which is either:
* `T = ml::f<F, Args...>`
  * if `ml::f<F, Args...>` is *valid* and not *ill-formed*, or
* `T = Default`
  * if `ml::f<F, Args...>` is *not valid* and is *ill-formed*

`Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f::  Default F, Args... -> T <-> Pipe
```

### Example

It can be used to implement logic based on introspection. To demonstrate, we define a metafunction, that extracts the `ValueType` alias from a type if it has one, or returns [`ml::None`](../Vocabulary/None.md), if the type does not define such an alias.

```c++
struct A { using ValueType = int;};
struct B {};

template <typename _T>
using GetType = typename _T::ValueType;

using T0 = ml::f<ml::IfValidOr<>,
                 ml::None,       // Default
                 ml::F<GetType>, // make GetType a metafunction
                 A               // type for which to check
                 >;
using T1 = ml::f<ml::IfValidOr<>,
                 ml::None,       // Default
                 ml::F<GetType>, // make GetType a metafunction
                 B               // type for which to check
                 >;
static_assert( std::is_same_v<
                          T0, int>);
static_assert( std::is_same_v<
                          T1, ml::None>);
```

