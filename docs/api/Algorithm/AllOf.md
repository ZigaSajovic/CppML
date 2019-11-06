# `<CppML/Algorithm/AllOf.hpp>`

## `AllOf`

```c++
template <typename Predicate, typename Pipe = ml::Identity>
struct AllOf {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `AllOf<Predicate, Pipe>`

`AllOf<Predicate, Pipe>` is a metafunction that returns [`ml::Bool`](../Vocabulary/Const.md)`<truth_value>`, where truth_value marks whether the predicate holds for all elements of the parameter pack `Ts`.  The result is passed to `Pipe`, which defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
AllOf<Predicate, Pipe>:: Ts... -> ml::Bool<truth_value> -> ResultOf(Pipe)
```

#### Predicate

Predicate must be a metafunction returning [`ml::Bool<truth_value>`](../Vocabulary/Const.md).
```
f:: T -> ml::Bool<truth_value>
```

### Example

```c++
using T0 = ml::Invoke<
                     ml::AllOf<ml::IsClass<>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<T, ml::Bool<false>);

using T1 = ml::Invoke<
                     ml::AllOf<
                               ml::IsClass<>,
                               ml::Not<>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<T, ml::Bool<true>);
```
