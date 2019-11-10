# `<CppML/Algorithm/Partition.hpp>`

### `Partition<Predicate, Pipe>`

`Partition<Predicate, Pipe>` is a metafunction that passes to `Pipe` two [`ml::ListT`](../Vocabulary/List.md)`<Us...>`, where the first list consists of `Us...`, types which evaluate to [`ml::Bool`](../Vocabulary/Value.md)`<true>` under `Predicate`, and the second those `Us...` that evaluate to [`ml::Bool`](../Vocabulary/Value.md)`<false>`. Formally speaking, `Partition<Predicate, Pipe>` forms equivalence classes of `Ts...` under `Predicate`. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: Ts... -> (ml::ListT<U0s...>, ml::ListT<U1s...>) >-> Pipe
```

#### Predicate

Predicate can be any metafunction returning a single type.
```
f:: T -> U
```

### Example

We partition a parameter pack, to those whose alignment is greater than 4, and those whose it is not.
```c++
using T = ml::Invoke<
              ml::Partition<
                    ml::AligmentOf<
                        ml::PartialRR<
                            ml::Greater<>,
                            ml::Int<4>>>>,
              int, char, long, bool, double>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<
                      ml::ListT<long, double>,
                      ml::ListT<int, char, bool>);
```
**NOTE** that
```
ml::AligmentOf<          // take aligment of the input and pipe into
      ml::PartialRR<       // a partial evaluation of the metafunction
          ml::Greater<>, // greater
          ml::Int<4>>>   // on ml::Int<4>
```
is a metafunction of the type
```
f:: T -> AligmentOf(T) >-> Curry<Greater>(4)
```
and conforms to the [predicate](#predicate) constraints.
