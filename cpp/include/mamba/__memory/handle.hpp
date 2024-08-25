#pragma once

#include <memory>
#include <type_traits>

#include "mamba/__concepts/object.hpp"

namespace mamba::builtins::__memory {

// Simple alias without constraints. Adding concepts::Object here makes it
// impossible to evaluate T because it is not a complete type at this point
template <typename T>
using handle_t = std::shared_ptr<T>;

template <typename T, typename U>
concept HandleOf = __concepts::Object<U> && requires {
  typename std::enable_if_t<std::is_same_v<T, handle_t<U>>>;
};

/// @brief Concept for handles of objects. Used as a disjunct with Value for
/// managed entities in variables, members, function arguments, and actual
/// container storage elements (but not the raw template element type itself).
/// @see managed.hpp
template <typename T>
concept Handle = HandleOf<T, typename T::element_type>;

/// @brief Instantiates an object of type @tparam T with @p args and returns
/// a handle to the object.
template <__concepts::Object T, typename... Args>
static handle_t<T> Init(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

}  // namespace mamba::builtins::__memory
