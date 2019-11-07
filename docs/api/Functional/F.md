# `<CppML/Functional/F.hpp>`

## `F`

```c++
template <template <class ...> class TF>
struct F {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `F<TF>`

`F<TS>` creates a metafunction from a *template*.

```c++
f:: Ts... -> TF<Ts...>
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

