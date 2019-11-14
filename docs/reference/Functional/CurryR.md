# `<CppML/Functional/CurryR.hpp>`

## `CurryR`

```c++
template <typename F>
struct CurryR {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `CurryR<F>`

Let `F` be a metafunction `Args... -> Us...`. Than `CurryR<F>` is a metafunction that takes a parameter pack `T0s...`, and returns a metafunction `F': T1s... -> Us...`, in such a way, that `F(T1s..., T0...) == F'(T1s...)`.

```c++
f:: T1s... -> T0s... -> Us...
```

**NOTE**

This is similar to [`ml::Curry`](./Curry.md), with the order of the parameter packs `T0s...` and `T1s...` switched.

### Example

We can create a metafunction that checks if alignment of a type `T` is **greater** than alignment of *some other type* `U`, by taking [`ml::Map`](./Map.md) of [`ml::AligmentOf`](../TypeTraits/AligmentOf.md)  that has [`ml::Greater`](../Arithmetic/Greater.md) as `Pipe`, and curry it on the right with `U`.

```c++
using Maker = ml::CurryR<
                ml::Map<
                    ml::AligmentOf<>,
                    ml::Greater<>>>;

using IsMoreThanInt = ml::f<Maker, int>;
using IsMoreThanChar = ml::f<Maker, char>;

using T0 = ml::f<IsMoreThanInt, float>;
using T1 = ml::f<IsMoreThanChar, float>;
static_assert(
        std::is_same_v<
                T0, ml::Bool<false>>);
static_assert(
        std::is_same_v<
                T1, ml::Bool<true>>);
```
