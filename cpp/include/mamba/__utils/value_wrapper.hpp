#pragma once

#include <utility>

#include "mamba/__concepts/value.hpp"

namespace mamba::builtins::__utils {

template <__concepts::Value T>
struct ValueWrapper {
 public:
  constexpr ValueWrapper(T&& t) : t_(std::forward<T>(t)) {}

  ValueWrapper& operator=(T&& t) constexpr { t_ = std::forward<T>(t); }

  constexpr T& operator*() { return t_; }
  constexpr const T& operator*() const { return t_; }
  constexpr operator T() const { return t_; }

 private:
  T t_;
};

}  // namespace mamba::builtins::__utils
