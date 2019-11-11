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

* [`AllOf`](./Algorithm/AllOf.md)
* [`AnyOf`](./Algorithm/AnyOf.md)
* [`Contains`](./Algorithm/Contains.md)
* [`CountIf`](./Algorithm/CountIf.md)
* [`Filter`](./Algorithm/Filter.md)
* [`FilterIds`](./Algorithm/FilterIds.md)
* [`FindIf`](./Algorithm/FindIf.md)
* [`FindIfNot`](./Algorithm/FindIfNot.md)
* [`GroupBy`](./Algorithm/GroupBy.md)
* [`GroupIdsBy`](./Algorithm/GroupIdsBy.md)
* [`MaxElement`](./Algorithm/MaxElement.md)
* [`NoneOf`](./Algorithm/NoneOf.md)
* [`Partition`](./Algorithm/Partition.md)
* [`PartitionIds`](./Algorithm/PartitionIds.md)
* [`Pivot`](./Algorithm/Pivot.md)
* [`Reduce`](./Algorithm/Reduce.md)
* [`RemoveIdsIf`](./Algorithm/RemoveIdsIf.md)
* [`RemoveIf`](./Algorithm/RemoveIf.md)
* [`ReplaceIf`](./Algorithm/ReplaceIf.md)
* [`Rotate`](./Algorithm/Rotate.md)
* [`Sort`](./Algorithm/Sort.md)
* [`UniqueCompare`](./Algorithm/UniqueCompare.md)
* [`Unique`](./Algorithm/Unique.md)
* [`ZipWith`](./Algorithm/ZipWith.md)
* [`ZipWithVariadic`](./Algorithm/ZipWithVariadic.md)

## `Arithmetic`

Contains *arithmetic operations* that operate on *types* (e. g. `Not`, `Less`). You can include any operation separately by `CppML/Arithmetic/<name>.hpp`, or include the entire header `CppML/Arithmetic.hpp`.

* [`Add`](./Arithmetic/Add.md)
* [`Decrement`](./Arithmetic/Decrement.md)
* [`Equals`](./Arithmetic/Equals.md)
* [`Greater`](./Arithmetic/Greater.md)
* [`Increment`](./Arithmetic/Increment.md)
* [`Less`](./Arithmetic/Less.md)
* [`Not`](./Arithmetic/Not.md)
* [`Subtract`](./Arithmetic/Subtract.md)

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
