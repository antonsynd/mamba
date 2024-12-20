# Mamba standard library (MSL)

## 1. Built-ins

### 1.1. Types

| Mamba | Python 3 analog | C++20 interop | Supported | Notes |
| --- | --- | --- | --- | --- |
| `bigint` | `int` | `std::int_least64_t` | Yes | 64-bit integer |
| `bool` | `bool` | `bool` | Yes | - |
| `bytearray` | `bytearray` | - | Not yet | - |
| `bytes` | `bytes` | - | Not yet | - |
| `dict[K, V]` | `dict[K, V]` | - | Not yet | Specifically `collections.OrderedDict[K, V]` |
| `double` | `float` | `std::float64_t` | Yes | 64-bit float |
| `float` | `float` | `std::float32_t` | Yes | 32-bit float |
| `frozenset[T]` | `frozenset[T]` | - | Partial | - |
| `int` | `int` | `std::int_least32_t` | Yes | 32-bit integer |
| `list[T]` | `list[T]` | Convertible to `std::vector<T>` | Yes | - |
| `None` | `None` | Bidi-convertible with `std::nullopt_t` | Yes | - |
| `set[T]` | `set[T]` | - | Partial | - |
| `str` | `str` | Bidi-convertible with `std::string` | Partial | - |
| `tuple[...]` | `tuple[...]` | - | Not yet | - |
