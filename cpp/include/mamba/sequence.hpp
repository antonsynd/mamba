#pragma once

#include "mamba/concepts/entity.hpp"
#include "mamba/iteration.hpp"
#include "mamba/memory/managed.hpp"
#include "mamba/memory/read_only.hpp"
#include "mamba/types/bool.hpp"
#include "mamba/types/int.hpp"

namespace mamba::builtins {
namespace concepts {

template <typename T, typename U>
concept TypedSequence = concepts::TypedIterable<T, U> &&
                        requires(const T& sequence, memory::ReadOnly<U> elem) {
                          { sequence.In(elem) } -> std::same_as<types::Bool>;
                          { sequence.Len() } -> std::same_as<types::Int>;
                          {
                            sequence.Max()
                          } -> std::same_as<memory::managed_t<U>>;
                          {
                            sequence.Min()
                          } -> std::same_as<memory::managed_t<U>>;
                        };

template <typename T>
concept Sequence = concepts::TypedSequence<T, typename T::element>;

}  // namespace concepts

template <concepts::Sequence T>
memory::managed_t<typename T::element> Min(const T& sequence) {
  return sequence.Min();
}

template <concepts::Sequence T>
memory::managed_t<typename T::element> Max(const T& sequence) {
  return sequence.Max();
}

template <concepts::Sequence T>
types::Bool In(const T& sequence, memory::ReadOnly<typename T::element> value) {
  return sequence.In(value);
}

template <concepts::Sequence T>
types::Int Len(const T& sequence) {
  return sequence.Len();
}

}  // namespace mamba::builtins
