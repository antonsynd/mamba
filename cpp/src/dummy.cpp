#include <iostream>

namespace mamba::builtins {

constexpr auto kDummy = 0;

void foobar(int i) {
  std::cout << i << std::endl;
}

}  // namespace mamba::builtins
