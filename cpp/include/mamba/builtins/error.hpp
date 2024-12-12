#pragma once

#include <stdexcept>
#include <utility>

#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

class ValueError : public std::runtime_error {
 public:
  explicit ValueError(const details::Str& message)
      : std::runtime_error(message) {}
};

class IndexError : public std::runtime_error {
 public:
  explicit IndexError(const details::Str& message)
      : std::runtime_error(message) {}
};

class AttributeError : public std::runtime_error {
 public:
  explicit AttributeError(const details::Str& message)
      : std::runtime_error(message) {}
};

class StopIteration : public std::runtime_error {
 public:
  explicit StopIteration() : std::runtime_error("") {}
};

}  // namespace mamba::builtins
