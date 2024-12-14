#pragma once

#include <utility>

#include "mamba/builtins/__concepts/equatable.hpp"
#include "mamba/builtins/__types/bool.hpp"

// Specialization of != if __Ne__() is defined
template <mamba::builtins::details::InequatableObject T>
bool operator!=(const T& lhs, const T& rhs) {
  return lhs.__Ne__(rhs);
}

// IWYU pragma: private
