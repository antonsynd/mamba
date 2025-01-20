#pragma once

#include "mamba/builtins/__meta/value.hpp"
#include "mamba/builtins/__meta/wrapped.hpp"

namespace mamba::builtins::details {

template <typename T>
concept IsValid =
    IsValue<T> || (IsWrapped<T> && IsNotValue<typename T::element_type>);

template <typename T>
concept IsNotValid = !IsValid<T>;

}  // namespace mamba::builtins::details
