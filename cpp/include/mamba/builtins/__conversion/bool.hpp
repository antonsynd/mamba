#pragma once

#include "mamba/builtins/__dunder/__bool/bool.hpp"   // IWYU pragma: export
#include "mamba/builtins/__dunder/__bool/float.hpp"  // IWYU pragma: export
#include "mamba/builtins/__dunder/__bool/int.hpp"    // IWYU pragma: export
#include "mamba/builtins/__dunder/__bool/none.hpp"   // IWYU pragma: export
#include "mamba/builtins/__dunder/__bool/tuple.hpp"  // IWYU pragma: export
#include "mamba/builtins/__memory/args.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::__conversion {

template <__concepts::NotValue T>
__types::Bool Bool(const T& t) {
  return t.__Bool__();
}

}  // namespace mamba::builtins::__conversion
