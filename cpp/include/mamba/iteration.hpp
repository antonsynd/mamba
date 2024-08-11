#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/entity.hpp"
#include "mamba/handle.hpp"
#include "mamba/reference.hpp"

namespace mamba::builtins {

template <concepts::Entity T>
class Iterator {
 public:
  virtual ~Iterator() = default;

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
memory::Handle<T> Iter(memory::Handle<T>& iterable_handle) {
  // Simply copy the handle
  return iterable_handle;
}

}  // namespace mamba::builtins
