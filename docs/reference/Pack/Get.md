# `<CppML/Pack/Get.hpp>`

## `Get`

```c++
template <int N, typename Pipe = ml::Identity>
struct Get {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Get<N, Pipe>`

`Get<N, Pipe>` is a metafunction that passes to `Pipe` the `N`-th element of the parameter pack `Ts...`. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f::  Ts... -> Tn >-> Pipe
```

**NOTE**

Indexing starts at `0`.

### Example

```c++
using T = ml::f<
               ml::Get<2>,
               int, char, bool, double>;
static_assert(
              std::is_same_v<
                            T, bool>);

```
