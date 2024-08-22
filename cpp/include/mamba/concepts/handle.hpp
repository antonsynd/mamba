#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/concepts/object.hpp"
#include "mamba/concepts/utils.hpp"
#include "mamba/types/bool.hpp"

namespace mamba::builtins::concepts {

/// @brief Concept for handles of objects. Used as a disjunct with Value
/// types to form the Entity concept.
template <typename T>
concept Handle =
    HasElementType<T> && Object<typename T::element_type> && requires {
      typename std::enable_if_t<
          std::is_same_v<T, std::shared_ptr<typename T::element_type>>>;
    };

template <typename T>
concept EquatableHandle = Handle<T> && requires(const T t) {
  { t->Eq(*t) } -> std::same_as<types::Bool>;
};

template <typename T>
concept GreaterThanComparableHandle = Handle<T> && requires(const T t) {
  { t->Gt(*t) } -> std::same_as<types::Bool>;
};

template <typename T>
concept LessThanComparableHandle = Handle<T> && requires(const T t) {
  { t->Lt(*t) } -> std::same_as<types::Bool>;
};

}  // namespace mamba::builtins::concepts
