#pragma once

#include "mamba/concepts/entity.hpp"
#include "mamba/templates/utils.hpp"

namespace mamba::builtins::memory {

template <concepts::Entity T>
constexpr templates::Owned<T> own(T t) {
  if constexpr (concepts::Handle<T>) {
    return std::move(t);
  } else {
    return t;
  }
}

}  // namespace mamba::builtins::memory
