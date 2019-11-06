# `<CppML/Algorithm/Unique.hpp>`

## `Unique`

```c++
template <typename Pipe = ml::ToList>
struct Unique {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Unique<Pipe>`

`Unique<Pipe>` is a metafunction that passes to `Pipe` a parameter pack `Us...`, which consists of unique elements of the parameter pack `Ts...`.  `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: Ts... -> Us... -> ResultOf(Pipe)
```

### Example

```c++
using T = ml::Invoke<
                    ml::Unique<>,
                        int, double, int, long>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<
                    int, double, long>>);
```
