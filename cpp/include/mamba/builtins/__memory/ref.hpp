#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

namespace mamba::builtins {
namespace __memory {

// Simple alias
template <typename T>
using Ref = std::shared_ptr<std::decay_t<T>>;

}  // namespace __memory

namespace __concepts {

template <typename T>
concept IsRef = std::same_as<T, __memory::Ref<typename T::element_type>>;

}  // namespace __concepts
}  // namespace mamba::builtins

// IWYU pragma: private
