#pragma once

#include "mamba/types/bool.hpp"
#include "mamba/types/float.hpp"
#include "mamba/types/str.hpp"

namespace mamba::builtins {

using Float = types::Float;

types::Bool AsBool(Float f) {
  return f != 0;
}

types::Str AsStr(Float f) {
  return std::to_string(f);
}

types::Str Repr(Float f) {
  return std::to_string(f);
}

}  // namespace mamba::builtins
