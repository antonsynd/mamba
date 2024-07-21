#pragma once
#include <type_traits>

#include "mamba/alpha/types.hpp"

namespace mamba {

namespace {

template <typename T>
using IntegerOrBoolean =
    std::enable_if_t<std::disjunction_v<std::is_same<T, bool>::value,
                                        std::is_same<T, int>::value>>;

}  // anonymous namespace

template <typename T = int, typename = IntegerOrBoolean<T>>
class Integer : internal::ValueType<T> {
 public:
  Integer(T v) : internal::ValueType<T>(v) {}
};

class Boolean final : public Integer<bool> {
 public:
  Boolean(bool b) : Integer<bool>(b) {}
};

}  // namespace mamba
