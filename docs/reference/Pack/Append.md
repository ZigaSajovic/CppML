# `<CppML/Pack/Append.hpp>`

## `Append`

```c++
template <typename T, typename Pipe = ml::ToList>
struct Append {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Append<T, Pipe>`

`Append<T, Pipe>` is a metafunction that passes to `Pipe` the parameter pack `Ts...`, with `T` appended; i.e. `Ts..., T`. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: Ts... -> Ts..., T >-> Pipe
```

**NOTE**

If you have a need to append more than one element to a parameter pack being passed to `Pipe`, you should be looking at partial evaluations from the right, [`ml::PartialR`](../Functional/PartialR.md), from the `Functional` header.

### Example

```c++
using AF = ml::Append<int, ml::F<std::tuple>>;

using T = ml::Invoke<
                   AF,
                   std::string>;
static_assert(
              std::is_same_v<
                  T,
                  std::tuple<std::string, int>>);

```
