#pragma once

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::__types {

// Forward-declaration
class Str;

class Object {
 public:
  /// @note Mamba-specific
  using self = Object;

  virtual ~Object() = default;

  virtual Str __Repr__() const = 0;
  virtual Str __Str__() const { return __Repr__(); }
  virtual Bool __Bool__() const = 0;

  virtual Bool __Eq__(const self& other) const {
    return __Id__() == other.__Id__();
  }

  virtual BigInt __Id__() const = 0;

  // For C++ implicit conversion to bool
  virtual operator bool() const { return __Bool__(); }

  // For C++ code generation, facilitating the identity operator `is` like so:
  // ~a == ~b where a and b are objects, not values.
  virtual BigInt operator~() const { return __Id__(); }
};

}  // namespace mamba::builtins::__types

// IWYU pragma: private
