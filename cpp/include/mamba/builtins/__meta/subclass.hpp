#pragma once

#include <concepts>
#include <type_traits>

namespace mamba::builtins::details {

template <typename Derived, typename Base>
concept SubclassOf =
    std::same_as<Derived, Base> || std::is_base_of_v<Base, Derived>;

}  // namespace mamba::builtins::details

// IWYU pragma: private
