#pragma once
#include <type_traits>

namespace mamba::internal {

enum class GetValueReturnType { kValue, kReference };

template <GetValueReturnType T>
constexpr bool get_value_return_type_is_value_type =
    T == GetValueReturnType::kValue;

template <typename T, GetValueReturnType G = GetValueReturnType::kValue>
class ValueType {
 public:
  using value_t = T;
  using get_value_return_type_v = G;
  using get_value_t = std::
      conditional_t<get_value_return_type_is_value_type<G>, const T, const T&>;

  ValueType(T&& v) : v_(std::forward(v)) {}

  get_value_t GetValue() const { return static_cast<T>(v_); }

  void SetValue(T&& v) { v_ = std::forward(v); }

 private:
  T v_;
};

}  // namespace mamba::internal
