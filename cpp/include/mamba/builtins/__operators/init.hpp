#pragma once

#include <memory>
#include <utility>

#include "mamba/builtins/__memory/args.hpp"

namespace mamba::builtins::__operators {

/// @brief Instantiates an object of type @tparam T with @p args and returns
/// a reference to the object.
template <typename T, typename... Args>
std::shared_ptr<T> Init(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

}  // namespace mamba::builtins::__operators
