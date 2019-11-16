# `<CppML/Functional/Constant.hpp>`

## `Constant`

```c++
template <typename T, typename Pipe = ml::Identity>
struct Constant {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Constant<T>`

`Constant<T>` is a metafunction that always passes `T` to `Pipe`. `Pipe` default to [`ml::Identity`](./Identity.md).

```c++
f:: Ts... -> T >-> Pipe
```
### Example

```c++
using T = ml::f<
              ml::Constant<bool>,
              ml::Int<1>, char>;
static_assert(
      std::is_same_v<
            T,bool>);
```
