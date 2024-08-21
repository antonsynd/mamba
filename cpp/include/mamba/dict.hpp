#pragma once

#include <memory>
#include <optional>
#include <unordered_map>

#include "mamba/concepts/entity.hpp"
#include "mamba/error.hpp"
#include "mamba/list.hpp"
#include "mamba/types/int.hpp"

namespace mamba::builtins {

template <concepts::Entity K, concepts::Entity V>
class Dict : public std::enable_shared_from_this<Dict<K, V>> {
 public:
  using key_type = K;
  using mapped_type = V;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value&;

  /// @brief Creates an empty dict.
  /// @code `dict()`
  Dict() {}

  template <concepts::Mapping T>
  Dict(const Mapping& mapping) {}

  /// class dict(**kwargs)
  /// class dict(mapping, **kwargs)
  /// class dict(iterable, **kwargs)

  List<K> AsList() {}

  types::Int Len() const { return m_.size(); }

  mapped_type& operator[](const K& key) {
    auto it = m_.find(key);

    if (it == m_.end()) {
      // In this base class, it is expected to throw
      return Missing(key);
    }

    return it->second;
  }

  const mapped_type& operator[](const K& key) const {
    auto it = m_.find(key);

    if (it == m_.end()) {
      // In this base class, it is expected to throw
      return Missing(key);
    }

    return it->second;
  }

  // TODO: make generic access, if K is Handle, then const K&, else K
  virtual mapped_type Missing(const K& key) { throw ValueError(""); }

  void DeleteKey(const K& key) {
    auto it = m_.find(key);

    if (it == m_.end()) {
      // In this base class, it is expected to throw
      return Missing(key);
    }
  }

  types::Bool In(K key) const {}

  // Iter()

  void Clear() { m_.clear(); }

  /// @brief Creates a shallow copy of the dict.
  /// @code dict.copy()
  memory::Handle<Dict<K, V>> Copy() const {
    return memory::Init<Dict<K, V>>(*this);
  }

  // static FromKeys();

  // Get(key, default)

  // Items()

  // Pop()

  // PopItem()

  // Reversed()

  // SetDefault(key, default)

  // Update(other)

  // Values()

  // operator|(other)
  // operator|=(other)

 private:
  std::unordered_map<K, V> m_;
};

namespace details {

class DictionaryView {};

}  // namespace details

}  // namespace mamba::builtins
