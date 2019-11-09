# `<CppML/ControlFlow/IfElse.hpp>`

## `IfElse`

```c++
template <bool Test>
struct IfElse {
  template <typename T0, typename T1>
  using f = /* .... */;
};
```
### `IfElse<Test>`

`IfElse<Test>` is a metafunction that returns `U`, which is `T0` if `First` is `true`, and `T1` otherwise.

```c++
f:: T0, T1 -> U
```

### Example

```c++
using U = ml::Invoke<
              IfElse<true>,
              int,
              char;

static_assert(
          std::is_same_v<
                         U, int>);
```


