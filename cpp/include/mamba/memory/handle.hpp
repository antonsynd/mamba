#pragma once

#include <memory>

#include "mamba/concepts/object.hpp"
#include "mamba/concepts/value.hpp"

namespace mamba::builtins::memory {

template <typename T>
using Handle = std::shared_ptr<T>;

template <concepts::Object T, typename... Args>
static Handle<T> Init(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

}  // namespace mamba::builtins::memory
