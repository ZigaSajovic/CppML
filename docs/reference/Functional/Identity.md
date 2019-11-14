# `<CppML/Functional/Identity.hpp>`

## `Identity`

```c++
struct Identity {
  template <typename T>
  using f = /* .... */;
};
```
### `Identity`

`Identity` evaluates to the type it was passed.
```c++
f:: T -> T
```

### Example


```c++
using T = ml::f<
              ml::Identity,
              int>;
static_assert(
        std::is_same_v<
              int, T>);
```
