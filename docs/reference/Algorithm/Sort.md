# `<CppML/Algorithm/Sort.hpp>`

## `Sort`

```c++
template <typename Compare, typename Pipe = ml::ToList>
struct Sort {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Sort<Compare, Pipe>`

`Sort<Compare, Pipe>` is a metafunction that passes to `Pipe` a parameter pack `Us...` which is such a reordering of the parameter pack `Ts...`, that is sorted by the `Compare` metafunction. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: Ts... -> Us... >-> Pipe
```

#### Compare

Compare must be a metafunction acting on two types and returning [`ml::Bool<truth_value>`](../Vocabulary/Value.md).
```
f:: (T, U) -> ml::Bool<truth_value>
```

### Example

We sort types by their alignment.

```c++
using T = ml::Invoke<
                    ml::Sort<
                        ml::Map<
                                ml::AligmentOf<>,
                                ml::Greater<>>>,
                        int, double, char, long>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<
                    long, double, int, char>>);
```

**NOTE** that
```c++
ml::Map<
        ml::AligmentOf<>, // maps each element by taking its alignment
        ml::Greater<>>      // and pipes the resulting parameter pack into greater
```
is a metafunction of type
```
(T, U) -> (AligmentOf(T), AligmentOf(U)) >-> ml::Greater
```
and is as such a valid [compare](#compare) metafunction. See [`ml::Map`](../Functional/Map.md).
