# Mamba standard library (MSL)

## 1. Built-ins

### 1.1. Types

Mamba aims to support all Python types possible, but with compile-time type
limitations. This means that collections like `dict` and `set` can only hold
elements of the same type (though these elements can be polymorphic through
inheritance).

Mamba also explicitly limits numeric types to a certain bit width, adding
additional types to fill the gaps created in this way. For example, Python's
`int` is variable-width, but in Mamba, it is 32-bit, with `bigint` being
introduced to cover 64-bit use cases. No support for 128-bit integers is
planned at the moment.

Python's `None` type is relegated to be the "null" value for Mamba's
`Optional[T]` type, which wraps any type `T` in the same way that C++'s
`std::optional<T>` does. This also means that any type by default cannot be
assigned `None` directly, and corresponding variables must be instantiated at
their declaration if there is no default value (or default constructor).

Tuples can still store data of varying types, but they are internally wrapped
in a C++ `std::any` and must be explicitly cast to the expected type.

| Mamba | Python 3 analog | C++20 interop | Supported | Notes |
| --- | --- | --- | --- | --- |
| `bigint` | `int` | `std::int_least64_t` | Yes | 64-bit signed integer |
| `bool` | `bool` | `bool` | Yes | - |
| `byte` | `int` | - | Not yet | 8-bit unsigned integer |
| `bytearray` | `bytearray` | - | Not yet | - |
| `bytes` | `bytes` | - | Not yet | - |
| `complex` | `complex` | - | Partial | - |
| `dict[K, V]` | `dict[K, V]` | - | Not yet | Specifically `collections.OrderedDict[K, V]` |
| `double` | `float` | `std::float64_t` | Yes | 64-bit float |
| `float` | `float` | `std::float32_t` | Yes | 32-bit float |
| `frozenset[T]` | `frozenset[T]` | - | Partial | - |
| `int` | `int` | `std::int_least32_t` | Yes | 32-bit signed integer |
| `list[T]` | `list[T]` | Convertible to `std::vector<T>` | Yes | - |
| `None` | `None` | Bidi-convertible with `std::nullopt_t` | Yes | - |
| `object` | `object` | N/A | Yes | Abstract base class of all non-value types |
| `Optional[T]` | `Optional[T]` | `std::optional<T>` | Not yet | - |
| `set[T]` | `set[T]` | - | Partial | - |
| `str` | `str` | Bidi-convertible with `std::string` | Partial | Underlyingly always UTF-16 |
| `tuple[...]` | `tuple[...]` | - | Not yet | - |

#### 1.1.1. Values and non-values (objects)

With the exception of the `None` type, the built-in types are divided into
value and non-value (object) types.

| Type | Type category | Notes |
| --- | --- | --- |
| `bigint` | Value | - |
| `bool` | Value | - |
| `bytearray` | Object | - |
| `bytes` | Value | - |
| `complex` | Value | - |
| `dict[K, V]` | Object | - |
| `double` | Value | - |
| `float` | Value | - |
| `frozenset[T]` | Object | - |
| `list[T]` | Object | - |
| `None` | N/A | - |
| `object` | Object | - |
| `Optional[T]` | N/A | - |
| `set[T]` | Object | - |
| `str` | Value | - |
| `tuple[...]` | Value | - |

Value types are internally passed by value (copy), whereas non-value (object)
types are passed by reference (technically lvalue references over
a `std::shared_ptr` to internal data).

The `None` type does not fit into either of these paradigms and only exists to
mean the absence of a payload of type `T` in an `Optional[T]`.

### 1.2. Functions

| Mamba | Python 3 analog | Supported | Notes |
| --- | --- | --- | --- |
| `bool(Any) -> bool` | `bool(Any)` | Yes | - |
| `iter(Iterable[T]) -> Iterable[T]` | `iter(Iterable[T])` | Yes | - |
| `len(Iterable[T]) -> int` | `len(Iterable[T])` | Yes | - |
| `next(Iterator[T]) -> T` | `next(Iterator[T])` | Yes | - |
| `print(...)` | `print(...)` | Not yet | - |
| `repr(Any) -> str` | `repr(Any)` | Yes | - |
| `str(Any) -> str` | `str(Any)` | Yes | - |

### 1.3. Dunder methods

| Mamba | Python 3 analog | Supported | Notes |
| --- | --- | --- | --- |
| `__bool__() -> bool` | `__bool__()` | Yes | - |
| `__contains__() -> bool` | `__contains__()` | Yes | - |
| `__id__() -> bigint` | `__id__()` | Yes | - |
| `__int__() -> int` | `__int__()` | Yes | - |
| `__iter__() -> Iterator[T]` | `__iter__()` | Yes | - |
| `__len__() -> int` | `__len__()` | Yes | - |
| `__next__() -> T` | `__next__()` | Yes | - |
| `__repr__() -> str` | `__repr__()` | Yes | - |
| `__str__() -> str` | `__str__()` | Yes | - |

### 1.4. Operators

| Mamba | Python 3 analog | Supported | Notes |
| --- | --- | --- | --- |
| `x in y` | `x in y` | Yes | Calls `x.__contains__(y)` |
| `x is y` | `x is y` | Yes | Calls `x.__id__() == y.__id__()` |
| `x == y` | `x == y` | Yes | Calls `x.__eq__(y)` |
| `x != y` | `x != y` | Yes | Calls `x.__ne__(y)` or `not x.__eq__(y)`, whichever is available first |

### 1.5. Important base classes and traits

There are no formal traits in Mamba, but they are expressed in the API as if
they existed. (Internally, they are C++20 concepts). Where possible, these
traits are actually special subclasses of the `object` type, and serve as the
base class of other types, e.g. `Iterator[T]` is the base class of all iterator
types like `ListIterator[T]`.
