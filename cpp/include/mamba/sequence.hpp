#pragma once

#include "mamba/bool.hpp"
#include "mamba/int.hpp"
#include "mamba/iteration.hpp"

namespace mamba::builtins::types {

template <typename T>
concept Sequence = concepts::Iterable<T> && requires(const T sequence) {
  typename T::value;
  // { sequence.In(typename T::value{}) } -> std::same_as<types::Bool>;
  { sequence.Len() } -> std::same_as<types::Int>;
  { sequence.Max() } -> std::same_as<typename T::value>;
  { sequence.Min() } -> std::same_as<typename T::value>;
};

template <Sequence T>
T::value Min(const T& sequence) {
  return sequence.Min();
}

template <Sequence T>
T::value Max(const T& sequence) {
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
