#include <gtest/gtest.h>

#include "mamba/int.hpp"
#include "mamba/list.hpp"

namespace mamba::builtins::test {

TEST(List, EmptyConstructor) {
  // If/when/then
  List<Int> l;
}

}  // namespace mamba::builtins::test
