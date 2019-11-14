# `<CppML/Algorithm/MaxElement.hpp>`

## `MaxElement`

```c++
template <typename Compare, typename Pipe = ml::Identity>
struct MaxElement {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `MaxElement<Compare, Pipe>`

`MaxElement<Compare, Pipe>` is a metafunction that passes to `Pipe` the element `U` of the parameter pack `Ts...` which is maximal, given the `Compare` metafunction. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f:: Ts... -> U >-> Pipe
```

#### Compare

Compare must be a metafunction acting on two types and returning [`ml::Bool<truth_value>`](../Vocabulary/Value.md).
```
f:: (T, U) -> ml::Bool<truth_value>
```

### Example

```c++
using T0 = ml::f<
                 ml::MaxElement<
                      ml::Map<
                              ml::AligmentOf<>,
                              ml::Greater<>>>,
                 int, double, char>;
static_assert(
              std::is_same_v<
                  T, double>);
```

**NOTE** that
```c++
ml::Map<
        ml::AligmentOf<>, // maps each element by taking its aligment
        ml::Greater<>>      // and pipes the resulting parameter pack into greater
```
is a metafunction of type
```
(T, U) -> (AligmentOf(T), AligmentOf(U)) >-> Greater
```
and is as such a valid [compare](#compare) metafunction. See [`ml::Map`](../Functional/Map.md).
