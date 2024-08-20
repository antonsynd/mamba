#pragma once

#include <memory>
#include <type_traits>

#include "mamba/concepts/object.hpp"
#include "mamba/concepts/utils.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept Handle =
    HasElementType<T> && Object<typename T::element_type> && requires {
      typename std::enable_if_t<
          std::is_same_v<T, std::shared_ptr<typename T::element_type>>>;
    };

}  // namespace mamba::builtins::concepts
