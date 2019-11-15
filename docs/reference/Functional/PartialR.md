# `<CppML/Functional/PartialR.hpp>`

## `PartialR`

```c++
template <typename F, typename ...Args>
struct PartialR {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `PartialR<F, Args...>`

`PartialR<F, Args...>` is a metafunction, that is a partial evaluation of `F`. When invoked on `Ts...`, it is as if `F` was invoked on `Ts..., Args...`.

```c++
f:: Ts... -> F(Ts..., Args...)
```

### Example

We can create a metafunction that checks if alignment of a type `T` is **greater** than alignment `int`, by taking [`ml::Map`](./Map.md) of [`ml::AlignOf`](../TypeTraits/AligmentOf.md)  that has [`ml::Greater`](../Arithmetic/Greater.md) as `Pipe`, and partially evaluate it on the right by `int`.

```c++
using IsMoreThanInt = 
          ml::PartialR<
              ml::Map<
                ml::AlignOf<>,
                ml::Greater<>>,
              int>;

using T0 = ml::f<F, float>;
using T1 = ml::f<F, double>;
static_assert(
        std::is_same_v<
                T0, ml::Bool<false>>);
static_assert(
        std::is_same_v<
                T1, ml::Bool<true>>);
```
