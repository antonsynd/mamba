#pragma once

#include <memory>

#include "mamba/traits.hpp"

namespace mamba::builtins::container {

template <typename T>
using value_t =
    std::conditional_t<traits::is_value_type_v<T>, T, std::shared_ptr<T>>;

template <typename T>
using reference_t = value_t<T>&;

template <typename T>
using const_reference_t = const value_t<T>&;

}  // namespace mamba::builtins::container
