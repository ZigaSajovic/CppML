# `<CppML/Functional/Curry.hpp>`

## `Curry`

```c++
template <typename F>
struct Curry {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Curry<F>`

Let `F` be a metafunction `Args... -> Us...`. Than `Curry<F>` is a metafunction that takes a parameter pack `T0s...`, and returns a metafunction `F': T1s... -> Us...`, in such a way, that `F(T0s..., T1s...) == F'(T1s...)`.

```c++
f:: T0s... -> T1s... -> Us...
```

### Example

One can create a metafunction that checks if a type is equal to some type, by currying [`ml::IsSame`](../TypeTraits/IsSame.md), and invoking it on that type.

```c++
using MakePredicate = ml::Curry<ml::IsSame<>>;
using IsInt = ml::Invoke<
                          MakePredicate, int>;
using IsDouble = ml::Invoke<
                          MakePredicate, double>;

using T0 = ml::Invoke<IsDouble, double>;
using T1 = ml::Invoke<IsInt, int>;
static_assert(
      std::is_same_v<T0, ml::Bool<true>);
static_assert(
      std::is_same_v<T1, ml::Bool<true>);
```
