# `<CppML/Pack/Length.hpp>`

## `Length`

```c++
template <typename Pipe = ml::Identity>
struct Length {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Length<Pipe>`

`Length<Pipe>` is a metafunction that passes to `Pipe`  an [`ml::Int`](../Vocabulary/Value.md)`<size>`, where `size` is the length of the parameter pack `Ts...`. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f::  Ts... -> ml::Int<size> >-> Pipe
```

**NOTE**

To get  the number of template arguments of a type (e.g. `std::tuple<Args...>`), use  [`ml::Length`](./Length.md) as the `Pipe` of [`ml::Unwrap`](./Functional/Unwrap). See [example](#example) below.

### Example

```c++
using T0 = ml::f<
                 ml::Length<>,
                 int, char, bool>;

using T1 = ml::f<
                 ml::Unwrap<
                          ml::Length<>>,
                 std::tuple<int, char, bool>>;

static_assert( std::is_same_v<T0, ml::Int<3>>);
static_assert( std::is_same_v<T1, ml::Int<3>>);

```
