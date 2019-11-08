# `<CppML/Functional/Invoke.hpp>`

#### Table of Contents

* [`Invoke`](#invoke)
* [`f`](#f)

## `Invoke`

```c++
template <typename F, typename ...Ts>
using Invoke = /*...*/;
```
### `Invoke<F, Ts...>`

`Invoke<F, Ts...>` is a convenience alias that invokes the metafunction `F` on a parameter pack `Ts...`. It is equivalent to
```c++
typename F::template f<Ts...>;
```

## `f`

```c++
template <typename F, typename ...Ts>
using f = /*...*/;
```
### `f<F, Ts...>`

`f<F, Ts...>` is a convenience alias that invokes the metafunction `F` on a parameter pack `Ts...`. It is equivalent to
```c++
typename F::template f<Ts...>;
```

**NOTE**

It is identical to [`ml::Invoke`](#invoke).
