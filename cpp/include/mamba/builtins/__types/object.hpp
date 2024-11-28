#pragma once

#include <type_traits>

#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {
namespace __types {

namespace details {

class ObjectBase {
 public:
  virtual ~ObjectBase() = default;

  virtual Str __Repr__() const = 0;
};

}  // namespace details

template <typename T>
class Object : public details::ObjectBase,
               public std::enable_shared_from_this<T> {};

}  // namespace __types

namespace __concepts {

template <typename T>
concept IsObject = std::is_base_of_v<__types::Object<T>, T>;

}  // namespace __concepts
}  // namespace mamba::builtins

// IWYU pragma: private
