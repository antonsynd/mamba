# mamba

Mamba is an educational project exploring a transpilation target for
[Sidewinder](https://github.com/antonsynd/sidewinder), a statically-typed
Pythonic language, to C++20.

Check the `cpp/test` subdirectory for status on the implementation.

## Design

This provides a C++ transpilation target for a statically-typed Pythonic
language called [Sidewinder](https://github.com/antonsynd/sidewinder). This
aims to provide a nearly 1-to-1 equivalent of the built-in symbols in
Sidewinder (which are based on those in Python 3), so that a transpiler can
translate those symbols as trivially as possible.

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
