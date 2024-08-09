#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/handle.hpp"
#include "mamba/value.hpp"

namespace mamba::builtins {

template <concepts::Value T>
class Iterator {
 public:
  virtual memory::Handle<Iterator<T>> Iter() = 0;
  virtual T Next() = 0;
};

namespace concepts {

template <typename T>
concept Iterable = requires(T iterable) {
  typename T::value;
  {
    iterable.Iter()
  } -> std::same_as<memory::Handle<Iterator<typename T::value>>>;
};

}  // namespace concepts

template <concepts::Value T>
T Next(Iterator<T>& it) {
  return it.Next();
}

template <concepts::Iterable T>
memory::Handle<Iterator<typename T::value>> Iter(T& iterable) {
  return iterable.Iter();
}

}  // namespace mamba::builtins
