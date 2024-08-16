#pragma once

#include <utility>

#include "mamba/types/bool.hpp"
#include "mamba/types/int.hpp"
#include "mamba/types/str.hpp"

namespace mamba::builtins {

using Str = types::Str;

types::Int Len(const Str& s) {
  return s.size();
}

types::Bool AsBool(Str s) {
  return !s.empty();
}

/// @note The return value is expected to be a new copy of @p s. Returning an
/// lvalue ref is not expected here. However, we can move a temporary if it
/// was passed in, hence the use of a forwarding reference.
Str AsStr(Str&& s) {
  return std::forward<Str>(s);
}

/// @note The return value is expected to be a new copy of @p s. Returning an
/// lvalue ref is not expected here. However, we can move a temporary if it
/// was passed in, hence the use of a forwarding reference.
Str Repr(Str&& s) {
  return std::forward<Str>(s);
}

}  // namespace mamba::builtins
