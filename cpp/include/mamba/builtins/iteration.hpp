#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/__concepts/entity.hpp"
#include "mamba/__memory/managed.hpp"
#include "mamba/builtins/__types/object.hpp"

namespace mamba::builtins {

template <__concepts::Entity T>
class Iterator : public builtins::__types::Object {
 public:
  using element = T;
  using value = __memory::managed_t<element>;

  virtual ~Iterator() = default;

  virtual __memory::handle_t<Iterator<element>> Iter() = 0;
  virtual value Next() = 0;
};

namespace __concepts {

template <typename T, typename U>
concept TypedIterable = requires(T* iterable) {
  { iterable->Iter() } -> std::same_as<__memory::handle_t<Iterator<U>>>;
};

template <typename T>
concept Iterable = TypedIterable<T, typename T::element>;

}  // namespace __concepts

template <__concepts::Entity T>
__memory::managed_t<T> Next(Iterator<T>& it) {
  return it.Next();
}

template <__concepts::Iterable T>
__memory::handle_t<Iterator<typename T::element>> Iter(T& it) {
  return it.Iter();
}

}  // namespace mamba::builtins
