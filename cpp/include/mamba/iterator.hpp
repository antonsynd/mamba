#pragma once

#include "mamba/sequence.hpp"

namespace mamba::builtins {

// TODO
template <types::Sequence T>
class Iterator {
 public:
  Iterator<T> Iter() const { return *this; }
  T::value_t Next() { return {}; }
};

}  // namespace mamba::builtins
