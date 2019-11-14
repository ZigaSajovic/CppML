# `<CppML/Arithmetic/Increment.hpp>`

## `Increment`

```c++
template <typename Pipe = ml::Identity>
struct Increment {
  template <typename T>
  using f = /* .... */;
};
```
### `Increment<Pipe>`

`Increment<Pipe>` is a metafunction that passes to `Pipe` an [`ml::Int`](../Vocabulary/Value.md)`<value>`, where value is an increment of the `::value` of underlying type. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f:: T -> ml::Int<value> -> ResultOf(Pipe)
```

#### T

Types `T` needs an `::value` alias, like [`ml::Value<Type, value>`](../Vocabulary/Value.md).

### Example

```c++
using T0 = ml::f<
                 ml::Increment<>,
                 ml::Int<0>>;
static_assert(
              std::is_same_v<T0, ml::Int<1>);
```



