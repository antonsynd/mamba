#pragma once

#include <memory>

#include "mamba/object.hpp"

namespace mamba::builtins::memory::v2 {

template <concepts::Object T>
using Handle = std::shared_ptr<T>;

template <concepts::Object T, typename... Args>
Handle<T> Init(Args&&... args) {
  return T::Init(std::forward<Args>(args)...);
}

template <concepts::Object T, typename... Args>
Handle<T> Make(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

}  // namespace mamba::builtins::memory::v2
