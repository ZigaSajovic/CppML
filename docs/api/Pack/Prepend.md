# `<CppML/Pack/Prepend.hpp>`

## `Prepend`

```c++
template <typename T, typename Pipe = ml::ToList>
struct Prepend {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Prepend<T, Pipe>`

`Prepend<T, Pipe>` is a metafunction that passes to `Pipe` the parameter pack `Ts...`, with `T` prepended; i.e. `T, Ts...`. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: Ts... -> T, Ts... >-> Pipe
```

**NOTE**

If you have a need to prepend more than one element to a parameter pack being passed to `Pipe`, you should be looking at partial evaluations from the left, [`ml::Partial`](../Functional/Partial.md), from the `Functional` header.

### Example

```c++
using AF = ml::Prepend<int, ml::Map<
                              ml::F<std::tuple>>>;
using T = ml::Invoke<
                   AF,
                   std::string>;
static_assert(
              std::is_same_v<
                  T,
                  std::tuple<int, std::string>>);

```
