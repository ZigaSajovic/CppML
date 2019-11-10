# `<CppML/Functional/DelayedEval.hpp>`

#### Table of Contents

* [`DelayedEval`](#delayedeval)
* [`DelayedAliasEval`](#delayedaliaseval)

## `DelayedEval`

```c++
template <typename F, int N, typename ...Ts>
using DelayedEval = /*...*/
};
```
### `DelayedEval<F, N, Ts...>`

`DelayedEval<F, N, Ts...>` is a helper metafunction invoker that combats the *non-varadic parameter pack used as argument for a  varadic parameter pack in alias* compiler error. It happens, for example, when you pass a *parameter pack* to an alias expecting 
```c++
<typename T, typename ...Ts>
```
a type and a parameter pack.

It is not meant to be used outside implementations.

## `DelayedAliasEval`

```c++
template <typename <class...> class F, int N, typename ...Ts>
using DelayedAliasEval = /*...*/
};
```
### `DelayedAliasEval<F, N, Ts...>`

`DelayedEval<F, N, Ts...>` is a helper metafunction invoker that combats the *non-varadic parameter pack used as argument for a  varadic parameter pack in alias* compiler error. It happens, for example, when you pass a *parameter pack* to an alias expecting 
```c++
<typename T, typename ...Ts>
```
a type and a parameter pack.

It is not meant to be used outside implementations.
