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
* `T = ml::Invoke<F, Args...>`
  * if `ml::Invoke<F, Args...>` is *valid* and not *ill-formed*, or
* `T = Default`
  * if `ml::Invoke<F, Args...>` is *not valid* and is *ill-formed*

`Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f::  Default F, Args... -> T <-> Pipe
```

### Example

It can be used to implement logic based on introspection.

```c++
struct A { using T = int;};
struct B { using U = int;};
template <typename _T>
using GetType = typename _T::T;
using T0 = ml::Invoke<ml::IfValidOr<>,
                      ml::None,       // Default
                      ml::F<GetType>, // metafunction to check
                      A               // type for which to check
                      >;
using T1 = ml::Invoke<ml::IfValidOr<>,
                      ml::None,       // Default
                      ml::F<GetType>, // metafunction to check
                      B               // type for which to check
                      >;
static_assert( std::is_same_v<
                          T0, int>);
static_assert( std::is_same_v<
                          T1, ml::None>);
```

