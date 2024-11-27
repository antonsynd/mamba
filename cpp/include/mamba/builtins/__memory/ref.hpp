#pragma once

#include <memory>

namespace mamba::builtins::__memory {

// Simple alias
template <typename T>
using Ref = std::shared_ptr<T>;

/// @brief Instantiates an object of type @tparam T with @p args and returns
/// a reference to the object.
template <typename T, typename... Args>
static Ref<T> Init(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

}  // namespace mamba::builtins::__memory

// IWYU pragma: private
