# `<CppML/Functional/Compose.hpp>`

## `Compose`

```c++
template <typename ...Fs>
struct Compose {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Compose<Fs...>`

`Compose<Fs...>` is a composition of metafunctions in the parameter pack `Fs...`. As such, `Compose<Fs...>` is itself a metafunction. There is no explicit `Pipe` argument, because the first one, `F0`, is `Pipe` implicitly.

```c++
f:: Ts... -> Ftn >-> ... -> Ft0
```

#### Fs...

Each metafunction `Fi` in the parameter pack `Fs...` needs to be able to take output of the `F_{i+1}` as input.

**NOTE** that composition happens from the outside in.

### Example

There are situations, where you do not have access to the `Pipe` argument. For instance, you get passed a predicate, which you want to negate.

```c++
using Predicate = ml::IsSame<>;
using NegatedPredicate = ml::Compose<
                                ml::Not<>,
                                Predicate>;
using T0 = ml::Invoke<
                  Predicate,
                  int, int>;
using T1 = ml::Invoke<
                  NegatedPredicate,
                  int, int>;
static_assert(
        std::is_same_v<
              T0, ml::Bool<true>>);
static_assert(
        std::is_same_v<
              T1, ml::Bool<false>>);
```

`NegatedPredicate` is of course equivalent to the `Pipe` formulation.

```c++
using NegatedPredicate2 = ml::IsSame<ml::Not<>>;
```
