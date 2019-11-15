# `CppML` Reference

The constructs of `CppML` are divided in into several smaller libraries, which are described below:

| Library                     | Description                                                                                                              |
|-----------------------------|--------------------------------------------------------------------------------------------------------------------------|
| [`Algorithm`](#algorithm)   | Algorithms over parameter packs (e.g. [`Sort`](./Algorithm/Sort.md), [`ZipWith`](./Algorithm/ZipWith.md), etc.)          |
| [`Arithmetic`](#arithmetic) | Arithmetic operations on type-values (e.g. [`Greater`](./Arithmetic/Greater.md), [`Not`](./Arithmetic/Not.md), etc.) |
| [`Functional`](#functional) | Manipulation of metafunctions (e.g. [`Curry`](./Functional/Curry.md), [`Map`](./Functional/Map.md), etc.)                |
| [`Pack`](#pack)             | Manipulation of parameter packs (e.g. [`Drop`](./Pack/Drop.md), [`Get`](./Pack/Get.md), etc.)                            |
| [`TypeTraits`](#typetraits) | Insights into types (e.g. [`IsSame`](./TypeTraits/IsSame.md), [`IsClass`](./TypeTraits/IsClass.md), etc.)                |
| [`Vocabulary`](#vocabulary) | Vocabulary types of `CppML`   (e.g. [`ListT`](./Vocabulary/ListT.md), [`Value`](./Vocabulary/Value.md), etc.)            |



### Structure

CppML is structured as follows:
* each library has an associated header `.hpp` and a directory of the same name in the `CppML/` directory. For example, the `Algorithm` library has an `Algorithm.hpp` header located in the `include/CppML`
* every component of each library has a dedicated `.hpp` header inside the libraries associated directory. For example, `Sort`, a component of the `Algorithm` library, has a header located at `include/CppML/Algorithm/Sort.hpp`.

Thus, to use any component, you can either include its specific header (e.g. `#include <CppML/Algorithm/Sort.hpp>`), or include its libraries header `#include <CppML/Algorithm.hpp>`. Note that you may include all libraries at once using `#include <CppML/CppML.hpp>`.



## `Algorithm`

Find the algorithm of your interest in the table below. Each of them has it own `reference page`, where you can find a *specification of its structure*, a definition of its *metafunction type*, and an *example of use*.


| Construct                                           | Description                                                      | Type of `f` in `::f >-> Pipe`   |
|-----------------------------------------------------|------------------------------------------------------------------|---------------------------------|
| [`AllOf`](./Algorithm/AllOf.md)                     | Checks if a `Predicate` holds for all of `Ts...`.                | `Ts... -> Bool<t>`              |
| [`AnyOf`](./Algorithm/AnyOf.md)                     | Checks if a `Predicate` holds for any of `Ts...`.                | `Ts... -> Bool<t>`              |
| [`Contains`](./Algorithm/Contains.md)               | Checks if `Ts...` contains `T`.                                  | `Ts... -> Bool<t>`              |
| [`CountIf`](./Algorithm/CountIf.md)                 | Counts `Ts...` for which the `Predicate` holds.                  | `Ts... -> Bool<t>`              |
| [`Filter`](./Algorithm/Filter.md)                   | Filters `Ts...`, for which the `Predicate` holds.                | `Ts... -> Us...`                |
| [`FilterIds`](./Algorithm/FilterIds.md)             | Filters indexes of `Ts...`, for which the `Predicate` holds.     | `Ts... -> Int<Is>...`           |
| [`FindIf`](./Algorithm/FindIf.md)                   | Index of `Ts...` for which the `Predicate` holds.                | `Ts... -> Int<I>`               |
| [`FindIfNot`](./Algorithm/FindIfNot.md)             | Index of `Ts...` for which the `Predicate` does not hold.        | `Ts... -> Int<I>`               |
| [`GroupBy`](./Algorithm/GroupBy.md)                 | Groups `Ts...`, given their image under `By`.                    | `Ts... -> ListT<Us...>...`      |
| [`GroupIdsBy`](./Algorithm/GroupIdsBy.md)           | Groups indexes of `Ts...`, given their (`T`'s) image under `By`. | `Ts... -> ListT<Int<Is>...>...` |
| [`InclusiveScan`](./Algorithm/InclusiveScan.md)     | Inclusive scan under the binary `F`.                             | `Ts... -> T0, F(T0, T1), ...`   |
| [`MaxElement`](./Algorithm/MaxElement.md)           | Get maximal element, given a `Comparator`.                       | `Ts... -> U`                    |
| [`NoneOf`](./Algorithm/NoneOf.md)                   | Checks if a `Predicate` holds for none of `Ts...`.               | `Ts... -> Bool<t>`              |
| [`Partition`](./Algorithm/Partition.md)             | Partitions `Ts...` given a `Predicate`.                          | `Ts... -> ListT<Us...>...`      |
| [`PartitionIds`](./Algorithm/PartitionIds.md)       | Partitions indexes of `Ts...` given a `Predicate`.               | `Ts... -> ListT<Int<Is>...>...` |
| [`Pivot`](./Algorithm/Pivot.md)                     | Pivots `Ts...` around the `N`-th element, making it the first.   | `Ts... -> Us...`                |
| [`Reduce`](./Algorithm/Reduce.md)                   | Reduce `Ts...`, given an accumulator `F`.                        | `Init, Ts... -> U`              |
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

Find the construct of your interest in the table below. Each of them has it own `reference page`, where you can find a *specification of its structure*, a definition of its *metafunction type*, and an *example of use*.

| Construct                                | Description                  | Type of `f` in `::f >-> Pipe`                 |
|------------------------------------------|------------------------------|-----------------------------------------------|
| [`Add`](./Arithmetic/Add.md)             | Adds two `Value`s.           | `Value<T, t>, Value<U, u> -> Value<V, t + u>` |
| [`Decrement`](./Arithmetic/Decrement.md) | Decrements a `Value`         | `Value<t, T> -> Value<--t, T>`                |
| [`Equals`](./Arithmetic/Equals.md)       | Equality check for `Values`. | `Value<T, t>, Value<U, u> -> Bool<t>`         |
| [`Greater`](./Arithmetic/Greater.md)     | Greater for `Values`.        | `Value<T, t>, Value<U, u> -> Bool<t>`         |
| [`Increment`](./Arithmetic/Increment.md) | Increments a `Value`.        | `Value<t, T> -> Value<++t, T>`                |
| [`Less`](./Arithmetic/Less.md)           | Less for `Values`.           | `Value<T, t>, Value<U, u> -> Bool<t>`         |
| [`Not`](./Arithmetic/Not.md)             | Negates a `Value`.           | `Bool<t> -> Bool< not t>`                     |
| [`Subtract`](./Arithmetic/Subtract.md)   | Subtracts two `Value`s.      | `Value<T, t>, Value<U, u> -> Value<V, t + u>` |

## `Functional`

Contains *functional* utilities (e.g. `Map`). You can include any construct separately by `CppML/Functional/<name>.hpp`, or include the entire header `CppML/Functional.hpp`.

Find the construct of your interest in the table below. Each of them has it own `reference page`, where you can find a *specification of its structure*, a definition of its *metafunction type*, and an *example of use*.

| Construct                                    | Description                                          | Type of `f` in `::f >-> Pipe`  |
|----------------------------------------------|------------------------------------------------------|--------------------------------|
| [`Bind`](./Functional/Bind.md)               | Metafunction with args bound to specific positions.  | `Ts... -> Us...`               |
| [`BranchPipe`](./Functional/BranchPipe.md)   | Branches to one of two `Pipes`, given a `Predicate`. | `Ts... -> Ts...`               |
| [`Compose`](./Functional/Compose.md)         | Composition of metafunctions `Fs...`.                | `Ts... -> F0(F1(...(Fn(Us...)` |
| [`Constant`](./Functional/Constant.md)       | Metafunction that always returns `U`.                | `Ts... -> U`                   |
| [`Curry`](./Functional/Curry.md)             | The Curry (from the left) operator                   | `T0s... -> T1s... -> Us...`    |
| [`CurryR`](./Functional/CurryR.md)           | The Curry (from the right) operator                  | `T1s... -> T0s... -> Us...`    |
| [`DelayedEval`](./Functional/DelayedEval.md) | Delays an evaluation until compiler knows the arity. | `Ts... -> Us...`               |
| [`f`](./Functional/Invoke.md)                | Invokes the `f` alias of the metafunction `F`        | `Ts... -> F::f<Ts...>`         |
| [`F`](./Functional/F.md)                     | Lifts a template to a metafunction                   | `Ts... -> Template<Ts...>`     |
| [`Identity`](./Functional/Identity.md)       | Identity metafunction.                               | `T -> T`                       |
| [`IfElse`](./Functional/IfElse.md)           | Chooses between `T` and `U`.                         | `T, U -> V`                    |
| [`InvokeWith`](./Functional/InvokeWith.md)   | Invokes the metafunction on `Ts...`                  | `Ts... -> Us... -> Us...`      |
| [`Map`](./Functional/Map.md)                 | Maps `Ts...` by `F`.                                 | `Ts... -> F(Ts)...`            |
| [`Partial`](./Functional/Partial.md)         | Partial evaluation of `F` on `T0s...` from the left  | `T1... -> F(T0..., T1...)`     |
| [`PartialR`](./Functional/PartialR.md)       | Partial Evaluation of `F` on `T1s...` from the right | `T0... -> F(T0..., T1...)`     |
| [`Product`](./Functional/Product.md)         | Product of metafunctions `Fs...`                     | `Ts... -> Fs(Ts...)...`        |
| [`ProductMap`](./Functional/ProductMap.md)   | Product map of metafunctions `Fs`                    | `Ts... -> Fs(Ts)...`           |
| [`ToList`](./Functional/ToList.md)           | Wraps `Ts...` in an `ListT`                          | `Ts... -> ListT<Ts...>`        |
| [`ToValue`](./Functional/ToValue.md)         | Invokes `::value` on `Ts...`                         | `Value<Ts, ts>... -> ts...`    |
| [`Unwrap`](./Functional/Unwrap.md)           | Unwraps the template around `Ts...`                  | `Template<Ts...> -> Ts...`     |

## `Pack`

Contains *utilities* for manipulating *parameter packs*. You can include any construct separately by `CppML/Pack/<name>.hpp`, or include the entire header `CppML/Pack.hpp`.

Find the construct of your interest in the table below. Each of them has it own `reference page`, where you can find a *specification of its structure*, a definition of its *metafunction type*, and an *example of use*.

| Construct                                  | Description                              | Type of `f` in `::f >-> Pipe`                     |
|--------------------------------------------|------------------------------------------|---------------------------------------------------|
| [`Drop`](./Pack/Drop.md)                   | Drops first `N` of `Ts...`               | `T1, ... Tn, Ts... -> Ts...`                      |
| [`Front`](./Pack/Front.md)                 | Gets first element of `Ts...`            | `T, Ts... -> T`                                   |
| [`Get`](./Pack/Get.md)                     | Gets `N`-th element of `Ts...`           | `T1, ... Tn, Ts... -> Tn`                         |
| [`Head`](./Pack/Head.md)                   | First `N` of `Ts...`                     | `T1, ... Tn, Ts... -> T1, ... Tn`                 |
| [`Insert`](./Pack/Insert.md)               | Inserts `U` as `N`-th element of `Ts...` | `T1, ... Tn, Ts... -> T1, ... U, Tn, Ts... `      |
| [`Length`](./Pack/Length.md)               | Length of `Ts...`                        | `Ts... -> Int<sizeof...(Ts)`                      |
| [`Concat`](./Pack/Concat.md)               | Concatenates `N` templates `T`           | `T<A0s...>... -> T<A0s..., A1s..., Ans...>`       |
| [`PackExtractor`](./Pack/PackExtractor.md) | Extracts `N`-th element.                 | `Int<N> -> T`                                     |
| [`Prepend`](./Pack/Prepend.md)             | Prepends `T` to `Ts...`                  | `Ts... -> T, Ts...`                               |
| [`Range`](./Pack/Range.md)                 | Pack of `Int<I>` in range                | `From, To -> Int<From>..., Int<To - 1>`           |
| [`Tail`](./Pack/Tail.md)                   | Last `N` of `Ts...`                      | `Ts..., T_{-N}, ... T_{-1} -> T_{-N}, ... T_{-1}` |

## `TypeTraits`

Contains metafunctions that *reason* about the input *types*. You can include any construct separately by `CppML/TypeTraits/<name>.hpp`, or include the entire header `CppML/TypeTraits.hpp`.

| Construct                                            | Description                                               | Type of `f` in `::f >-> Pipe`   |
|------------------------------------------------------|-----------------------------------------------------------|---------------------------------|
| [`AlignOf`](./TypeTraits/AligmentOf.md)           | Get alignment of `T`                                      | `T -> Int<alignof(T)>`          |
| [`IsClass`](./TypeTraits/IsClass.md)                 | Checks if `T` is a class type                             | `T -> Bool<t>`                  |
| [`IsConstructible`](./TypeTraits/IsConstructible.md) | Checks if `T` is constructable from `Ts...`               | `T, Ts... -> Bool<t>`           |
| [`IsConvertible`](./TypeTraits/IsConvertible.md)     | Checks if `T` is convertible to `U`                       | `T, U -> Bool<t>`               |
| [`IsSame`](./TypeTraits/IsSame.md)                   | Checks if `T` and `U` are the same type                   | `T, U -> Bool<t>`               |
| [`IsSameTemplate`](./TypeTraits/IsSameTemplate.md)   | Checks if `T<Ts...>` and `U<Us...>` are the same template | `T<Ts...>, U<Us...> -> Bool<t>` |
| [`IfValidOr`](./TypeTraits/IsValid.md)               | `F::f<Ts...>` if it is not ill-formed, else `U`           | `U, F, Ts... -> V`              |
| [`IsValid`](./TypeTraits/IsValid.md)                 | Check if `F` invoked on `Ts...` is not ill-formed         | `F, Ts... -> Bool<t>`           |

## `Vocabulary`

Contains the *vocabulary* constructs of **CppML**. You can include any construct separately by `CppML/Vocabulary/<name>.hpp`, or include the entire header `CppML/Vocabulary.hpp`.

Find the construct of your interest in the table below. Each of them has it own `reference page`, where you can find a *specification of its structure*, a definition of its *metafunction type*, and an *example of use*.

| Construct                        | Description                 |
|----------------------------------|-----------------------------|
| [`Value`](./Vocabulary/Value.md) | Represents a type-value     |
| [`List`](./Vocabulary/List.md)   | Represents a list of types  |
| [`None`](./Vocabulary/None.md)   | Represents the nothing type |
