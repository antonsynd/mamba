#pragma once

#include <utility>

#include "mamba/builtins/__memory/args.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/iteration.hpp"

namespace mamba::builtins {
namespace details {

template <typename T, typename U>
concept HasSequenceMethods = requires(const T sequence, Const<U> elem) {
  { sequence.__Contains__(elem) } -> std::same_as<Bool>;
  { sequence.__Len__() } -> std::same_as<Int>;
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
details::Bool Contains(const T& sequence,
                       details::Const<details::SequenceValueType<T>> value) {
  return sequence.__Contains__(value);
}

template <details::Sequence T>
details::Int Len(const T& sequence) {
  return sequence.__Len__();
}

}  // namespace mamba::builtins
