#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/concepts/entity.hpp"
#include "mamba/concepts/utils.hpp"

namespace mamba::builtins {

template <concepts::Entity T>
class Iterator {
 public:
  using value = T;

  virtual ~Iterator() = default;

  virtual Iterator<T> Iter() { return *this; };
  virtual T Next() { throw StopIteration("end of iterator"); };
};

namespace concepts {

template <typename T, typename U>
concept TypedIterable = requires(T iterable) {
  { iterable.Iter() } -> std::same_as<Iterator<U>>;
};

template <typename T>
concept Iterable = HasValueType<T> && TypedIterable<T, typename T::value>;

}  // namespace concepts

template <concepts::Entity T>
T Next(Iterator<T>& it) {
  return it.Next();
}

template <concepts::Entity T>
Iterator<T> Iter(Iterator<T>& it) {
  // Return a copy
  return it;
}

template <concepts::Iterable T>
Iterator<typename T::value> Iter(T& it) {
  return it.Iter();
}

}  // namespace mamba::builtins
