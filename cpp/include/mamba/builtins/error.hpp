#pragma once

#include <stdexcept>
#include <utility>

#include "mamba/builtins/__memory/args.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

class ValueError : public std::runtime_error {
 public:
  explicit ValueError(__memory::Const<__types::Str> message)
      : std::runtime_error(*message) {}
};

class IndexError : public std::runtime_error {
 public:
  explicit IndexError(__memory::Const<__types::Str> message)
      : std::runtime_error(*message) {}
};

class AttributeError : public std::runtime_error {
 public:
  explicit AttributeError(__memory::Const<__types::Str> message)
      : std::runtime_error(*message) {}
};

class StopIteration : public std::runtime_error {
 public:
  explicit StopIteration(__memory::Const<__types::Str> message)
      : std::runtime_error(*message) {}
};

}  // namespace mamba::builtins
