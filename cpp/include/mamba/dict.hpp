#pragma once

#include <unordered_map>

namespace mamba::builtins::types {

template <typename K, typename V>
using Dict = std::unordered_map<K, V>;

}  // namespace mamba::builtins::types
