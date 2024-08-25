#pragma once

#include "mamba/__concepts/str_convertible.hpp"
#include "mamba/__memory/handle.hpp"
#include "mamba/builtins/__as_str/bool.hpp"   // IWYU pragma: export
#include "mamba/builtins/__as_str/float.hpp"  // IWYU pragma: export
#include "mamba/builtins/__as_str/int.hpp"    // IWYU pragma: export
#include "mamba/builtins/__as_str/none.hpp"   // IWYU pragma: export
#include "mamba/builtins/__as_str/str.hpp"    // IWYU pragma: export
#include "mamba/builtins/__as_str/tuple.hpp"  // IWYU pragma: export
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

template <__concepts::StrConvertibleObject T>
__types::Str AsStr(const T& t) {
  return t.AsStr();
}

template <__concepts::StrConvertibleObject T>
__types::Str AsStr(const __memory::handle_t<T>& t) {
  return AsStr(*t);
}

}  // namespace mamba::builtins
