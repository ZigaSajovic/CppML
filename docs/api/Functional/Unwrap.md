# `<CppML/Functional/Unwrap.hpp>`

## `Unwrap`

```c++
template <typename Pipe>
struct Unwrap {
  template <typename Wrapped>
  using f = /* .... */;
};
```
### `Unwrap<Pipe>`

`Unwrap<Pipe>` is a metafunction that passes to `Pipe` the parameter pack `Ts...`, which is generated unwrapping the outermost template of `Template<Ts...>`.

```c++
f:: Wrapper<Ts...> -> Ts... >-> Pipe
```

#### `Wrapped`

`Wrapped` needs to be an instantiation of a class template, `Template<Ts...>`.

### Example

[`ml::Unwrap`](./Unwrap.md) is usually used to unwrap the elements of a list-like and pass them to a metafunction `Pipe` expecting a parameter pack. It should be rarely needed, as you should strive for chaining metafunctions via `Pipe`s (where parameter packs are forwarded). In general, there are two situations where you might need it:
* you are already holding a list-like, and need to invoke a metafunction on the parameters it is holding, or
* you need to compose two concrete metafunctions via [`ml::Compose`](./Compose.md) (because you do not have access to setting their `Pipe`s), and the first returns a list-like.

Suppose we have two concrete metafunctions (with no access to their `Pipe` parameters).

```c++
using cF0 = ml::Pivot<2>;
using cF1 = ml::Map<ml::Increment<>>;
```
They cannot be composed, because `cF0` returns an [`ml::ListT`](../Vocabulary/List.md), and `cF1` expects a parameter pack. So we [`ml::Unwrap`](../Vocabulary/Unwrap.md).
```c++
using T0 = ml::Invoke<
              ml::Unwrap<cF1>,
              ml::Invoke<
                  cF1,
                  ml::Int<0>, ml::Int<1>, ml::Int<2>>>
```
We can use [`ml::Compose`](./Compose.md), instead of invoking twice.
```c++
using F = ml::Compose<
                ml::Unwrap<cF1>,
                cF0>;
using T1 = ml::Invoke<
                  F,
                  ml::Int<0>, ml::Int<1>, ml::Int<2>>;
```
