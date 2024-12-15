#pragma once

#include <string_view>

#include "mamba/builtins/__concepts/hashable.hpp"
#include "mamba/builtins/__types/traits.hpp"
#include "mamba/collections/abc/abstract_set.hpp"

namespace mamba {
namespace collections::abc {

template <builtins::details::Hashable T>
class MutableSet : public AbstractSet<T> {};

}  // namespace collections::abc

namespace builtins::details {
template <typename T>
struct Traits<collections::abc::MutableSet<T>> {
  static constexpr std::string_view kName = "MutableSet";
};

}  // namespace builtins::details
}  // namespace mamba
