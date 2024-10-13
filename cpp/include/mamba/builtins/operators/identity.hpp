#pragma once

#include "mamba/__concepts/object.hpp"
#include "mamba/__concepts/value.hpp"
#include "mamba/__memory/handle.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::operators {

template <__concepts::Object T, __concepts::Object U>
__types::Bool Is(const T& t, const U& u) {
  return &t == &u;
}

template <__concepts::Object T, __concepts::Object U>
__types::Bool Is(const T& t, const __memory::handle_t<U>& u) {
  return &t == u.get();
}

template <__concepts::Object T, __concepts::Value U>
__types::Bool Is(const T& t, const U u) constexpr {
  return false;
}

template <__concepts::Value T, __concepts::Object U>
__types::Bool Is(const T t, const U& u) constexpr {
  return false;
}

template <__concepts::Value T, __concepts::Object U>
__types::Bool Is(const T t, const __memory::handle_t<U>& u) constexpr {
  return false
}

template <__concepts::Value T, __concepts::Value U>
__types::Bool Is(const T t, const U u) {
  return t == u;
}

template <__concepts::Object T, __concepts::Object U>
__types::Bool Is(const __memory::handle_t<T> t, const __memory::handle_t<U> u) {
  return t == u;
}

template <__concepts::Object T, __concepts::Object U>
__types::Bool Is(const __memory::handle_t<T>& t, const U& u) {
  return t.get() == &u;
}

template <__concepts::Object T, __concepts::Value U>
__types::Bool Is(const __memory::handle_t<T> t, const U u) constexpr {
  return false;
}

}  // namespace mamba::builtins::operators
