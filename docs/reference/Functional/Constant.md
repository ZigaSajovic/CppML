# `<CppML/Functional/Constant.hpp>`

## `Constant`

```c++
template <typename T>
struct Constant {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Constant<T>`

`Constant<T>` is a metafunction always evaluates to `T`.

```c++
f:: Ts... -> T
```
### Example

```c++
using T = ml::Invoke<
              ml::Constant<bool>,
              ml::Int<1>, char>;
static_assert(
      std::is_same_v<
            T,bool>);
```
