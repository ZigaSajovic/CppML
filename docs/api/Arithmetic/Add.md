# `<CppML/Arithmetic/Add.hpp>`

## `Add`

```c++
template <typename Pipe = ml::Identity>
struct Add {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Add<Pipe>`

`Add<Pipe>` is a metafunction that passes to `Pipe` an [`ml::Int`](../Vocabulary/Const.md)`<value>`, where value is the sum of `::value`s of underlying types. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f:: T, U -> ml::Int<value> -> ResultOf(Pipe)
```

#### T, U

Types `T` and `U` need an `::value` alias, like [`ml::Const<Type, value>`](../Vocabulary/Const.md).

### Example

```c++
using T0 = ml::Invoke<
                     ml::Add<>,
                     ml::Int<1>, ml::Int<2>>;
static_assert(
              std::is_same_v<T0, ml::Int<3>);
```

