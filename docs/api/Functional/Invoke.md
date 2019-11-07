# `<CppML/Functional/Invoke.hpp>`

## `Invoke`

```c++
template <typename F, typename ...Ts>
using Invoke = /*...*/
```
### `Invoke<F, Ts...>`

`Invoke<F, Ts...>` is a convenience alias that invokes the metafunction `F` on a parameter pack `Ts...`. It is equivalent to
```c++
typename F::template f<Ts...>;
```
