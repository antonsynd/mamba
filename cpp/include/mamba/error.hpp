#pragma once

#include <stdexcept>
#include <utility>

#include "mamba/str.hpp"

namespace mamba::builtins {

class ValueError : public std::runtime_error {
 public:
  explicit ValueError(types::Str message)
      : std::runtime_error(std::move(message)) {}
};

class IndexError : public std::runtime_error {
 public:
  explicit IndexError(types::Str message)
      : std::runtime_error(std::move(message)) {}
};

class AttributeError : public std::runtime_error {
 public:
  explicit AttributeError(types::Str message)
      : std::runtime_error(std::move(message)) {}
};

}  // namespace mamba::builtins
