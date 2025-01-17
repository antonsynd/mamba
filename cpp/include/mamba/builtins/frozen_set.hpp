#pragma once

#include "mamba/collections/abc/abstract_set.hpp"

namespace mamba::builtins {

template <typename T>
class FrozenSet final : public details::AbstractSet<T> {};

}  // namespace mamba::builtins
