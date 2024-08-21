#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/concepts/entity.hpp"
#include "mamba/concepts/utils.hpp"
#include "mamba/memory/handle.hpp"

namespace mamba::builtins {

template <concepts::Entity T>
class Iterator {
 public:
  using value = T;

  virtual ~Iterator() = default;

  virtual memory::Handle<Iterator<T>> Iter() = 0;
  virtual T Next() = 0;
};

namespace concepts {

template <typename T, typename U>
concept TypedIterable = requires(T* iterable) {
  { iterable->Iter() } -> std::same_as<memory::Handle<Iterator<U>>>;
};

template <typename T>
concept Iterable = HasValueType<T> && TypedIterable<T, typename T::value>;

}  // namespace concepts

template <concepts::Entity T>
T Next(Iterator<T>& it) {
  return it.Next();
}

template <concepts::Iterable T>
memory::Handle<Iterator<typename T::value>> Iter(T& it) {
  return it.Iter();
}

}  // namespace mamba::builtins
