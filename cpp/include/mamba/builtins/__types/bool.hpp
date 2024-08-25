#pragma once

namespace mamba::builtins::__types {

/// @note This goes against the Python specification which says bool is an
/// integer. This is to ensure we can write separate builtin functions for
/// Int and Bool.
using Bool = bool;

}  // namespace mamba::builtins::__types
