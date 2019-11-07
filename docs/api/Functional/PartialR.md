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

We can create a metafunction that checks if alignment of a type is greater than `4`, by taking the [`ml::ProductMap`](./ProductMap.md) of [`ml::AlimentOf`](../TypeTraits/AligmentOf.md) and [`ml::Identitiy`](./Identity.md), and `Pipe` it to [`ml::Greater`](../Arithmetic/Greater.md), and partially evaluate it on the right with `ml::Int<1>`.

```c++
using F = ml::PartialR<
              ml::ProductMap<
                  ml::AligmentOf<>,
                  ml::Identity,
                  ml::Greater<>>,
              ml::Int<4>>;

using T0 = ml::Invoke< F, int>;
using T1 = ml::Invoke< F, double>;
static_assert(
        std::is_same_v<
                T0, ml::Bool<false>>);
static_assert(
        std::is_same_v<
                T1, ml::Bool<true>>);
```
