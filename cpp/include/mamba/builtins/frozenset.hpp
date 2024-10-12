#pragma once

#include <algorithm>
#include <concepts>
#include <initializer_list>
#include <memory>
#include <optional>
#include <sstream>
#include <unordered_set>
#include <utility>

#include "mamba/__concepts/entity.hpp"
#include "mamba/__memory/handle.hpp"
#include "mamba/__memory/managed.hpp"
#include "mamba/__memory/read_only.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/set.hpp'
#include "mamba/builtins/__types/str.hpp"
#include "mamba/builtins/as_str.hpp"
#include "mamba/builtins/error.hpp"
#include "mamba/builtins/iteration.hpp"
#include "mamba/builtins/repr.hpp"

namespace mamba::builtins {

template <__concepts::Entity T>
class FrozenSet final : public __types::SetBase<T, FrozenSet<T>> {
 private:
  using base = __types::SetBase<T>;

 public:
  /// @note Mamba-specific
  using element = T;

  using key_type = __memory::managed_t<element>;
  using value_type = key_type;
  using reference = value_type&;
  using const_reference = const value_type&;

  /// @note Mamba-specific
  using storage = std::unordered_set<value_type>;

  using iterator = storage::iterator;
  using const_iterator = storage::const_iterator;

  /// @note Mamba-specific
  using self = FrozenSet<element>;
  using handle = __memory::handle_t<self>;

  /// @brief Creates an empty frozen set.
  /// @code frozenset()
  FrozenSet() {}

  /// @brief Creates a frozen set from the elements in @p it. Value types
  /// are copied.
  /// @code frozenset(Iterable)
  template <typename It>
    requires __concepts::TypedIterable<It, element>
  explicit FrozenSet(It& iterable) : base(iterable) {}

  /// @brief Creates a frozen set with the provided variadic arguments.
  /// @code frozenset(...)
  template <typename... Args>
  FrozenSet(Args... rest) : base(std::forward<Args>(rest)...) {}

  /// @brief Creates a frozen set from an initializer list.
  FrozenSet(std::initializer_list<value_type> elements)
      : base(std::move(elements)) {}

  /// @brief Generic constructor forwarding arguments to actual constructor
  /// methods.
  /// @code FrozenSet.__init__()
  template <typename... Args>
  static handle Init(Args&&... args) {
    return __memory::Init<self>(std::forward<Args>(args)...);
  }

  /// @brief Returns the string representation of the frozen set.
  /// @code str(frozenset)
  __types::Str AsStr() const override { return AsStr("frozenset(", ")"); }

  /// @brief Returns the representation of the frozen set.
  /// @code repr(frozen set)
  __types::Str Repr() const override { return ReprImpl("frozenset(", ")"); }
};

}  // namespace mamba::builtins
