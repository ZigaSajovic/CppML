# `<CppML/Functional/F.hpp>`

## `F`

```c++
template <template <class ...> class TF, typename Pipe = ml::Identity>
struct F {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `F<TF, Pipe>`

`F<TF, Pipe>` creates a metafunction from a *template*, that passes `TF<Args...>` to `Pipe`. `Pipe` defaults to [`ml::Identity`](./Identity.md).

```c++
f:: Ts... -> TF<Ts...> >-> Pipe
```

### Example

If we want to `Pipe` the result of a metacomputation into a `std::tuple`, we can transform it into a metafunction, and use it as `Pipe`.

```c++
using F = ml::F<std::tuple>;
using T = ml::Invoke<
              ml::Pivot<
                    2,
                    F>,
              int, char, double>;
static_assert(
        std::is_same_v<
              T,
              std::tuple<double, int, char>>);
```
