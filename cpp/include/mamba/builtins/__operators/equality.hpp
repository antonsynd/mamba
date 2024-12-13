#pragma once

#include <utility>

#include "mamba/builtins/__concepts/equatable.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__utils/log.hpp"

// Specialization of != if __Ne__() is defined
template <mamba::builtins::details::InequatableObject T>
bool operator!=(const T& lhs, const T& rhs) {
  mamba::builtins::details::Error() << "global inequality inequatable";
  return lhs.__Ne__(rhs);
}

// IWYU pragma: private
