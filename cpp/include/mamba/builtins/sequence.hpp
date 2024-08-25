#pragma once

#include "mamba/__concepts/entity.hpp"
#include "mamba/__memory/handle.hpp"
#include "mamba/__memory/managed.hpp"
#include "mamba/__memory/read_only.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/iteration.hpp"

namespace mamba::builtins {
namespace __concepts {

template <typename T, typename U>
concept TypedSequence =
    __concepts::TypedIterable<T, U> &&
    requires(const T& sequence, __memory::ReadOnly<U> elem) {
      { sequence.In(elem) } -> std::same_as<__types::Bool>;
      { sequence.Len() } -> std::same_as<__types::Int>;
      { sequence.Max() } -> std::same_as<__memory::managed_t<U>>;
      { sequence.Min() } -> std::same_as<__memory::managed_t<U>>;
    };

template <typename T>
concept Sequence = __concepts::TypedSequence<T, typename T::element>;

}  // namespace __concepts

template <__concepts::Sequence T>
__memory::managed_t<typename T::element> Min(const T& sequence) {
  return sequence.Min();
}

template <__concepts::Sequence T>
__memory::managed_t<typename T::element> Min(
    const __memory::handle_t<T>& sequence) {
  return Min(*sequence);
}

template <__concepts::Sequence T>
__memory::managed_t<typename T::element> Max(const T& sequence) {
  return sequence.Max();
}

template <__concepts::Sequence T>
__memory::managed_t<typename T::element> Max(
    const __memory::handle_t<T>& sequence) {
  return Max(*sequence);
}

template <__concepts::Sequence T>
__types::Bool In(const T& sequence,
                 __memory::ReadOnly<typename T::element> value) {
  return sequence.In(value);
}

template <__concepts::Sequence T>
__types::Bool In(const __memory::handle_t<T>& sequence,
                 __memory::ReadOnly<typename T::element> value) {
  return In(*sequence, value);
}

template <__concepts::Sequence T>
__types::Int Len(const T& sequence) {
  return sequence.Len();
}

template <__concepts::Sequence T>
__types::Int Len(const __memory::handle_t<T>& sequence) {
  return Len(*sequence);
}

}  // namespace mamba::builtins
