#pragma once

#include <concepts>
#include <type_traits>

namespace mamba::builtins::details {

template <typename T, typename U>
concept SubclassOf = std::same_as<T, U> || std::is_base_of_v<T, U>;

}  // namespace mamba::builtins::details

// IWYU pragma: private
