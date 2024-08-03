# mamba

This project consists of two parts:
* A C++ transpilation target for a statically-typed subset of Python. This aims
to provide a nearly 1-to-1 equivalent of many Python's built-in symbols, so
that a transpiler can easily translate those Python symbols as trivially as
possible.
* A Python-based transpiler to transpile a statically-typed subset of Python
to C++.

Requires C++20.
