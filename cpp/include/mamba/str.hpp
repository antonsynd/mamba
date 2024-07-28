#pragma once

#include <string>

#include "mamba/int.hpp"

namespace mamba::builtins::types {

// TODO: Make it Unicode friendly
using Str = std::string;

namespace str {

Int Len(const Str& s) {
  return s.size();
}

}  // namespace str

}  // namespace mamba::builtins::types
