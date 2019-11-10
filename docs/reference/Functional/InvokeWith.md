# `<CppML/Functional/InvokeWith.hpp>`

## `InvokeWith`

```c++
template <typename ...Ts>
struct InvokeWith {
  template <typename F>
  using f = ml::Invoke<F, Ts...>;
};
```
### `InvokeWith<Ts...>

`InvokeWith<Ts...>` is metafunction that takes a metafunction `F: Ts... -> U`, and invokes it with the provided `Ts...`.

```c++
f:: (Ts... -> U) -> U
```
