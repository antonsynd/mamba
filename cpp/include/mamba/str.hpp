#pragma once

#include <string>

#include "mamba/int.hpp"

namespace mamba::builtins {

// TODO: Make it Unicode friendly
using Str = std::string;

namespace str {

int_t Len(const str_t& s) {
  return s.size();
}

}  // namespace str

}  // namespace mamba::builtins
