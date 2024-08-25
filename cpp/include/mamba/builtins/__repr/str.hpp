#pragma once

#include <utility>

#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

/// @note The return value is expected to be a new copy of @p s. Returning an
/// lvalue ref is not expected here. However, we can move a temporary if it
/// was passed in, hence the use of a forwarding reference.
inline __types::Str Repr(__types::Str s) {
  return std::forward<__types::Str>(s);
}

}  // namespace mamba::builtins
