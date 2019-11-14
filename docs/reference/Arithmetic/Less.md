# `<CppML/Arithmetic/Less.hpp>`

## `Less`

```c++
template <typename Pipe = ml::Identity>
struct Less {
  template <typename T, typename U>
  using f = /* .... */;
};
```
### `Less<Pipe>`

`Less<Pipe>` is a metafunction that passes to `Pipe` an [`ml::Bool`](../Vocabulary/Value.md)`<truth_value>`, where truth_value marks whether the first `::value` of underlying types is less than the second. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f:: T, U -> ml::Bool<truth_value> -> ResultOf(Pipe)
```

#### T, U

Types `T` and `U` need an `::value` alias, like [`ml::Value<Type, value>`](../Vocabulary/Value.md).

### Example

```c++
using T0 = ml::f<
                 ml::Less<>,
                 ml::Int<0>, ml::Int<2>>;
static_assert(
              std::is_same_v<T0, ml::Bool<true>);

using T1 = ml::f<
                 ml::Less<ml::Not<>>,
                 ml::Int<0>, ml::Int<2>>;
static_assert(
              std::is_same_v<T1, ml::Bool<false>);
```
