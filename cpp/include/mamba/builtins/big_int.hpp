#pragma once

#include "mamba/builtins/__dunder/__bool/big_int.hpp"  // IWYU: export
#include "mamba/builtins/__dunder/__repr/big_int.hpp"  // IWYU: export
#include "mamba/builtins/__dunder/__str/big_int.hpp"   // IWYU: export
#include "mamba/builtins/__types/big_int.hpp"          // IWYU: export

namespace mamba::builtins {

using BigIntType = __types::BigInt;

}  // namespace mamba::builtins

// IWYU pragma: private
