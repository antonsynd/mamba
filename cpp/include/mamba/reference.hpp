#pragma once

#include <type_traits>

#include "mamba/handle.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept Reference = requires {
  typename std::enable_if_t<
      std::is_same_v<T, memory::Handle<typename T::element_type>>>;
};

}  // namespace mamba::builtins::concepts
