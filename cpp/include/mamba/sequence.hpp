#pragma once

#include "mamba/bool.hpp"

namespace mamba::builtins::types {

template <typename T>
concept Sequence = requires { typename T::value_t; };

template <Sequence T>
T::value_t Min(const T& sequence) {
  return sequence.Min();
}

template <Sequence T>
T::value_t Max(const T& sequence) {
  return sequence.Max();
}

template <Sequence T, typename U>
types::Bool In(const T& sequence, U value) {
  return sequence.In(value);
}

template <Sequence T>
types::Int Len(const T& sequence) {
  return sequence.Len();
}

}  // namespace mamba::builtins::types
