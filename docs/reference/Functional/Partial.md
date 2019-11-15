# `<CppML/Functional/Partial.hpp>`

## `Partial`

```c++
template <typename F, typename ...Args>
struct Partial {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Partial<F, Args...>`

`Partial<F, Args...>` is a metafunction, that is a partial evaluation of `F`. When invoked on `Ts...`, it is as if `F` was invoked on `Args..., Ts...`.

```c++
f:: Ts... -> F(Args..., Ts...)
```

### Example

We can create a metafunction that checks if alignment of a type `T` is **greater** than alignment `int`, by taking [`ml::Map`](./Map.md) of [`ml::AlignOf`](../TypeTraits/AligmentOf.md)  that has [`ml::Less`](../Arithmetic/Less.md) as `Pipe`, and partially evaluate it on the left by `int` (note the order of arguments).

```c++
using IsMoreThanInt = 
          ml::Partial<
              ml::Map<
                ml::AlignOf<>,
                ml::Less<>>,
              int>;

using T0 = ml::f<IsMoreThanInt, float>;
using T1 = ml::f<IsMoreThanInt, double>;
static_assert(
        std::is_same_v<
                T0, ml::Bool<false>>);
static_assert(
        std::is_same_v<
    
