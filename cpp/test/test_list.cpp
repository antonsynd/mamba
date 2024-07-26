#include <gtest/gtest.h>

#include "mamba/int.hpp"
#include "mamba/list.hpp"

namespace mamba::builtins::test {

TEST(List, EmptyConstructor) {
  // If/when
  List<Int> l;

  // Then
  EXPECT_EQ(Len(l), 0);
}

}  // namespace mamba::builtins::test
