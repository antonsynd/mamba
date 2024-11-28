#pragma once

#include "mamba/builtins/__operators/equality.hpp"      // IWYU pragma: export
#include "mamba/builtins/__operators/greater_than.hpp"  // IWYU pragma: export
#include "mamba/builtins/__operators/greater_than_or_equal.hpp"  // IWYU pragma: export
#include "mamba/builtins/__operators/identity.hpp"   // IWYU pragma: export
#include "mamba/builtins/__operators/init.hpp"       // IWYU pragma: export
#include "mamba/builtins/__operators/less_than.hpp"  // IWYU pragma: export
#include "mamba/builtins/__operators/less_than_or_equal.hpp"  // IWYU pragma: export

namespace mamba::builtins {

template <typename T, typename... Args>
using Init = mamba::builtins::__operators::Init<T, Args>;

template <typename T>
using Is = Is<T>;

}  // namespace mamba::builtins
