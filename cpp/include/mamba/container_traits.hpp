#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/concepts.hpp"

namespace mamba::builtins::container {

template <typename T>
using value_t = std::conditional_t<Value<T>, T, std::shared_ptr<T>>;

template <typename T>
using reference_t = value_t<T>&;

template <typename T>
using const_reference_t = const value_t<T>&;

}  // namespace mamba::builtins::container
