#pragma once

#include <string>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__types/traits.hpp"

namespace mamba::__utils {

template <typename T>
std::string type_name() {
  if constexpr (builtins::details::Value<T>) {
    return builtins::details::Traits<T>::kName;
  } else {
    return T::__Name__();
  }
}

}  // namespace mamba::__utils
