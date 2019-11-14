# `<CppML/Algorithm/ZipWithVariadic.hpp>`

## `ZipWithVariadic`

```c++
template <template <class...> With, typename Pipe = ml::ToList>
struct ZipWithVariadic {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `ZipWithVariadic<With, Pipe>`

`ZipWithVariadic<With, Pipe>` is a metafunction takes a parameter pack of [`ml::ListT`](../Vocabulary/List.md)`<Ts...>...., `[`ml::ListT`](../Vocabulary/List.md)`<Us...>...` and passes to `Pipe` a parameter pack `With<T0, U0, ...> ... With<Tn, Un, ...>`. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: ml::ListT<Ts...>, ml::ListT<Us...>... -> With<T0, U0, ...> ... With<Tn, Un, ...> >-> Pipe
```

#### With

With **must** be a variadic template.

**NOTE**: for non-variadic template `With`, see [`ml::ZipWith`](./ZipWith.md).

### Example

```c++
using T0 = ml::f<
                 ml::ZipWithVariadic<std::pair>,
                 ml::ListT<int, char>,
                 ml::ListT<float, double>>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<
                      std::pair<int, float>,
                      std::pair<char, double>>>);
```
