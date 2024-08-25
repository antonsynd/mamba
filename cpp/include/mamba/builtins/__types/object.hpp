#pragma once

#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__types {

class Object {
  virtual Str Repr() const = 0;
};

}  // namespace mamba::builtins::__types
