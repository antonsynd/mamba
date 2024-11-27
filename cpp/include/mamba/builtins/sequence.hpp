#pragma once

#include <utility>

#include "mamba/builtins/__memory/const.hpp"
#include "mamba/builtins/__memory/entity.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/iteration.hpp"

namespace mamba::builtins {
namespace __concepts {

template <typename T, typename U>
concept TypedSequence = __concepts::TypedIterable<T, U> &&
                        requires(const T& sequence, __memory::Const<U> elem) {
                          {
                            sequence.__Contains__(elem)
                          } -> std::same_as<__types::Bool>;
                          { sequence.__Len__() } -> std::same_as<__types::Int>;
                          {
                            sequence.Max()
                          } -> std::same_as<__memory::Entity<U>>;
                          {
                            sequence.Min()
                          } -> std::same_as<__memory::Entity<U>>;
                        };

template <typename T>
concept Sequence = __concepts::TypedSequence<T, typename T::element>;

}  // namespace __concepts

template <__concepts::Sequence T>
__memory::Entity<typename T::element> Min(__memory::Const<T> sequence) {
  return sequence->Min();
}

template <__concepts::Sequence T>
__memory::Entity<typename T::element> Max(__memory::Const<T> sequence) {
  return sequence->Max();
}

template <__concepts::Sequence T>
__types::Bool Contains(__memory::Const<T> sequence,
                       __memory::Const<typename T::element> value) {
  return sequence->__Contains__(value);
}

template <__concepts::Sequence T>
__types::Int Len(__memory::Const<T> sequence) {
  return sequence->__Len__();
}

}  // namespace mamba::builtins
