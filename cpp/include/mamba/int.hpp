#pragma once

#include "mamba/types/bool.hpp"
#include "mamba/types/int.hpp"
#include "mamba/types/str.hpp"

namespace mamba::builtins {

using Int = types::Int;

types::Bool AsBool(Int i) {
  return i != 0;
}

types::Str AsStr(Int i) {
  return std::to_string(i);
}

types::Str Repr(Int i) {
  return std::to_string(i);
}

}  // namespace mamba::builtins
