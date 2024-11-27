#pragma once

#include "mamba/builtins/__dunder/__bool/str.hpp"  // IWYU: export
#include "mamba/builtins/__dunder/__repr/str.hpp"  // IWYU: export
#include "mamba/builtins/__dunder/__str/str.hpp"   // IWYU: export
#include "mamba/builtins/__types/int.hpp"          // IWYU: export
#include "mamba/builtins/__types/str.hpp"          // IWYU: export

namespace mamba::builtins {

using StrType = __types::Str;

__types::Int Len(const StrType& s) {
  return s.size();
}

}  // namespace mamba::builtins
