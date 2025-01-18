#pragma once

#include <utility>

#include "mamba/builtins/__meta/types.hpp"

namespace mamba::builtins::details {

template <typename T>
using Handle = std::conditional_t<Value<T>, T, std::shared_ptr<T>>;

template <typename T>
using Raw = std::conditional_t<Reference<T>, typename T::element_type, T>;

template <typename T>
auto Unwrap(T&& t) {
  if constexpr (Reference<T>) {
    return std::forward<T::element_type>(*t);
  } else {
    return std::forward<T>(t);
  }
}

template <NotValue T>
std::shared_ptr<T> New(T&& t) {
  return std::make_shared<T>(std::move(t));
}

}  // namespace mamba::builtins::details

// IWYU pragma: private
