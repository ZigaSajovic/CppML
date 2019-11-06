# `<CppML/Arithmetic/Greater.hpp>`

## `Greater`

```c++
template <typename Pipe = ml::Identity>
struct Greater {
  template <typename T, typename U>
  using f = /* .... */;
};
```
### `Greater<Pipe>`

`Greater<Pipe>` is a metafunction that passes to `Pipe` an [`ml::Bool`](../Vocabulary/Const.md)`<truth_value>`, where truth_value marks whether the first `::value` of underlying types is greater than the second. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f:: T, U -> ml::Bool<truth_value> -> ResultOf(Pipe)
```

#### T, U

Types `T` and `U` need an `::value` alias, like [`ml::Const<Type, value>`](../Vocabulary/Const.md).

### Example

```c++
using T0 = ml::Invoke<
                     ml::Greater<>,
                     ml::Int<0>, ml::Int<2>>;
static_assert(
              std::is_same_v<T0, ml::Bool<false>);

using T1 = ml::Invoke<
                     ml::Greater<ml::Not<>>,
                     ml::Int<0>, ml::Int<2>>;
static_assert(
              std::is_same_v<T1, ml::Bool<true>);
```
