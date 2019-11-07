# `<CppML/Algorithm/NoneOf.hpp>`


## `NoneOf`

```c++
template <typename Predicate, typename Pipe = ml::Identity>
struct NoneOf {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `NoneOf<Predicate, Pipe>`

`NoneOf<Predicate, Pipe>` is a metafunction that passes to `Pipe` an [`ml::Bool`](../Vocabulary/Value.md)`<truth_value>`, where truth_value marks whether the predicate holds for all elements of the parameter pack `Ts`.  `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f:: Ts... -> ml::Bool<truth_value> -> ResultOf(Pipe)
```

#### Predicate

Predicate must be a metafunction returning [`ml::Bool<truth_value>`](../Vocabulary/Value.md).
```
f:: T -> ml::Bool<truth_value>
```

### Example

```c++
using T0 = ml::Invoke<
                     ml::NoneOf<ml::IsClass<>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<T, ml::Bool<false>);

using T1 = ml::Invoke<
                     ml::NoneOf<
                               ml::IsClass<>,
                               ml::Not<>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<T, ml::Bool<true>);
```
