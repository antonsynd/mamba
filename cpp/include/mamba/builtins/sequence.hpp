#pragma once

#include <utility>

#include "mamba/builtins/__memory/args.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/iteration.hpp"

namespace mamba::builtins {
namespace __concepts {

template <typename T, typename U>
concept SequenceOf = __concepts::IterableOf<T, U> &&
                     requires(const T sequence, __memory::Const<U> elem) {
                       {
                         sequence.__Contains__(elem)
                       } -> std::same_as<__types::Bool>;
                       { sequence.__Len__() } -> std::same_as<__types::Int>;
                       { sequence.Max() } -> std::same_as<__memory::Ret<U>>;
                       { sequence.Min() } -> std::same_as<__memory::Ret<U>>;
                     };

template <typename T>
concept Sequence = __concepts::SequenceOf<T, typename T::element>;

template <typename T>
concept SequenceRef =
    __concepts::IsRef<T> && Sequence<typename T::element_type>;

}  // namespace __concepts

template <__concepts::SequenceRef T>
__memory::Ret<typename T::element> Min(const T& sequence) {
  return sequence->Min();
}

template <__concepts::SequenceRef T>
__memory::Ret<typename T::element> Max(const T& sequence) {
  return sequence->Max();
}

template <__concepts::SequenceRef T>
__types::Bool Contains(const T& sequence,
                       __memory::Const<typename T::element> value) {
  return sequence->__Contains__(value);
}

template <__concepts::SequenceRef T>
__types::Int Len(const T& sequence) {
  return sequence->__Len__();
}

}  // namespace mamba::builtins
