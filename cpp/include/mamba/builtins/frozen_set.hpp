#pragma once

#include "mamba/builtins/__types/abstract_set.hpp"

namespace mamba::builtins {

template <typename T>
class FrozenSet final : public details::AbstractSet<T> {};

}  // namespace mamba::builtins
