# CppML API Reference

#### Headers

| Header                        | Description                                                                                                                     |
|:------------------------------|:--------------------------------------------------------------------------------------------------------------------------------|
| [`Algorithm`](#algorithm)     | Algorithms over parameter packs (e.g. [`Sort`](./Algorithm/Sort.md), [`ZipWith`](./Algorithm/ZipWith.md), etc.)                 |
| [`Arithmetic`](#arithmetic)   | Arithmetic operations on type-values (e.g. [`Greater`](./Arithmetic/Greater.md), [`Not`](./Arithmetic/Not.md), etc.)            |
| [`ControlFlow`](#controlflow) | Constructs that control the flow of metaprograms (e.g. [`IfElse`](./ControlFlow/IfElse.md), [`For`](./ControlFlow/For.md) etc.) |
| [`Functional`](#functional)   | Manipulation of metafunctions (e.g. [`Curry`](./Functional/Curry.md), [`Map`](./Functional/Map.md), etc.)                       |
| [`Pack`](#pack)               | Manipulation of parameter packs (e.g. [`Drop`](./Pack/Drop.md), [`Get`](./Pack/Get.md), etc.)                                   |
| [`TypeTraits`](#typetraits)   | Insights into types (e.g. [`IsSameAs`](./TypeTraits/IsSameAs.md), [`IsClass`](./TypeTraits/IsClass.md), etc.)                   |
| [`Vocabulary`](#vocabulary)   | Vocabulary types of `CppML`   (e.g. [`ListT`](./Vocabulary/ListT.md), [`Value`](./Vocabulary/Value.md), etc.)                   |



## `Algorithm`

Contains *algorithms* that operate on *parameter packs*. You can include any algorithm separately by `CppML/Algorithm/<name>.hpp`, or include the entire header `CppML/Algorithm.hpp`.

| Algorithm                                           | Description                                                      | Type of `f` in `::f >-> Pipe`   |
|-----------------------------------------------------|------------------------------------------------------------------|---------------------------------|
| [`AllOf`](./Algorithm/AllOf.md)                     | Checks if a `Predicate` holds for all of `Ts...`.                | `Ts... -> Bool<t>`              |
| [`AnyOf`](./Algorithm/AnyOf.md)                     | Checks if a `Predicate` holds for any of `Ts...`.                | `Ts... -> Bool<t>`              |
| [`Contains`](./Algorithm/Contains.md)               | Checks is `Ts...` contains `T`.                                  | `Ts... -> Bool<t>`              |
| [`CountIf`](./Algorithm/CountIf.md)                 | Counts `Ts...` for which the `Predicate` holds.                  | `Ts... -> Bool<t>`              |
| [`Filter`](./Algorithm/Filter.md)                   | Filters `Ts...`, for which the `Predicate` holds.                | `Ts... -> Us...`                |
| [`FilterIds`](./Algorithm/FilterIds.md)             | Filters indexes of `Ts...`, for which the `Predicate` holds.     | `Ts... -> Int<Is>...`           |
| [`FindIf`](./Algorithm/FindIf.md)                   | Index of `Ts...` for which the `Predicate` holds.                | `Ts... -> Int<I>`               |
| [`FindIfNot`](./Algorithm/FindIfNot.md)             | Index of `Ts...` for which the `Predicate` does not hold.        | `Ts... -> Int<I>`               |
| [`GroupBy`](./Algorithm/GroupBy.md)                 | Groups `Ts...`, given their image under `By`.                    | `Ts... -> ListT<Us...>...`      |
| [`GroupIdsBy`](./Algorithm/GroupIdsBy.md)           | Groups indexes of `Ts...`, given their (`T`'s) image under `By`. | `Ts... -> ListT<Int<Is>...>...` |
| [`MaxElement`](./Algorithm/MaxElement.md)           | Get maximal element, given a `Comparator`.                       | `Ts... -> U`                    |
| [`NoneOf`](./Algorithm/NoneOf.md)                   | Checks if a `Predicate` holds for none of `Ts...`.               | `Ts... -> Bool<t>`              |
| [`Partition`](./Algorithm/Partition.md)             | Partitions `Ts...` given a `Predicate`.                          | `Ts... -> ListT<Us...>...`      |
| [`PartitionIds`](./Algorithm/PartitionIds.md)       | Partitions indexes of `Ts...` given a `Predicate`.               | `Ts... -> ListT<Int<Is>...>...` |
| [`Pivot`](./Algorithm/Pivot.md)                     | Pivots `Ts...` around the `N`-th element, making it the first.   | `Ts... -> Us...`                |
| [`Reduce`](./Algorithm/Reduce.md)                   | Reduce `Ts...`, given an accumulator `F`.                        | `Ts... -> U`                    |
| [`RemoveIdsIf`](./Algorithm/RemoveIdsIf.md)         | Removes indexes of `Ts...` for which the `Predicate` holds.      | `Ts... -> Us...`                |
| [`RemoveIf`](./Algorithm/RemoveIf.md)               | Removes elements of `Ts...` for which the `Predicate` holds.     | `Ts... -> Int<Is>...`           |
| [`ReplaceIf`](./Algorithm/ReplaceIf.md)             | Replace `Ts...`, for which the `Predicate` holds, by `U`.        | `Ts... -> Us...`                |
| [`Rotate`](./Algorithm/Rotate.md)                   | Pivots `Ts...` in the range `[First, Middle, Last)`.             | `Ts... -> Us...`                |
| [`Sort`](./Algorithm/Sort.md)                       | Sorts `Ts...`, given a `Comparator`.                             | `Ts... -> Us...`                |
| [`UniqueCompare`](./Algorithm/UniqueCompare.md)     | Unique elements of `Ts...`, given a `Comparator`.                | `Ts... -> Us...`                |
| [`Unique`](./Algorithm/Unique.md)                   | Unique elements of `Ts...`.                                      | `Ts... -> Us...`                |
| [`ZipWith`](./Algorithm/ZipWith.md)                 | Zips two lists with a `With` template.                           | `Ts... -> With<Us...>...`       |
| [`ZipWithVariadic`](./Algorithm/ZipWithVariadic.md) | Zips two lists with a variadic `With` template.                  | `Ts... -> With<Us...>...`       |

## `Arithmetic`

Contains *arithmetic operations* that operate on *types* (e. g. `Not`, `Less`). You can include any operation separately by `CppML/Arithmetic/<name>.hpp`, or include the entire header `CppML/Arithmetic.hpp`.

| Arithmetic                               | Description                 | Type of `f` in `::f >-> Pipe`                 |
|------------------------------------------|-----------------------------|-----------------------------------------------|
| [`Add`](./Arithmetic/Add.md)             | Adds two `Value`s           | `Value<T, t>, Value<U, u> -> Value<V, t + u>` |
| [`Decrement`](./Arithmetic/Decrement.md) | Decrements a `Value`        | `Value<t, T> -> Value<--t, T>`                |
| [`Equals`](./Arithmetic/Equals.md)       | Equality check for `Values` | `Value<T, t>, Value<U, u> -> Bool<t>`         |
| [`Greater`](./Arithmetic/Greater.md)     | Greater for `Values`        | `Value<T, t>, Value<U, u> -> Bool<t>`         |
| [`Increment`](./Arithmetic/Increment.md) | Increments a `Value`        | `Value<t, T> -> Value<++t, T>`                |
| [`Less`](./Arithmetic/Less.md)           | Less for `Values`           | `Value<T, t>, Value<U, u> -> Bool<t>`         |
| [`Not`](./Arithmetic/Not.md)             | Negates a `Value`           | `Bool<t> -> Bool< not t>`                     |
| [`Subtract`](./Arithmetic/Subtract.md)   | Subtracts two `Value`s      | `Value<T, t>, Value<U, u> -> Value<V, t + u>` |

## `ControlFlow`

Contains constructs that *control* the *flow* of a metaprogram (e.g. `IfElse`). You can include any operation separately by `CppML/ControlFlow/<name>.hpp`, or include the entire header `CppML/ControlFlow.hpp`.

* [`For`](./ControlFlow/For.md)
* [`IfElse`](./ControlFlow/IfElse.md)

## `Functional`

Contains *functional* utilities (e.g. `Map`). You can include any construct separately by `CppML/Functional/<name>.hpp`, or include the entire header `CppML/Functional.hpp`.

* [`Bind`](./Functional/Bind.md)
* [`Compose`](./Functional/Compose.md)
* [`Constant`](./Functional/Constant.md)
* [`Curry`](./Functional/Curry.md)
* [`CurryR`](./Functional/CurryR.md)
* [`DelayedEval`](./Functional/DelayedEval.md)
* [`F`](./Functional/F.md)
* [`Identity`](./Functional/Identity.md)
* [`Invoke`](./Functional/Invoke.md)
* [`InvokeWith`](./Functional/InvokeWith.md)
* [`Map`](./Functional/Map.md)
* [`Partial`](./Functional/Partial.md)
* [`PartialR`](./Functional/PartialR.md)
* [`Product`](./Functional/Product.md)
* [`ProductMap`](./Functional/ProductMap.md)
* [`ToList`](./Functional/ToList.md)
* [`ToValue`](./Functional/ToValue.md)
* [`Unwrap`](./Functional/Unwrap.md)

## `Pack`

Contains *utilities* for manipulating *parameter packs*. You can include any construct separately by `CppML/Pack/<name>.hpp`, or include the entire header `CppML/Pack.hpp`.

* [`Append`](./Pack/Append.md)
* [`Drop`](./Pack/Drop.md)
* [`Front`](./Pack/Front.md)
* [`Get`](./Pack/Get.md)
* [`Head`](./Pack/Head.md)
* [`Insert`](./Pack/Insert.md)
* [`Length`](./Pack/Length.md)
* [`Concat`](./Pack/Concat.md)
* [`PackExtractor`](./Pack/PackExtractor.md)
* [`Prepend`](./Pack/Prepend.md)
* [`Range`](./Pack/Range.md)
* [`Tail`](./Pack/Tail.md)

## `TypeTraits`

Contains metafunctions that *reason* about the input *types*. You can include any construct separately by `CppML/TypeTraits/<name>.hpp`, or include the entire header `CppML/TypeTraits.hpp`.

* [`AligmentOf`](./TypeTraits/AligmentOf.md)
* [`CopyRefness`](./TypeTraits/CopyRefness.md)
* [`IsClass`](./TypeTraits/IsClass.md)
* [`IsConstructible`](./TypeTraits/IsConstructible.md)
* [`IsConvertible`](./TypeTraits/IsConvertible.md)
* [`IsSame`](./TypeTraits/IsSame.md)
* [`IsSameTemplate`](./TypeTraits/IsSameTemplate.md)
* [`IsValid`](./TypeTraits/IsValid.md)
* [`VoidTT`](./TypeTraits/VoidTT.md)

## `Vocabulary`

Contains the *vocabulary* constructs of **CppML**. You can include any construct separately by `CppML/Vocabulary/<name>.hpp`, or include the entire header `CppML/Vocabulary.hpp`.

* [`Any`](./Vocabulary/Any.md)
* [`Value`](./Vocabulary/Value.md)
* [`List`](./Vocabulary/List.md)
* [`None`](./Vocabulary/None.md)
