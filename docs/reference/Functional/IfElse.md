# `<CppML/Functional/IfElse.hpp>`

## `IfElse`

```c++
template <typename B, typename Pipe = ml::Identity>
struct IfElse {
  template <typename T0, typename T1>
  using f = /* .... */;
};
```
### `IfElse<Bool<t>, Pipe>`

`IfElse<Test>` is a metafunction that passes to  `U`, which is `T0` if `B` is [`ml::Bool`](../Vocabulary/Value.md)`<true>`, and `T1` if `B` is [`ml::Bool`](../Vocabulary/Value.md)`<false>`. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f:: T0, T1 -> U
```

### Example

```c++
using U = ml::f<
              IfElse<ml::Bool<true>>,
              int,
              char;

static_assert(
          std::is_same_v<
                         U, int>);
```


