#pragma once

#include "mamba/builtins/__concepts/orderable.hpp"
#include "mamba/builtins/__types/bool.hpp"

template <mamba::builtins::__concepts::GreaterThanComparableObject T>
bool operator<(const T& lhs, const T& rhs) {
  return lhs.__Lt__(rhs);
}

// IWYU pragma: private
