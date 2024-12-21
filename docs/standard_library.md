# Mamba standard library (MSL)

## 1. Built-ins

### 1.1. Types

| Mamba | Python 3 analog | C++20 interop | Supported | Notes |
| --- | --- | --- | --- | --- |
| `bigint` | `int` | `std::int_least64_t` | Yes | 64-bit integer |
| `bool` | `bool` | `bool` | Yes | - |
| `bytearray` | `bytearray` | - | Not yet | - |
| `bytes` | `bytes` | - | Not yet | - |
| `complex` | `complex` | - | Partial | - |
| `dict[K, V]` | `dict[K, V]` | - | Not yet | Specifically `collections.OrderedDict[K, V]` |
| `double` | `float` | `std::float64_t` | Yes | 64-bit float |
| `float` | `float` | `std::float32_t` | Yes | 32-bit float |
| `frozenset[T]` | `frozenset[T]` | - | Partial | - |
| `int` | `int` | `std::int_least32_t` | Yes | 32-bit integer |
| `list[T]` | `list[T]` | Convertible to `std::vector<T>` | Yes | - |
| `None` | `None` | Bidi-convertible with `std::nullopt_t` | Yes | - |
| `object` | `object` | N/A | Yes | Abstract base class of all non-value types |
| `Optional[T]` | `Optional[T]` | `std::optional<T>` | Not yet | - |
| `set[T]` | `set[T]` | - | Partial | - |
| `str` | `str` | Bidi-convertible with `std::string` | Partial | - |
| `tuple[...]` | `tuple[...]` | - | Not yet | - |

#### 1.1.1. Values and non-values (objects)

With the exception of the `None` type, the built-in types are divided into value and non-value (object) types.

Value types:
* `bigint`
* `bool`
* `bytes`
* `complex`
* `double`
* `float`
* `int`
* `str`
* `tuple`

Non-value (object) types:
* `bytearray`
* `dict`
* `list`
* `frozenset`
* `object`
* `set`

Value types are internally passed by value (copy), whereas non-value (object) types are passed by reference (technically lvalue references over a `std::shared_ptr` to internal data).

The `None` type does not fit into either of these paradigms and only exists to mean the absence of a payload of type `T` in an `Optional[T]`.

### 1.2. Functions

| Mamba | Python 3 analog | Supported | Notes |
| --- | --- | --- | --- |
| `bool(v)` | `bool(v)` | Yes | - |
| `iter(iterable)` | `iter(iterable)` | Yes | - |
| `len(iterable)` | `len(iterable)` | Yes | - |
| `next(iterator)` | `next(iterator)` | Yes | - |
| `print(...)` | `print(...)` | Not yet | - |
| `repr(v)` | `repr(v)` | Yes | - |
| `str(v)` | `str(v)` | Yes | - |

### 1.3. Dunder methods

| Mamba | Python 3 analog | Supported | Notes |
| --- | --- | --- | --- |
| `__bool__()` | `__bool__()` | Yes | - |
| `__int__()` | `__int__()` | Yes | - |
| `__iter__()` | `__iter__()` | Yes | - |
| `__len__()` | `__len__()` | Yes | - |
| `__next__()` | `__next__()` | Yes | - |
| `__repr__()` | `__repr__()` | Yes | - |
| `__str__()` | `__str__()` | Yes | - |
