#pragma once

#include <memory>

#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__types {

class Object : public std::enable_shared_from_this<Object> {
 public:
  virtual ~Object() = default;
  virtual Str __Repr__() const = 0;
};

}  // namespace mamba::builtins::__types

// IWYU pragma: private
