#pragma once

#include <utility>

#include "mamba/__concepts/object.hpp"
#include "mamba/__concepts/value.hpp"
#include "mamba/__memory/handle.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::operators {

template <__concepts::Object T, __concepts::Object U>
__types::Bool Eq(const T& t, const U& u) {
  return t.Eq(u);
}

template <__concepts::Object T, __concepts::Object U>
__types::Bool Eq(const T& t, const __memory::handle_t<U>& u) {
  return t.Eq(*u);
}

template <__concepts::Object T, __concepts::Value U>
__types::Bool Eq(const T& t, const U u) {
  return t.Eq(u);
}

template <__concepts::Value T, __concepts::Object U>
__types::Bool Eq(const T t, const U& u) {
  return t == u;
}

template <__concepts::Value T, __concepts::Object U>
__types::Bool Eq(const T t, const __memory::handle_t<U>& u) {
  return t == *u;
}

template <__concepts::Value T, __concepts::Value U>
__types::Bool Eq(const T t, const U u) {
  return t == u;
}

template <__concepts::Object T, __concepts::Object U>
__types::Bool Eq(const __memory::handle_t<T> t, const __memory::handle_t<U> u) {
  return t->Eq(*u);
}

template <__concepts::Object T, __concepts::Object U>
__types::Bool Eq(const __memory::handle_t<T>& t, const U& u) {
  return t->Eq(u);
}

template <__concepts::Object T, __concepts::Value U>
__types::Bool Eq(const __memory::handle_t<T> t, const U u) {
  return t->Eq(u);
}

}  // namespace mamba::builtins::operators

// C++ operators

// NOTE: operator==() and operator!=() with handle_t<T> as both arguments
// conflicts with std::shared_ptr<T>::operator!=(), so they are not defined

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Object U>
bool operator==(const T& t, const U& u) {
  return t.Eq(u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Object U>
bool operator==(const T& t, const mamba::builtins::__memory::handle_t<U>& u) {
  return t.Eq(*u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Value U>
bool operator==(const T& t, const U u) {
  return t.Eq(u);
}

template <mamba::builtins::__concepts::Value T,
          mamba::builtins::__concepts::Object U>
bool operator==(const T t, const U& u) {
  return t == u;
}

template <mamba::builtins::__concepts::Value T,
          mamba::builtins::__concepts::Object U>
bool operator==(const T t, const mamba::builtins::__memory::handle_t<U>& u) {
  return t == *u;
}

template <mamba::builtins::__concepts::Value T,
          mamba::builtins::__concepts::Value U>
bool operator==(const T t, const U u) {
  return t == u;
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Object U>
bool operator==(const mamba::builtins::__memory::handle_t<T>& t, const U& u) {
  return t->Eq(u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Value U>
bool operator==(const mamba::builtins::__memory::handle_t<T> t, const U u) {
  return t->Eq(u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Object U>
bool operator!=(const T& t, const U& u) {
  return !(t == u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Object U>
bool operator!=(const T& t, const mamba::builtins::__memory::handle_t<U>& u) {
  return !(t == u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Value U>
bool operator!=(const T& t, const U u) {
  return !(t == u);
}

template <mamba::builtins::__concepts::Value T,
          mamba::builtins::__concepts::Object U>
bool operator!=(const T t, const U& u) {
  return !(t == u);
}

template <mamba::builtins::__concepts::Value T,
          mamba::builtins::__concepts::Object U>
bool operator!=(const T t, const mamba::builtins::__memory::handle_t<U>& u) {
  return !(t == u);
}

template <mamba::builtins::__concepts::Value T,
          mamba::builtins::__concepts::Value U>
bool operator!=(const T t, const U u) {
  return !(t == u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Object U>
bool operator!=(const mamba::builtins::__memory::handle_t<T>& t, const U& u) {
  return !(t == u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Value U>
bool operator!=(const mamba::builtins::__memory::handle_t<T> t, const U u) {
  return !(t == u);
}
