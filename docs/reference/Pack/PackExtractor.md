# `<CppML/Pack/PackExtractor.hpp>`

## `PackExtractor`

```c++
template <typename ...Ts>
struct PackExtractor {
  template <typename I>
  using f = /* .... */;
};
```
### `PackExtractor<Ts...>`

`PackExtractor<Ts...>` is a metafunction that returns `U`, which is the `I::value`-th element of the parameter pack `Ts...`.

```c++
f::  I -> U 
```

### Example

```c++
using Extractor = ml::PackExtractor<int, char, bool>;

using T = ml::f<
               Extractor,
               ml::Int<1>>;

static_assert( std::is_same_v<T, char>);
```
