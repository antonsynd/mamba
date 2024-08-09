#pragma once

#include <memory>

namespace mamba::builtins::memory {

template <typename T>
using Handle = std::shared_ptr<T>;

}  // namespace mamba::builtins::memory
