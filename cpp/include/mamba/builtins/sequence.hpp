#pragma once

#include <utility>

#include "mamba/builtins/__meta/args.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/iteration.hpp"

namespace mamba::builtins {
namespace details {

template <typename T, typename U>
concept HasSequenceMethods = requires(const T sequence, const U& elem) {
  { sequence.Contains(elem) } -> std::same_as<bool>;
  { sequence.Len() } -> std::same_as<Int>;
  { sequence.Max() } -> std::same_as<U>;
  { sequence.Min() } -> std::same_as<U>;
};

template <typename T, typename U>
concept SequenceOf = IterableOf<T, U> && HasSequenceMethods<T, U>;

template <typename T>
concept Sequence = SequenceOf<T, typename T::value_type>;

}  // namespace details

namespace details {

/// @brief Simple convenience alias.
template <Sequence T>
using SequenceValueType = typename T::value_type;

}  // namespace details

template <details::Sequence T>
details::SequenceValueType<T> Min(const T& sequence) {
  return sequence.Min();
}

template <details::Sequence T>
details::SequenceValueType<T> Max(const T& sequence) {
  return sequence.Max();
}

template <details::Sequence T>
bool In(const details::SequenceValueType<T>& value, const T& sequence) {
  return sequence.Contains(value);
}

template <details::Sequence T>
bool Contains(const T& sequence, const details::SequenceValueType<T>& value) {
  return sequence.Contains(value);
}

template <details::Sequence T>
details::Int Len(const T& sequence) {
  return sequence.Len();
}

}  // namespace mamba::builtins
