#pragma once

#include <stdexcept>
#include <utility>

#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

class ValueError : public std::runtime_error {
 public:
  explicit ValueError(__types::Str message)
      : std::runtime_error(std::move(message)) {}
};

class IndexError : public std::runtime_error {
 public:
  explicit IndexError(__types::Str message)
      : std::runtime_error(std::move(message)) {}
};

class AttributeError : public std::runtime_error {
 public:
  explicit AttributeError(__types::Str message)
      : std::runtime_error(std::move(message)) {}
};

class StopIteration : public std::runtime_error {
 public:
  explicit StopIteration(__types::Str message)
      : std::runtime_error(std::move(message)) {}
};

}  // namespace mamba::builtins
