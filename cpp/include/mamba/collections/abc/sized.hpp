#pragma once

#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/__types/size.hpp"

namespace mamba::collections::abc {

class Sized : virtual public builtins::details::Object {
  virtual builtins::details::Size Len() const = 0;
};

}  // namespace mamba::collections::abc
