# `<CppML/Functional/ToList.hpp>`

## `ToList`

```c++
struct ToList {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `ToList`

`ToList` is a metafunction that returns the parameter pack `Ts...` wrapped in a list; [`ml::ListT`](../Vocabulary/List.md)`<Ts...>`.

```c++
f:: Ts... -> ml::ListT<Ts...>
```

[`ml::ListT`](../Vocabulary/List.md) is used as the default `Pipe` for all metafunctions that forward a parameter pack. Remember that a parameter pack is not a type, and can therefore cannot be what a metafunction returns.

### Example

```c++
using T = ml::Invoke<
                ml::ToList,
                int, char>;
static_assert(
        std::is_same_v<
                T,
                ml::ListT<
                    int, char>>);
```
