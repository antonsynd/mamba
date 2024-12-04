#pragma once

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__types {

class Object {
 public:
  virtual ~Object() = default;

  virtual Str __Repr__() const = 0;
  virtual Str __Str__() const { return __Repr__(); }
  virtual Bool __Bool__() const = 0;
  virtual BigInt __Id__() const = 0;

  // For C++ implicit conversion to bool
  virtual operator bool() const { __Bool__(); }
};

}  // namespace mamba::builtins::__types

// IWYU pragma: private
