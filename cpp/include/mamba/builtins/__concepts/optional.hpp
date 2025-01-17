#pragma once

#include <concepts>
#include <optional>
#include <type_traits>

namespace mamba::builtins::details {

template <typename T>
concept Optional = requires {
  typename T::value_type;
} && std::is_same_v<std::decay_t<T>, std::optional<typename T::value_type>>;

}  // namespace mamba::builtins::details
