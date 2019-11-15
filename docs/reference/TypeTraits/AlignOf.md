# `<CppML/TypeTraits/AlignOf.hpp>`

## `AlignOf`

```c++
template <typename Pipe = ml::Identity>
struct AlignOf {
  template <typename T>
  using f = /* .... */;
};
```
### `AlignOf<Pipe>`

`AlignOf<Pipe>` is a metafunction that passes to `Pipe` an `ml::Int<aligment>`, where `aligment` is the *alignment* of `T`. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f::  T ->  ml::Int<alignmentOf(T)> <-> Pipe
```

### Example

```c++
using T = ml::f<
                ml::AlignOf<>,
                double>;
static_assert( std::is_same_v<
                          T0,
                          ml::Int<8>>);
```
