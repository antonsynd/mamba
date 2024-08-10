#pragma once

#include <memory>

#include "mamba/object.hpp"

namespace mamba::builtins::memory {

template <concepts::Object T>
using Handle = std::shared_ptr<T>;

template <concepts::Object T, typename... Args>
Handle<T> Init(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

}  // namespace mamba::builtins::memory
