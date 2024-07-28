#pragma once

#include "mamba/bool.hpp"

namespace mamba::builtins::types {

template <typename T>
T::value_t Min(const T& sequence) {
  return sequence.Min();
}

template <typename T>
T::value_t Max(const T& sequence) {
  return sequence.Max();
}

template <typename T, typename U>
types::Bool In(const T& sequence, U v) {
  return sequence.In(v);
}

template <typename T>
types::Int Len(const T& sequence) {
  return sequence.Len();
}

}  // namespace mamba::builtins::types
