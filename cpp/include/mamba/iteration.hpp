#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/entity.hpp"

namespace mamba::builtins {

template <concepts::Entity T>
class Iterator {
 public:
  virtual ~Iterator() = default;

  virtual Iterator<T> Iter() = 0;
  virtual T Next() = 0;
};

namespace concepts {

template <typename T>
concept Iterable = requires(T iterable) {
  typename T::value;
  { iterable.Iter() } -> std::same_as<Iterator<typename T::value>>;
};

}  // namespace concepts

template <concepts::Value T>
T Next(Iterator<T>& it) {
  return it.Next();
}

template <concepts::Iterable T>
T Iter(T& it) {
  // Return a copy
  return it;
}

}  // namespace mamba::builtins
