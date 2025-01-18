#pragma once

#include <concepts>

#include "mamba/builtins/__meta/args.hpp"
#include "mamba/builtins/__types/size.hpp"

namespace mamba::builtins::details {

template <typename T>
concept Hashable = requires(const T t) {
  { Unwrap(t).__Hash__() } -> std::same_as<Size>;
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
