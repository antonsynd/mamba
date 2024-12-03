#pragma once

#include <utility>

#include "mamba/builtins/__operators/equality.hpp"      // IWYU pragma: export
#include "mamba/builtins/__operators/greater_than.hpp"  // IWYU pragma: export
#include "mamba/builtins/__operators/greater_than_or_equal.hpp"  // IWYU pragma: export
#include "mamba/builtins/__operators/identity.hpp"   // IWYU pragma: export
#include "mamba/builtins/__operators/less_than.hpp"  // IWYU pragma: export
#include "mamba/builtins/__operators/less_than_or_equal.hpp"  // IWYU pragma: export

namespace mamba::builtins {

// Export Is() operators
using __operators::identity;

}  // namespace mamba::builtins
