# `<CppML/Arithmetic/Not.hpp>`

## `Not`

```c++
template <typename Pipe = ml::Identity>
struct Not {
  template <typename T>
  using f = /* .... */;
};
```
### `Not<Pipe>`

`Not<Pipe>` is a metafunction that passes to `Pipe` an [`ml::Bool`](../Vocabulary/Const.md)`<truth_value>`, where value is the negation of `::value` of underlying type. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f:: T -> ml::Bool<truth_value> -> ResultOf(Pipe)
```

#### T

Types `T` needs an `::value` alias, like [`ml::Const<Type, value>`](../Vocabulary/Const.md).

### Example

```c++
using T0 = ml::Invoke<
                     ml::Not<>,
                     ml::Bool<true>>;
static_assert(
              std::is_same_v<T0, ml::Bool<false>);
```


