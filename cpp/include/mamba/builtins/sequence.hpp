#pragma once

#include <utility>

#include "mamba/builtins/__memory/args.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/iteration.hpp"

namespace mamba::builtins {
namespace __concepts {

template <typename T, typename U>
concept HasSequenceMethods =
    requires(const T sequence, __memory::Const<U> elem) {
      { sequence.__Contains__(elem) } -> std::same_as<__types::Bool>;
      { sequence.__Len__() } -> std::same_as<__types::Int>;
      { sequence.Max() } -> std::same_as<U>;
      { sequence.Min() } -> std::same_as<U>;
    };

template <typename T, typename U>
concept SequenceOf = __concepts::IterableOf<T, U> && HasSequenceMethods<T, U>;

template <typename T>
concept Sequence = __concepts::SequenceOf<T, typename T::value_type>;

}  // namespace __concepts

namespace details {

/// @brief Simple convenience alias.
template <__concepts::Sequence T>
using SequenceValueType = typename T::value_type;

}  // namespace details

template <__concepts::Sequence T>
details::SequenceValueType<T> Min(const T& sequence) {
  return sequence.Min();
}

template <__concepts::Sequence T>
details::SequenceValueType<T> Max(const T& sequence) {
  return sequence.Max();
}

template <__concepts::Sequence T>
__types::Bool Contains(const T& sequence,
                       __memory::Const<details::SequenceValueType<T>> value) {
  return sequence.__Contains__(value);
}

template <__concepts::Sequence T>
__types::Int Len(const T& sequence) {
  return sequence.__Len__();
}

}  // namespace mamba::builtins
