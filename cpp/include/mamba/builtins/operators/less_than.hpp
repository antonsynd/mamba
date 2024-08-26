#pragma once

#include "mamba/__concepts/object.hpp"
#include "mamba/__concepts/value.hpp"
#include "mamba/__memory/handle.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::operators {

template <__concepts::Object T, __concepts::Object U>
__types::Bool Lt(const T& t, const U& u) {
  return t.Lt(u);
}

template <__concepts::Object T, __concepts::Object U>
__types::Bool Lt(const T& t, const __memory::handle_t<U>& u) {
  return t.Lt(*u);
}

template <__concepts::Object T, __concepts::Value U>
__types::Bool Lt(const T& t, const U u) {
  return t.Lt(u);
}

template <__concepts::Value T, __concepts::Object U>
__types::Bool Lt(const T t, const U& u) {
  return t < u;
}

template <__concepts::Value T, __concepts::Object U>
__types::Bool Lt(const T t, const __memory::handle_t<U>& u) {
  return t < *u;
}

template <__concepts::Value T, __concepts::Value U>
__types::Bool Lt(const T t, const U u) {
  return t < u;
}

template <__concepts::Object T, __concepts::Object U>
__types::Bool Lt(const __memory::handle_t<T> t, const __memory::handle_t<U> u) {
  return t->Lt(*u);
}

template <__concepts::Object T, __concepts::Object U>
__types::Bool Lt(const __memory::handle_t<T>& t, const U& u) {
  return t->Lt(u);
}

template <__concepts::Object T, __concepts::Value U>
__types::Bool Lt(const __memory::handle_t<T> t, const U u) {
  return t->Lt(u);
}

}  // namespace mamba::builtins::operators

// C++ operators
template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Object U>
bool operator<(const T& t, const U& u) {
  return t.Lt(u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Object U>
bool operator<(const T& t, const mamba::builtins::__memory::handle_t<U>& u) {
  return t.Lt(*u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Value U>
bool operator<(const T& t, const U u) {
  return t.Lt(u);
}

template <mamba::builtins::__concepts::Value T,
          mamba::builtins::__concepts::Object U>
bool operator<(const T t, const U& u) {
  return t < u;
}

template <mamba::builtins::__concepts::Value T,
          mamba::builtins::__concepts::Object U>
bool operator<(const T t, const mamba::builtins::__memory::handle_t<U>& u) {
  return t < *u;
}

template <mamba::builtins::__concepts::Value T,
          mamba::builtins::__concepts::Value U>
bool operator<(const T t, const U u) {
  return t < u;
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Object U>
bool operator<(const mamba::builtins::__memory::handle_t<T> t,
               const mamba::builtins::__memory::handle_t<U> u) {
  return t->Lt(*u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Object U>
bool operator<(const mamba::builtins::__memory::handle_t<T>& t, const U& u) {
  return t->Lt(u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Value U>
bool operator<(const mamba::builtins::__memory::handle_t<T> t, const U u) {
  return t->Lt(u);
}
