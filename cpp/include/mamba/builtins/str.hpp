#pragma once

#include "mamba/builtins/__as_bool/str.hpp"  // IWYU: export
#include "mamba/builtins/__as_str/str.hpp"   // IWYU: export
#include "mamba/builtins/__repr/str.hpp"     // IWYU: export
#include "mamba/builtins/__types/int.hpp"    // IWYU: export
#include "mamba/builtins/__types/str.hpp"    // IWYU: export

namespace mamba::builtins {

using Str = __types::Str;

__types::Int Len(const Str& s) {
  return s.size();
}

}  // namespace mamba::builtins
