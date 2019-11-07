# CppML API Reference

#### Headers

* [`Algorithm`](#algorithm)
  * *algorithms* that operate on *parameter packs*
* [`Arithmetic`](#arithmetic)
  * *arithmetic* operations on *types*
* [`Functional`](#functional)
  * *functional* utilities (e.g. [`Curry`](./Functional/Curry.md), [`Map`](./Functional/Map.md), [`ProductMap`](./Functional/ProductMap.md), etc.)
* [`Pack`](#pack)
  * manipulation of *parameter packs*
* [`TypeTraits`](#typetraits)
  * metafunctions that *reason* about the input *types*
* [`Vocabulary`](#vocabulary)
  * *vocabulary* constructs of **CppML**

## `Algorithm`

Contains *algorithms* that operate on *parameter packs*. You can include any algorithm separately by `CppML/Algorithm/<name>.hpp`, or include the entire header `CppML/Algorithm.hpp`.

* [`AllOf`](Algorithm/AllOf.md)
* [`AnyOf`](Algorithm/AnyOf.md)
* [`Contains`](Algorithm/Contains.md)
* [`CountIf`](Algorithm/CountIf.md)
* [`Filter`](Algorithm/Filter.md)
* [`FilterIds`](Algorithm/FilterIds.md)
* [`FindIf`](Algorithm/FindIf.md)
* [`FindIfNot`](Algorithm/FindIfNot.md)
* [`GroupBy`](Algorithm/GroupBy.md)
* [`GroupIdsBy`](Algorithm/GroupIdsBy.md)
* [`MaxElement`](Algorithm/MaxElement.md)
* [`NoneOf`](Algorithm/NoneOf.md)
* [`Partition`](Algorithm/Partition.md)
* [`PartitionIds`](Algorithm/PartitionIds.md)
* [`Pivot`](Algorithm/Pivot.md)
* [`Reduce`](Algorithm/Reduce.md)
* [`RemoveIdsIf`](Algorithm/RemoveIdsIf.md)
* [`RemoveIf`](Algorithm/RemoveIf.md)
* [`ReplaceIf`](Algorithm/ReplaceIf.md)
* [`Rotate`](Algorithm/Rotate.md)
* [`Sort`](Algorithm/Sort.md)
* [`UniqueCompare`](Algorithm/UniqueCompare.md)
* [`Unique`](Algorithm/Unique.md)
* [`ZipWith`](Algorithm/ZipWith.md)
* [`ZipWithVariadic`](Algorithm/ZipWithVariadic.md)

## `Arithmetic`

Contains *arithmetic operations* that operate on *types* (e. g. `Not`, `Less`). You can include any operation separately by `CppML/Arithmetic/<name>.hpp`, or include the entire header `CppML/Arithmetic.hpp`.

* [`Add`](Arithmetic/Add.md)
* [`Decrement`](Arithmetic/Decrement.md)
* [`Equals`](Arithmetic/Equals.md)
* [`Greater`](Arithmetic/Greater.md)
* [`Increment`](Arithmetic/Increment.md)
* [`Less`](Arithmetic/Less.md)
* [`Not`](Arithmetic/Not.md)
* [`Subtract`](Arithmetic/Subtract.md)

## `Functional`

Contains *functional* utilities (e.g. `Map`). You can include any construct separately by `CppML/Functional/<name>.hpp`, or include the entire header `CppML/Functional.hpp`.

* [`Bind`](Functional/Bind.md)
* [`Compose`](Functional/Compose.md)
* [`Constant`](Functional/Constant.md)
* [`Curry`](Functional/Curry.md)
* [`CurryR`](Functional/CurryR.md)
* [`DelayedEval`](Functional/DelayedEval.md)
* [`F`](Functional/F.md)
* [`Identity`](Functional/Identity.md)
* [`Invoke`](Functional/Invoke.md)
* [`InvokeWith`](Functional/InvokeWith.md)
* [`Map`](Functional/Map.md)
* [`Partial`](Functional/Partial.md)
* [`PartialR`](Functional/PartialR.md)
* [`Product`](Functional/Product.md)
* [`ProductMap`](Functional/ProductMap.md)
* [`ToList`](Functional/ToList.md)
* [`ToValue`](Functional/ToValue.md)
* [`Unwrap`](Functional/Unwrap.md)

## `Pack`

Contains *utilities* for manipulating *parameter packs*. You can include any construct separately by `CppML/Pack/<name>.hpp`, or include the entire header `CppML/Pack.hpp`.

* [`Append`](Pack/Append.md)
* [`Drop`](Pack/Drop.md)
* [`Front`](Pack/Front.md)
* [`Get`](Pack/Get.md)
* [`Head`](Pack/Head.md)
* [`Insert`](Pack/Insert.md)
* [`Length`](Pack/Length.md)
* [`Concat`](Pack/Concat.md)
* [`PackExtractor`](Pack/PackExtractor.md)
* [`Prepend`](Pack/Prepend.md)
* [`Range`](Pack/Range.md)
* [`Tail`](Pack/Tail.md)

## `TypeTraits`

Contains metafunctions that *reason* about the input *types*. You can include any construct separately by `CppML/TypeTraits/<name>.hpp`, or include the entire header `CppML/TypeTraits.hpp`.

* [`AligmentOf`](TypeTraits/AligmentOf.md)
* [`CopyRefness`](TypeTraits/CopyRefness.md)
* [`IsClass`](TypeTraits/IsClass.md)
* [`IsConstructible`](TypeTraits/IsConstructible.md)
* [`IsConvertible`](TypeTraits/IsConvertible.md)
* [`IsSame`](TypeTraits/IsSame.md)
* [`IsSameTemplate`](TypeTraits/IsSameTemplate.md)
* [`IsValid`](TypeTraits/IsValid.md)
* [`VoidTT`](TypeTraits/VoidTT.md)

## `Vocabulary`

Contains the *vocabulary* constructs of **CppML**. You can include any construct separately by `CppML/Vocabulary/<name>.hpp`, or include the entire header `CppML/Vocabulary.hpp`.

* [`Value`](Vocabulary/Value.md)
* [`IfElse`](Vocabulary/IfElse.md)
* [`List`](Vocabulary/List.md)
* [`None`](Vocabulary/None.md)
* [`Wildcard`](Vocabulary/Wildcard.md)
