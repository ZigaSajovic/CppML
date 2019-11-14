# `<CppML/Pack/Front.hpp>`

## `Front`

```c++
template <typename Pipe = ml::ToList>
struct Front {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Front<Pipe>`

`Front<Pipe>` is a metafunction that passes to `Pipe` the first element of the parameter pack `Ts...`. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f::  T0, T's... -> T0 >-> Pipe
```

### Example

```c++
using AF = ml::Front<ml::F<std::tuple>>;
using T = ml::f<
               AF,
               int, char, bool, double>;
static_assert(
              std::is_same_v<
                  T,
                  std::tuple<int>>);

```
