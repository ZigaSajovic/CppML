# CppML API Reference

#### Headers

* [`Algorithm`](#algorithm)
  * *algorithms* that operate on *parameter packs*
* [`Arithmetic`](#arithmetic)
  * *arithmetic* operations on *types*
* [`Functional`](#functional)
  * *functional* utilities (e.g. `Compose`, `Map`)
* [`Pack`](#pack)
  * manipulation of *parameter packs*
* [`TypeTraits`](#typetraits)
  * metafunctions that *reason* about the input *types*
* [`Vocabulary`](#vocabulary)
  * *vocabulary* constructs of **CppML**

## `Algorithm`

Contains *algorithms* that operate on *parameter packs*. You can include any algorithm separately by `CppML/Algorithm/<name>.hpp`, or include the entire header `CppML/Algorithm.hpp`.

* [`AllOf`](Algorithm/AllOf.hpp)
* [`AnyOf`](Algorithm/AnyOf.hpp)
* [`Contains`](Algorithm/Contains.hpp)
* [`CountIf`](Algorithm/CountIf.hpp)
* [`Filter`](Algorithm/Filter.hpp)
* [`FilterIds`](Algorithm/FilterIds.hpp)
* [`FindIf`](Algorithm/FindIf.hpp)
* [`FindIfNot`](Algorithm/FindIfNot.hpp)
* [`GroupBy`](Algorithm/GroupBy.hpp)
* [`GroupIdsBy`](Algorithm/GroupIdsBy.hpp)
* [`MaxElement`](Algorithm/MaxElement.hpp)
* [`NoneOf`](Algorithm/NoneOf.hpp)
* [`Partition`](Algorithm/Partition.hpp)
* [`Pivot`](Algorithm/Pivot.hpp)
* [`Reduce`](Algorithm/Reduce.hpp)
* [`RemoveIdsIf`](Algorithm/RemoveIdsIf.hpp)
* [`RemoveIf`](Algorithm/RemoveIf.hpp)
* [`ReplaceIf`](Algorithm/ReplaceIf.hpp)
* [`Rotate`](Algorithm/Rotate.hpp)
* [`Sort`](Algorithm/Sort.hpp)
* [`UniqueCompare`](Algorithm/UniqueCompare.hpp)
* [`Unique`](Algorithm/Unique.hpp)
* [`ZipWith`](Algorithm/ZipWith.hpp)
* [`ZipWithVariadic`](Algorithm/ZipWithVariadic.hpp)

## `Arithmetic`

Contains *arithmetic operations* that operate on *types* (e. g. `Not`, `Less`). You can include any operation separately by `CppML/Arithmetic/<name>.hpp`, or include the entire header `CppML/Arithmetic.hpp`.

* [`Equals`](Arithmetic/Equals.hpp)
* [`Greater`](Arithmetic/Greater.hpp)
* [`Less`](Arithmetic/Less.hpp)
* [`Not`](Arithmetic/Not.hpp)

## `Functional`

Contains *functional* utilities (e.g. `Map`). You can include any construct separately by `CppML/Functional/<name>.hpp`, or include the entire header `CppML/Functional.hpp`.

* [`Compose`](Functional/Compose.hpp)
* [`ConstantF`](Functional/ConstantF.hpp)
* [`DelayedEval`](Functional/DelayedEval.hpp)
* [`F`](Functional/F.hpp)
* [`Identity`](Functional/Identity.hpp)
* [`Invoke`](Functional/Invoke.hpp)
* [`InvokeWith`](Functional/InvokeWith.hpp)
* [`Map`](Functional/Map.hpp)
* [`PartialEvaluator`](Functional/PartialEvaluator.hpp)
* [`Partial`](Functional/Partial.hpp)
* [`PipeN`](Functional/PipeN.hpp)
* [`Product`](Functional/Product.hpp)
* [`ProductMap`](Functional/ProductMap.hpp)
* [`ToList`](Functional/ToList.hpp)
* [`ToValue`](Functional/ToValue.hpp)
* [`UnList`](Functional/UnList.hpp)
* [`WrapIn`](Functional/WrapIn.hpp)

## `Pack`

Contains *utilities* for manipulating *parameter packs*. You can include any construct separately by `CppML/Pack/<name>.hpp`, or include the entire header `CppML/Pack.hpp`.

* [`Append`](Pack/Append.hpp)
* [`Drop`](Pack/Drop.hpp)
* [`Front`](Pack/Front.hpp)
* [`Get`](Pack/Get.hpp)
* [`Head`](Pack/Head.hpp)
* [`Insert`](Pack/Insert.hpp)
* [`Length`](Pack/Length.hpp)
* [`Merge`](Pack/Merge.hpp)
* [`PackExtractor`](Pack/PackExtractor.hpp)
* [`Prepend`](Pack/Prepend.hpp)
* [`Range`](Pack/Range.hpp)
* [`Tail`](Pack/Tail.hpp)

## `TypeTraits`

Contains metafunctions that *reason* about the input *types*. You can include any construct separately by `CppML/TypeTraits/<name>.hpp`, or include the entire header `CppML/TypeTraits.hpp`.

* [`AligmentOf`](TypeTraits/AligmentOf.hpp)
* [`CopyRefness`](TypeTraits/CopyRefness.hpp)
* [`IsClass`](TypeTraits/IsClass.hpp)
* [`IsConstructible`](TypeTraits/IsConstructible.hpp)
* [`IsConvertible`](TypeTraits/IsConvertible.hpp)
* [`IsSame`](TypeTraits/IsSame.hpp)
* [`IsSameTemplate`](TypeTraits/IsSameTemplate.hpp)
* [`IsValid`](TypeTraits/IsValid.hpp)
* [`VoidTT`](TypeTraits/VoidTT.hpp)

## `Vocabulary`

Contains the *vocabulary* constructs of **CppML**. You can include any construct separately by `CppML/Vocabulary/<name>.hpp`, or include the entire header `CppML/Vocabulary.hpp`.

* [`Const`](Vocabulary/Const.hpp)
* [`IfElse`](Vocabulary/IfElse.hpp)
* [`List`](Vocabulary/List.hpp)
* [`None`](Vocabulary/None.hpp)
* [`Wildcard`](Vocabulary/Wildcard.hpp)
