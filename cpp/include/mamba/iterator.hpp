#pragma once

#include <type_traits>

#include "mamba/sequence.hpp"
#include "mamba/value.hpp"

namespace mamba::builtins {

// template <typename T>
// class iterator_t {
//  public:
//   virtual T operator*() const = 0;
//   virtual T* operator->() const = 0;
//   virtual iterator_t<T>& operator++() = 0;
//   virtual iterator_t<T>& operator++(int) = 0;

//   virtual iterator_t<T> operator+(int) = 0;
//   virtual iterator_t<T>& operator+=(int) = 0;
// };

// TODO
template <concepts::Value T>
class Iterator {
 public:
  virtual Iterator<T> Iter() const = 0;
  virtual T Next() = 0;
};

template <concepts::Value T, types::Sequence S>
Iterator<T> Iter(const S& sequence) {
  return sequence.Iter();
}

}  // namespace mamba::builtins
