#pragma

#include <initializer_list>

namespace mamba::builtins::details {

template <typename T>
std::initializer_list<T> Lit(std::initializer_list<T>&& t) {
  return t;
}

}  // namespace mamba::builtins::details
