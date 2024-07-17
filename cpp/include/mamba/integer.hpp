#pragma once
#include <type_traits>

namespace mamba {

namespace {
template <typename T>
using IntegerOrBoolean = std::disjunction_t<std::is_same<T, bool>::value,
                                            std::is_same<T, int>::value>;
}  // anonymous namespace

template <typename T = int, typename = IntegerOrBoolean<T>>
class Integer {
 public:
  Integer(T v) : v_(v) {}

  T GetValue() const { return static_cast<T>(v_); }
  void SetValue(T v) { v_ = v; }

 private:
  T v_;
};

class Boolean final : public Integer<bool> {
 public:
  Boolean(bool b) : Integer<bool>(b) {}
};

}  // namespace mamba
