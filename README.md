# mamba

Mamba is a transpiler for a statically-typed subset of Python 3 to C++20.

This is mainly an educational project to explore what challenges there are in
implementing a programming language. I don't currently have plans to complete
anything besides a statically-typed subset of the Python builtins.

Check the C++ and Python tests for status on the implementation and what
works and what doesn't.

## Design

This project consists of two parts:
* A C++ transpilation target for a statically-typed subset of Python. This aims
to provide a nearly 1-to-1 equivalent of many Python's built-in symbols, so
that a transpiler can easily translate those Python symbols as trivially as
possible.
* A Python-based transpiler to transpile a statically-typed subset of Python
to C++.

## Requirements
* C++20*
* clang-format
* include-what-you-use
* [Google Test](https://github.com/google/googletest)
* [Chiri](https://github.com/antonsynd/chiri)
* CMake 3.14+
* Python 3.8+

*My local development is on macOS with `clang`. I might test `g++` later on,
but right now, for best results, use `clang`.

## How to build and run tests

```sh
chiri pkg release
```

## Statically-typed subset of Python

| Feature | Supported? | Notes |
| --- | --- | --- |
| `dict[K, V]` | TODO | All keys must be of the same type `K` and all values must be of type `V` |
| `float` | `Yes` | N/A |
| `int` | `Yes` | N/A |
| `list[T]` | `Yes` | All elements must be of the same type `T` |
| `set[T]` | TODO | All elements must be of the same type `T` |
| `str` | TODO | N/A |
| `tuple[...]` | TODO | N/A |
