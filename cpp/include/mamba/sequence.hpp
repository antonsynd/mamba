#pragma once

#include "mamba/concepts/entity.hpp"
#include "mamba/iteration.hpp"
#include "mamba/types/bool.hpp"
#include "mamba/types/int.hpp"

namespace mamba::builtins {

template <typename T>
concept Sequence = concepts::Iterable<T> &&
                   requires(const T sequence, typename T::value elem) {
                     { sequence.In(elem) } -> std::same_as<types::Bool>;
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

template <Sequence T, concepts::Entity U>
types::Bool In(const T& sequence, U value) {
  return sequence.In(value);
}

template <Sequence T>
types::Int Len(const T& sequence) {
  return sequence.Len();
}

}  // namespace mamba::builtins
