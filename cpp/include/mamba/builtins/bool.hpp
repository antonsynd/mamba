#pragma once

#include "mamba/builtins/__as_bool/bool.hpp"  // IWYU: export
#include "mamba/builtins/__as_str/bool.hpp"   // IWYU: export
#include "mamba/builtins/__repr/bool.hpp"     // IWYU: export
#include "mamba/builtins/__types/bool.hpp"    // IWYU: export

namespace mamba::builtins {

using Bool = __types::Bool;

}  // namespace mamba::builtins
