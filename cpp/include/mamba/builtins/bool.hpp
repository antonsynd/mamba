#pragma once

#include "mamba/builtins/__dunder/__bool/bool.hpp"  // IWYU: export
#include "mamba/builtins/__dunder/__repr/bool.hpp"  // IWYU: export
#include "mamba/builtins/__dunder/__str/bool.hpp"   // IWYU: export
#include "mamba/builtins/__types/bool.hpp"          // IWYU: export

namespace mamba::builtins {

using BoolType = __types::Bool;

}  // namespace mamba::builtins
