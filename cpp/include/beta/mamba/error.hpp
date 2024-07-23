#pragma once

#include <stdexcept>
#include <utility>

#include "mamba/str.hpp"

namespace mamba::builtins {

class ValueError : public std::runtime_error {
 public:
  explicit ValueError(str_t message) : std::runtime_error(std::move(message)) {}
};

}  // namespace mamba::builtins
