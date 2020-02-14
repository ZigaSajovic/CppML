# `<CppML/Algorithm/FindIf.hpp>`

## `FindIf`

```c++
template <typename Predicate, typename Pipe = ml::Identity>
struct FindIf {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `FindIf<Predicate, Pipe>`

`FindIf<Predicate, Pipe>` is a metafunction that passes to `Pipe` the first element of the parameter pack `Ts...`, for which the predicate holds. If none match the predicate, it passes [`ml::None`](../Vocabulary/None.md). `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f:: Ts... -> T >-> Pipe
```

#### Predicate

Predicate must be a metafunction returning [`ml::Bool<truth_value>`](../Vocabulary/Value.md).
```
f:: T -> ml::Bool<truth_value>
```

### Example

```c++
using T0 = ml::f<
                 ml::FindIf<ml::IsClass<>>,
                 int, char, std::string>;
static_assert(
              std::is_same_v<
                  T, std::string>);

using T1 = ml::f<
                 ml::FindIf<
                           ml::IsClass<ml::Not<>>>,
                 int, char, std::string>;
static_assert(
              std::is_same_v<
                  T, int>);
```

