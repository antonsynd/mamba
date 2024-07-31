#pragma once

#include <type_traits>

#include "mamba/sequence.hpp"

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
template <types::Sequence T>
class Iterator {
 public:
  virtual Iterator<T> Iter() const = 0;
  virtual T::value Next() = 0;

  // virtual iterator_t<T::value_t> begin() = 0;
  // virtual iterator_t<T::value_t> end() = 0;
};

template <typename T>
  requires types::Sequence<T> || std::is_same_v<T, Iterator<T>>
Iterator<T> Iter(const T& sequence) {
  return sequence.Iter();
}

}  // namespace mamba::builtins
