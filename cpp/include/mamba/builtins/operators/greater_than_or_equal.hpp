#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/operators/equality.hpp"
#include "mamba/builtins/operators/greater_than.hpp"

namespace mamba::builtins::operators {

template <typename T, typename U>
__types::Bool GtEq(T&& t, U&& u) {
  return Gt(std::forward<T>(t), std::forward<U>(u)) ||
         Eq(std::forward<T>(t), std::forward<U>(u));
}

}  // namespace mamba::builtins::operators

// C++ operators
template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Object U>
bool operator>=(const T& t, const U& u) {
  return t.GtEq(u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Object U>
bool operator>=(const T& t, const mamba::builtins::__memory::handle_t<U>& u) {
  return t.GtEq(*u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Value U>
bool operator>=(const T& t, const U u) {
  return t.GtEq(u);
}

template <mamba::builtins::__concepts::Value T,
          mamba::builtins::__concepts::Object U>
bool operator>=(const T t, const U& u) {
  return t >= u;
}

template <mamba::builtins::__concepts::Value T,
          mamba::builtins::__concepts::Object U>
bool operator>=(const T t, const mamba::builtins::__memory::handle_t<U>& u) {
  return t >= *u;
}

template <mamba::builtins::__concepts::Value T,
          mamba::builtins::__concepts::Value U>
bool operator>=(const T t, const U u) {
  return t >= u;
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Object U>
bool operator>=(const mamba::builtins::__memory::handle_t<T> t,
                const mamba::builtins::__memory::handle_t<U> u) {
  return t->GtEq(*u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Object U>
bool operator>=(const mamba::builtins::__memory::handle_t<T>& t, const U& u) {
  return t->GtEq(u);
}

template <mamba::builtins::__concepts::Object T,
          mamba::builtins::__concepts::Value U>
bool operator>=(const mamba::builtins::__memory::handle_t<T> t, const U u) {
  return t->GtEq(u);
}
