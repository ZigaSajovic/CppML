# `<CppML/Algorithm/ZipWith.hpp>`

## `ZipWith`

```c++
template <template <class...> With, typename Pipe = ml::ToList>
struct ZipWith {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `ZipWith<With, Pipe>`

`ZipWith<With, Pipe>` is a metafunction takes a parameter pack of [`ml::ListT`](../Vocabulary/List.md)`<Ts...>...., `[`ml::ListT`](../Vocabulary/List.md)`<Us...>...` and passes to `Pipe` a parameter pack `With<T0, U0, ...> ... With<Tn, Un, ...>`. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: ml::ListT<Ts...>, ml::ListT<Us...>... -> With<T0, U0, ...> ... With<Tn, Un, ...> -> ResultOf(Pipe)
```

#### With

With can be any template, which **does not** need to be variadic.

**NOTE**: because `With` does not need to be a variadic template, we cannot build the zip with it (i.e. if `With` needs exactly two arguments). For this reason the elements are first zipped using [ml::ListT](../Vocabulary/List.md) and re-zipped at the end using `With`. There exists [`ml::ZipWithVariadic`](./ZipWithVariadic.md) which builds the zip directly using `With`, which must be variadic.

### Example

```c++
using T0 = ml::Invoke<
                     ml::ZipWith<std::pair>,
                     ml::ListT<int, char>,
                     ml::ListT<float, double>>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<
                      std::pair<int, float>,
                      std::pair<char, double>>>);
```
