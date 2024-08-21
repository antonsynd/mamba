#pragma once

#include <memory>

#include "mamba/concepts/object.hpp"

namespace mamba::builtins::memory {

// Simple alias without constraints. Adding concepts::Object here makes it
// impossible to evaluate T because it is not a complete type at this point
template <typename T>
using Handle = std::shared_ptr<T>;

/// @brief Instantiates an object of type @tparam T with @p args and returns
/// a handle to the object.
template <concepts::Object T, typename... Args>
static Handle<T> Init(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

}  // namespace mamba::builtins::memory
