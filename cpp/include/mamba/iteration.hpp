#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/concepts/entity.hpp"
#include "mamba/memory/managed.hpp"

namespace mamba::builtins {

template <concepts::Entity T>
class Iterator {
 public:
  using element = T;
  using value = memory::managed_t<element>;

  virtual ~Iterator() = default;

  virtual memory::handle_t<Iterator<element>> Iter() = 0;
  virtual value Next() = 0;

  virtual types::Str Repr() const { return ""; }
};

namespace concepts {

template <typename T, typename U>
concept TypedIterable = requires(T* iterable) {
  { iterable->Iter() } -> std::same_as<memory::handle_t<Iterator<U>>>;
};

template <typename T>
concept Iterable = TypedIterable<T, typename T::element>;

}  // namespace concepts

template <concepts::Entity T>
memory::managed_t<T> Next(Iterator<T>& it) {
  return it.Next();
}

template <concepts::Iterable T>
memory::handle_t<Iterator<typename T::element>> Iter(T& it) {
  return it.Iter();
}

}  // namespace mamba::builtins
