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
## `F1`

```c++
template <template <class> class TF>
struct F1 {
  template <typename T>
  using f = /* .... */;
};
```
### `F1<TF>`

`F1<TS>` creates a metafunction of one variable from a *template*.

```c++
f:: T -> TF<T>
```
## `F2`

```c++
template <template <class, class> class TF>
struct F2 {
  template <typename T, typename U>
  using f = /* .... */;
};
```
### `F2<TF>`

`F2<TS>` creates a metafunction of two variables from a *template*.

```c++
f:: T, U -> TF<T, U>
```
