# `<CppML/TypeTraits/AligmentOf.hpp>`

## `AligmentOf`

```c++
template <typename Pipe = ml::Identity>
struct AligmentOf {
  template <typename T>
  using f = /* .... */;
};
```
### `AligmentOf<Pipe>`

`AligmentOf<Pipe>` is a metafunction that passes to `Pipe` an `ml::Int<aligment>`, where `aligment` is the *alignment* of `T`. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f::  T ->  ml::Int<alignmentOf(T)> <-> Pipe
```

### Example

```c++
using T = ml::Invoke<
                ml::AligmentOf<>,
                double>;
static_assert( std::is_same_v<
                          T0,
                          ml::Int<8>>);
```
