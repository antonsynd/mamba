# Mamba Draft

## Types

| Mamba type | Mamba alias | Python type | C/C++ type |
| --- | --- | --- | --- |
| `byte` | - | - | `byte` |
| `sbyte` | - | - | `signed byte` |
| `int` | - | `int` | `long int` |
| `uint` | - | - | `unsigned long int` |
| `float` | - | `float` | `double` |
| `str` | - | `str` | `std::string` |
| `list[T]` | `[T]` | `list[T]` | `T[]` |
| `list[T]` | `[T]` | `list[T]` | `std::vector<T>` |
| `tuple[A, B, C, ...]` | `(A, B, C, ...)` | `tuple[A, B, C, ...]` | `std::tuple<A, B, C, ...>` |
| `list[byte]` | - | `bytearray` | `byte[]` |
| `frozen list[byte]` | - | `bytes` | `const byte[]` |
| `dict[K, V]` | `{K: V}` | `dict[K, V]` | `std::unordered_map<K, V>` |
| `set[T]` | `{T}` | `set[T]` | `std::unordered_set<T>` |
| `frozen set[T]` | - | `frozenset[T]` | `const std::unordered_set<T>` |
| `Optional[T]` | `T?` | `Optional[T]` | `std::optional<T>` |
| `Function[R, A, B, C, ...]` | `(A, B, C, ...) -> R` | - | `std::function<R(A, B, C, ...)>` |
| `Reference[T]` | `T&` | - | `T&` |

## Operators

| Mamba operator | Mamba alias | Python operator | C/C++ operator | Notes |
| --- | --- | --- | --- | --- |
| `ref(value)` | - | - | lvalue reference `value` | If `value` is immutable |
| `value` | - | - | lvalue reference `value` | If `value` is mutable |
| `value` | `` | - | copy `value` | If `value` is immutable |
| `copy(value)` | - | - | copy `value` | If `value` is mutable |
