#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__types {

class Object {
 public:
  virtual ~Object() = default;

  virtual Str __Repr__() const = 0;
  virtual Bool __Bool__() const = 0;
  virtual Int __Id__() const = 0;
};

}  // namespace mamba::builtins::__types

// IWYU pragma: private
