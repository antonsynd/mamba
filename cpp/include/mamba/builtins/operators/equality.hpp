#pragma once

#include <utility>

#include "mamba/builtins/__concepts/comparable.hpp"
#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__memory/const.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/none.hpp"

// NOTE: operator==() and operator!=() with handle_t<T> as both arguments
// conflicts with std::shared_ptr<T>::operator!=(), so they are not defined

template <typename T>
bool operator==(mamba::builtins::__memory::Const<T> lhs,
                mamba::builtins::__memory::Const<T> rhs) {
  return lhs.__Eq__(rhs);
}

template <mamba::builtins::__concepts::Inequatable T>
bool operator!=(mamba::builtins::__memory::Const<T> lhs,
                mamba::builtins::__memory::Const<T> rhs) {
  return lhs.__Ne__(rhs);
}

template <typename T>
bool operator!=(mamba::builtins::__memory::Const<T> lhs,
                mamba::builtins::__memory::Const<T> rhs) {
  return !(lhs == rhs);
}

// Specializations for None type
template <typename T, typename U = T>
bool operator==(mamba::builtins::__memory::Const<T> lhs,
                mamba::builtins::__types::None<U>) {
  if constexpr (mamba::builtins::__concepts::Value<T>) {
    return false;
  } else {
    return !lhs;
  }
}

template <typename T, typename U = T>
bool operator!=(mamba::builtins::__memory::Const<T> lhs,
                mamba::builtins::__types::None<U>) {
  if constexpr (mamba::builtins::__concepts::Value<T>) {
    return true;
  } else {
    return !!lhs;
  }
}

// IWYU pragma: private
