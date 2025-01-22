#pragma once

#include <string_view>

#include "mamba/builtins/__meta/hashable.hpp"
#include "mamba/builtins/__types/traits.hpp"
#include "mamba/collections/abc/set.hpp"

namespace mamba {
namespace collections::abc {

template <builtins::details::Hashable T>
class MutableSet : public Set<T> {
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

  // Use the same constructors
  using AbstractSet::AbstractSet;

  // Bring in the mutation methods
  using AbstractSet::Add;

  /// @brief Removes @p elem from the set. If the set is empty or
  /// @p elem does not occur in the set, throws KeyError.
  /// @code set.remove(elem)
  void Remove(__meta::ReadOnly<element> elem) {
    auto it_opt = TryFind(elem);

    if (!it_opt) {
      throw KeyError("Set.Remove(x): x not in set");
    }

    s_.erase(*it_opt);
  }

  /// @brief Removes @p elem from the set. If the set is empty or
  /// @p elem does not occur in the set, does nothing.
  /// @code set.remove(elem)
  void Discard(__meta::ReadOnly<element> elem) {
    auto it_opt = TryFind(elem);

    if (it_opt) {
      s_.erase(*it_opt);
    }
  }

  /// @brief Removes an arbitrary element and returns it. If the set is empty,
  /// then throws KeyError.
  /// @code set.pop()
  value_type Pop() {
    if (s_.empty()) {
      throw KeyError("pop from an empty set");
    }

    auto it = s_.begin();
    // Copy, but it's okay, it's either a shared pointer or a raw value
    auto elem = *it;

    s_.erase(it);

    return elem;
  }

  void Update(void other) {}
  self& operator|=(void other) {
    Update(other);
    return *this;
  }

  void IntersectionUpdate(void other) {}
  self& operator&=(void other) {
    IntersectionUpdate(other);
    return *this;
  }

  void DifferenceUpdate(void other) {}
  self& operator-=(void other) {
    DifferenceUpdate(other);
    return *this;
  }

  void SymmetricDifferenceUpdate(void other) {}
  self& operator^=(void other) {
    SymmetricDifferenceUpdate(other);
    return *this;
  }
};

}  // namespace collections::abc

namespace builtins::details {
template <typename T>
struct Traits<collections::abc::MutableSet<T>> {
  static constexpr std::string_view kName = "MutableSet";
};

}  // namespace builtins::details
}  // namespace mamba
