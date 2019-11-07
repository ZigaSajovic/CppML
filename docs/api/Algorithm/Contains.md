# `<CppML/Algorithm/Contains.hpp>`

## `Contains`

```c++
template <typename T, typename Pipe = ml::Identity>
struct Contains {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Contains<T, Pipe>`

`Contains<T, Pipe>` is a metafunction that returns [`ml::Bool`](../Vocabulary/Value.md)`<truth_value>`, where truth_value marks whether the parameter pack `Ts` contains `T`.  The result is passed to `Pipe`, which defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
Contains<T, Pipe>:: Ts... -> ml::Bool<truth_value> -> ResultOf(Pipe)
```

### Example

```c++
using T0 = ml::Invoke<
                     ml::Contains<int>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<T, ml::Bool<true>);

using T1 = ml::Invoke<
                     ml::Contains<
                               int,
                               ml::Not<>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<T, ml::Bool<false>);
```
