#pragma once

#include <stdexcept>
#include <utility>

#include "mamba/str.hpp"

namespace mamba::builtins {

class ValueError : public std::runtime_error {
 public:
  explicit ValueError(Str message) : std::runtime_error(std::move(message)) {}
};

}  // namespace mamba::builtins
