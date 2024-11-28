#pragma once

#include <concepts>
#include <memory>

namespace mamba::builtins {
namespace __memory {

// Simple alias
template <typename T>
using Ref = std::shared_ptr<T>;

}  // namespace __memory

namespace __concepts {

template <typename T>
concept IsRef = std::same_as<T, __memory::Ref<typename T::element_type>>;

}  // namespace __concepts
}  // namespace mamba::builtins

// IWYU pragma: private
