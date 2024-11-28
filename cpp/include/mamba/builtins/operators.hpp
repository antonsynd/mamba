#pragma once

#include <utility>

#include "mamba/builtins/__operators/equality.hpp"      // IWYU pragma: export
#include "mamba/builtins/__operators/greater_than.hpp"  // IWYU pragma: export
#include "mamba/builtins/__operators/greater_than_or_equal.hpp"  // IWYU pragma: export
#include "mamba/builtins/__operators/identity.hpp"   // IWYU pragma: export
#include "mamba/builtins/__operators/init.hpp"       // IWYU pragma: export
#include "mamba/builtins/__operators/less_than.hpp"  // IWYU pragma: export
#include "mamba/builtins/__operators/less_than_or_equal.hpp"  // IWYU pragma: export

namespace mamba::builtins {

template <typename T, typename... Args>
auto Init(Args&&... args) {
  return mamba::builtins::__operators::Init<T, Args...>(
      std::forward<Args>(args)...);
}

template <typename T>
auto Is(T&& other) {
  return mamba::builtins::__operators::Is<T>(std::forward<T>(other));
}

}  // namespace mamba::builtins
