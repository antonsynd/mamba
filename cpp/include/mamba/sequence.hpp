#pragma once

#include "mamba/concepts/entity.hpp"
#include "mamba/concepts/utils.hpp"
#include "mamba/iteration.hpp"
#include "mamba/types/bool.hpp"
#include "mamba/types/int.hpp"

namespace mamba::builtins {
namespace concepts {

template <typename T, typename U>
concept TypedSequence = concepts::TypedIterable<T, U> &&
                        requires(const T& sequence, const U& elem) {
                          { sequence.In(elem) } -> std::same_as<types::Bool>;
                          { sequence.Len() } -> std::same_as<types::Int>;
                          { sequence.Max() } -> std::same_as<U>;
                          { sequence.Min() } -> std::same_as<U>;
                        };

template <typename T>
concept Sequence =
    HasValueType<T> && concepts::TypedSequence<T, typename T::value>;

}  // namespace concepts

template <concepts::Sequence T>
T::value Min(const T& sequence) {
  return sequence.Min();
}

template <concepts::Sequence T>
T::value Max(const T& sequence) {
  return sequence.Max();
}

template <concepts::Sequence T>
types::Bool In(const T& sequence, const typename T::value& value) {
  return sequence.In(value);
}

template <concepts::Sequence T>
types::Int Len(const T& sequence) {
  return sequence.Len();
}

}  // namespace mamba::builtins
