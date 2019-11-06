# `<CppML/Arithmetic/Equals.hpp>`

## `Equals`

```c++
template <typename Pipe = ml::Identity>
struct Equals {
  template <typename T, typename U>
  using f = /* .... */;
};
```
### `Equals<Pipe>`

`Equals<Pipe>` is a metafunction that passes to `Pipe` an [`ml::Bool`](../Vocabulary/Const.md)`<truth_value>`, where truth_value marks whether the `::value`s of underlying types are equal. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f:: T, U -> ml::Bool<truth_value> -> ResultOf(Pipe)
```

**NOTE**: this is not [`ml::IsSame`](../TypeTraits/IsSame.md), which checks is the two input types are the same type.

#### T, U

Types `T` and `U` need an `::value` alias, like [`ml::Const<Type, value>`](../Vocabulary/Const.md).

### Example

```c++
using T0 = ml::Invoke<
                     ml::Equals<>,
                     ml::Int<0>, ml::Int<2>>;
static_assert(
              std::is_same_v<T0, ml::Bool<false>);

using T1 = ml::Invoke<
                     ml::Equals< ml::Not<>>,
                     ml::Int<0>, ml::Int<2>>;
static_assert(
              std::is_same_v<T1, ml::Bool<true>);
```
