#pragma once

#include "mamba/__concepts/bool_convertible.hpp"
#include "mamba/__memory/read_only.hpp"
#include "mamba/builtins/__as_bool/bool.hpp"   // IWYU pragma: export
#include "mamba/builtins/__as_bool/float.hpp"  // IWYU pragma: export
#include "mamba/builtins/__as_bool/int.hpp"    // IWYU pragma: export
#include "mamba/builtins/__as_bool/none.hpp"   // IWYU pragma: export
#include "mamba/builtins/__as_bool/str.hpp"    // IWYU pragma: export
#include "mamba/builtins/__as_bool/tuple.hpp"  // IWYU pragma: export
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins {

template <__concepts::BoolConvertibleObject T>
__types::Bool AsBool(__memory::ReadOnlyObject<T> t) {
  return t->AsBool();
}

}  // namespace mamba::builtins
