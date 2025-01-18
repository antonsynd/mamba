#pragma once

#include <algorithm>
#include <concepts>
#include <initializer_list>
#include <memory>
#include <optional>
#include <sstream>
#include <unordered_set>
#include <utility>

#include "mamba/builtins/__meta/hashable.hpp"
#include "mamba/collections/abc/mutable_set.hpp"

namespace mamba::builtins {

template <details::Hashable T>
class Set final : public details::MutableSet<T> {
 public:
  using value_type = T;

  /// @note Mamba-specific
  using self = AbstractSet<value_type>;
  using storage = std::unordered_set<value_type>;

  using key_type = value_type;
  using reference = value_type&;
  using const_reference = const value_type&;

  using iterator = storage::iterator;
  using const_iterator = storage::const_iterator;

  // Use constructors from base class
  using collections::abc::MutableSet::MutableSet;

  /// @brief Generic constructor forwarding arguments to actual constructor
  /// methods.
  /// @code Set.__init__()
  template <typename... Args>
  static self __Init__(Args&&... args) {
    return self(std::forward<Args>(args)...);
  }
};

namespace details {

template <typename T>
struct Traits<Set<T>> {
  static constexpr std::string_view kName = "Set";
};

}  // namespace details
}  // namespace mamba::builtins
