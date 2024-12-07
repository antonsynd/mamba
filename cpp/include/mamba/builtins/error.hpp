#pragma once

#include <stdexcept>
#include <utility>

#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

class ValueError : public std::runtime_error {
 public:
  explicit ValueError(const __types::Str& message)
      : std::runtime_error(message) {}
};

class IndexError : public std::runtime_error {
 public:
  explicit IndexError(const __types::Str& message)
      : std::runtime_error(message) {}
};

class AttributeError : public std::runtime_error {
 public:
  explicit AttributeError(const __types::Str& message)
      : std::runtime_error(message) {}
};

class StopIteration : public std::runtime_error {
 public:
  explicit StopIteration() : std::runtime_error("") {}
};

}  // namespace mamba::builtins
