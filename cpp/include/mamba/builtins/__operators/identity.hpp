#pragma once

#include <optional>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__memory/args.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/none.hpp"
#include "mamba/builtins/__types/object.hpp"

namespace mamba::builtins {

// Values are identical if they have the same value
template <details::Value T>
details::Bool Is(const T lhs, const T rhs) {
  return lhs == rhs;
}

// Objects are identical if they have the same id (implementation detail:
// which is their memory address)
details::Bool Is(const details::Object& lhs, const details::Object& rhs) {
  return ~lhs == ~rhs;
}

// Specialization for None type, only None is identical to None
template <typename T>
details::Bool Is(const std::optional<T>& lhs, details::None) {
  return !lhs;
}

template <typename T>
details::Bool Is(details::None, const std::optional<T>& rhs) {
  return !rhs;
}

details::Bool Is(details::None, details::None) {
  return true;
}

}  // namespace mamba::builtins

// IWYU pragma: private
