# `<CppML/Algorithm/AnyOf.hpp>`

## `AnyOf`

```c++
template <typename Predicate, typename Pipe = ml::Identity>
struct AnyOf {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `AnyOf<Predicate, Pipe>`

`AnyOf<Predicate, Pipe>` is a metafunction that passes to `Pipe` and [`ml::Bool`](../Vocabulary/Value.md)`<truth_value>`, where truth_value marks whether the predicate holds for any element of the parameter pack `Ts`. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f:: Ts... -> ml::Bool<truth_value> >-> Pipe
```

#### Predicate

Predicate must be a metafunction returning [`ml::Bool<truth_value>`](../Vocabulary/Value.md).
```
f: T -> ml::Bool<truth_value>
```

### Example

```c++
using T0 = ml::Invoke<
                     ml::AnyOf<ml::IsClass<>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<T, ml::Bool<true>);

using T1 = ml::Invoke<
                     ml::AnyOf<
                               ml::IsClass<>,
                               ml::Not<>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<T, ml::Bool<false>);
```
