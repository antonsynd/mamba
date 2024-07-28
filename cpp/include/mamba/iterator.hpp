#pragma once

#include <type_traits>

#include "mamba/sequence.hpp"

namespace mamba::builtins {

// TODO
template <types::Sequence T>
class Iterator {
 public:
  virtual Iterator<T> Iter() const = 0;
  virtual T::value_t Next() = 0;
};

template <typename T>
  requires types::Sequence<T> || std::is_same_v<T, Iterator<T>>
Iterator<T> Iter(const T& sequence) {
  return sequence.Iter();
}

}  // namespace mamba::builtins
