#pragma once

#include <initializer_list>
#include <memory>
#include <optional>
#include <unordered_map>

#include "mamba/__concepts/entity.hpp"
#include "mamba/__memory/handle.hpp"
#include "mamba/__memory/managed.hpp"
#include "mamba/__memory/read_only.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/error.hpp"
#include "mamba/builtins/list.hpp"

namespace mamba::builtins {

template <__concepts::Entity K, __concepts::Entity V>
class Dict : public std::enable_shared_from_this<Dict<K, V>> {
 public:
  /// @note Mamba-specific
  using key_element = K;
  using mapped_element = V;

  using key_type = __memory::managed_t<key_element>;
  using mapped_type = __memory::managed_t<mapped_element>;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;

  /// @note Mamba-specific
  using storage = std::unordered_map<key_type, mapped_type>;

  using iterator = storage::iterator;
  using const_iterator = storage::const_iterator;

  /// @note Mamba-specific
  using self = Dict<key_element, mapped_element>;
  using handle = __memory::handle_t<self>;

  /// @brief Creates an empty dict.
  /// @code dict()
  Dict() {}

  Dict(std::initializer_list<std::pair<key_type, mapped_type>>) {};

  // template <concepts::Mapping T>
  // Dict(const Mapping& mapping) {}

  /// class dict(**kwargs)
  /// class dict(mapping, **kwargs)
  /// class dict(iterable, **kwargs)

  /// @brief Generic constructor forwarding arguments to actual constructor
  /// methods.
  /// @code Dict.__init__()
  template <typename... Args>
  static handle Init(Args&&... args) {
    return __memory::Init<self>(std::forward<Args>(args)...);
  }

  __memory::handle_t<List<key_element>> AsList() {
    auto l = __memory::Init<List<key_element>>();

    for (const auto it : m_) {
      l.Append(it->first);
    }

    return l;
  }

  __types::Int Len() const { return m_.size(); }

  mapped_type& operator[](__memory::ReadOnly<key_element> key) {
    auto it = m_.find(key);

    if (it == m_.end()) {
      // In this base class, it is expected to throw
      return Missing(key);
    }

    return it->second;
  }

  const mapped_type& operator[](__memory::ReadOnly<key_element> key) const {
    auto it = m_.find(key);

    if (it == m_.end()) {
      // In this base class, it is expected to throw
      return Missing(key);
    }

    return it->second;
  }

  virtual mapped_type Missing(__memory::ReadOnly<key_element> key) {
    throw ValueError("");
  }

  void DeleteKey(__memory::ReadOnly<key_element> key) {
    auto it = m_.find(key);

    if (it == m_.end()) {
      // In this base class, it is expected to throw
      return Missing(key);
    }
  }

  __types::Bool Contains(__memory::ReadOnly<key_element> key) const {
    return m_.contains(key);
  }

  // Iter()

  /// @brief Clears the elements of the dict.
  /// @code dict.clear()
  void Clear() { m_.clear(); }

  /// @brief Creates a shallow copy of the dict.
  /// @code dict.copy()
  handle Copy() const { return Init(*this); }

  // static FromKeys();

  mapped_type Get(__memory::ReadOnly<key_element> key,
                  mapped_type default_value) {
    auto it = m_.find(key);

    if (it == m_.end()) {
      return default_value;
    }

    return it->second;
  }

  // Items()

  // Pop()

  // PopItem()

  // Reversed()

  // SetDefault(key, default)

  void Update(const self& other) {
    //
  }

  // Values()

  handle operator|(const self& other) const {
    auto res = Init(*this);
    res.Update(other);
    return res;
  }

  void operator|=(const self& other) { Update(other); }

  /// @brief Returns the string representation of the dict.
  /// @code str(dict)
  __types::Str AsStr() const {
    std::ostringstream oss;

    oss << "{";

    if (!m_.empty()) {
      const auto last = m_.size() - 1;
      auto it = m_.begin();

      for (size_t i = 0; i < last; ++i, ++it) {
        oss << builtins::AsStr(it->first) << ": " << builtins::AsStr(it->second)
            << ", ";
      }

      oss << builtins::AsStr(it->first) << ": " << builtins::AsStr(it->second);
    }

    oss << "}";

    return oss.str();
  }

  /// @brief Returns the representation of the dict.
  /// @code repr(dict)
  __types::Str Repr() const {
    std::ostringstream oss;

    oss << "{";

    if (!m_.empty()) {
      const auto last = m_.size() - 1;
      auto it = m_.begin();

      for (size_t i = 0; i < last; ++i, ++it) {
        oss << builtins::AsStr(it->first) << ": " << builtins::AsStr(it->second)
            << ", ";
      }

      oss << builtins::AsStr(it->first) << ": " << builtins::AsStr(it->second);
    }

    oss << "}";

    return oss.str();
  }

 private:
  storage m_;
};

namespace details {

class DictionaryView {};

}  // namespace details

}  // namespace mamba::builtins
