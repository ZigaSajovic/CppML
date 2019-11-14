# `<CppML/Algorithm/UniqueCompare.hpp>`

## `UniqueCompare`

```c++
template <typename Compare, typename Pipe = ml::ToList>
struct UniqueCompare {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `UniqueCompare<Compare, Pipe>`

`UniqueCompare<Compare, Pipe>` is a metafunction that passes to `Pipe` a parameter pack `Us...`, which consists of those elements of the parameter pack `Ts...`, which are unique, under the `Compare` metafunction. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: Ts... -> Us... >-> Pipe
```

#### Compare

Compare must be a metafunction acting on two types and returning [`ml::Bool<truth_value>`](../Vocabulary/Value.md).
```
f:: (T, U) -> ml::Bool<truth_value>
```

### Example

```c++
using T = ml::f<
                ml::UniqueCompare<
                    ml::IsSame<>>,
                int, double, int, long>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<
                    int, double, long>>);
```
