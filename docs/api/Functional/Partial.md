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

One can create a metafunction that checks if a type is equal to `int`, by partially evaluating [`ml::IsSame`](../TypeTraits/IsSame.md).

```c++
using Predicate = ml::Partial<
                        ml::IsSame<>,
                        int>;
using T0 = ml::Invoke<Predicate, double>;
using T1 = ml::Invoke<Predicate, int>;
static_assert(
      std::is_same_v<T0, ml::Bool<false>);
static_assert(
      std::is_same_v<T1, ml::Bool<true>);
```

One can create a metafunction that appends to a list, by partially evaluating the [`ml::ToList`](./ToList.md) metafunction.

```c++

using Appender = ml::Partial<
                      ml::ToList,
                      int, char>;
using T = ml::Invoke<
                Appender,
                double, bool>;
static_assert(
      std::is_same_v<
            T,
            ml::ListT<
                int, char, double, bool>>);
```

